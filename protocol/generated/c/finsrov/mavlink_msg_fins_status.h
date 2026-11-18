#pragma once
// MESSAGE FINS_STATUS PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_FINS_STATUS 60001


typedef struct __mavlink_fins_status_t {
 uint64_t session; /*<  NX session.*/
 uint64_t client_session; /*<  Current controller session.*/
 uint32_t epoch; /*<  Accepted control generation.*/
 uint32_t faults; /*<  Fault flags; bit 0 setpoint expired.*/
 float depth_target; /*< [m] Positive down.*/
 uint8_t mode; /*<  Actual mode.*/
 uint8_t armed; /*<  Motor enable state.*/
 uint8_t hold_depth; /*<  Depth controller active.*/
 uint8_t camera_light; /*<  Camera light state.*/
 uint8_t frame_light; /*<  Frame light state.*/
} mavlink_fins_status_t;

#define MAVLINK_MSG_ID_FINS_STATUS_LEN 33
#define MAVLINK_MSG_ID_FINS_STATUS_MIN_LEN 33
#define MAVLINK_MSG_ID_60001_LEN 33
#define MAVLINK_MSG_ID_60001_MIN_LEN 33

#define MAVLINK_MSG_ID_FINS_STATUS_CRC 145
#define MAVLINK_MSG_ID_60001_CRC 145



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_FINS_STATUS { \
    60001, \
    "FINS_STATUS", \
    10, \
    {  { "session", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_fins_status_t, session) }, \
         { "client_session", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_fins_status_t, client_session) }, \
         { "epoch", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_fins_status_t, epoch) }, \
         { "faults", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_fins_status_t, faults) }, \
         { "depth_target", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_fins_status_t, depth_target) }, \
         { "mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 28, offsetof(mavlink_fins_status_t, mode) }, \
         { "armed", NULL, MAVLINK_TYPE_UINT8_T, 0, 29, offsetof(mavlink_fins_status_t, armed) }, \
         { "hold_depth", NULL, MAVLINK_TYPE_UINT8_T, 0, 30, offsetof(mavlink_fins_status_t, hold_depth) }, \
         { "camera_light", NULL, MAVLINK_TYPE_UINT8_T, 0, 31, offsetof(mavlink_fins_status_t, camera_light) }, \
         { "frame_light", NULL, MAVLINK_TYPE_UINT8_T, 0, 32, offsetof(mavlink_fins_status_t, frame_light) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_FINS_STATUS { \
    "FINS_STATUS", \
    10, \
    {  { "session", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_fins_status_t, session) }, \
         { "client_session", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_fins_status_t, client_session) }, \
         { "epoch", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_fins_status_t, epoch) }, \
         { "faults", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_fins_status_t, faults) }, \
         { "depth_target", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_fins_status_t, depth_target) }, \
         { "mode", NULL, MAVLINK_TYPE_UINT8_T, 0, 28, offsetof(mavlink_fins_status_t, mode) }, \
         { "armed", NULL, MAVLINK_TYPE_UINT8_T, 0, 29, offsetof(mavlink_fins_status_t, armed) }, \
         { "hold_depth", NULL, MAVLINK_TYPE_UINT8_T, 0, 30, offsetof(mavlink_fins_status_t, hold_depth) }, \
         { "camera_light", NULL, MAVLINK_TYPE_UINT8_T, 0, 31, offsetof(mavlink_fins_status_t, camera_light) }, \
         { "frame_light", NULL, MAVLINK_TYPE_UINT8_T, 0, 32, offsetof(mavlink_fins_status_t, frame_light) }, \
         } \
}
#endif

/**
 * @brief Pack a fins_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param session  NX session.
 * @param client_session  Current controller session.
 * @param epoch  Accepted control generation.
 * @param faults  Fault flags; bit 0 setpoint expired.
 * @param depth_target [m] Positive down.
 * @param mode  Actual mode.
 * @param armed  Motor enable state.
 * @param hold_depth  Depth controller active.
 * @param camera_light  Camera light state.
 * @param frame_light  Frame light state.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t session, uint64_t client_session, uint32_t epoch, uint32_t faults, float depth_target, uint8_t mode, uint8_t armed, uint8_t hold_depth, uint8_t camera_light, uint8_t frame_light)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_STATUS_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, client_session);
    _mav_put_uint32_t(buf, 16, epoch);
    _mav_put_uint32_t(buf, 20, faults);
    _mav_put_float(buf, 24, depth_target);
    _mav_put_uint8_t(buf, 28, mode);
    _mav_put_uint8_t(buf, 29, armed);
    _mav_put_uint8_t(buf, 30, hold_depth);
    _mav_put_uint8_t(buf, 31, camera_light);
    _mav_put_uint8_t(buf, 32, frame_light);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_STATUS_LEN);
#else
    mavlink_fins_status_t packet;
    packet.session = session;
    packet.client_session = client_session;
    packet.epoch = epoch;
    packet.faults = faults;
    packet.depth_target = depth_target;
    packet.mode = mode;
    packet.armed = armed;
    packet.hold_depth = hold_depth;
    packet.camera_light = camera_light;
    packet.frame_light = frame_light;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_FINS_STATUS_MIN_LEN, MAVLINK_MSG_ID_FINS_STATUS_LEN, MAVLINK_MSG_ID_FINS_STATUS_CRC);
}

/**
 * @brief Pack a fins_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param session  NX session.
 * @param client_session  Current controller session.
 * @param epoch  Accepted control generation.
 * @param faults  Fault flags; bit 0 setpoint expired.
 * @param depth_target [m] Positive down.
 * @param mode  Actual mode.
 * @param armed  Motor enable state.
 * @param hold_depth  Depth controller active.
 * @param camera_light  Camera light state.
 * @param frame_light  Frame light state.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_status_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t session, uint64_t client_session, uint32_t epoch, uint32_t faults, float depth_target, uint8_t mode, uint8_t armed, uint8_t hold_depth, uint8_t camera_light, uint8_t frame_light)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_STATUS_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, client_session);
    _mav_put_uint32_t(buf, 16, epoch);
    _mav_put_uint32_t(buf, 20, faults);
    _mav_put_float(buf, 24, depth_target);
    _mav_put_uint8_t(buf, 28, mode);
    _mav_put_uint8_t(buf, 29, armed);
    _mav_put_uint8_t(buf, 30, hold_depth);
    _mav_put_uint8_t(buf, 31, camera_light);
    _mav_put_uint8_t(buf, 32, frame_light);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_STATUS_LEN);
#else
    mavlink_fins_status_t packet;
    packet.session = session;
    packet.client_session = client_session;
    packet.epoch = epoch;
    packet.faults = faults;
    packet.depth_target = depth_target;
    packet.mode = mode;
    packet.armed = armed;
    packet.hold_depth = hold_depth;
    packet.camera_light = camera_light;
    packet.frame_light = frame_light;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FINS_STATUS_MIN_LEN, MAVLINK_MSG_ID_FINS_STATUS_LEN, MAVLINK_MSG_ID_FINS_STATUS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FINS_STATUS_MIN_LEN, MAVLINK_MSG_ID_FINS_STATUS_LEN);
#endif
}

/**
 * @brief Pack a fins_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param session  NX session.
 * @param client_session  Current controller session.
 * @param epoch  Accepted control generation.
 * @param faults  Fault flags; bit 0 setpoint expired.
 * @param depth_target [m] Positive down.
 * @param mode  Actual mode.
 * @param armed  Motor enable state.
 * @param hold_depth  Depth controller active.
 * @param camera_light  Camera light state.
 * @param frame_light  Frame light state.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t session,uint64_t client_session,uint32_t epoch,uint32_t faults,float depth_target,uint8_t mode,uint8_t armed,uint8_t hold_depth,uint8_t camera_light,uint8_t frame_light)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_STATUS_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, client_session);
    _mav_put_uint32_t(buf, 16, epoch);
    _mav_put_uint32_t(buf, 20, faults);
    _mav_put_float(buf, 24, depth_target);
    _mav_put_uint8_t(buf, 28, mode);
    _mav_put_uint8_t(buf, 29, armed);
    _mav_put_uint8_t(buf, 30, hold_depth);
    _mav_put_uint8_t(buf, 31, camera_light);
    _mav_put_uint8_t(buf, 32, frame_light);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_STATUS_LEN);
#else
    mavlink_fins_status_t packet;
    packet.session = session;
    packet.client_session = client_session;
    packet.epoch = epoch;
    packet.faults = faults;
    packet.depth_target = depth_target;
    packet.mode = mode;
    packet.armed = armed;
    packet.hold_depth = hold_depth;
    packet.camera_light = camera_light;
    packet.frame_light = frame_light;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_FINS_STATUS_MIN_LEN, MAVLINK_MSG_ID_FINS_STATUS_LEN, MAVLINK_MSG_ID_FINS_STATUS_CRC);
}

/**
 * @brief Encode a fins_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param fins_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_fins_status_t* fins_status)
{
    return mavlink_msg_fins_status_pack(system_id, component_id, msg, fins_status->session, fins_status->client_session, fins_status->epoch, fins_status->faults, fins_status->depth_target, fins_status->mode, fins_status->armed, fins_status->hold_depth, fins_status->camera_light, fins_status->frame_light);
}

/**
 * @brief Encode a fins_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param fins_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_fins_status_t* fins_status)
{
    return mavlink_msg_fins_status_pack_chan(system_id, component_id, chan, msg, fins_status->session, fins_status->client_session, fins_status->epoch, fins_status->faults, fins_status->depth_target, fins_status->mode, fins_status->armed, fins_status->hold_depth, fins_status->camera_light, fins_status->frame_light);
}

/**
 * @brief Encode a fins_status struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param fins_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_status_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_fins_status_t* fins_status)
{
    return mavlink_msg_fins_status_pack_status(system_id, component_id, _status, msg,  fins_status->session, fins_status->client_session, fins_status->epoch, fins_status->faults, fins_status->depth_target, fins_status->mode, fins_status->armed, fins_status->hold_depth, fins_status->camera_light, fins_status->frame_light);
}

/**
 * @brief Send a fins_status message
 * @param chan MAVLink channel to send the message
 *
 * @param session  NX session.
 * @param client_session  Current controller session.
 * @param epoch  Accepted control generation.
 * @param faults  Fault flags; bit 0 setpoint expired.
 * @param depth_target [m] Positive down.
 * @param mode  Actual mode.
 * @param armed  Motor enable state.
 * @param hold_depth  Depth controller active.
 * @param camera_light  Camera light state.
 * @param frame_light  Frame light state.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_fins_status_send(mavlink_channel_t chan, uint64_t session, uint64_t client_session, uint32_t epoch, uint32_t faults, float depth_target, uint8_t mode, uint8_t armed, uint8_t hold_depth, uint8_t camera_light, uint8_t frame_light)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_STATUS_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, client_session);
    _mav_put_uint32_t(buf, 16, epoch);
    _mav_put_uint32_t(buf, 20, faults);
    _mav_put_float(buf, 24, depth_target);
    _mav_put_uint8_t(buf, 28, mode);
    _mav_put_uint8_t(buf, 29, armed);
    _mav_put_uint8_t(buf, 30, hold_depth);
    _mav_put_uint8_t(buf, 31, camera_light);
    _mav_put_uint8_t(buf, 32, frame_light);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_STATUS, buf, MAVLINK_MSG_ID_FINS_STATUS_MIN_LEN, MAVLINK_MSG_ID_FINS_STATUS_LEN, MAVLINK_MSG_ID_FINS_STATUS_CRC);
#else
    mavlink_fins_status_t packet;
    packet.session = session;
    packet.client_session = client_session;
    packet.epoch = epoch;
    packet.faults = faults;
    packet.depth_target = depth_target;
    packet.mode = mode;
    packet.armed = armed;
    packet.hold_depth = hold_depth;
    packet.camera_light = camera_light;
    packet.frame_light = frame_light;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_STATUS, (const char *)&packet, MAVLINK_MSG_ID_FINS_STATUS_MIN_LEN, MAVLINK_MSG_ID_FINS_STATUS_LEN, MAVLINK_MSG_ID_FINS_STATUS_CRC);
#endif
}

/**
 * @brief Send a fins_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_fins_status_send_struct(mavlink_channel_t chan, const mavlink_fins_status_t* fins_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_fins_status_send(chan, fins_status->session, fins_status->client_session, fins_status->epoch, fins_status->faults, fins_status->depth_target, fins_status->mode, fins_status->armed, fins_status->hold_depth, fins_status->camera_light, fins_status->frame_light);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_STATUS, (const char *)fins_status, MAVLINK_MSG_ID_FINS_STATUS_MIN_LEN, MAVLINK_MSG_ID_FINS_STATUS_LEN, MAVLINK_MSG_ID_FINS_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_FINS_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_fins_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t session, uint64_t client_session, uint32_t epoch, uint32_t faults, float depth_target, uint8_t mode, uint8_t armed, uint8_t hold_depth, uint8_t camera_light, uint8_t frame_light)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, client_session);
    _mav_put_uint32_t(buf, 16, epoch);
    _mav_put_uint32_t(buf, 20, faults);
    _mav_put_float(buf, 24, depth_target);
    _mav_put_uint8_t(buf, 28, mode);
    _mav_put_uint8_t(buf, 29, armed);
    _mav_put_uint8_t(buf, 30, hold_depth);
    _mav_put_uint8_t(buf, 31, camera_light);
    _mav_put_uint8_t(buf, 32, frame_light);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_STATUS, buf, MAVLINK_MSG_ID_FINS_STATUS_MIN_LEN, MAVLINK_MSG_ID_FINS_STATUS_LEN, MAVLINK_MSG_ID_FINS_STATUS_CRC);
#else
    mavlink_fins_status_t *packet = (mavlink_fins_status_t *)msgbuf;
    packet->session = session;
    packet->client_session = client_session;
    packet->epoch = epoch;
    packet->faults = faults;
    packet->depth_target = depth_target;
    packet->mode = mode;
    packet->armed = armed;
    packet->hold_depth = hold_depth;
    packet->camera_light = camera_light;
    packet->frame_light = frame_light;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_STATUS, (const char *)packet, MAVLINK_MSG_ID_FINS_STATUS_MIN_LEN, MAVLINK_MSG_ID_FINS_STATUS_LEN, MAVLINK_MSG_ID_FINS_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE FINS_STATUS UNPACKING


/**
 * @brief Get field session from fins_status message
 *
 * @return  NX session.
 */
static inline uint64_t mavlink_msg_fins_status_get_session(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field client_session from fins_status message
 *
 * @return  Current controller session.
 */
static inline uint64_t mavlink_msg_fins_status_get_client_session(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field epoch from fins_status message
 *
 * @return  Accepted control generation.
 */
static inline uint32_t mavlink_msg_fins_status_get_epoch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  16);
}

/**
 * @brief Get field faults from fins_status message
 *
 * @return  Fault flags; bit 0 setpoint expired.
 */
static inline uint32_t mavlink_msg_fins_status_get_faults(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  20);
}

/**
 * @brief Get field depth_target from fins_status message
 *
 * @return [m] Positive down.
 */
static inline float mavlink_msg_fins_status_get_depth_target(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field mode from fins_status message
 *
 * @return  Actual mode.
 */
static inline uint8_t mavlink_msg_fins_status_get_mode(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  28);
}

/**
 * @brief Get field armed from fins_status message
 *
 * @return  Motor enable state.
 */
static inline uint8_t mavlink_msg_fins_status_get_armed(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  29);
}

/**
 * @brief Get field hold_depth from fins_status message
 *
 * @return  Depth controller active.
 */
static inline uint8_t mavlink_msg_fins_status_get_hold_depth(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  30);
}

/**
 * @brief Get field camera_light from fins_status message
 *
 * @return  Camera light state.
 */
static inline uint8_t mavlink_msg_fins_status_get_camera_light(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  31);
}

/**
 * @brief Get field frame_light from fins_status message
 *
 * @return  Frame light state.
 */
static inline uint8_t mavlink_msg_fins_status_get_frame_light(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  32);
}

/**
 * @brief Decode a fins_status message into a struct
 *
 * @param msg The message to decode
 * @param fins_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_fins_status_decode(const mavlink_message_t* msg, mavlink_fins_status_t* fins_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    fins_status->session = mavlink_msg_fins_status_get_session(msg);
    fins_status->client_session = mavlink_msg_fins_status_get_client_session(msg);
    fins_status->epoch = mavlink_msg_fins_status_get_epoch(msg);
    fins_status->faults = mavlink_msg_fins_status_get_faults(msg);
    fins_status->depth_target = mavlink_msg_fins_status_get_depth_target(msg);
    fins_status->mode = mavlink_msg_fins_status_get_mode(msg);
    fins_status->armed = mavlink_msg_fins_status_get_armed(msg);
    fins_status->hold_depth = mavlink_msg_fins_status_get_hold_depth(msg);
    fins_status->camera_light = mavlink_msg_fins_status_get_camera_light(msg);
    fins_status->frame_light = mavlink_msg_fins_status_get_frame_light(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_FINS_STATUS_LEN? msg->len : MAVLINK_MSG_ID_FINS_STATUS_LEN;
        memset(fins_status, 0, MAVLINK_MSG_ID_FINS_STATUS_LEN);
    memcpy(fins_status, _MAV_PAYLOAD(msg), len);
#endif
}
