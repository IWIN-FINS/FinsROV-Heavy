/** @file
 *  @brief MAVLink comm protocol generated from finsrov.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_FINSROV_H
#define MAVLINK_FINSROV_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_FINSROV.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#define MAVLINK_FINSROV_XML_HASH 5144541823068825674

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{0, 50, 9, 9, 0, 0, 0}, {111, 34, 16, 16, 0, 0, 0}, {60000, 145, 19, 19, 0, 0, 0}, {60001, 145, 33, 33, 0, 0, 0}, {60002, 26, 54, 54, 0, 0, 0}, {60003, 5, 59, 59, 0, 0, 0}, {60004, 116, 26, 26, 0, 0, 0}, {60005, 236, 27, 27, 0, 0, 0}, {60006, 64, 36, 36, 0, 0, 0}, {60007, 10, 108, 108, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_FINSROV

// ENUM DEFINITIONS


/** @brief  */
#ifndef HAVE_ENUM_FINS_MODE
#define HAVE_ENUM_FINS_MODE
typedef enum FINS_MODE
{
   FINS_MODE_IDLE=0, /* Stopped. | */
   FINS_MODE_MANUAL=1, /* Exclusive manual source. | */
   FINS_MODE_TRAJECTORY=2, /* NX feedback trajectory. | */
   FINS_MODE_ENUM_END=3, /*  | */
} FINS_MODE;
#endif

/** @brief  */
#ifndef HAVE_ENUM_FINS_ACTION
#define HAVE_ENUM_FINS_ACTION
typedef enum FINS_ACTION
{
   FINS_ACTION_SET_MODE=1, /* Set mode and generation. | */
   FINS_ACTION_SET_ARMED=2, /* Absolute motor enable. | */
   FINS_ACTION_RESET_ODOMETRY=3, /* Reset local origin. | */
   FINS_ACTION_SET_CAMERA_LIGHT=4, /* Absolute camera light. | */
   FINS_ACTION_SET_FRAME_LIGHT=5, /* Absolute frame light. | */
   FINS_ACTION_ENUM_END=6, /*  | */
} FINS_ACTION;
#endif

/** @brief  */
#ifndef HAVE_ENUM_FINS_RESULT
#define HAVE_ENUM_FINS_RESULT
typedef enum FINS_RESULT
{
   FINS_RESULT_ACCEPTED=0, /* Applied. | */
   FINS_RESULT_REJECTED=1, /* Rejected; see reason. | */
   FINS_RESULT_INVALID=2, /* Invalid; see reason. | */
   FINS_RESULT_ENUM_END=3, /*  | */
} FINS_RESULT;
#endif

/** @brief  */
#ifndef HAVE_ENUM_FINS_REASON
#define HAVE_ENUM_FINS_REASON
typedef enum FINS_REASON
{
   FINS_REASON_NONE=0, /* No rejection. | */
   FINS_REASON_STALE_REQUEST=1, /* Out-of-order request. | */
   FINS_REASON_BAD_GENERATION=2, /* Invalid control generation or mode. | */
   FINS_REASON_SWITCH_DENIED=3, /* Mode switch denied by vehicle. | */
   FINS_REASON_BAD_VALUE=4, /* Unsupported action or value. | */
   FINS_REASON_ENUM_END=5, /*  | */
} FINS_REASON;
#endif

/** @brief  */
#ifndef HAVE_ENUM_FINS_VERTICAL_MODE
#define HAVE_ENUM_FINS_VERTICAL_MODE
typedef enum FINS_VERTICAL_MODE
{
   FINS_VERTICAL_MANUAL=0, /* Manual up/down. | */
   FINS_VERTICAL_HOLD_DEPTH=1, /* Depth positive down in metres. | */
   FINS_VERTICAL_MODE_ENUM_END=2, /*  | */
} FINS_VERTICAL_MODE;
#endif

// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_timesync.h"
#include "./mavlink_msg_fins_capabilities.h"
#include "./mavlink_msg_fins_status.h"
#include "./mavlink_msg_fins_odometry.h"
#include "./mavlink_msg_fins_control_setpoint.h"
#include "./mavlink_msg_fins_action_request.h"
#include "./mavlink_msg_fins_action_ack.h"
#include "./mavlink_msg_fins_aux_setpoint.h"
#include "./mavlink_msg_fins_telemetry.h"

// base include
#include "../minimal/minimal.h"


#if MAVLINK_FINSROV_XML_HASH == MAVLINK_PRIMARY_XML_HASH
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_HEARTBEAT, MAVLINK_MESSAGE_INFO_TIMESYNC, MAVLINK_MESSAGE_INFO_FINS_CAPABILITIES, MAVLINK_MESSAGE_INFO_FINS_STATUS, MAVLINK_MESSAGE_INFO_FINS_ODOMETRY, MAVLINK_MESSAGE_INFO_FINS_CONTROL_SETPOINT, MAVLINK_MESSAGE_INFO_FINS_ACTION_REQUEST, MAVLINK_MESSAGE_INFO_FINS_ACTION_ACK, MAVLINK_MESSAGE_INFO_FINS_AUX_SETPOINT, MAVLINK_MESSAGE_INFO_FINS_TELEMETRY}
# define MAVLINK_MESSAGE_NAMES {{ "FINS_ACTION_ACK", 60005 }, { "FINS_ACTION_REQUEST", 60004 }, { "FINS_AUX_SETPOINT", 60006 }, { "FINS_CAPABILITIES", 60000 }, { "FINS_CONTROL_SETPOINT", 60003 }, { "FINS_ODOMETRY", 60002 }, { "FINS_STATUS", 60001 }, { "FINS_TELEMETRY", 60007 }, { "HEARTBEAT", 0 }, { "TIMESYNC", 111 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_FINSROV_H
