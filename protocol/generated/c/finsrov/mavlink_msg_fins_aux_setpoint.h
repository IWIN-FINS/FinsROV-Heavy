#pragma once
// MESSAGE FINS_AUX_SETPOINT PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_FINS_AUX_SETPOINT 60006


typedef struct __mavlink_fins_aux_setpoint_t {
 uint64_t session; /*<  PC session.*/
 uint64_t target_session; /*<  NX session.*/
 uint64_t source_us; /*< [us] Synchronized NX clock.*/
 uint32_t epoch; /*<  Confirmed generation.*/
 uint32_t sequence; /*<  Independent auxiliary sequence.*/
 uint16_t valid_ms; /*< [ms] At most 200.*/
 int8_t cam_yaw; /*<  -1, 0, 1.*/
 int8_t cam_pitch; /*<  -1, 0, 1.*/
} mavlink_fins_aux_setpoint_t;

#define MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN 36
#define MAVLINK_MSG_ID_FINS_AUX_SETPOINT_MIN_LEN 36
#define MAVLINK_MSG_ID_60006_LEN 36
#define MAVLINK_MSG_ID_60006_MIN_LEN 36

#define MAVLINK_MSG_ID_FINS_AUX_SETPOINT_CRC 64
#define MAVLINK_MSG_ID_60006_CRC 64



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_FINS_AUX_SETPOINT { \
    60006, \
    "FINS_AUX_SETPOINT", \
    8, \
    {  { "session", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_fins_aux_setpoint_t, session) }, \
         { "target_session", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_fins_aux_setpoint_t, target_session) }, \
         { "source_us", NULL, MAVLINK_TYPE_UINT64_T, 0, 16, offsetof(mavlink_fins_aux_setpoint_t, source_us) }, \
         { "epoch", NULL, MAVLINK_TYPE_UINT32_T, 0, 24, offsetof(mavlink_fins_aux_setpoint_t, epoch) }, \
         { "sequence", NULL, MAVLINK_TYPE_UINT32_T, 0, 28, offsetof(mavlink_fins_aux_setpoint_t, sequence) }, \
         { "valid_ms", NULL, MAVLINK_TYPE_UINT16_T, 0, 32, offsetof(mavlink_fins_aux_setpoint_t, valid_ms) }, \
         { "cam_yaw", NULL, MAVLINK_TYPE_INT8_T, 0, 34, offsetof(mavlink_fins_aux_setpoint_t, cam_yaw) }, \
         { "cam_pitch", NULL, MAVLINK_TYPE_INT8_T, 0, 35, offsetof(mavlink_fins_aux_setpoint_t, cam_pitch) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_FINS_AUX_SETPOINT { \
    "FINS_AUX_SETPOINT", \
    8, \
    {  { "session", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_fins_aux_setpoint_t, session) }, \
         { "target_session", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_fins_aux_setpoint_t, target_session) }, \
         { "source_us", NULL, MAVLINK_TYPE_UINT64_T, 0, 16, offsetof(mavlink_fins_aux_setpoint_t, source_us) }, \
         { "epoch", NULL, MAVLINK_TYPE_UINT32_T, 0, 24, offsetof(mavlink_fins_aux_setpoint_t, epoch) }, \
         { "sequence", NULL, MAVLINK_TYPE_UINT32_T, 0, 28, offsetof(mavlink_fins_aux_setpoint_t, sequence) }, \
         { "valid_ms", NULL, MAVLINK_TYPE_UINT16_T, 0, 32, offsetof(mavlink_fins_aux_setpoint_t, valid_ms) }, \
         { "cam_yaw", NULL, MAVLINK_TYPE_INT8_T, 0, 34, offsetof(mavlink_fins_aux_setpoint_t, cam_yaw) }, \
         { "cam_pitch", NULL, MAVLINK_TYPE_INT8_T, 0, 35, offsetof(mavlink_fins_aux_setpoint_t, cam_pitch) }, \
         } \
}
#endif

/**
 * @brief Pack a fins_aux_setpoint message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param session  PC session.
 * @param target_session  NX session.
 * @param source_us [us] Synchronized NX clock.
 * @param epoch  Confirmed generation.
 * @param sequence  Independent auxiliary sequence.
 * @param valid_ms [ms] At most 200.
 * @param cam_yaw  -1, 0, 1.
 * @param cam_pitch  -1, 0, 1.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_aux_setpoint_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t session, uint64_t target_session, uint64_t source_us, uint32_t epoch, uint32_t sequence, uint16_t valid_ms, int8_t cam_yaw, int8_t cam_pitch)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, target_session);
    _mav_put_uint64_t(buf, 16, source_us);
    _mav_put_uint32_t(buf, 24, epoch);
    _mav_put_uint32_t(buf, 28, sequence);
    _mav_put_uint16_t(buf, 32, valid_ms);
    _mav_put_int8_t(buf, 34, cam_yaw);
    _mav_put_int8_t(buf, 35, cam_pitch);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN);
#else
    mavlink_fins_aux_setpoint_t packet;
    packet.session = session;
    packet.target_session = target_session;
    packet.source_us = source_us;
    packet.epoch = epoch;
    packet.sequence = sequence;
    packet.valid_ms = valid_ms;
    packet.cam_yaw = cam_yaw;
    packet.cam_pitch = cam_pitch;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_AUX_SETPOINT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_CRC);
}

/**
 * @brief Pack a fins_aux_setpoint message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param session  PC session.
 * @param target_session  NX session.
 * @param source_us [us] Synchronized NX clock.
 * @param epoch  Confirmed generation.
 * @param sequence  Independent auxiliary sequence.
 * @param valid_ms [ms] At most 200.
 * @param cam_yaw  -1, 0, 1.
 * @param cam_pitch  -1, 0, 1.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_aux_setpoint_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t session, uint64_t target_session, uint64_t source_us, uint32_t epoch, uint32_t sequence, uint16_t valid_ms, int8_t cam_yaw, int8_t cam_pitch)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, target_session);
    _mav_put_uint64_t(buf, 16, source_us);
    _mav_put_uint32_t(buf, 24, epoch);
    _mav_put_uint32_t(buf, 28, sequence);
    _mav_put_uint16_t(buf, 32, valid_ms);
    _mav_put_int8_t(buf, 34, cam_yaw);
    _mav_put_int8_t(buf, 35, cam_pitch);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN);
#else
    mavlink_fins_aux_setpoint_t packet;
    packet.session = session;
    packet.target_session = target_session;
    packet.source_us = source_us;
    packet.epoch = epoch;
    packet.sequence = sequence;
    packet.valid_ms = valid_ms;
    packet.cam_yaw = cam_yaw;
    packet.cam_pitch = cam_pitch;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_AUX_SETPOINT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN);
#endif
}

/**
 * @brief Pack a fins_aux_setpoint message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param session  PC session.
 * @param target_session  NX session.
 * @param source_us [us] Synchronized NX clock.
 * @param epoch  Confirmed generation.
 * @param sequence  Independent auxiliary sequence.
 * @param valid_ms [ms] At most 200.
 * @param cam_yaw  -1, 0, 1.
 * @param cam_pitch  -1, 0, 1.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_aux_setpoint_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t session,uint64_t target_session,uint64_t source_us,uint32_t epoch,uint32_t sequence,uint16_t valid_ms,int8_t cam_yaw,int8_t cam_pitch)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, target_session);
    _mav_put_uint64_t(buf, 16, source_us);
    _mav_put_uint32_t(buf, 24, epoch);
    _mav_put_uint32_t(buf, 28, sequence);
    _mav_put_uint16_t(buf, 32, valid_ms);
    _mav_put_int8_t(buf, 34, cam_yaw);
    _mav_put_int8_t(buf, 35, cam_pitch);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN);
#else
    mavlink_fins_aux_setpoint_t packet;
    packet.session = session;
    packet.target_session = target_session;
    packet.source_us = source_us;
    packet.epoch = epoch;
    packet.sequence = sequence;
    packet.valid_ms = valid_ms;
    packet.cam_yaw = cam_yaw;
    packet.cam_pitch = cam_pitch;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_AUX_SETPOINT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_CRC);
}

/**
 * @brief Encode a fins_aux_setpoint struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param fins_aux_setpoint C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_aux_setpoint_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_fins_aux_setpoint_t* fins_aux_setpoint)
{
    return mavlink_msg_fins_aux_setpoint_pack(system_id, component_id, msg, fins_aux_setpoint->session, fins_aux_setpoint->target_session, fins_aux_setpoint->source_us, fins_aux_setpoint->epoch, fins_aux_setpoint->sequence, fins_aux_setpoint->valid_ms, fins_aux_setpoint->cam_yaw, fins_aux_setpoint->cam_pitch);
}

/**
 * @brief Encode a fins_aux_setpoint struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param fins_aux_setpoint C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_aux_setpoint_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_fins_aux_setpoint_t* fins_aux_setpoint)
{
    return mavlink_msg_fins_aux_setpoint_pack_chan(system_id, component_id, chan, msg, fins_aux_setpoint->session, fins_aux_setpoint->target_session, fins_aux_setpoint->source_us, fins_aux_setpoint->epoch, fins_aux_setpoint->sequence, fins_aux_setpoint->valid_ms, fins_aux_setpoint->cam_yaw, fins_aux_setpoint->cam_pitch);
}

/**
 * @brief Encode a fins_aux_setpoint struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param fins_aux_setpoint C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_aux_setpoint_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_fins_aux_setpoint_t* fins_aux_setpoint)
{
    return mavlink_msg_fins_aux_setpoint_pack_status(system_id, component_id, _status, msg,  fins_aux_setpoint->session, fins_aux_setpoint->target_session, fins_aux_setpoint->source_us, fins_aux_setpoint->epoch, fins_aux_setpoint->sequence, fins_aux_setpoint->valid_ms, fins_aux_setpoint->cam_yaw, fins_aux_setpoint->cam_pitch);
}

/**
 * @brief Send a fins_aux_setpoint message
 * @param chan MAVLink channel to send the message
 *
 * @param session  PC session.
 * @param target_session  NX session.
 * @param source_us [us] Synchronized NX clock.
 * @param epoch  Confirmed generation.
 * @param sequence  Independent auxiliary sequence.
 * @param valid_ms [ms] At most 200.
 * @param cam_yaw  -1, 0, 1.
 * @param cam_pitch  -1, 0, 1.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_fins_aux_setpoint_send(mavlink_channel_t chan, uint64_t session, uint64_t target_session, uint64_t source_us, uint32_t epoch, uint32_t sequence, uint16_t valid_ms, int8_t cam_yaw, int8_t cam_pitch)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, target_session);
    _mav_put_uint64_t(buf, 16, source_us);
    _mav_put_uint32_t(buf, 24, epoch);
    _mav_put_uint32_t(buf, 28, sequence);
    _mav_put_uint16_t(buf, 32, valid_ms);
    _mav_put_int8_t(buf, 34, cam_yaw);
    _mav_put_int8_t(buf, 35, cam_pitch);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_AUX_SETPOINT, buf, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_CRC);
#else
    mavlink_fins_aux_setpoint_t packet;
    packet.session = session;
    packet.target_session = target_session;
    packet.source_us = source_us;
    packet.epoch = epoch;
    packet.sequence = sequence;
    packet.valid_ms = valid_ms;
    packet.cam_yaw = cam_yaw;
    packet.cam_pitch = cam_pitch;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_AUX_SETPOINT, (const char *)&packet, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_CRC);
#endif
}

/**
 * @brief Send a fins_aux_setpoint message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_fins_aux_setpoint_send_struct(mavlink_channel_t chan, const mavlink_fins_aux_setpoint_t* fins_aux_setpoint)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_fins_aux_setpoint_send(chan, fins_aux_setpoint->session, fins_aux_setpoint->target_session, fins_aux_setpoint->source_us, fins_aux_setpoint->epoch, fins_aux_setpoint->sequence, fins_aux_setpoint->valid_ms, fins_aux_setpoint->cam_yaw, fins_aux_setpoint->cam_pitch);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_AUX_SETPOINT, (const char *)fins_aux_setpoint, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_CRC);
#endif
}

#if MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_fins_aux_setpoint_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t session, uint64_t target_session, uint64_t source_us, uint32_t epoch, uint32_t sequence, uint16_t valid_ms, int8_t cam_yaw, int8_t cam_pitch)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, target_session);
    _mav_put_uint64_t(buf, 16, source_us);
    _mav_put_uint32_t(buf, 24, epoch);
    _mav_put_uint32_t(buf, 28, sequence);
    _mav_put_uint16_t(buf, 32, valid_ms);
    _mav_put_int8_t(buf, 34, cam_yaw);
    _mav_put_int8_t(buf, 35, cam_pitch);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_AUX_SETPOINT, buf, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_CRC);
#else
    mavlink_fins_aux_setpoint_t *packet = (mavlink_fins_aux_setpoint_t *)msgbuf;
    packet->session = session;
    packet->target_session = target_session;
    packet->source_us = source_us;
    packet->epoch = epoch;
    packet->sequence = sequence;
    packet->valid_ms = valid_ms;
    packet->cam_yaw = cam_yaw;
    packet->cam_pitch = cam_pitch;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_AUX_SETPOINT, (const char *)packet, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_MIN_LEN, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_CRC);
#endif
}
#endif

#endif

// MESSAGE FINS_AUX_SETPOINT UNPACKING


/**
 * @brief Get field session from fins_aux_setpoint message
 *
 * @return  PC session.
 */
static inline uint64_t mavlink_msg_fins_aux_setpoint_get_session(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field target_session from fins_aux_setpoint message
 *
 * @return  NX session.
 */
static inline uint64_t mavlink_msg_fins_aux_setpoint_get_target_session(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field source_us from fins_aux_setpoint message
 *
 * @return [us] Synchronized NX clock.
 */
static inline uint64_t mavlink_msg_fins_aux_setpoint_get_source_us(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  16);
}

/**
 * @brief Get field epoch from fins_aux_setpoint message
 *
 * @return  Confirmed generation.
 */
static inline uint32_t mavlink_msg_fins_aux_setpoint_get_epoch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  24);
}

/**
 * @brief Get field sequence from fins_aux_setpoint message
 *
 * @return  Independent auxiliary sequence.
 */
static inline uint32_t mavlink_msg_fins_aux_setpoint_get_sequence(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  28);
}

/**
 * @brief Get field valid_ms from fins_aux_setpoint message
 *
 * @return [ms] At most 200.
 */
static inline uint16_t mavlink_msg_fins_aux_setpoint_get_valid_ms(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  32);
}

/**
 * @brief Get field cam_yaw from fins_aux_setpoint message
 *
 * @return  -1, 0, 1.
 */
static inline int8_t mavlink_msg_fins_aux_setpoint_get_cam_yaw(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  34);
}

/**
 * @brief Get field cam_pitch from fins_aux_setpoint message
 *
 * @return  -1, 0, 1.
 */
static inline int8_t mavlink_msg_fins_aux_setpoint_get_cam_pitch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  35);
}

/**
 * @brief Decode a fins_aux_setpoint message into a struct
 *
 * @param msg The message to decode
 * @param fins_aux_setpoint C-struct to decode the message contents into
 */
static inline void mavlink_msg_fins_aux_setpoint_decode(const mavlink_message_t* msg, mavlink_fins_aux_setpoint_t* fins_aux_setpoint)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    fins_aux_setpoint->session = mavlink_msg_fins_aux_setpoint_get_session(msg);
    fins_aux_setpoint->target_session = mavlink_msg_fins_aux_setpoint_get_target_session(msg);
    fins_aux_setpoint->source_us = mavlink_msg_fins_aux_setpoint_get_source_us(msg);
    fins_aux_setpoint->epoch = mavlink_msg_fins_aux_setpoint_get_epoch(msg);
    fins_aux_setpoint->sequence = mavlink_msg_fins_aux_setpoint_get_sequence(msg);
    fins_aux_setpoint->valid_ms = mavlink_msg_fins_aux_setpoint_get_valid_ms(msg);
    fins_aux_setpoint->cam_yaw = mavlink_msg_fins_aux_setpoint_get_cam_yaw(msg);
    fins_aux_setpoint->cam_pitch = mavlink_msg_fins_aux_setpoint_get_cam_pitch(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN? msg->len : MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN;
        memset(fins_aux_setpoint, 0, MAVLINK_MSG_ID_FINS_AUX_SETPOINT_LEN);
    memcpy(fins_aux_setpoint, _MAV_PAYLOAD(msg), len);
#endif
}
