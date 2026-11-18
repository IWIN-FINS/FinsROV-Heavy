#pragma once
// MESSAGE FINS_ACTION_REQUEST PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_FINS_ACTION_REQUEST 60004


typedef struct __mavlink_fins_action_request_t {
 uint64_t session; /*<  PC session.*/
 uint64_t target_session; /*<  NX session.*/
 uint32_t request_id; /*<  Unique per session.*/
 uint32_t epoch; /*<  New generation for SET_MODE; current generation otherwise.*/
 uint8_t action; /*<  Requested action.*/
 uint8_t value; /*<  Desired mode or boolean state.*/
} mavlink_fins_action_request_t;

#define MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN 26
#define MAVLINK_MSG_ID_FINS_ACTION_REQUEST_MIN_LEN 26
#define MAVLINK_MSG_ID_60004_LEN 26
#define MAVLINK_MSG_ID_60004_MIN_LEN 26

#define MAVLINK_MSG_ID_FINS_ACTION_REQUEST_CRC 116
#define MAVLINK_MSG_ID_60004_CRC 116



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_FINS_ACTION_REQUEST { \
    60004, \
    "FINS_ACTION_REQUEST", \
    6, \
    {  { "session", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_fins_action_request_t, session) }, \
         { "target_session", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_fins_action_request_t, target_session) }, \
         { "request_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_fins_action_request_t, request_id) }, \
         { "epoch", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_fins_action_request_t, epoch) }, \
         { "action", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_fins_action_request_t, action) }, \
         { "value", NULL, MAVLINK_TYPE_UINT8_T, 0, 25, offsetof(mavlink_fins_action_request_t, value) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_FINS_ACTION_REQUEST { \
    "FINS_ACTION_REQUEST", \
    6, \
    {  { "session", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_fins_action_request_t, session) }, \
         { "target_session", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_fins_action_request_t, target_session) }, \
         { "request_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_fins_action_request_t, request_id) }, \
         { "epoch", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_fins_action_request_t, epoch) }, \
         { "action", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_fins_action_request_t, action) }, \
         { "value", NULL, MAVLINK_TYPE_UINT8_T, 0, 25, offsetof(mavlink_fins_action_request_t, value) }, \
         } \
}
#endif

/**
 * @brief Pack a fins_action_request message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param session  PC session.
 * @param target_session  NX session.
 * @param request_id  Unique per session.
 * @param epoch  New generation for SET_MODE; current generation otherwise.
 * @param action  Requested action.
 * @param value  Desired mode or boolean state.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_action_request_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t session, uint64_t target_session, uint32_t request_id, uint32_t epoch, uint8_t action, uint8_t value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, target_session);
    _mav_put_uint32_t(buf, 16, request_id);
    _mav_put_uint32_t(buf, 20, epoch);
    _mav_put_uint8_t(buf, 24, action);
    _mav_put_uint8_t(buf, 25, value);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN);
#else
    mavlink_fins_action_request_t packet;
    packet.session = session;
    packet.target_session = target_session;
    packet.request_id = request_id;
    packet.epoch = epoch;
    packet.action = action;
    packet.value = value;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_ACTION_REQUEST;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_MIN_LEN, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_CRC);
}

/**
 * @brief Pack a fins_action_request message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param session  PC session.
 * @param target_session  NX session.
 * @param request_id  Unique per session.
 * @param epoch  New generation for SET_MODE; current generation otherwise.
 * @param action  Requested action.
 * @param value  Desired mode or boolean state.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_action_request_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t session, uint64_t target_session, uint32_t request_id, uint32_t epoch, uint8_t action, uint8_t value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, target_session);
    _mav_put_uint32_t(buf, 16, request_id);
    _mav_put_uint32_t(buf, 20, epoch);
    _mav_put_uint8_t(buf, 24, action);
    _mav_put_uint8_t(buf, 25, value);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN);
#else
    mavlink_fins_action_request_t packet;
    packet.session = session;
    packet.target_session = target_session;
    packet.request_id = request_id;
    packet.epoch = epoch;
    packet.action = action;
    packet.value = value;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_ACTION_REQUEST;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_MIN_LEN, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_MIN_LEN, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN);
#endif
}

/**
 * @brief Pack a fins_action_request message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param session  PC session.
 * @param target_session  NX session.
 * @param request_id  Unique per session.
 * @param epoch  New generation for SET_MODE; current generation otherwise.
 * @param action  Requested action.
 * @param value  Desired mode or boolean state.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_action_request_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t session,uint64_t target_session,uint32_t request_id,uint32_t epoch,uint8_t action,uint8_t value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, target_session);
    _mav_put_uint32_t(buf, 16, request_id);
    _mav_put_uint32_t(buf, 20, epoch);
    _mav_put_uint8_t(buf, 24, action);
    _mav_put_uint8_t(buf, 25, value);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN);
#else
    mavlink_fins_action_request_t packet;
    packet.session = session;
    packet.target_session = target_session;
    packet.request_id = request_id;
    packet.epoch = epoch;
    packet.action = action;
    packet.value = value;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_ACTION_REQUEST;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_MIN_LEN, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_CRC);
}

/**
 * @brief Encode a fins_action_request struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param fins_action_request C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_action_request_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_fins_action_request_t* fins_action_request)
{
    return mavlink_msg_fins_action_request_pack(system_id, component_id, msg, fins_action_request->session, fins_action_request->target_session, fins_action_request->request_id, fins_action_request->epoch, fins_action_request->action, fins_action_request->value);
}

/**
 * @brief Encode a fins_action_request struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param fins_action_request C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_action_request_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_fins_action_request_t* fins_action_request)
{
    return mavlink_msg_fins_action_request_pack_chan(system_id, component_id, chan, msg, fins_action_request->session, fins_action_request->target_session, fins_action_request->request_id, fins_action_request->epoch, fins_action_request->action, fins_action_request->value);
}

/**
 * @brief Encode a fins_action_request struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param fins_action_request C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_action_request_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_fins_action_request_t* fins_action_request)
{
    return mavlink_msg_fins_action_request_pack_status(system_id, component_id, _status, msg,  fins_action_request->session, fins_action_request->target_session, fins_action_request->request_id, fins_action_request->epoch, fins_action_request->action, fins_action_request->value);
}

/**
 * @brief Send a fins_action_request message
 * @param chan MAVLink channel to send the message
 *
 * @param session  PC session.
 * @param target_session  NX session.
 * @param request_id  Unique per session.
 * @param epoch  New generation for SET_MODE; current generation otherwise.
 * @param action  Requested action.
 * @param value  Desired mode or boolean state.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_fins_action_request_send(mavlink_channel_t chan, uint64_t session, uint64_t target_session, uint32_t request_id, uint32_t epoch, uint8_t action, uint8_t value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, target_session);
    _mav_put_uint32_t(buf, 16, request_id);
    _mav_put_uint32_t(buf, 20, epoch);
    _mav_put_uint8_t(buf, 24, action);
    _mav_put_uint8_t(buf, 25, value);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_ACTION_REQUEST, buf, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_MIN_LEN, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_CRC);
#else
    mavlink_fins_action_request_t packet;
    packet.session = session;
    packet.target_session = target_session;
    packet.request_id = request_id;
    packet.epoch = epoch;
    packet.action = action;
    packet.value = value;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_ACTION_REQUEST, (const char *)&packet, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_MIN_LEN, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_CRC);
#endif
}

/**
 * @brief Send a fins_action_request message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_fins_action_request_send_struct(mavlink_channel_t chan, const mavlink_fins_action_request_t* fins_action_request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_fins_action_request_send(chan, fins_action_request->session, fins_action_request->target_session, fins_action_request->request_id, fins_action_request->epoch, fins_action_request->action, fins_action_request->value);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_ACTION_REQUEST, (const char *)fins_action_request, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_MIN_LEN, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_CRC);
#endif
}

#if MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_fins_action_request_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t session, uint64_t target_session, uint32_t request_id, uint32_t epoch, uint8_t action, uint8_t value)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, target_session);
    _mav_put_uint32_t(buf, 16, request_id);
    _mav_put_uint32_t(buf, 20, epoch);
    _mav_put_uint8_t(buf, 24, action);
    _mav_put_uint8_t(buf, 25, value);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_ACTION_REQUEST, buf, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_MIN_LEN, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_CRC);
#else
    mavlink_fins_action_request_t *packet = (mavlink_fins_action_request_t *)msgbuf;
    packet->session = session;
    packet->target_session = target_session;
    packet->request_id = request_id;
    packet->epoch = epoch;
    packet->action = action;
    packet->value = value;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_ACTION_REQUEST, (const char *)packet, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_MIN_LEN, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_CRC);
#endif
}
#endif

#endif

// MESSAGE FINS_ACTION_REQUEST UNPACKING


/**
 * @brief Get field session from fins_action_request message
 *
 * @return  PC session.
 */
static inline uint64_t mavlink_msg_fins_action_request_get_session(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field target_session from fins_action_request message
 *
 * @return  NX session.
 */
static inline uint64_t mavlink_msg_fins_action_request_get_target_session(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field request_id from fins_action_request message
 *
 * @return  Unique per session.
 */
static inline uint32_t mavlink_msg_fins_action_request_get_request_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  16);
}

/**
 * @brief Get field epoch from fins_action_request message
 *
 * @return  New generation for SET_MODE; current generation otherwise.
 */
static inline uint32_t mavlink_msg_fins_action_request_get_epoch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  20);
}

/**
 * @brief Get field action from fins_action_request message
 *
 * @return  Requested action.
 */
static inline uint8_t mavlink_msg_fins_action_request_get_action(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  24);
}

/**
 * @brief Get field value from fins_action_request message
 *
 * @return  Desired mode or boolean state.
 */
static inline uint8_t mavlink_msg_fins_action_request_get_value(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  25);
}

/**
 * @brief Decode a fins_action_request message into a struct
 *
 * @param msg The message to decode
 * @param fins_action_request C-struct to decode the message contents into
 */
static inline void mavlink_msg_fins_action_request_decode(const mavlink_message_t* msg, mavlink_fins_action_request_t* fins_action_request)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    fins_action_request->session = mavlink_msg_fins_action_request_get_session(msg);
    fins_action_request->target_session = mavlink_msg_fins_action_request_get_target_session(msg);
    fins_action_request->request_id = mavlink_msg_fins_action_request_get_request_id(msg);
    fins_action_request->epoch = mavlink_msg_fins_action_request_get_epoch(msg);
    fins_action_request->action = mavlink_msg_fins_action_request_get_action(msg);
    fins_action_request->value = mavlink_msg_fins_action_request_get_value(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN? msg->len : MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN;
        memset(fins_action_request, 0, MAVLINK_MSG_ID_FINS_ACTION_REQUEST_LEN);
    memcpy(fins_action_request, _MAV_PAYLOAD(msg), len);
#endif
}
