#pragma once
// MESSAGE FINS_CAPABILITIES PACKING

#include <stdint.h>

#define MAVLINK_MSG_ID_FINS_CAPABILITIES 60000


typedef struct __mavlink_fins_capabilities_t {
 uint64_t session; /*<  Random boot/session identity.*/
 uint32_t mode_mask; /*<  Bits 0 idle, 1 manual, 2 trajectory. Zero for ground station.*/
 uint32_t features; /*<  Bit 0 depth hold, 1 auxiliary controls.*/
 uint16_t protocol_version; /*<  Application contract version, currently 1.*/
 uint8_t simulated; /*<  One for simulator, zero for real hardware.*/
} mavlink_fins_capabilities_t;

#define MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN 19
#define MAVLINK_MSG_ID_FINS_CAPABILITIES_MIN_LEN 19
#define MAVLINK_MSG_ID_60000_LEN 19
#define MAVLINK_MSG_ID_60000_MIN_LEN 19

#define MAVLINK_MSG_ID_FINS_CAPABILITIES_CRC 145
#define MAVLINK_MSG_ID_60000_CRC 145



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_FINS_CAPABILITIES { \
    60000, \
    "FINS_CAPABILITIES", \
    5, \
    {  { "session", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_fins_capabilities_t, session) }, \
         { "protocol_version", NULL, MAVLINK_TYPE_UINT16_T, 0, 16, offsetof(mavlink_fins_capabilities_t, protocol_version) }, \
         { "mode_mask", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_fins_capabilities_t, mode_mask) }, \
         { "features", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_fins_capabilities_t, features) }, \
         { "simulated", NULL, MAVLINK_TYPE_UINT8_T, 0, 18, offsetof(mavlink_fins_capabilities_t, simulated) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_FINS_CAPABILITIES { \
    "FINS_CAPABILITIES", \
    5, \
    {  { "session", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_fins_capabilities_t, session) }, \
         { "protocol_version", NULL, MAVLINK_TYPE_UINT16_T, 0, 16, offsetof(mavlink_fins_capabilities_t, protocol_version) }, \
         { "mode_mask", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_fins_capabilities_t, mode_mask) }, \
         { "features", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_fins_capabilities_t, features) }, \
         { "simulated", NULL, MAVLINK_TYPE_UINT8_T, 0, 18, offsetof(mavlink_fins_capabilities_t, simulated) }, \
         } \
}
#endif

/**
 * @brief Pack a fins_capabilities message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param session  Random boot/session identity.
 * @param protocol_version  Application contract version, currently 1.
 * @param mode_mask  Bits 0 idle, 1 manual, 2 trajectory. Zero for ground station.
 * @param features  Bit 0 depth hold, 1 auxiliary controls.
 * @param simulated  One for simulator, zero for real hardware.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_capabilities_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t session, uint16_t protocol_version, uint32_t mode_mask, uint32_t features, uint8_t simulated)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint32_t(buf, 8, mode_mask);
    _mav_put_uint32_t(buf, 12, features);
    _mav_put_uint16_t(buf, 16, protocol_version);
    _mav_put_uint8_t(buf, 18, simulated);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN);
#else
    mavlink_fins_capabilities_t packet;
    packet.session = session;
    packet.mode_mask = mode_mask;
    packet.features = features;
    packet.protocol_version = protocol_version;
    packet.simulated = simulated;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_CAPABILITIES;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_FINS_CAPABILITIES_MIN_LEN, MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN, MAVLINK_MSG_ID_FINS_CAPABILITIES_CRC);
}

/**
 * @brief Pack a fins_capabilities message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param session  Random boot/session identity.
 * @param protocol_version  Application contract version, currently 1.
 * @param mode_mask  Bits 0 idle, 1 manual, 2 trajectory. Zero for ground station.
 * @param features  Bit 0 depth hold, 1 auxiliary controls.
 * @param simulated  One for simulator, zero for real hardware.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_capabilities_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t session, uint16_t protocol_version, uint32_t mode_mask, uint32_t features, uint8_t simulated)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint32_t(buf, 8, mode_mask);
    _mav_put_uint32_t(buf, 12, features);
    _mav_put_uint16_t(buf, 16, protocol_version);
    _mav_put_uint8_t(buf, 18, simulated);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN);
#else
    mavlink_fins_capabilities_t packet;
    packet.session = session;
    packet.mode_mask = mode_mask;
    packet.features = features;
    packet.protocol_version = protocol_version;
    packet.simulated = simulated;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_CAPABILITIES;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FINS_CAPABILITIES_MIN_LEN, MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN, MAVLINK_MSG_ID_FINS_CAPABILITIES_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FINS_CAPABILITIES_MIN_LEN, MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN);
#endif
}

/**
 * @brief Pack a fins_capabilities message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param session  Random boot/session identity.
 * @param protocol_version  Application contract version, currently 1.
 * @param mode_mask  Bits 0 idle, 1 manual, 2 trajectory. Zero for ground station.
 * @param features  Bit 0 depth hold, 1 auxiliary controls.
 * @param simulated  One for simulator, zero for real hardware.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_fins_capabilities_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t session,uint16_t protocol_version,uint32_t mode_mask,uint32_t features,uint8_t simulated)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint32_t(buf, 8, mode_mask);
    _mav_put_uint32_t(buf, 12, features);
    _mav_put_uint16_t(buf, 16, protocol_version);
    _mav_put_uint8_t(buf, 18, simulated);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN);
#else
    mavlink_fins_capabilities_t packet;
    packet.session = session;
    packet.mode_mask = mode_mask;
    packet.features = features;
    packet.protocol_version = protocol_version;
    packet.simulated = simulated;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FINS_CAPABILITIES;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_FINS_CAPABILITIES_MIN_LEN, MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN, MAVLINK_MSG_ID_FINS_CAPABILITIES_CRC);
}

/**
 * @brief Encode a fins_capabilities struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param fins_capabilities C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_capabilities_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_fins_capabilities_t* fins_capabilities)
{
    return mavlink_msg_fins_capabilities_pack(system_id, component_id, msg, fins_capabilities->session, fins_capabilities->protocol_version, fins_capabilities->mode_mask, fins_capabilities->features, fins_capabilities->simulated);
}

/**
 * @brief Encode a fins_capabilities struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param fins_capabilities C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_capabilities_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_fins_capabilities_t* fins_capabilities)
{
    return mavlink_msg_fins_capabilities_pack_chan(system_id, component_id, chan, msg, fins_capabilities->session, fins_capabilities->protocol_version, fins_capabilities->mode_mask, fins_capabilities->features, fins_capabilities->simulated);
}

/**
 * @brief Encode a fins_capabilities struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param fins_capabilities C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_fins_capabilities_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_fins_capabilities_t* fins_capabilities)
{
    return mavlink_msg_fins_capabilities_pack_status(system_id, component_id, _status, msg,  fins_capabilities->session, fins_capabilities->protocol_version, fins_capabilities->mode_mask, fins_capabilities->features, fins_capabilities->simulated);
}

/**
 * @brief Send a fins_capabilities message
 * @param chan MAVLink channel to send the message
 *
 * @param session  Random boot/session identity.
 * @param protocol_version  Application contract version, currently 1.
 * @param mode_mask  Bits 0 idle, 1 manual, 2 trajectory. Zero for ground station.
 * @param features  Bit 0 depth hold, 1 auxiliary controls.
 * @param simulated  One for simulator, zero for real hardware.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_fins_capabilities_send(mavlink_channel_t chan, uint64_t session, uint16_t protocol_version, uint32_t mode_mask, uint32_t features, uint8_t simulated)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN];
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint32_t(buf, 8, mode_mask);
    _mav_put_uint32_t(buf, 12, features);
    _mav_put_uint16_t(buf, 16, protocol_version);
    _mav_put_uint8_t(buf, 18, simulated);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_CAPABILITIES, buf, MAVLINK_MSG_ID_FINS_CAPABILITIES_MIN_LEN, MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN, MAVLINK_MSG_ID_FINS_CAPABILITIES_CRC);
#else
    mavlink_fins_capabilities_t packet;
    packet.session = session;
    packet.mode_mask = mode_mask;
    packet.features = features;
    packet.protocol_version = protocol_version;
    packet.simulated = simulated;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_CAPABILITIES, (const char *)&packet, MAVLINK_MSG_ID_FINS_CAPABILITIES_MIN_LEN, MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN, MAVLINK_MSG_ID_FINS_CAPABILITIES_CRC);
#endif
}

/**
 * @brief Send a fins_capabilities message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_fins_capabilities_send_struct(mavlink_channel_t chan, const mavlink_fins_capabilities_t* fins_capabilities)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_fins_capabilities_send(chan, fins_capabilities->session, fins_capabilities->protocol_version, fins_capabilities->mode_mask, fins_capabilities->features, fins_capabilities->simulated);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_CAPABILITIES, (const char *)fins_capabilities, MAVLINK_MSG_ID_FINS_CAPABILITIES_MIN_LEN, MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN, MAVLINK_MSG_ID_FINS_CAPABILITIES_CRC);
#endif
}

#if MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_fins_capabilities_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t session, uint16_t protocol_version, uint32_t mode_mask, uint32_t features, uint8_t simulated)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, session);
    _mav_put_uint32_t(buf, 8, mode_mask);
    _mav_put_uint32_t(buf, 12, features);
    _mav_put_uint16_t(buf, 16, protocol_version);
    _mav_put_uint8_t(buf, 18, simulated);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_CAPABILITIES, buf, MAVLINK_MSG_ID_FINS_CAPABILITIES_MIN_LEN, MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN, MAVLINK_MSG_ID_FINS_CAPABILITIES_CRC);
#else
    mavlink_fins_capabilities_t *packet = (mavlink_fins_capabilities_t *)msgbuf;
    packet->session = session;
    packet->mode_mask = mode_mask;
    packet->features = features;
    packet->protocol_version = protocol_version;
    packet->simulated = simulated;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FINS_CAPABILITIES, (const char *)packet, MAVLINK_MSG_ID_FINS_CAPABILITIES_MIN_LEN, MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN, MAVLINK_MSG_ID_FINS_CAPABILITIES_CRC);
#endif
}
#endif

#endif

// MESSAGE FINS_CAPABILITIES UNPACKING


/**
 * @brief Get field session from fins_capabilities message
 *
 * @return  Random boot/session identity.
 */
static inline uint64_t mavlink_msg_fins_capabilities_get_session(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field protocol_version from fins_capabilities message
 *
 * @return  Application contract version, currently 1.
 */
static inline uint16_t mavlink_msg_fins_capabilities_get_protocol_version(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  16);
}

/**
 * @brief Get field mode_mask from fins_capabilities message
 *
 * @return  Bits 0 idle, 1 manual, 2 trajectory. Zero for ground station.
 */
static inline uint32_t mavlink_msg_fins_capabilities_get_mode_mask(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field features from fins_capabilities message
 *
 * @return  Bit 0 depth hold, 1 auxiliary controls.
 */
static inline uint32_t mavlink_msg_fins_capabilities_get_features(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  12);
}

/**
 * @brief Get field simulated from fins_capabilities message
 *
 * @return  One for simulator, zero for real hardware.
 */
static inline uint8_t mavlink_msg_fins_capabilities_get_simulated(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  18);
}

/**
 * @brief Decode a fins_capabilities message into a struct
 *
 * @param msg The message to decode
 * @param fins_capabilities C-struct to decode the message contents into
 */
static inline void mavlink_msg_fins_capabilities_decode(const mavlink_message_t* msg, mavlink_fins_capabilities_t* fins_capabilities)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    fins_capabilities->session = mavlink_msg_fins_capabilities_get_session(msg);
    fins_capabilities->mode_mask = mavlink_msg_fins_capabilities_get_mode_mask(msg);
    fins_capabilities->features = mavlink_msg_fins_capabilities_get_features(msg);
    fins_capabilities->protocol_version = mavlink_msg_fins_capabilities_get_protocol_version(msg);
    fins_capabilities->simulated = mavlink_msg_fins_capabilities_get_simulated(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN? msg->len : MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN;
        memset(fins_capabilities, 0, MAVLINK_MSG_ID_FINS_CAPABILITIES_LEN);
    memcpy(fins_capabilities, _MAV_PAYLOAD(msg), len);
#endif
}
