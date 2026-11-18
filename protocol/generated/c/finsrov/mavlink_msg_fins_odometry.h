#pragma once
// MESSAGE FINS_ODOMETRY PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_FINS_ODOMETRY 60002


typedef struct __mavlink_fins_odometry_t {
 uint64_t session; /*<  NX session.*/
 uint64_t source_us; /*< [us] NX monotonic capture time.*/
 uint32_t sample_seq; /*<  Wrap-aware sample sequence.*/
 uint32_t reset_id; /*<  Changes whenever odometry origin is reset.*/
 float x; /*< [m] World X.*/
 float y; /*< [m] World Y.*/
 float yaw; /*< [rad] CCW yaw.*/
 float vx; /*< [m/s] World X velocity.*/
 float vy; /*< [m/s] World Y velocity.*/
 float yaw_rate; /*< [rad/s] CCW yaw rate.*/
 float depth; /*< [m] Depth positive down.*/
 uint8_t valid; /*<  Horizontal pose and velocity valid.*/
 uint8_t depth_valid; /*<  Depth valid.*/
} mavlink_fins_odometry_t;

#define MAVLINK_MSG_ID_FINS_ODOMETRY_LEN 54
#define MAVLINK_MSG_ID_FINS_ODOMETRY_MIN_LEN 54
#define MAVLINK_MSG_ID_60002_LEN 54
#define MAVLINK_MSG_ID_60002_MIN_LEN 54

#define MAVLINK_MSG_ID_FINS_ODOMETRY_CRC 26
#define MAVLINK_MSG_ID_60002_CRC 26



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_FINS_ODOMETRY { \
    60002, \
    "FINS_ODOMETRY", \
    13, \
    {  { "session", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_fins_odometry_t, session) }, \
         { "source_us", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_fins_odometry_t, source_us) }, \
         { "sample_seq", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_fins_odometry_t, sample_seq) }, \
         { "reset_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_fins_odometry_t, reset_id) }, \
         { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_fins_odometry_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_fins_odometry_t, y) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_fins_odometry_t, yaw) }, \
         { "vx", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_fins_odometry_t, vx) }, \
         { "vy", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_fins_odometry_t, vy) }, \
         { "yaw_rate", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_fins_odometry_t, yaw_rate) }, \
         { "depth", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_fins_odometry_t, depth) }, \
         { "valid", NULL, MAVLINK_TYPE_UINT8_T, 0, 52, offsetof(mavlink_fins_odometry_t, valid) }, \
         { "depth_valid", NULL, MAVLINK_TYPE_UINT8_T, 0, 53, offsetof(mavlink_fins_odometry_t, depth_valid) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_FINS_ODOMETRY { \
    "FINS_ODOMETRY", \
    13, \
    {  { "session", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_fins_odometry_t, session) }, \
         { "source_us", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_fins_odometry_t, source_us) }, \
         { "sample_seq", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_fins_odometry_t, sample_seq) }, \
         { "reset_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_fins_odometry_t, reset_id) }, \
         { "x", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_fins_odometry_t, x) }, \
         { "y", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_fins_odometry_t, y) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_fins_odometry_t, yaw) }, \
         { "vx", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_fins_odometry_t, vx) }, \
         { "vy", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_fins_odometry_t, vy) }, \
         { "yaw_rate", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_fins_odometry_t, yaw_rate) }, \
         { "depth", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_fins_odometry_t, depth) }, \
         { "valid", NULL, MAVLINK_TYPE_UINT8_T, 0, 52, offsetof(mavlink_fins_odometry_t, valid) }, \
         { "depth_valid", NULL, MAVLINK_TYPE_UINT8_T, 0, 53, offsetof(mavlink_fins_odometry_t, depth_valid) }, \
         } \
}
#endif

/**
 * @brief Pack a fins_odometry message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param session  NX session.
 * @param source_us [us] NX monotonic capture time.
 * @param sample_seq  Wrap-aware sample sequence.
 * @param reset_id  Changes whenever odometry origin is reset.
 * @param x [m] World X.
 * @param y [m] World Y.
 * @param yaw [rad] CCW yaw.
 * @param vx [m/s] World X velocity.
 * @param vy [m/s] World Y velocity.
 * @param yaw_rate [rad/s] CCW yaw rate.
 * @param depth [m] Depth positive down.
 * @param valid  Horizontal pose and velocity valid.
 * @param depth_valid  Depth valid.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_odometry_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t session, uint64_t source_us, uint32_t sample_seq, uint32_t reset_id, float x, float y, float yaw, float vx, float vy, float yaw_rate, float depth, uint8_t valid, uint8_t depth_valid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_ODOMETRY_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, source_us);
    _mav_put_uint32_t(buf, 16, sample_seq);
    _mav_put_uint32_t(buf, 20, reset_id);
    _mav_put_float(buf, 24, x);
    _mav_put_float(buf, 28, y);
    _mav_put_float(buf, 32, yaw);
    _mav_put_float(buf, 36, vx);
    _mav_put_float(buf, 40, vy);
    _mav_put_float(buf, 44, yaw_rate);
    _mav_put_float(buf, 48, depth);
    _mav_put_uint8_t(buf, 52, valid);
    _mav_put_uint8_t(buf, 53, depth_valid);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_ODOMETRY_LEN);
#else
    mavlink_fins_odometry_t packet;
    packet.session = session;
    packet.source_us = source_us;
    packet.sample_seq = sample_seq;
    packet.reset_id = reset_id;
    packet.x = x;
    packet.y = y;
    packet.yaw = yaw;
    packet.vx = vx;
    packet.vy = vy;
    packet.yaw_rate = yaw_rate;
    packet.depth = depth;
    packet.valid = valid;
    packet.depth_valid = depth_valid;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_ODOMETRY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_ODOMETRY;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_FINS_ODOMETRY_MIN_LEN, MAVLINK_MSG_ID_FINS_ODOMETRY_LEN, MAVLINK_MSG_ID_FINS_ODOMETRY_CRC);
}

/**
 * @brief Pack a fins_odometry message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param session  NX session.
 * @param source_us [us] NX monotonic capture time.
 * @param sample_seq  Wrap-aware sample sequence.
 * @param reset_id  Changes whenever odometry origin is reset.
 * @param x [m] World X.
 * @param y [m] World Y.
 * @param yaw [rad] CCW yaw.
 * @param vx [m/s] World X velocity.
 * @param vy [m/s] World Y velocity.
 * @param yaw_rate [rad/s] CCW yaw rate.
 * @param depth [m] Depth positive down.
 * @param valid  Horizontal pose and velocity valid.
 * @param depth_valid  Depth valid.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_odometry_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t session, uint64_t source_us, uint32_t sample_seq, uint32_t reset_id, float x, float y, float yaw, float vx, float vy, float yaw_rate, float depth, uint8_t valid, uint8_t depth_valid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_ODOMETRY_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, source_us);
    _mav_put_uint32_t(buf, 16, sample_seq);
    _mav_put_uint32_t(buf, 20, reset_id);
    _mav_put_float(buf, 24, x);
    _mav_put_float(buf, 28, y);
    _mav_put_float(buf, 32, yaw);
    _mav_put_float(buf, 36, vx);
    _mav_put_float(buf, 40, vy);
    _mav_put_float(buf, 44, yaw_rate);
    _mav_put_float(buf, 48, depth);
    _mav_put_uint8_t(buf, 52, valid);
    _mav_put_uint8_t(buf, 53, depth_valid);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_ODOMETRY_LEN);
#else
    mavlink_fins_odometry_t packet;
    packet.session = session;
    packet.source_us = source_us;
    packet.sample_seq = sample_seq;
    packet.reset_id = reset_id;
    packet.x = x;
    packet.y = y;
    packet.yaw = yaw;
    packet.vx = vx;
    packet.vy = vy;
    packet.yaw_rate = yaw_rate;
    packet.depth = depth;
    packet.valid = valid;
    packet.depth_valid = depth_valid;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_ODOMETRY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_ODOMETRY;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FINS_ODOMETRY_MIN_LEN, MAVLINK_MSG_ID_FINS_ODOMETRY_LEN, MAVLINK_MSG_ID_FINS_ODOMETRY_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FINS_ODOMETRY_MIN_LEN, MAVLINK_MSG_ID_FINS_ODOMETRY_LEN);
#endif
}

/**
 * @brief Pack a fins_odometry message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param session  NX session.
 * @param source_us [us] NX monotonic capture time.
 * @param sample_seq  Wrap-aware sample sequence.
 * @param reset_id  Changes whenever odometry origin is reset.
 * @param x [m] World X.
 * @param y [m] World Y.
 * @param yaw [rad] CCW yaw.
 * @param vx [m/s] World X velocity.
 * @param vy [m/s] World Y velocity.
 * @param yaw_rate [rad/s] CCW yaw rate.
 * @param depth [m] Depth positive down.
 * @param valid  Horizontal pose and velocity valid.
 * @param depth_valid  Depth valid.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_odometry_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t session,uint64_t source_us,uint32_t sample_seq,uint32_t reset_id,float x,float y,float yaw,float vx,float vy,float yaw_rate,float depth,uint8_t valid,uint8_t depth_valid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_ODOMETRY_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, source_us);
    _mav_put_uint32_t(buf, 16, sample_seq);
    _mav_put_uint32_t(buf, 20, reset_id);
    _mav_put_float(buf, 24, x);
    _mav_put_float(buf, 28, y);
    _mav_put_float(buf, 32, yaw);
    _mav_put_float(buf, 36, vx);
    _mav_put_float(buf, 40, vy);
    _mav_put_float(buf, 44, yaw_rate);
    _mav_put_float(buf, 48, depth);
    _mav_put_uint8_t(buf, 52, valid);
    _mav_put_uint8_t(buf, 53, depth_valid);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_ODOMETRY_LEN);
#else
    mavlink_fins_odometry_t packet;
    packet.session = session;
    packet.source_us = source_us;
    packet.sample_seq = sample_seq;
    packet.reset_id = reset_id;
    packet.x = x;
    packet.y = y;
    packet.yaw = yaw;
    packet.vx = vx;
    packet.vy = vy;
    packet.yaw_rate = yaw_rate;
    packet.depth = depth;
    packet.valid = valid;
    packet.depth_valid = depth_valid;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_ODOMETRY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_ODOMETRY;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_FINS_ODOMETRY_MIN_LEN, MAVLINK_MSG_ID_FINS_ODOMETRY_LEN, MAVLINK_MSG_ID_FINS_ODOMETRY_CRC);
}

/**
 * @brief Encode a fins_odometry struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param fins_odometry C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_odometry_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_fins_odometry_t* fins_odometry)
{
    return mavlink_msg_fins_odometry_pack(system_id, component_id, msg, fins_odometry->session, fins_odometry->source_us, fins_odometry->sample_seq, fins_odometry->reset_id, fins_odometry->x, fins_odometry->y, fins_odometry->yaw, fins_odometry->vx, fins_odometry->vy, fins_odometry->yaw_rate, fins_odometry->depth, fins_odometry->valid, fins_odometry->depth_valid);
}

/**
 * @brief Encode a fins_odometry struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param fins_odometry C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_odometry_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_fins_odometry_t* fins_odometry)
{
    return mavlink_msg_fins_odometry_pack_chan(system_id, component_id, chan, msg, fins_odometry->session, fins_odometry->source_us, fins_odometry->sample_seq, fins_odometry->reset_id, fins_odometry->x, fins_odometry->y, fins_odometry->yaw, fins_odometry->vx, fins_odometry->vy, fins_odometry->yaw_rate, fins_odometry->depth, fins_odometry->valid, fins_odometry->depth_valid);
}

/**
 * @brief Encode a fins_odometry struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param fins_odometry C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_odometry_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_fins_odometry_t* fins_odometry)
{
    return mavlink_msg_fins_odometry_pack_status(system_id, component_id, _status, msg,  fins_odometry->session, fins_odometry->source_us, fins_odometry->sample_seq, fins_odometry->reset_id, fins_odometry->x, fins_odometry->y, fins_odometry->yaw, fins_odometry->vx, fins_odometry->vy, fins_odometry->yaw_rate, fins_odometry->depth, fins_odometry->valid, fins_odometry->depth_valid);
}

/**
 * @brief Send a fins_odometry message
 * @param chan MAVLink channel to send the message
 *
 * @param session  NX session.
 * @param source_us [us] NX monotonic capture time.
 * @param sample_seq  Wrap-aware sample sequence.
 * @param reset_id  Changes whenever odometry origin is reset.
 * @param x [m] World X.
 * @param y [m] World Y.
 * @param yaw [rad] CCW yaw.
 * @param vx [m/s] World X velocity.
 * @param vy [m/s] World Y velocity.
 * @param yaw_rate [rad/s] CCW yaw rate.
 * @param depth [m] Depth positive down.
 * @param valid  Horizontal pose and velocity valid.
 * @param depth_valid  Depth valid.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_fins_odometry_send(mavlink_channel_t chan, uint64_t session, uint64_t source_us, uint32_t sample_seq, uint32_t reset_id, float x, float y, float yaw, float vx, float vy, float yaw_rate, float depth, uint8_t valid, uint8_t depth_valid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_ODOMETRY_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, source_us);
    _mav_put_uint32_t(buf, 16, sample_seq);
    _mav_put_uint32_t(buf, 20, reset_id);
    _mav_put_float(buf, 24, x);
    _mav_put_float(buf, 28, y);
    _mav_put_float(buf, 32, yaw);
    _mav_put_float(buf, 36, vx);
    _mav_put_float(buf, 40, vy);
    _mav_put_float(buf, 44, yaw_rate);
    _mav_put_float(buf, 48, depth);
    _mav_put_uint8_t(buf, 52, valid);
    _mav_put_uint8_t(buf, 53, depth_valid);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_ODOMETRY, buf, MAVLINK_MSG_ID_FINS_ODOMETRY_MIN_LEN, MAVLINK_MSG_ID_FINS_ODOMETRY_LEN, MAVLINK_MSG_ID_FINS_ODOMETRY_CRC);
#else
    mavlink_fins_odometry_t packet;
    packet.session = session;
    packet.source_us = source_us;
    packet.sample_seq = sample_seq;
    packet.reset_id = reset_id;
    packet.x = x;
    packet.y = y;
    packet.yaw = yaw;
    packet.vx = vx;
    packet.vy = vy;
    packet.yaw_rate = yaw_rate;
    packet.depth = depth;
    packet.valid = valid;
    packet.depth_valid = depth_valid;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_ODOMETRY, (const char *)&packet, MAVLINK_MSG_ID_FINS_ODOMETRY_MIN_LEN, MAVLINK_MSG_ID_FINS_ODOMETRY_LEN, MAVLINK_MSG_ID_FINS_ODOMETRY_CRC);
#endif
}

/**
 * @brief Send a fins_odometry message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_fins_odometry_send_struct(mavlink_channel_t chan, const mavlink_fins_odometry_t* fins_odometry)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_fins_odometry_send(chan, fins_odometry->session, fins_odometry->source_us, fins_odometry->sample_seq, fins_odometry->reset_id, fins_odometry->x, fins_odometry->y, fins_odometry->yaw, fins_odometry->vx, fins_odometry->vy, fins_odometry->yaw_rate, fins_odometry->depth, fins_odometry->valid, fins_odometry->depth_valid);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_ODOMETRY, (const char *)fins_odometry, MAVLINK_MSG_ID_FINS_ODOMETRY_MIN_LEN, MAVLINK_MSG_ID_FINS_ODOMETRY_LEN, MAVLINK_MSG_ID_FINS_ODOMETRY_CRC);
#endif
}

#if MAVLINK_MSG_ID_FINS_ODOMETRY_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_fins_odometry_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t session, uint64_t source_us, uint32_t sample_seq, uint32_t reset_id, float x, float y, float yaw, float vx, float vy, float yaw_rate, float depth, uint8_t valid, uint8_t depth_valid)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, source_us);
    _mav_put_uint32_t(buf, 16, sample_seq);
    _mav_put_uint32_t(buf, 20, reset_id);
    _mav_put_float(buf, 24, x);
    _mav_put_float(buf, 28, y);
    _mav_put_float(buf, 32, yaw);
    _mav_put_float(buf, 36, vx);
    _mav_put_float(buf, 40, vy);
    _mav_put_float(buf, 44, yaw_rate);
    _mav_put_float(buf, 48, depth);
    _mav_put_uint8_t(buf, 52, valid);
    _mav_put_uint8_t(buf, 53, depth_valid);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_ODOMETRY, buf, MAVLINK_MSG_ID_FINS_ODOMETRY_MIN_LEN, MAVLINK_MSG_ID_FINS_ODOMETRY_LEN, MAVLINK_MSG_ID_FINS_ODOMETRY_CRC);
#else
    mavlink_fins_odometry_t *packet = (mavlink_fins_odometry_t *)msgbuf;
    packet->session = session;
    packet->source_us = source_us;
    packet->sample_seq = sample_seq;
    packet->reset_id = reset_id;
    packet->x = x;
    packet->y = y;
    packet->yaw = yaw;
    packet->vx = vx;
    packet->vy = vy;
    packet->yaw_rate = yaw_rate;
    packet->depth = depth;
    packet->valid = valid;
    packet->depth_valid = depth_valid;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_ODOMETRY, (const char *)packet, MAVLINK_MSG_ID_FINS_ODOMETRY_MIN_LEN, MAVLINK_MSG_ID_FINS_ODOMETRY_LEN, MAVLINK_MSG_ID_FINS_ODOMETRY_CRC);
#endif
}
#endif

#endif

// MESSAGE FINS_ODOMETRY UNPACKING


/**
 * @brief Get field session from fins_odometry message
 *
 * @return  NX session.
 */
static inline uint64_t mavlink_msg_fins_odometry_get_session(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field source_us from fins_odometry message
 *
 * @return [us] NX monotonic capture time.
 */
static inline uint64_t mavlink_msg_fins_odometry_get_source_us(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field sample_seq from fins_odometry message
 *
 * @return  Wrap-aware sample sequence.
 */
static inline uint32_t mavlink_msg_fins_odometry_get_sample_seq(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  16);
}

/**
 * @brief Get field reset_id from fins_odometry message
 *
 * @return  Changes whenever odometry origin is reset.
 */
static inline uint32_t mavlink_msg_fins_odometry_get_reset_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  20);
}

/**
 * @brief Get field x from fins_odometry message
 *
 * @return [m] World X.
 */
static inline float mavlink_msg_fins_odometry_get_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field y from fins_odometry message
 *
 * @return [m] World Y.
 */
static inline float mavlink_msg_fins_odometry_get_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field yaw from fins_odometry message
 *
 * @return [rad] CCW yaw.
 */
static inline float mavlink_msg_fins_odometry_get_yaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field vx from fins_odometry message
 *
 * @return [m/s] World X velocity.
 */
static inline float mavlink_msg_fins_odometry_get_vx(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field vy from fins_odometry message
 *
 * @return [m/s] World Y velocity.
 */
static inline float mavlink_msg_fins_odometry_get_vy(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field yaw_rate from fins_odometry message
 *
 * @return [rad/s] CCW yaw rate.
 */
static inline float mavlink_msg_fins_odometry_get_yaw_rate(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field depth from fins_odometry message
 *
 * @return [m] Depth positive down.
 */
static inline float mavlink_msg_fins_odometry_get_depth(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field valid from fins_odometry message
 *
 * @return  Horizontal pose and velocity valid.
 */
static inline uint8_t mavlink_msg_fins_odometry_get_valid(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  52);
}

/**
 * @brief Get field depth_valid from fins_odometry message
 *
 * @return  Depth valid.
 */
static inline uint8_t mavlink_msg_fins_odometry_get_depth_valid(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  53);
}

/**
 * @brief Decode a fins_odometry message into a struct
 *
 * @param msg The message to decode
 * @param fins_odometry C-struct to decode the message contents into
 */
static inline void mavlink_msg_fins_odometry_decode(const mavlink_message_t* msg, mavlink_fins_odometry_t* fins_odometry)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    fins_odometry->session = mavlink_msg_fins_odometry_get_session(msg);
    fins_odometry->source_us = mavlink_msg_fins_odometry_get_source_us(msg);
    fins_odometry->sample_seq = mavlink_msg_fins_odometry_get_sample_seq(msg);
    fins_odometry->reset_id = mavlink_msg_fins_odometry_get_reset_id(msg);
    fins_odometry->x = mavlink_msg_fins_odometry_get_x(msg);
    fins_odometry->y = mavlink_msg_fins_odometry_get_y(msg);
    fins_odometry->yaw = mavlink_msg_fins_odometry_get_yaw(msg);
    fins_odometry->vx = mavlink_msg_fins_odometry_get_vx(msg);
    fins_odometry->vy = mavlink_msg_fins_odometry_get_vy(msg);
    fins_odometry->yaw_rate = mavlink_msg_fins_odometry_get_yaw_rate(msg);
    fins_odometry->depth = mavlink_msg_fins_odometry_get_depth(msg);
    fins_odometry->valid = mavlink_msg_fins_odometry_get_valid(msg);
    fins_odometry->depth_valid = mavlink_msg_fins_odometry_get_depth_valid(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_FINS_ODOMETRY_LEN? msg->len : MAVLINK_MSG_ID_FINS_ODOMETRY_LEN;
        memset(fins_odometry, 0, MAVLINK_MSG_ID_FINS_ODOMETRY_LEN);
    memcpy(fins_odometry, _MAV_PAYLOAD(msg), len);
#endif
}
