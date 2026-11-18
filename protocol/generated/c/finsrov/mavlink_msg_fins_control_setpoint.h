#pragma once
// MESSAGE FINS_CONTROL_SETPOINT PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT 60003


typedef struct __mavlink_fins_control_setpoint_t {
 uint64_t session; /*<  PC session.*/
 uint64_t target_session; /*<  NX session.*/
 uint64_t source_us; /*< [us] Send time expressed in synchronized NX monotonic clock.*/
 uint32_t epoch; /*<  Confirmed mode generation.*/
 uint32_t sequence; /*<  Setpoint sequence.*/
 float yaw; /*<  Normalized yaw -1 to 1.*/
 float forward; /*<  Normalized forward -1 to 1.*/
 float left; /*<  Normalized left -1 to 1.*/
 float down; /*<  Normalized down 0 to 1.*/
 float up; /*<  Normalized up 0 to 1.*/
 float depth_target; /*< [m] Target depth when vertical_mode is 1.*/
 uint16_t valid_ms; /*< [ms] Validity, at most 200 ms.*/
 uint8_t vertical_mode; /*<  Vertical control selection.*/
} mavlink_fins_control_setpoint_t;

#define MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN 59
#define MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_MIN_LEN 59
#define MAVLINK_MSG_ID_60003_LEN 59
#define MAVLINK_MSG_ID_60003_MIN_LEN 59

#define MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_CRC 5
#define MAVLINK_MSG_ID_60003_CRC 5



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_FINS_CONTROL_SETPOINT { \
    60003, \
    "FINS_CONTROL_SETPOINT", \
    13, \
    {  { "session", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_fins_control_setpoint_t, session) }, \
         { "target_session", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_fins_control_setpoint_t, target_session) }, \
         { "source_us", NULL, MAVLINK_TYPE_UINT64_T, 0, 16, offsetof(mavlink_fins_control_setpoint_t, source_us) }, \
         { "epoch", NULL, MAVLINK_TYPE_UINT32_T, 0, 24, offsetof(mavlink_fins_control_setpoint_t, epoch) }, \
         { "sequence", NULL, MAVLINK_TYPE_UINT32_T, 0, 28, offsetof(mavlink_fins_control_setpoint_t, sequence) }, \
         { "valid_ms", NULL, MAVLINK_TYPE_UINT16_T, 0, 56, offsetof(mavlink_fins_control_setpoint_t, valid_ms) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_fins_control_setpoint_t, yaw) }, \
         { "forward", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_fins_control_setpoint_t, forward) }, \
         { "left", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_fins_control_setpoint_t, left) }, \
         { "down", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_fins_control_setpoint_t, down) }, \
         { "up", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_fins_control_setpoint_t, up) }, \
         { "depth_target", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_fins_control_setpoint_t, depth_target) }, \
         { "vertical_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 58, offsetof(mavlink_fins_control_setpoint_t, vertical_mode) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_FINS_CONTROL_SETPOINT { \
    "FINS_CONTROL_SETPOINT", \
    13, \
    {  { "session", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_fins_control_setpoint_t, session) }, \
         { "target_session", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_fins_control_setpoint_t, target_session) }, \
         { "source_us", NULL, MAVLINK_TYPE_UINT64_T, 0, 16, offsetof(mavlink_fins_control_setpoint_t, source_us) }, \
         { "epoch", NULL, MAVLINK_TYPE_UINT32_T, 0, 24, offsetof(mavlink_fins_control_setpoint_t, epoch) }, \
         { "sequence", NULL, MAVLINK_TYPE_UINT32_T, 0, 28, offsetof(mavlink_fins_control_setpoint_t, sequence) }, \
         { "valid_ms", NULL, MAVLINK_TYPE_UINT16_T, 0, 56, offsetof(mavlink_fins_control_setpoint_t, valid_ms) }, \
         { "yaw", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_fins_control_setpoint_t, yaw) }, \
         { "forward", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_fins_control_setpoint_t, forward) }, \
         { "left", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_fins_control_setpoint_t, left) }, \
         { "down", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_fins_control_setpoint_t, down) }, \
         { "up", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_fins_control_setpoint_t, up) }, \
         { "depth_target", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_fins_control_setpoint_t, depth_target) }, \
         { "vertical_mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 58, offsetof(mavlink_fins_control_setpoint_t, vertical_mode) }, \
         } \
}
#endif

/**
 * @brief Pack a fins_control_setpoint message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param session  PC session.
 * @param target_session  NX session.
 * @param source_us [us] Send time expressed in synchronized NX monotonic clock.
 * @param epoch  Confirmed mode generation.
 * @param sequence  Setpoint sequence.
 * @param valid_ms [ms] Validity, at most 200 ms.
 * @param yaw  Normalized yaw -1 to 1.
 * @param forward  Normalized forward -1 to 1.
 * @param left  Normalized left -1 to 1.
 * @param down  Normalized down 0 to 1.
 * @param up  Normalized up 0 to 1.
 * @param depth_target [m] Target depth when vertical_mode is 1.
 * @param vertical_mode  Vertical control selection.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_control_setpoint_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t session, uint64_t target_session, uint64_t source_us, uint32_t epoch, uint32_t sequence, uint16_t valid_ms, float yaw, float forward, float left, float down, float up, float depth_target, uint8_t vertical_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, target_session);
    _mav_put_uint64_t(buf, 16, source_us);
    _mav_put_uint32_t(buf, 24, epoch);
    _mav_put_uint32_t(buf, 28, sequence);
    _mav_put_float(buf, 32, yaw);
    _mav_put_float(buf, 36, forward);
    _mav_put_float(buf, 40, left);
    _mav_put_float(buf, 44, down);
    _mav_put_float(buf, 48, up);
    _mav_put_float(buf, 52, depth_target);
    _mav_put_uint16_t(buf, 56, valid_ms);
    _mav_put_uint8_t(buf, 58, vertical_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN);
#else
    mavlink_fins_control_setpoint_t packet;
    packet.session = session;
    packet.target_session = target_session;
    packet.source_us = source_us;
    packet.epoch = epoch;
    packet.sequence = sequence;
    packet.yaw = yaw;
    packet.forward = forward;
    packet.left = left;
    packet.down = down;
    packet.up = up;
    packet.depth_target = depth_target;
    packet.valid_ms = valid_ms;
    packet.vertical_mode = vertical_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_CRC);
}

/**
 * @brief Pack a fins_control_setpoint message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param session  PC session.
 * @param target_session  NX session.
 * @param source_us [us] Send time expressed in synchronized NX monotonic clock.
 * @param epoch  Confirmed mode generation.
 * @param sequence  Setpoint sequence.
 * @param valid_ms [ms] Validity, at most 200 ms.
 * @param yaw  Normalized yaw -1 to 1.
 * @param forward  Normalized forward -1 to 1.
 * @param left  Normalized left -1 to 1.
 * @param down  Normalized down 0 to 1.
 * @param up  Normalized up 0 to 1.
 * @param depth_target [m] Target depth when vertical_mode is 1.
 * @param vertical_mode  Vertical control selection.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_control_setpoint_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t session, uint64_t target_session, uint64_t source_us, uint32_t epoch, uint32_t sequence, uint16_t valid_ms, float yaw, float forward, float left, float down, float up, float depth_target, uint8_t vertical_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, target_session);
    _mav_put_uint64_t(buf, 16, source_us);
    _mav_put_uint32_t(buf, 24, epoch);
    _mav_put_uint32_t(buf, 28, sequence);
    _mav_put_float(buf, 32, yaw);
    _mav_put_float(buf, 36, forward);
    _mav_put_float(buf, 40, left);
    _mav_put_float(buf, 44, down);
    _mav_put_float(buf, 48, up);
    _mav_put_float(buf, 52, depth_target);
    _mav_put_uint16_t(buf, 56, valid_ms);
    _mav_put_uint8_t(buf, 58, vertical_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN);
#else
    mavlink_fins_control_setpoint_t packet;
    packet.session = session;
    packet.target_session = target_session;
    packet.source_us = source_us;
    packet.epoch = epoch;
    packet.sequence = sequence;
    packet.yaw = yaw;
    packet.forward = forward;
    packet.left = left;
    packet.down = down;
    packet.up = up;
    packet.depth_target = depth_target;
    packet.valid_ms = valid_ms;
    packet.vertical_mode = vertical_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN);
#endif
}

/**
 * @brief Pack a fins_control_setpoint message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param session  PC session.
 * @param target_session  NX session.
 * @param source_us [us] Send time expressed in synchronized NX monotonic clock.
 * @param epoch  Confirmed mode generation.
 * @param sequence  Setpoint sequence.
 * @param valid_ms [ms] Validity, at most 200 ms.
 * @param yaw  Normalized yaw -1 to 1.
 * @param forward  Normalized forward -1 to 1.
 * @param left  Normalized left -1 to 1.
 * @param down  Normalized down 0 to 1.
 * @param up  Normalized up 0 to 1.
 * @param depth_target [m] Target depth when vertical_mode is 1.
 * @param vertical_mode  Vertical control selection.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_control_setpoint_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t session,uint64_t target_session,uint64_t source_us,uint32_t epoch,uint32_t sequence,uint16_t valid_ms,float yaw,float forward,float left,float down,float up,float depth_target,uint8_t vertical_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, target_session);
    _mav_put_uint64_t(buf, 16, source_us);
    _mav_put_uint32_t(buf, 24, epoch);
    _mav_put_uint32_t(buf, 28, sequence);
    _mav_put_float(buf, 32, yaw);
    _mav_put_float(buf, 36, forward);
    _mav_put_float(buf, 40, left);
    _mav_put_float(buf, 44, down);
    _mav_put_float(buf, 48, up);
    _mav_put_float(buf, 52, depth_target);
    _mav_put_uint16_t(buf, 56, valid_ms);
    _mav_put_uint8_t(buf, 58, vertical_mode);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN);
#else
    mavlink_fins_control_setpoint_t packet;
    packet.session = session;
    packet.target_session = target_session;
    packet.source_us = source_us;
    packet.epoch = epoch;
    packet.sequence = sequence;
    packet.yaw = yaw;
    packet.forward = forward;
    packet.left = left;
    packet.down = down;
    packet.up = up;
    packet.depth_target = depth_target;
    packet.valid_ms = valid_ms;
    packet.vertical_mode = vertical_mode;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_CRC);
}

/**
 * @brief Encode a fins_control_setpoint struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param fins_control_setpoint C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_control_setpoint_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_fins_control_setpoint_t* fins_control_setpoint)
{
    return mavlink_msg_fins_control_setpoint_pack(system_id, component_id, msg, fins_control_setpoint->session, fins_control_setpoint->target_session, fins_control_setpoint->source_us, fins_control_setpoint->epoch, fins_control_setpoint->sequence, fins_control_setpoint->valid_ms, fins_control_setpoint->yaw, fins_control_setpoint->forward, fins_control_setpoint->left, fins_control_setpoint->down, fins_control_setpoint->up, fins_control_setpoint->depth_target, fins_control_setpoint->vertical_mode);
}

/**
 * @brief Encode a fins_control_setpoint struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param fins_control_setpoint C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_control_setpoint_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_fins_control_setpoint_t* fins_control_setpoint)
{
    return mavlink_msg_fins_control_setpoint_pack_chan(system_id, component_id, chan, msg, fins_control_setpoint->session, fins_control_setpoint->target_session, fins_control_setpoint->source_us, fins_control_setpoint->epoch, fins_control_setpoint->sequence, fins_control_setpoint->valid_ms, fins_control_setpoint->yaw, fins_control_setpoint->forward, fins_control_setpoint->left, fins_control_setpoint->down, fins_control_setpoint->up, fins_control_setpoint->depth_target, fins_control_setpoint->vertical_mode);
}

/**
 * @brief Encode a fins_control_setpoint struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param fins_control_setpoint C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_control_setpoint_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_fins_control_setpoint_t* fins_control_setpoint)
{
    return mavlink_msg_fins_control_setpoint_pack_status(system_id, component_id, _status, msg,  fins_control_setpoint->session, fins_control_setpoint->target_session, fins_control_setpoint->source_us, fins_control_setpoint->epoch, fins_control_setpoint->sequence, fins_control_setpoint->valid_ms, fins_control_setpoint->yaw, fins_control_setpoint->forward, fins_control_setpoint->left, fins_control_setpoint->down, fins_control_setpoint->up, fins_control_setpoint->depth_target, fins_control_setpoint->vertical_mode);
}

/**
 * @brief Send a fins_control_setpoint message
 * @param chan MAVLink channel to send the message
 *
 * @param session  PC session.
 * @param target_session  NX session.
 * @param source_us [us] Send time expressed in synchronized NX monotonic clock.
 * @param epoch  Confirmed mode generation.
 * @param sequence  Setpoint sequence.
 * @param valid_ms [ms] Validity, at most 200 ms.
 * @param yaw  Normalized yaw -1 to 1.
 * @param forward  Normalized forward -1 to 1.
 * @param left  Normalized left -1 to 1.
 * @param down  Normalized down 0 to 1.
 * @param up  Normalized up 0 to 1.
 * @param depth_target [m] Target depth when vertical_mode is 1.
 * @param vertical_mode  Vertical control selection.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_fins_control_setpoint_send(mavlink_channel_t chan, uint64_t session, uint64_t target_session, uint64_t source_us, uint32_t epoch, uint32_t sequence, uint16_t valid_ms, float yaw, float forward, float left, float down, float up, float depth_target, uint8_t vertical_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, target_session);
    _mav_put_uint64_t(buf, 16, source_us);
    _mav_put_uint32_t(buf, 24, epoch);
    _mav_put_uint32_t(buf, 28, sequence);
    _mav_put_float(buf, 32, yaw);
    _mav_put_float(buf, 36, forward);
    _mav_put_float(buf, 40, left);
    _mav_put_float(buf, 44, down);
    _mav_put_float(buf, 48, up);
    _mav_put_float(buf, 52, depth_target);
    _mav_put_uint16_t(buf, 56, valid_ms);
    _mav_put_uint8_t(buf, 58, vertical_mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT, buf, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_CRC);
#else
    mavlink_fins_control_setpoint_t packet;
    packet.session = session;
    packet.target_session = target_session;
    packet.source_us = source_us;
    packet.epoch = epoch;
    packet.sequence = sequence;
    packet.yaw = yaw;
    packet.forward = forward;
    packet.left = left;
    packet.down = down;
    packet.up = up;
    packet.depth_target = depth_target;
    packet.valid_ms = valid_ms;
    packet.vertical_mode = vertical_mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT, (const char *)&packet, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_CRC);
#endif
}

/**
 * @brief Send a fins_control_setpoint message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_fins_control_setpoint_send_struct(mavlink_channel_t chan, const mavlink_fins_control_setpoint_t* fins_control_setpoint)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_fins_control_setpoint_send(chan, fins_control_setpoint->session, fins_control_setpoint->target_session, fins_control_setpoint->source_us, fins_control_setpoint->epoch, fins_control_setpoint->sequence, fins_control_setpoint->valid_ms, fins_control_setpoint->yaw, fins_control_setpoint->forward, fins_control_setpoint->left, fins_control_setpoint->down, fins_control_setpoint->up, fins_control_setpoint->depth_target, fins_control_setpoint->vertical_mode);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT, (const char *)fins_control_setpoint, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_CRC);
#endif
}

#if MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_fins_control_setpoint_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t session, uint64_t target_session, uint64_t source_us, uint32_t epoch, uint32_t sequence, uint16_t valid_ms, float yaw, float forward, float left, float down, float up, float depth_target, uint8_t vertical_mode)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, target_session);
    _mav_put_uint64_t(buf, 16, source_us);
    _mav_put_uint32_t(buf, 24, epoch);
    _mav_put_uint32_t(buf, 28, sequence);
    _mav_put_float(buf, 32, yaw);
    _mav_put_float(buf, 36, forward);
    _mav_put_float(buf, 40, left);
    _mav_put_float(buf, 44, down);
    _mav_put_float(buf, 48, up);
    _mav_put_float(buf, 52, depth_target);
    _mav_put_uint16_t(buf, 56, valid_ms);
    _mav_put_uint8_t(buf, 58, vertical_mode);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT, buf, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_CRC);
#else
    mavlink_fins_control_setpoint_t *packet = (mavlink_fins_control_setpoint_t *)msgbuf;
    packet->session = session;
    packet->target_session = target_session;
    packet->source_us = source_us;
    packet->epoch = epoch;
    packet->sequence = sequence;
    packet->yaw = yaw;
    packet->forward = forward;
    packet->left = left;
    packet->down = down;
    packet->up = up;
    packet->depth_target = depth_target;
    packet->valid_ms = valid_ms;
    packet->vertical_mode = vertical_mode;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT, (const char *)packet, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_CRC);
#endif
}
#endif

#endif

// MESSAGE FINS_CONTROL_SETPOINT UNPACKING


/**
 * @brief Get field session from fins_control_setpoint message
 *
 * @return  PC session.
 */
static inline uint64_t mavlink_msg_fins_control_setpoint_get_session(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field target_session from fins_control_setpoint message
 *
 * @return  NX session.
 */
static inline uint64_t mavlink_msg_fins_control_setpoint_get_target_session(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field source_us from fins_control_setpoint message
 *
 * @return [us] Send time expressed in synchronized NX monotonic clock.
 */
static inline uint64_t mavlink_msg_fins_control_setpoint_get_source_us(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  16);
}

/**
 * @brief Get field epoch from fins_control_setpoint message
 *
 * @return  Confirmed mode generation.
 */
static inline uint32_t mavlink_msg_fins_control_setpoint_get_epoch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  24);
}

/**
 * @brief Get field sequence from fins_control_setpoint message
 *
 * @return  Setpoint sequence.
 */
static inline uint32_t mavlink_msg_fins_control_setpoint_get_sequence(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  28);
}

/**
 * @brief Get field valid_ms from fins_control_setpoint message
 *
 * @return [ms] Validity, at most 200 ms.
 */
static inline uint16_t mavlink_msg_fins_control_setpoint_get_valid_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  56);
}

/**
 * @brief Get field yaw from fins_control_setpoint message
 *
 * @return  Normalized yaw -1 to 1.
 */
static inline float mavlink_msg_fins_control_setpoint_get_yaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field forward from fins_control_setpoint message
 *
 * @return  Normalized forward -1 to 1.
 */
static inline float mavlink_msg_fins_control_setpoint_get_forward(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field left from fins_control_setpoint message
 *
 * @return  Normalized left -1 to 1.
 */
static inline float mavlink_msg_fins_control_setpoint_get_left(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field down from fins_control_setpoint message
 *
 * @return  Normalized down 0 to 1.
 */
static inline float mavlink_msg_fins_control_setpoint_get_down(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field up from fins_control_setpoint message
 *
 * @return  Normalized up 0 to 1.
 */
static inline float mavlink_msg_fins_control_setpoint_get_up(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field depth_target from fins_control_setpoint message
 *
 * @return [m] Target depth when vertical_mode is 1.
 */
static inline float mavlink_msg_fins_control_setpoint_get_depth_target(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Get field vertical_mode from fins_control_setpoint message
 *
 * @return  Vertical control selection.
 */
static inline uint8_t mavlink_msg_fins_control_setpoint_get_vertical_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  58);
}

/**
 * @brief Decode a fins_control_setpoint message into a struct
 *
 * @param msg The message to decode
 * @param fins_control_setpoint C-struct to decode the message contents into
 */
static inline void mavlink_msg_fins_control_setpoint_decode(const mavlink_message_t* msg, mavlink_fins_control_setpoint_t* fins_control_setpoint)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    fins_control_setpoint->session = mavlink_msg_fins_control_setpoint_get_session(msg);
    fins_control_setpoint->target_session = mavlink_msg_fins_control_setpoint_get_target_session(msg);
    fins_control_setpoint->source_us = mavlink_msg_fins_control_setpoint_get_source_us(msg);
    fins_control_setpoint->epoch = mavlink_msg_fins_control_setpoint_get_epoch(msg);
    fins_control_setpoint->sequence = mavlink_msg_fins_control_setpoint_get_sequence(msg);
    fins_control_setpoint->yaw = mavlink_msg_fins_control_setpoint_get_yaw(msg);
    fins_control_setpoint->forward = mavlink_msg_fins_control_setpoint_get_forward(msg);
    fins_control_setpoint->left = mavlink_msg_fins_control_setpoint_get_left(msg);
    fins_control_setpoint->down = mavlink_msg_fins_control_setpoint_get_down(msg);
    fins_control_setpoint->up = mavlink_msg_fins_control_setpoint_get_up(msg);
    fins_control_setpoint->depth_target = mavlink_msg_fins_control_setpoint_get_depth_target(msg);
    fins_control_setpoint->valid_ms = mavlink_msg_fins_control_setpoint_get_valid_ms(msg);
    fins_control_setpoint->vertical_mode = mavlink_msg_fins_control_setpoint_get_vertical_mode(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN? msg->len : MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN;
        memset(fins_control_setpoint, 0, MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_LEN);
    memcpy(fins_control_setpoint, _MAV_PAYLOAD(msg), len);
#endif
}
