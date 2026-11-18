#pragma once
// MESSAGE FINS_ACTION_ACK PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_FINS_ACTION_ACK 60005


typedef struct __mavlink_fins_action_ack_t {
 uint64_t session; /*<  NX session.*/
 uint64_t target_session; /*<  PC session.*/
 uint32_t request_id; /*<  Echo request ID.*/
 uint32_t epoch; /*<  Echo requested generation.*/
 uint8_t action; /*<  Echo action.*/
 uint8_t result; /*<  Execution result.*/
 uint8_t reason; /*<  Machine-readable rejection reason.*/
} mavlink_fins_action_ack_t;

#define MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN 27
#define MAVLINK_MSG_ID_FINS_ACTION_ACK_MIN_LEN 27
#define MAVLINK_MSG_ID_60005_LEN 27
#define MAVLINK_MSG_ID_60005_MIN_LEN 27

#define MAVLINK_MSG_ID_FINS_ACTION_ACK_CRC 236
#define MAVLINK_MSG_ID_60005_CRC 236



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_FINS_ACTION_ACK { \
    60005, \
    "FINS_ACTION_ACK", \
    7, \
    {  { "session", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_fins_action_ack_t, session) }, \
         { "target_session", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_fins_action_ack_t, target_session) }, \
         { "request_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_fins_action_ack_t, request_id) }, \
         { "epoch", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_fins_action_ack_t, epoch) }, \
         { "action", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_fins_action_ack_t, action) }, \
         { "result", NULL, MAVLINK_TYPE_UINT8_T, 0, 25, offsetof(mavlink_fins_action_ack_t, result) }, \
         { "reason", NULL, MAVLINK_TYPE_UINT8_T, 0, 26, offsetof(mavlink_fins_action_ack_t, reason) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_FINS_ACTION_ACK { \
    "FINS_ACTION_ACK", \
    7, \
    {  { "session", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_fins_action_ack_t, session) }, \
         { "target_session", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_fins_action_ack_t, target_session) }, \
         { "request_id", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_fins_action_ack_t, request_id) }, \
         { "epoch", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_fins_action_ack_t, epoch) }, \
         { "action", NULL, MAVLINK_TYPE_UINT8_T, 0, 24, offsetof(mavlink_fins_action_ack_t, action) }, \
         { "result", NULL, MAVLINK_TYPE_UINT8_T, 0, 25, offsetof(mavlink_fins_action_ack_t, result) }, \
         { "reason", NULL, MAVLINK_TYPE_UINT8_T, 0, 26, offsetof(mavlink_fins_action_ack_t, reason) }, \
         } \
}
#endif

/**
 * @brief Pack a fins_action_ack message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param session  NX session.
 * @param target_session  PC session.
 * @param request_id  Echo request ID.
 * @param epoch  Echo requested generation.
 * @param action  Echo action.
 * @param result  Execution result.
 * @param reason  Machine-readable rejection reason.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_action_ack_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t session, uint64_t target_session, uint32_t request_id, uint32_t epoch, uint8_t action, uint8_t result, uint8_t reason)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, target_session);
    _mav_put_uint32_t(buf, 16, request_id);
    _mav_put_uint32_t(buf, 20, epoch);
    _mav_put_uint8_t(buf, 24, action);
    _mav_put_uint8_t(buf, 25, result);
    _mav_put_uint8_t(buf, 26, reason);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN);
#else
    mavlink_fins_action_ack_t packet;
    packet.session = session;
    packet.target_session = target_session;
    packet.request_id = request_id;
    packet.epoch = epoch;
    packet.action = action;
    packet.result = result;
    packet.reason = reason;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_ACTION_ACK;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_FINS_ACTION_ACK_MIN_LEN, MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN, MAVLINK_MSG_ID_FINS_ACTION_ACK_CRC);
}

/**
 * @brief Pack a fins_action_ack message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param session  NX session.
 * @param target_session  PC session.
 * @param request_id  Echo request ID.
 * @param epoch  Echo requested generation.
 * @param action  Echo action.
 * @param result  Execution result.
 * @param reason  Machine-readable rejection reason.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_action_ack_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t session, uint64_t target_session, uint32_t request_id, uint32_t epoch, uint8_t action, uint8_t result, uint8_t reason)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, target_session);
    _mav_put_uint32_t(buf, 16, request_id);
    _mav_put_uint32_t(buf, 20, epoch);
    _mav_put_uint8_t(buf, 24, action);
    _mav_put_uint8_t(buf, 25, result);
    _mav_put_uint8_t(buf, 26, reason);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN);
#else
    mavlink_fins_action_ack_t packet;
    packet.session = session;
    packet.target_session = target_session;
    packet.request_id = request_id;
    packet.epoch = epoch;
    packet.action = action;
    packet.result = result;
    packet.reason = reason;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_ACTION_ACK;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FINS_ACTION_ACK_MIN_LEN, MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN, MAVLINK_MSG_ID_FINS_ACTION_ACK_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FINS_ACTION_ACK_MIN_LEN, MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN);
#endif
}

/**
 * @brief Pack a fins_action_ack message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param session  NX session.
 * @param target_session  PC session.
 * @param request_id  Echo request ID.
 * @param epoch  Echo requested generation.
 * @param action  Echo action.
 * @param result  Execution result.
 * @param reason  Machine-readable rejection reason.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_action_ack_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t session,uint64_t target_session,uint32_t request_id,uint32_t epoch,uint8_t action,uint8_t result,uint8_t reason)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, target_session);
    _mav_put_uint32_t(buf, 16, request_id);
    _mav_put_uint32_t(buf, 20, epoch);
    _mav_put_uint8_t(buf, 24, action);
    _mav_put_uint8_t(buf, 25, result);
    _mav_put_uint8_t(buf, 26, reason);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN);
#else
    mavlink_fins_action_ack_t packet;
    packet.session = session;
    packet.target_session = target_session;
    packet.request_id = request_id;
    packet.epoch = epoch;
    packet.action = action;
    packet.result = result;
    packet.reason = reason;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_ACTION_ACK;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_FINS_ACTION_ACK_MIN_LEN, MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN, MAVLINK_MSG_ID_FINS_ACTION_ACK_CRC);
}

/**
 * @brief Encode a fins_action_ack struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param fins_action_ack C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_action_ack_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_fins_action_ack_t* fins_action_ack)
{
    return mavlink_msg_fins_action_ack_pack(system_id, component_id, msg, fins_action_ack->session, fins_action_ack->target_session, fins_action_ack->request_id, fins_action_ack->epoch, fins_action_ack->action, fins_action_ack->result, fins_action_ack->reason);
}

/**
 * @brief Encode a fins_action_ack struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param fins_action_ack C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_action_ack_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_fins_action_ack_t* fins_action_ack)
{
    return mavlink_msg_fins_action_ack_pack_chan(system_id, component_id, chan, msg, fins_action_ack->session, fins_action_ack->target_session, fins_action_ack->request_id, fins_action_ack->epoch, fins_action_ack->action, fins_action_ack->result, fins_action_ack->reason);
}

/**
 * @brief Encode a fins_action_ack struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param fins_action_ack C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_action_ack_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_fins_action_ack_t* fins_action_ack)
{
    return mavlink_msg_fins_action_ack_pack_status(system_id, component_id, _status, msg,  fins_action_ack->session, fins_action_ack->target_session, fins_action_ack->request_id, fins_action_ack->epoch, fins_action_ack->action, fins_action_ack->result, fins_action_ack->reason);
}

/**
 * @brief Send a fins_action_ack message
 * @param chan MAVLink channel to send the message
 *
 * @param session  NX session.
 * @param target_session  PC session.
 * @param request_id  Echo request ID.
 * @param epoch  Echo requested generation.
 * @param action  Echo action.
 * @param result  Execution result.
 * @param reason  Machine-readable rejection reason.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_fins_action_ack_send(mavlink_channel_t chan, uint64_t session, uint64_t target_session, uint32_t request_id, uint32_t epoch, uint8_t action, uint8_t result, uint8_t reason)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, target_session);
    _mav_put_uint32_t(buf, 16, request_id);
    _mav_put_uint32_t(buf, 20, epoch);
    _mav_put_uint8_t(buf, 24, action);
    _mav_put_uint8_t(buf, 25, result);
    _mav_put_uint8_t(buf, 26, reason);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_ACTION_ACK, buf, MAVLINK_MSG_ID_FINS_ACTION_ACK_MIN_LEN, MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN, MAVLINK_MSG_ID_FINS_ACTION_ACK_CRC);
#else
    mavlink_fins_action_ack_t packet;
    packet.session = session;
    packet.target_session = target_session;
    packet.request_id = request_id;
    packet.epoch = epoch;
    packet.action = action;
    packet.result = result;
    packet.reason = reason;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_ACTION_ACK, (const char *)&packet, MAVLINK_MSG_ID_FINS_ACTION_ACK_MIN_LEN, MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN, MAVLINK_MSG_ID_FINS_ACTION_ACK_CRC);
#endif
}

/**
 * @brief Send a fins_action_ack message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_fins_action_ack_send_struct(mavlink_channel_t chan, const mavlink_fins_action_ack_t* fins_action_ack)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_fins_action_ack_send(chan, fins_action_ack->session, fins_action_ack->target_session, fins_action_ack->request_id, fins_action_ack->epoch, fins_action_ack->action, fins_action_ack->result, fins_action_ack->reason);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_ACTION_ACK, (const char *)fins_action_ack, MAVLINK_MSG_ID_FINS_ACTION_ACK_MIN_LEN, MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN, MAVLINK_MSG_ID_FINS_ACTION_ACK_CRC);
#endif
}

#if MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_fins_action_ack_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t session, uint64_t target_session, uint32_t request_id, uint32_t epoch, uint8_t action, uint8_t result, uint8_t reason)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint64_t(buf, 8, target_session);
    _mav_put_uint32_t(buf, 16, request_id);
    _mav_put_uint32_t(buf, 20, epoch);
    _mav_put_uint8_t(buf, 24, action);
    _mav_put_uint8_t(buf, 25, result);
    _mav_put_uint8_t(buf, 26, reason);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_ACTION_ACK, buf, MAVLINK_MSG_ID_FINS_ACTION_ACK_MIN_LEN, MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN, MAVLINK_MSG_ID_FINS_ACTION_ACK_CRC);
#else
    mavlink_fins_action_ack_t *packet = (mavlink_fins_action_ack_t *)msgbuf;
    packet->session = session;
    packet->target_session = target_session;
    packet->request_id = request_id;
    packet->epoch = epoch;
    packet->action = action;
    packet->result = result;
    packet->reason = reason;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_ACTION_ACK, (const char *)packet, MAVLINK_MSG_ID_FINS_ACTION_ACK_MIN_LEN, MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN, MAVLINK_MSG_ID_FINS_ACTION_ACK_CRC);
#endif
}
#endif

#endif

// MESSAGE FINS_ACTION_ACK UNPACKING


/**
 * @brief Get field session from fins_action_ack message
 *
 * @return  NX session.
 */
static inline uint64_t mavlink_msg_fins_action_ack_get_session(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field target_session from fins_action_ack message
 *
 * @return  PC session.
 */
static inline uint64_t mavlink_msg_fins_action_ack_get_target_session(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field request_id from fins_action_ack message
 *
 * @return  Echo request ID.
 */
static inline uint32_t mavlink_msg_fins_action_ack_get_request_id(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  16);
}

/**
 * @brief Get field epoch from fins_action_ack message
 *
 * @return  Echo requested generation.
 */
static inline uint32_t mavlink_msg_fins_action_ack_get_epoch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  20);
}

/**
 * @brief Get field action from fins_action_ack message
 *
 * @return  Echo action.
 */
static inline uint8_t mavlink_msg_fins_action_ack_get_action(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  24);
}

/**
 * @brief Get field result from fins_action_ack message
 *
 * @return  Execution result.
 */
static inline uint8_t mavlink_msg_fins_action_ack_get_result(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  25);
}

/**
 * @brief Get field reason from fins_action_ack message
 *
 * @return  Machine-readable rejection reason.
 */
static inline uint8_t mavlink_msg_fins_action_ack_get_reason(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  26);
}

/**
 * @brief Decode a fins_action_ack message into a struct
 *
 * @param msg The message to decode
 * @param fins_action_ack C-struct to decode the message contents into
 */
static inline void mavlink_msg_fins_action_ack_decode(const mavlink_message_t* msg, mavlink_fins_action_ack_t* fins_action_ack)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    fins_action_ack->session = mavlink_msg_fins_action_ack_get_session(msg);
    fins_action_ack->target_session = mavlink_msg_fins_action_ack_get_target_session(msg);
    fins_action_ack->request_id = mavlink_msg_fins_action_ack_get_request_id(msg);
    fins_action_ack->epoch = mavlink_msg_fins_action_ack_get_epoch(msg);
    fins_action_ack->action = mavlink_msg_fins_action_ack_get_action(msg);
    fins_action_ack->result = mavlink_msg_fins_action_ack_get_result(msg);
    fins_action_ack->reason = mavlink_msg_fins_action_ack_get_reason(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN? msg->len : MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN;
        memset(fins_action_ack, 0, MAVLINK_MSG_ID_FINS_ACTION_ACK_LEN);
    memcpy(fins_action_ack, _MAV_PAYLOAD(msg), len);
#endif
}
