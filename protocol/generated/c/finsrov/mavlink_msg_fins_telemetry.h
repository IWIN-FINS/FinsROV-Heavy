#pragma once
// MESSAGE FINS_TELEMETRY PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_FINS_TELEMETRY 60007


typedef struct __mavlink_fins_telemetry_t {
 uint64_t session; /*<  NX session.*/
 uint64_t source_us; /*< [us] NX capture time.*/
 uint32_t valid_mask; /*<  Bits 0 voltage, 1 pressure, 2 rpm, 3 IMU, 4 network prediction.*/
 float voltage; /*< [V] Battery voltage.*/
 float pressure[4]; /*< [Pa] Four absolute pressure measurements.*/
 float rpm[8]; /*< [rpm] Eight signed motor speeds.*/
 float accel[3]; /*< [m/s/s] FLU accelerometer.*/
 float gyro[3]; /*< [rad/s] FLU angular rates.*/
 float network[3]; /*<  Body vx, body vy in m/s, yaw rate in rad/s.*/
} mavlink_fins_telemetry_t;

#define MAVLINK_MSG_ID_FINS_TELEMETRY_LEN 108
#define MAVLINK_MSG_ID_FINS_TELEMETRY_MIN_LEN 108
#define MAVLINK_MSG_ID_60007_LEN 108
#define MAVLINK_MSG_ID_60007_MIN_LEN 108

#define MAVLINK_MSG_ID_FINS_TELEMETRY_CRC 10
#define MAVLINK_MSG_ID_60007_CRC 10

#define MAVLINK_MSG_FINS_TELEMETRY_FIELD_PRESSURE_LEN 4
#define MAVLINK_MSG_FINS_TELEMETRY_FIELD_RPM_LEN 8
#define MAVLINK_MSG_FINS_TELEMETRY_FIELD_ACCEL_LEN 3
#define MAVLINK_MSG_FINS_TELEMETRY_FIELD_GYRO_LEN 3
#define MAVLINK_MSG_FINS_TELEMETRY_FIELD_NETWORK_LEN 3

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_FINS_TELEMETRY { \
    60007, \
    "FINS_TELEMETRY", \
    9, \
    {  { "session", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_fins_telemetry_t, session) }, \
         { "source_us", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_fins_telemetry_t, source_us) }, \
         { "valid_mask", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_fins_telemetry_t, valid_mask) }, \
         { "voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_fins_telemetry_t, voltage) }, \
         { "pressure", NULL, MAVLINK_TYPE_FLOAT, 4, 24, offsetof(mavlink_fins_telemetry_t, pressure) }, \
         { "rpm", NULL, MAVLINK_TYPE_FLOAT, 8, 40, offsetof(mavlink_fins_telemetry_t, rpm) }, \
         { "accel", NULL, MAVLINK_TYPE_FLOAT, 3, 72, offsetof(mavlink_fins_telemetry_t, accel) }, \
         { "gyro", NULL, MAVLINK_TYPE_FLOAT, 3, 84, offsetof(mavlink_fins_telemetry_t, gyro) }, \
         { "network", NULL, MAVLINK_TYPE_FLOAT, 3, 96, offsetof(mavlink_fins_telemetry_t, network) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_FINS_TELEMETRY { \
    "FINS_TELEMETRY", \
    9, \
    {  { "session", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_fins_telemetry_t, session) }, \
         { "source_us", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_fins_telemetry_t, source_us) }, \
         { "valid_mask", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_fins_telemetry_t, valid_mask) }, \
         { "voltage", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_fins_telemetry_t, voltage) }, \
         { "pressure", NULL, MAVLINK_TYPE_FLOAT, 4, 24, offsetof(mavlink_fins_telemetry_t, pressure) }, \
         { "rpm", NULL, MAVLINK_TYPE_FLOAT, 8, 40, offsetof(mavlink_fins_telemetry_t, rpm) }, \
         { "accel", NULL, MAVLINK_TYPE_FLOAT, 3, 72, offsetof(mavlink_fins_telemetry_t, accel) }, \
         { "gyro", NULL, MAVLINK_TYPE_FLOAT, 3, 84, offsetof(mavlink_fins_telemetry_t, gyro) }, \
         { "network", NULL, MAVLINK_TYPE_FLOAT, 3, 96, offsetof(mavlink_fins_telemetry_t, network) }, \
         } \
}
#endif

/**
 * @brief Pack a fins_telemetry message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param session  NX session.
 * @param source_us [us] NX capture time.
 * @param valid_mask  Bits 0 voltage, 1 pressure, 2 rpm, 3 IMU, 4 network prediction.
 * @param voltage [V] Battery voltage.
 * @param pressure [Pa] Four absolute pressure measurements.
 * @param rpm [rpm] Eight signed motor speeds.
 * @param accel [m/s/s] FLU accelerometer.
 * @param gyro [rad/s] FLU angular rates.
 * @param network  Body vx, body vy in m/s, yaw rate in rad/s.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_telemetry_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t session, uint64_t source_us, uint32_t valid_mask, float voltage, const float *pressure, const float *rpm, const float *accel, const float *gyro, const float *network)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_TELEMETRY_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, source_us);
    _mav_put_uint32_t(buf, 16, valid_mask);
    _mav_put_float(buf, 20, voltage);
    _mav_put_float_array(buf, 24, pressure, 4);
    _mav_put_float_array(buf, 40, rpm, 8);
    _mav_put_float_array(buf, 72, accel, 3);
    _mav_put_float_array(buf, 84, gyro, 3);
    _mav_put_float_array(buf, 96, network, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_TELEMETRY_LEN);
#else
    mavlink_fins_telemetry_t packet;
    packet.session = session;
    packet.source_us = source_us;
    packet.valid_mask = valid_mask;
    packet.voltage = voltage;
    mav_array_memcpy(packet.pressure, pressure, sizeof(float)*4);
    mav_array_memcpy(packet.rpm, rpm, sizeof(float)*8);
    mav_array_memcpy(packet.accel, accel, sizeof(float)*3);
    mav_array_memcpy(packet.gyro, gyro, sizeof(float)*3);
    mav_array_memcpy(packet.network, network, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_TELEMETRY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_TELEMETRY;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_FINS_TELEMETRY_MIN_LEN, MAVLINK_MSG_ID_FINS_TELEMETRY_LEN, MAVLINK_MSG_ID_FINS_TELEMETRY_CRC);
}

/**
 * @brief Pack a fins_telemetry message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param session  NX session.
 * @param source_us [us] NX capture time.
 * @param valid_mask  Bits 0 voltage, 1 pressure, 2 rpm, 3 IMU, 4 network prediction.
 * @param voltage [V] Battery voltage.
 * @param pressure [Pa] Four absolute pressure measurements.
 * @param rpm [rpm] Eight signed motor speeds.
 * @param accel [m/s/s] FLU accelerometer.
 * @param gyro [rad/s] FLU angular rates.
 * @param network  Body vx, body vy in m/s, yaw rate in rad/s.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_telemetry_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t session, uint64_t source_us, uint32_t valid_mask, float voltage, const float *pressure, const float *rpm, const float *accel, const float *gyro, const float *network)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_TELEMETRY_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, source_us);
    _mav_put_uint32_t(buf, 16, valid_mask);
    _mav_put_float(buf, 20, voltage);
    _mav_put_float_array(buf, 24, pressure, 4);
    _mav_put_float_array(buf, 40, rpm, 8);
    _mav_put_float_array(buf, 72, accel, 3);
    _mav_put_float_array(buf, 84, gyro, 3);
    _mav_put_float_array(buf, 96, network, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_TELEMETRY_LEN);
#else
    mavlink_fins_telemetry_t packet;
    packet.session = session;
    packet.source_us = source_us;
    packet.valid_mask = valid_mask;
    packet.voltage = voltage;
    mav_array_memcpy(packet.pressure, pressure, sizeof(float)*4);
    mav_array_memcpy(packet.rpm, rpm, sizeof(float)*8);
    mav_array_memcpy(packet.accel, accel, sizeof(float)*3);
    mav_array_memcpy(packet.gyro, gyro, sizeof(float)*3);
    mav_array_memcpy(packet.network, network, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_TELEMETRY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_TELEMETRY;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FINS_TELEMETRY_MIN_LEN, MAVLINK_MSG_ID_FINS_TELEMETRY_LEN, MAVLINK_MSG_ID_FINS_TELEMETRY_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FINS_TELEMETRY_MIN_LEN, MAVLINK_MSG_ID_FINS_TELEMETRY_LEN);
#endif
}

/**
 * @brief Pack a fins_telemetry message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param session  NX session.
 * @param source_us [us] NX capture time.
 * @param valid_mask  Bits 0 voltage, 1 pressure, 2 rpm, 3 IMU, 4 network prediction.
 * @param voltage [V] Battery voltage.
 * @param pressure [Pa] Four absolute pressure measurements.
 * @param rpm [rpm] Eight signed motor speeds.
 * @param accel [m/s/s] FLU accelerometer.
 * @param gyro [rad/s] FLU angular rates.
 * @param network  Body vx, body vy in m/s, yaw rate in rad/s.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_telemetry_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t session,uint64_t source_us,uint32_t valid_mask,float voltage,const float *pressure,const float *rpm,const float *accel,const float *gyro,const float *network)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_TELEMETRY_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, source_us);
    _mav_put_uint32_t(buf, 16, valid_mask);
    _mav_put_float(buf, 20, voltage);
    _mav_put_float_array(buf, 24, pressure, 4);
    _mav_put_float_array(buf, 40, rpm, 8);
    _mav_put_float_array(buf, 72, accel, 3);
    _mav_put_float_array(buf, 84, gyro, 3);
    _mav_put_float_array(buf, 96, network, 3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_TELEMETRY_LEN);
#else
    mavlink_fins_telemetry_t packet;
    packet.session = session;
    packet.source_us = source_us;
    packet.valid_mask = valid_mask;
    packet.voltage = voltage;
    mav_array_memcpy(packet.pressure, pressure, sizeof(float)*4);
    mav_array_memcpy(packet.rpm, rpm, sizeof(float)*8);
    mav_array_memcpy(packet.accel, accel, sizeof(float)*3);
    mav_array_memcpy(packet.gyro, gyro, sizeof(float)*3);
    mav_array_memcpy(packet.network, network, sizeof(float)*3);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_TELEMETRY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_TELEMETRY;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_FINS_TELEMETRY_MIN_LEN, MAVLINK_MSG_ID_FINS_TELEMETRY_LEN, MAVLINK_MSG_ID_FINS_TELEMETRY_CRC);
}

/**
 * @brief Encode a fins_telemetry struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param fins_telemetry C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_telemetry_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_fins_telemetry_t* fins_telemetry)
{
    return mavlink_msg_fins_telemetry_pack(system_id, component_id, msg, fins_telemetry->session, fins_telemetry->source_us, fins_telemetry->valid_mask, fins_telemetry->voltage, fins_telemetry->pressure, fins_telemetry->rpm, fins_telemetry->accel, fins_telemetry->gyro, fins_telemetry->network);
}

/**
 * @brief Encode a fins_telemetry struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param fins_telemetry C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_telemetry_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_fins_telemetry_t* fins_telemetry)
{
    return mavlink_msg_fins_telemetry_pack_chan(system_id, component_id, chan, msg, fins_telemetry->session, fins_telemetry->source_us, fins_telemetry->valid_mask, fins_telemetry->voltage, fins_telemetry->pressure, fins_telemetry->rpm, fins_telemetry->accel, fins_telemetry->gyro, fins_telemetry->network);
}

/**
 * @brief Encode a fins_telemetry struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param fins_telemetry C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_telemetry_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_fins_telemetry_t* fins_telemetry)
{
    return mavlink_msg_fins_telemetry_pack_status(system_id, component_id, _status, msg,  fins_telemetry->session, fins_telemetry->source_us, fins_telemetry->valid_mask, fins_telemetry->voltage, fins_telemetry->pressure, fins_telemetry->rpm, fins_telemetry->accel, fins_telemetry->gyro, fins_telemetry->network);
}

/**
 * @brief Send a fins_telemetry message
 * @param chan MAVLink channel to send the message
 *
 * @param session  NX session.
 * @param source_us [us] NX capture time.
 * @param valid_mask  Bits 0 voltage, 1 pressure, 2 rpm, 3 IMU, 4 network prediction.
 * @param voltage [V] Battery voltage.
 * @param pressure [Pa] Four absolute pressure measurements.
 * @param rpm [rpm] Eight signed motor speeds.
 * @param accel [m/s/s] FLU accelerometer.
 * @param gyro [rad/s] FLU angular rates.
 * @param network  Body vx, body vy in m/s, yaw rate in rad/s.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_fins_telemetry_send(mavlink_channel_t chan, uint64_t session, uint64_t source_us, uint32_t valid_mask, float voltage, const float *pressure, const float *rpm, const float *accel, const float *gyro, const float *network)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_TELEMETRY_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, source_us);
    _mav_put_uint32_t(buf, 16, valid_mask);
    _mav_put_float(buf, 20, voltage);
    _mav_put_float_array(buf, 24, pressure, 4);
    _mav_put_float_array(buf, 40, rpm, 8);
    _mav_put_float_array(buf, 72, accel, 3);
    _mav_put_float_array(buf, 84, gyro, 3);
    _mav_put_float_array(buf, 96, network, 3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_TELEMETRY, buf, MAVLINK_MSG_ID_FINS_TELEMETRY_MIN_LEN, MAVLINK_MSG_ID_FINS_TELEMETRY_LEN, MAVLINK_MSG_ID_FINS_TELEMETRY_CRC);
#else
    mavlink_fins_telemetry_t packet;
    packet.session = session;
    packet.source_us = source_us;
    packet.valid_mask = valid_mask;
    packet.voltage = voltage;
    mav_array_memcpy(packet.pressure, pressure, sizeof(float)*4);
    mav_array_memcpy(packet.rpm, rpm, sizeof(float)*8);
    mav_array_memcpy(packet.accel, accel, sizeof(float)*3);
    mav_array_memcpy(packet.gyro, gyro, sizeof(float)*3);
    mav_array_memcpy(packet.network, network, sizeof(float)*3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_TELEMETRY, (const char *)&packet, MAVLINK_MSG_ID_FINS_TELEMETRY_MIN_LEN, MAVLINK_MSG_ID_FINS_TELEMETRY_LEN, MAVLINK_MSG_ID_FINS_TELEMETRY_CRC);
#endif
}

/**
 * @brief Send a fins_telemetry message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_fins_telemetry_send_struct(mavlink_channel_t chan, const mavlink_fins_telemetry_t* fins_telemetry)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_fins_telemetry_send(chan, fins_telemetry->session, fins_telemetry->source_us, fins_telemetry->valid_mask, fins_telemetry->voltage, fins_telemetry->pressure, fins_telemetry->rpm, fins_telemetry->accel, fins_telemetry->gyro, fins_telemetry->network);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_TELEMETRY, (const char *)fins_telemetry, MAVLINK_MSG_ID_FINS_TELEMETRY_MIN_LEN, MAVLINK_MSG_ID_FINS_TELEMETRY_LEN, MAVLINK_MSG_ID_FINS_TELEMETRY_CRC);
#endif
}

#if MAVLINK_MSG_ID_FINS_TELEMETRY_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_fins_telemetry_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t session, uint64_t source_us, uint32_t valid_mask, float voltage, const float *pressure, const float *rpm, const float *accel, const float *gyro, const float *network)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, source_us);
    _mav_put_uint32_t(buf, 16, valid_mask);
    _mav_put_float(buf, 20, voltage);
    _mav_put_float_array(buf, 24, pressure, 4);
    _mav_put_float_array(buf, 40, rpm, 8);
    _mav_put_float_array(buf, 72, accel, 3);
    _mav_put_float_array(buf, 84, gyro, 3);
    _mav_put_float_array(buf, 96, network, 3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_TELEMETRY, buf, MAVLINK_MSG_ID_FINS_TELEMETRY_MIN_LEN, MAVLINK_MSG_ID_FINS_TELEMETRY_LEN, MAVLINK_MSG_ID_FINS_TELEMETRY_CRC);
#else
    mavlink_fins_telemetry_t *packet = (mavlink_fins_telemetry_t *)msgbuf;
    packet->session = session;
    packet->source_us = source_us;
    packet->valid_mask = valid_mask;
    packet->voltage = voltage;
    mav_array_memcpy(packet->pressure, pressure, sizeof(float)*4);
    mav_array_memcpy(packet->rpm, rpm, sizeof(float)*8);
    mav_array_memcpy(packet->accel, accel, sizeof(float)*3);
    mav_array_memcpy(packet->gyro, gyro, sizeof(float)*3);
    mav_array_memcpy(packet->network, network, sizeof(float)*3);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_TELEMETRY, (const char *)packet, MAVLINK_MSG_ID_FINS_TELEMETRY_MIN_LEN, MAVLINK_MSG_ID_FINS_TELEMETRY_LEN, MAVLINK_MSG_ID_FINS_TELEMETRY_CRC);
#endif
}
#endif

#endif

// MESSAGE FINS_TELEMETRY UNPACKING


/**
 * @brief Get field session from fins_telemetry message
 *
 * @return  NX session.
 */
static inline uint64_t mavlink_msg_fins_telemetry_get_session(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field source_us from fins_telemetry message
 *
 * @return [us] NX capture time.
 */
static inline uint64_t mavlink_msg_fins_telemetry_get_source_us(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field valid_mask from fins_telemetry message
 *
 * @return  Bits 0 voltage, 1 pressure, 2 rpm, 3 IMU, 4 network prediction.
 */
static inline uint32_t mavlink_msg_fins_telemetry_get_valid_mask(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  16);
}

/**
 * @brief Get field voltage from fins_telemetry message
 *
 * @return [V] Battery voltage.
 */
static inline float mavlink_msg_fins_telemetry_get_voltage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field pressure from fins_telemetry message
 *
 * @return [Pa] Four absolute pressure measurements.
 */
static inline uint16_t mavlink_msg_fins_telemetry_get_pressure(const mavlink_message_t* msg, float *pressure)
{
    return _MAV_RETURN_float_array(msg, pressure, 4,  24);
}

/**
 * @brief Get field rpm from fins_telemetry message
 *
 * @return [rpm] Eight signed motor speeds.
 */
static inline uint16_t mavlink_msg_fins_telemetry_get_rpm(const mavlink_message_t* msg, float *rpm)
{
    return _MAV_RETURN_float_array(msg, rpm, 8,  40);
}

/**
 * @brief Get field accel from fins_telemetry message
 *
 * @return [m/s/s] FLU accelerometer.
 */
static inline uint16_t mavlink_msg_fins_telemetry_get_accel(const mavlink_message_t* msg, float *accel)
{
    return _MAV_RETURN_float_array(msg, accel, 3,  72);
}

/**
 * @brief Get field gyro from fins_telemetry message
 *
 * @return [rad/s] FLU angular rates.
 */
static inline uint16_t mavlink_msg_fins_telemetry_get_gyro(const mavlink_message_t* msg, float *gyro)
{
    return _MAV_RETURN_float_array(msg, gyro, 3,  84);
}

/**
 * @brief Get field network from fins_telemetry message
 *
 * @return  Body vx, body vy in m/s, yaw rate in rad/s.
 */
static inline uint16_t mavlink_msg_fins_telemetry_get_network(const mavlink_message_t* msg, float *network)
{
    return _MAV_RETURN_float_array(msg, network, 3,  96);
}

/**
 * @brief Decode a fins_telemetry message into a struct
 *
 * @param msg The message to decode
 * @param fins_telemetry C-struct to decode the message contents into
 */
static inline void mavlink_msg_fins_telemetry_decode(const mavlink_message_t* msg, mavlink_fins_telemetry_t* fins_telemetry)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    fins_telemetry->session = mavlink_msg_fins_telemetry_get_session(msg);
    fins_telemetry->source_us = mavlink_msg_fins_telemetry_get_source_us(msg);
    fins_telemetry->valid_mask = mavlink_msg_fins_telemetry_get_valid_mask(msg);
    fins_telemetry->voltage = mavlink_msg_fins_telemetry_get_voltage(msg);
    mavlink_msg_fins_telemetry_get_pressure(msg, fins_telemetry->pressure);
    mavlink_msg_fins_telemetry_get_rpm(msg, fins_telemetry->rpm);
    mavlink_msg_fins_telemetry_get_accel(msg, fins_telemetry->accel);
    mavlink_msg_fins_telemetry_get_gyro(msg, fins_telemetry->gyro);
    mavlink_msg_fins_telemetry_get_network(msg, fins_telemetry->network);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_FINS_TELEMETRY_LEN? msg->len : MAVLINK_MSG_ID_FINS_TELEMETRY_LEN;
        memset(fins_telemetry, 0, MAVLINK_MSG_ID_FINS_TELEMETRY_LEN);
    memcpy(fins_telemetry, _MAV_PAYLOAD(msg), len);
#endif
}
