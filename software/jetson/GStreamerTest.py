import os
import threading
import subprocess
import shlex
import time
import signal

# ===================== 配置项 =====================
VIDEO_DEVICE   = "/dev/video0"
VIDEO_W        = 1280
VIDEO_H        = 480
VIDEO_FPS      = 30
VIDEO_BITRATE  = 4_000_000     # 比特/秒
PC_VIDEO_PORT  = 5600          # 目标接收端口 (e.g., QGroundControl)
RTP_PT         = 96            # H.264 常用 96

# 相机模式
CAMERA_MODE    = 'mjpeg'

# Jetson NX 特有配置
FORCE_TARGET_IP = "192.168.0.1" # <-- **请修改为你的 PC/地面站 IP**
USE_NVENC       = True            # 优先使用 Jetson 硬件编码器 (nvv4l2h264enc)
VERBOSE_GST_LOG = True            # 打印 GStreamer 日志

# ===================== GStreamer 推流控制 =====================

def build_gst_cmd(target_ip: str) -> list:
    """
    生成适用于 Jetson NX 硬件加速的 GStreamer 推流命令。

    使用：
    1. V4L2 源 (v4l2src) 读取摄像头 RAW 数据 (NV12/YUYV)。
    2. NVIDIA 硬件编码器 (nvv4l2h264enc) 进行 H.264 编码。
    3. RTP 封装 (rtph264pay) 并通过 UDP 发送。
    """
    if not target_ip:
        raise ValueError("Target IP must be set.")

    # 1. 捕获源 (v4l2src)
    # 对于 Jetson，通常可以高效地直接读取 /dev/video* 的原始格式
    if CAMERA_MODE == 'raw':
        # 常见 RAW 格式：video/x-raw, format=NV12 或 YUY2
        # 我们使用 auto-detect (video/x-raw) 并设置分辨率/帧率
        source_pipeline = (
            f"v4l2src device={VIDEO_DEVICE} !"
            f" video/x-raw, width={VIDEO_W}, height={VIDEO_H}, framerate={VIDEO_FPS}/1 !"
            " nvvidconv ! video/x-raw(memory:NVMM), format=NV12 !"
        )
    elif CAMERA_MODE == 'mjpeg':
        # jpegdec 为软件解码；下面的 H.264 编码可使用 NVENC。
        source_pipeline = (
            f"v4l2src device={VIDEO_DEVICE} !"
            f" image/jpeg, width={VIDEO_W}, height={VIDEO_H}, framerate={VIDEO_FPS}/1 !"
            " jpegdec ! video/x-raw !"
            " nvvidconv ! video/x-raw(memory:NVMM), format=NV12 !" # 转换为 NVMM 内存
        )
    else:
        raise ValueError(f"Unsupported CAMERA_MODE: {CAMERA_MODE}")

    if not USE_NVENC:
        # Orin Nano 无 NVENC；CPU 编码路径保持系统内存，不传入 NVMM。
        source_pipeline = source_pipeline.replace(
            " nvvidconv ! video/x-raw(memory:NVMM), format=NV12 !", ""
        )

    # 2. 编码器 (nvv4l2h264enc)
    if USE_NVENC:
        # 保留原实装参数：4 Mbit/s，30 fps 时 GOP=15。
        encoder_pipeline = (
            " nvv4l2h264enc "
            " control-rate=1 bitrate={bitrate} "
            " preset-level=3 " # 3=Medium
            " iframeinterval={gop} ! "
            " h264parse ! "
        ).format(bitrate=VIDEO_BITRATE, gop=int(VIDEO_FPS / 2)) # 例如 GOP=15
    else:
        # 回退到 CPU 编码 (x264enc)
        encoder_pipeline = (
            " videoconvert ! video/x-raw,format=I420 ! x264enc tune=zerolatency speed-preset=ultrafast "
            " bitrate={bitrate} key-int-max={gop} ! "
            " h264parse ! "
        ).format(bitrate=int(VIDEO_BITRATE / 1000), gop=int(VIDEO_FPS / 2)) # x264enc bitrate 是 kbps

    # 3. 封装和发送 (rtph264pay -> udpsink)
    sink_pipeline = (
        f" rtph264pay config-interval=1 pt={RTP_PT} !"
        f" udpsink host={target_ip} port={PC_VIDEO_PORT}"
    )

    full_cmd = f"gst-launch-1.0 -e {source_pipeline} {encoder_pipeline} {sink_pipeline}"

    # 将命令字符串转换为 shlex 列表格式
    return shlex.split(full_cmd)

class VideoStreamer:
    def __init__(self, target_ip: str):
        self.target_ip = target_ip
        self.video_proc = None
        self.running = threading.Event()
        self.cmd = build_gst_cmd(target_ip)

    def start(self):
        print(f"尝试向 {self.target_ip}:{PC_VIDEO_PORT} 推流...")
        print(f"GStreamer Command: {' '.join(self.cmd)}")

        # 设置 GStreamer 日志级别
        env = os.environ.copy()
        if VERBOSE_GST_LOG:
            # env['GST_DEBUG'] = '3' # Level 3 (WARN)
            env['GST_DEBUG'] = '4' # Level 4 (INFO) - 推荐排查时使用
        else:
            env['GST_DEBUG'] = '1' # Level 1 (ERROR)

        try:
            self.video_proc = subprocess.Popen(
                self.cmd,
                env=env,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                start_new_session=True # 只向本程序创建的 GStreamer 进程组发送信号
            )
            self.running.set()

            # 启动一个线程来打印 GStreamer 输出
            threading.Thread(target=self._log_output, daemon=True).start()

        except FileNotFoundError:
            print("错误：gst-launch-1.0 未找到。请确保 GStreamer 已安装。")
        except Exception as e:
            print(f"启动 GStreamer 进程失败: {e}")

    def _log_output(self):
        """实时打印 GStreamer 进程的 stdout/stderr"""
        if not self.video_proc: return
        for line in self.video_proc.stdout:
            print(f"[GST] {line.decode('utf-8', errors='replace').strip()}")
        print("[GST] GStreamer 进程退出。")
        self.running.clear()

    def stop(self):
        if self.video_proc:
            print("停止 GStreamer 推流...")
            try:
                # 向进程组发送 SIGTERM，优雅地停止 GStreamer
                os.killpg(os.getpgid(self.video_proc.pid), signal.SIGTERM)
                self.video_proc.wait(timeout=5)
            except ProcessLookupError:
                self.video_proc.wait()
            except subprocess.TimeoutExpired:
                print("GStreamer 进程未能在 5s 内终止，强制杀死。")
                try:
                    os.killpg(self.video_proc.pid, signal.SIGKILL)
                except ProcessLookupError:
                    pass
                self.video_proc.wait()
            self.video_proc = None
        self.running.clear()

    def is_running(self):
        return self.running.is_set() and self.video_proc and self.video_proc.poll() is None

def handle_shutdown(signum, frame):
    raise KeyboardInterrupt


if __name__ == "__main__":
    signal.signal(signal.SIGTERM, handle_shutdown)
    exit_code = 1
    if not FORCE_TARGET_IP:
        print("请在脚本头部设置 FORCE_TARGET_IP 为目标 PC/地面站的 IP 地址！")
    else:
        streamer = VideoStreamer(FORCE_TARGET_IP)
        streamer.start()

        try:
            # 保持主线程运行，直到接收到中断信号 (Ctrl+C)
            while streamer.is_running():
                time.sleep(1)
        except KeyboardInterrupt:
            exit_code = 0
            print("\n接收到 Ctrl+C 信号...")
        finally:
            streamer.stop()
            print("程序退出。")
    raise SystemExit(exit_code)
