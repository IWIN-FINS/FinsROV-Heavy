# 自启服务streamer.service
# 自启脚本StreamerStart.sh

import signal
import socket
import struct
import time
import serial
import serial.tools.list_ports
import threading

# 手柄数据结构体
class JoystickState:
    def __init__(self):
        self.axes = [0.0] * 6
        self.buttons = [0] * 15
        self.hat = (0, 0)

    def from_bytes(self, data):
        fmt = '<6f15B2b'  # 6个float, 15个unsigned char, 2个signed char
        unpacked = struct.unpack(fmt, data)

        self.axes = list(unpacked[:6])
        self.buttons = list(unpacked[6:21])  # 第6-20个是按钮
        self.hat = (unpacked[21], unpacked[22])  # 最后2个是hat

    def __str__(self):
        axes_str = ', '.join([f'{a:.3f}' for a in self.axes])
        buttons_str = ', '.join([str(b) for b in self.buttons])
        hat_str = f'({self.hat[0]}, {self.hat[1]})'
        return f"Axes: [{axes_str}], Buttons: [{buttons_str}], Hat: {hat_str}"

def crc16_modbus(data):
    crc = 0xFFFF
    for byte in data:
        crc ^= byte
        for _ in range(8):
            if crc & 0x0001:
                crc = (crc >> 1) ^ 0xA001
            else:
                crc = crc >> 1
    return crc

def normalize_value(value, min_val=-1.0, max_val=1.0):
    """将值归一化到0-1范围"""
    return max(0.0, min(1.0, (value - min_val) / (max_val - min_val)))

# 配置参数
UDP_RECEIVE_PORT = 12345        # 监听手柄数据的UDP端口
UDP_SEND_PORT = 54321           # 发送下位机数据的UDP端口
UDP_SEND_IP = '192.168.0.1'       # 发送目标IP
SERIAL_PORT = '/dev/ttyTHS1'    # 串口设备
BAUDRATE = 115200               # 波特率

# 初始化串口
try:
    ser = serial.Serial(
        port=SERIAL_PORT,
        baudrate=BAUDRATE,
        bytesize=serial.EIGHTBITS,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        timeout=0.1,  # 设置超时以便能够响应线程退出
        xonxoff=False,
        rtscts=False,
        dsrdtr=False
    )
    print(f"串口 {SERIAL_PORT} 已打开，波特率 {BAUDRATE}")
except Exception as e:
    print(f"无法打开串口 {SERIAL_PORT}: {e}")
    raise SystemExit(1)

# 创建UDP socket
udp_receive_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
udp_receive_sock.settimeout(0.1)

udp_send_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# 全局变量
state = JoystickState()
packet_count = 0
serial_send_count = 0
serial_receive_count = 0
udp_send_count = 0
start_time = time.time()
running = True

def forward_to_serial(state):
    """将处理后的手柄数据通过串口转发"""
    global serial_send_count
    if ser and ser.is_open:
        try:
            # 提取所需数据并处理
            yaw_rate = -state.axes[0]  # 偏航角角速度
            forward_speed = -state.axes[3]  # 前后速度
            left_right_speed = -state.axes[2]  # 左右速度
            down_speed = normalize_value(state.axes[4])  # 下降速度，归一化到0-1
            up_speed = normalize_value(state.axes[5])  # 上升速度，归一化到0-1
            start_button = state.buttons[6]  # 启动键
            cam_fill_light = state.buttons[0] # 补光灯
            frame_fill_light = state.buttons[1]
            # arm_left = state.buttons[4]  # 左肩键左移
            # arm_right = state.buttons[5] # 右肩键右移
            cam_yaw = state.hat[0] #云台
            cam_pitch = state.hat[1]


            # 打包数据
            # data = struct.pack('5f5B2b',
            #                   yaw_rate,
            #                   forward_speed,
            #                   left_right_speed,
            #                   down_speed,
            #                   up_speed,
            #                   start_button,
            #                   cam_fill_light,
            #                   frame_fill_light,
            #                   arm_left,         # 新增两个按键
            #                   arm_right,
            #                   cam_yaw,
            #                   cam_pitch)

            data = struct.pack('<5f3B2b',
                    yaw_rate,
                    forward_speed,
                    left_right_speed,
                    down_speed,
                    up_speed,
                    start_button,
                    cam_fill_light,
                    frame_fill_light,
                    cam_yaw,
                    cam_pitch)

            # 构建数据帧：帧头(0xAA) + 数据 + CRC16-MODBUS(2字节)
            frame_header = b'\xAA'

            # 计算CRC16-MODBUS校验（包括帧头和数据）
            crc_data = frame_header + data
            crc = crc16_modbus(crc_data)
            crc_bytes = struct.pack('<H', crc)  # 小端序

            # 完整帧
            frame = frame_header + data + crc_bytes
            ser.write(frame)
            serial_send_count += 1
            return True, data
        except Exception as e:
            print(f"串口发送错误: {e}")
            return False, None
    return False, None

def serial_receive_thread():
    """串口接收线程"""
    global serial_receive_count, udp_send_count, running

    # buffer = bytearray()
    while running:
        if ser and ser.is_open:
            try:
                # 读取串口数据
                data = ser.read(ser.in_waiting or 1)
                if data:
                    serial_receive_count += 1
                    # buffer.extend(data)
                    # frame = bytes(buffer)

                    # 通过UDP转发
                    try:
                        udp_send_sock.sendto(data, (UDP_SEND_IP, UDP_SEND_PORT))
                        udp_send_count += 1

                        # 每50个包打印一次接收信息
                        if serial_receive_count % 50 == 1:
                            print(f"\n第 {serial_receive_count} 个串口接收数据块信息:")
                            # print(upload_data)
                            print(f"UDP转发到 {UDP_SEND_IP}:{UDP_SEND_PORT}")

                    except Exception as e:
                        print(f"UDP发送错误: {e}")

            except Exception as e:
                print(f"串口接收错误: {e}")
                time.sleep(0.1)
        else:
            time.sleep(0.1)

def print_frame_info(data, crc_value, state):
    yaw_rate, forward_speed, left_right_speed, down_speed, up_speed, start_button, cam_fill_light, frame_fill_light, cam_yaw, cam_pitch = struct.unpack('<5f3B2b', data)
    # (yaw_rate, forward_speed, left_right_speed, down_speed, up_speed, start_button, cam_fill_light,
    #  frame_fill_light, arm_left, arm_right, cam_yaw, cam_pitch) = struct.unpack('5f5B2b', data)
    print(f"帧头: 0xAA")
    print(f"数据长度: {len(data)} 字节")
    print(f"偏航角速度: {yaw_rate:.3f}")
    print(f"前后速度: {forward_speed:.3f}")
    print(f"左右速度: {left_right_speed:.3f}")
    print(f"下降速度(归一化): {down_speed:.3f}")
    print(f"上升速度(归一化): {up_speed:.3f}")
    print(f"启动键: {start_button}")
    print(f"相机补光灯: {cam_fill_light}")
    print(f"框架补光灯: {frame_fill_light}")
    # print(f"机械臂左移: {arm_left}")
    # print(f"机械臂右移: {arm_right}")
    print(f"云台YAW: {cam_yaw}")
    print(f"云台PITCH: {cam_pitch}")
    print(f"CRC16-MODBUS: 0x{crc_value:04X}")
    print(f"完整帧: 0xAA + {len(data)}字节数据 + 0x{crc_value:04X}")

def handle_shutdown(signum, frame):
    raise KeyboardInterrupt

signal.signal(signal.SIGTERM, handle_shutdown)

# 启动串口接收线程
receive_thread = threading.Thread(target=serial_receive_thread, daemon=True)
receive_thread.start()

try:
    # 绑定到所有接口的指定端口
    udp_receive_sock.bind(('', UDP_RECEIVE_PORT))
    print(f"开始监听UDP端口 {UDP_RECEIVE_PORT} (手柄数据)")
    print(f"UDP转发目标: {UDP_SEND_IP}:{UDP_SEND_PORT} (下位机数据)")

    while running:
        try:
            # 接收手柄数据
            data, addr = udp_receive_sock.recvfrom(1024)

            # 解析手柄数据
            if len(data) == 41:
                state.from_bytes(data)
                packet_count += 1

                # 转发到串口
                success, serial_data = forward_to_serial(state)
                if success:
                    # 每50个包打印一次帧信息用于调试
                    if serial_send_count % 50 == 1:
                        crc_data = b'\xAA' + serial_data
                        crc_value = crc16_modbus(crc_data)
                        print(f"\n第 {serial_send_count} 个串口发送帧信息:")
                        print_frame_info(serial_data, crc_value, state)

                # if packet_count % 50 == 0:
                #     elapsed = max(time.time() - start_time, 1e-9)
                #     print(f"\n[{elapsed:.1f}s] 统计信息:")
                #     print(f"UDP接收(手柄): {packet_count} 包")
                #     print(f"串口发送(控制): {serial_send_count} 包")
                #     print(f"串口接收(状态): {serial_receive_count} 包")
                #     print(f"UDP发送(状态): {udp_send_count} 包")
                #     print(f"UDP接收速率: {packet_count/elapsed:.1f} Hz")
                #     print(f"串口发送速率: {serial_send_count/elapsed:.1f} Hz")
                #     print(f"串口接收速率: {serial_receive_count/elapsed:.1f} Hz")
                #     print(f"UDP发送速率: {udp_send_count/elapsed:.1f} Hz")

        except socket.timeout:
            # 超时继续循环，允许检查其他条件
            continue

except KeyboardInterrupt:
    print("\n接收到中断信号，正在退出...")
    running = False

finally:
    # 设置运行标志为False并等待线程结束
    running = False
    receive_thread.join(timeout=1.0)

    # 关闭连接
    udp_receive_sock.close()
    udp_send_sock.close()
    if ser and ser.is_open:
        ser.close()
        print("串口已关闭")

    elapsed = max(time.time() - start_time, 1e-9)
    print(f"\n最终统计信息:")
    print(f"UDP接收(手柄): {packet_count} 个数据包")
    print(f"串口发送(控制): {serial_send_count} 个数据包")
    print(f"串口接收(状态): {serial_receive_count} 个数据包")
    print(f"UDP发送(状态): {udp_send_count} 个数据包")
    print(f"运行时间: {elapsed:.2f} 秒")
    print(f"UDP接收平均速率: {packet_count/elapsed:.1f} Hz")
    print(f"串口发送平均速率: {serial_send_count/elapsed:.1f} Hz")
    print(f"串口接收平均速率: {serial_receive_count/elapsed:.1f} Hz")
    print(f"UDP发送平均速率: {udp_send_count/elapsed:.1f} Hz")
    print("程序退出")
