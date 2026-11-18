/** @file
 *    @brief MAVLink comm protocol testsuite generated from finsrov.xml
 *    @see https://mavlink.io/en/
 */
#pragma once
#ifndef FINSROV_TESTSUITE_H
#define FINSROV_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_minimal(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_finsrov(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_minimal(system_id, component_id, last_msg);
    mavlink_test_finsrov(system_id, component_id, last_msg);
}
#endif

#include "../minimal/testsuite.h"


static void mavlink_test_timesync(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_TIMESYNC >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_timesync_t packet_in = {
        93372036854775807LL,93372036854776311LL
    };
    mavlink_timesync_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.tc1 = packet_in.tc1;
        packet1.ts1 = packet_in.ts1;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_TIMESYNC_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_TIMESYNC_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_timesync_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_timesync_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_timesync_pack(system_id, component_id, &msg , packet1.tc1 , packet1.ts1 );
    mavlink_msg_timesync_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_timesync_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.tc1 , packet1.ts1 );
    mavlink_msg_timesync_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_timesync_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_timesync_send(MAVLINK_COMM_1 , packet1.tc1 , packet1.ts1 );
    mavlink_msg_timesync_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("TIMESYNC") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_TIMESYNC) != NULL);
#endif
}

static void mavlink_test_fins_capabilities(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_FINS_CAPABILITIES >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_fins_capabilities_t packet_in = {
        93372036854775807ULL,963497880,963498088,18067,187
    };
    mavlink_fins_capabilities_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.session = packet_in.session;
        packet1.mode_mask = packet_in.mode_mask;
        packet1.features = packet_in.features;
        packet1.protocol_version = packet_in.protocol_version;
        packet1.simulated = packet_in.simulated;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_FINS_CAPABILITIES_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_FINS_CAPABILITIES_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_capabilities_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_fins_capabilities_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_capabilities_pack(system_id, component_id, &msg , packet1.session , packet1.protocol_version , packet1.mode_mask , packet1.features , packet1.simulated );
    mavlink_msg_fins_capabilities_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_capabilities_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.session , packet1.protocol_version , packet1.mode_mask , packet1.features , packet1.simulated );
    mavlink_msg_fins_capabilities_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_fins_capabilities_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_capabilities_send(MAVLINK_COMM_1 , packet1.session , packet1.protocol_version , packet1.mode_mask , packet1.features , packet1.simulated );
    mavlink_msg_fins_capabilities_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("FINS_CAPABILITIES") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_FINS_CAPABILITIES) != NULL);
#endif
}

static void mavlink_test_fins_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_FINS_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_fins_status_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,963498296,963498504,185.0,89,156,223,34,101
    };
    mavlink_fins_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.session = packet_in.session;
        packet1.client_session = packet_in.client_session;
        packet1.epoch = packet_in.epoch;
        packet1.faults = packet_in.faults;
        packet1.depth_target = packet_in.depth_target;
        packet1.mode = packet_in.mode;
        packet1.armed = packet_in.armed;
        packet1.hold_depth = packet_in.hold_depth;
        packet1.camera_light = packet_in.camera_light;
        packet1.frame_light = packet_in.frame_light;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_FINS_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_FINS_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_fins_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_status_pack(system_id, component_id, &msg , packet1.session , packet1.client_session , packet1.epoch , packet1.faults , packet1.depth_target , packet1.mode , packet1.armed , packet1.hold_depth , packet1.camera_light , packet1.frame_light );
    mavlink_msg_fins_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.session , packet1.client_session , packet1.epoch , packet1.faults , packet1.depth_target , packet1.mode , packet1.armed , packet1.hold_depth , packet1.camera_light , packet1.frame_light );
    mavlink_msg_fins_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_fins_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_status_send(MAVLINK_COMM_1 , packet1.session , packet1.client_session , packet1.epoch , packet1.faults , packet1.depth_target , packet1.mode , packet1.armed , packet1.hold_depth , packet1.camera_light , packet1.frame_light );
    mavlink_msg_fins_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("FINS_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_FINS_STATUS) != NULL);
#endif
}

static void mavlink_test_fins_odometry(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_FINS_ODOMETRY >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_fins_odometry_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,963498296,963498504,185.0,213.0,241.0,269.0,297.0,325.0,353.0,161,228
    };
    mavlink_fins_odometry_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.session = packet_in.session;
        packet1.source_us = packet_in.source_us;
        packet1.sample_seq = packet_in.sample_seq;
        packet1.reset_id = packet_in.reset_id;
        packet1.x = packet_in.x;
        packet1.y = packet_in.y;
        packet1.yaw = packet_in.yaw;
        packet1.vx = packet_in.vx;
        packet1.vy = packet_in.vy;
        packet1.yaw_rate = packet_in.yaw_rate;
        packet1.depth = packet_in.depth;
        packet1.valid = packet_in.valid;
        packet1.depth_valid = packet_in.depth_valid;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_FINS_ODOMETRY_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_FINS_ODOMETRY_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_odometry_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_fins_odometry_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_odometry_pack(system_id, component_id, &msg , packet1.session , packet1.source_us , packet1.sample_seq , packet1.reset_id , packet1.x , packet1.y , packet1.yaw , packet1.vx , packet1.vy , packet1.yaw_rate , packet1.depth , packet1.valid , packet1.depth_valid );
    mavlink_msg_fins_odometry_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_odometry_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.session , packet1.source_us , packet1.sample_seq , packet1.reset_id , packet1.x , packet1.y , packet1.yaw , packet1.vx , packet1.vy , packet1.yaw_rate , packet1.depth , packet1.valid , packet1.depth_valid );
    mavlink_msg_fins_odometry_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_fins_odometry_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_odometry_send(MAVLINK_COMM_1 , packet1.session , packet1.source_us , packet1.sample_seq , packet1.reset_id , packet1.x , packet1.y , packet1.yaw , packet1.vx , packet1.vy , packet1.yaw_rate , packet1.depth , packet1.valid , packet1.depth_valid );
    mavlink_msg_fins_odometry_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("FINS_ODOMETRY") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_FINS_ODOMETRY) != NULL);
#endif
}

static void mavlink_test_fins_control_setpoint(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_fins_control_setpoint_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,93372036854776815ULL,963498712,963498920,241.0,269.0,297.0,325.0,353.0,381.0,20147,51
    };
    mavlink_fins_control_setpoint_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.session = packet_in.session;
        packet1.target_session = packet_in.target_session;
        packet1.source_us = packet_in.source_us;
        packet1.epoch = packet_in.epoch;
        packet1.sequence = packet_in.sequence;
        packet1.yaw = packet_in.yaw;
        packet1.forward = packet_in.forward;
        packet1.left = packet_in.left;
        packet1.down = packet_in.down;
        packet1.up = packet_in.up;
        packet1.depth_target = packet_in.depth_target;
        packet1.valid_ms = packet_in.valid_ms;
        packet1.vertical_mode = packet_in.vertical_mode;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_control_setpoint_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_fins_control_setpoint_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_control_setpoint_pack(system_id, component_id, &msg , packet1.session , packet1.target_session , packet1.source_us , packet1.epoch , packet1.sequence , packet1.valid_ms , packet1.yaw , packet1.forward , packet1.left , packet1.down , packet1.up , packet1.depth_target , packet1.vertical_mode );
    mavlink_msg_fins_control_setpoint_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_control_setpoint_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.session , packet1.target_session , packet1.source_us , packet1.epoch , packet1.sequence , packet1.valid_ms , packet1.yaw , packet1.forward , packet1.left , packet1.down , packet1.up , packet1.depth_target , packet1.vertical_mode );
    mavlink_msg_fins_control_setpoint_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_fins_control_setpoint_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_control_setpoint_send(MAVLINK_COMM_1 , packet1.session , packet1.target_session , packet1.source_us , packet1.epoch , packet1.sequence , packet1.valid_ms , packet1.yaw , packet1.forward , packet1.left , packet1.down , packet1.up , packet1.depth_target , packet1.vertical_mode );
    mavlink_msg_fins_control_setpoint_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("FINS_CONTROL_SETPOINT") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT) != NULL);
#endif
}

static void mavlink_test_fins_action_request(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_FINS_ACTION_REQUEST >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_fins_action_request_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,963498296,963498504,77,144
    };
    mavlink_fins_action_request_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.session = packet_in.session;
        packet1.target_session = packet_in.target_session;
        packet1.request_id = packet_in.request_id;
        packet1.epoch = packet_in.epoch;
        packet1.action = packet_in.action;
        packet1.value = packet_in.value;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_FINS_ACTION_REQUEST_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_FINS_ACTION_REQUEST_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_action_request_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_fins_action_request_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_action_request_pack(system_id, component_id, &msg , packet1.session , packet1.target_session , packet1.request_id , packet1.epoch , packet1.action , packet1.value );
    mavlink_msg_fins_action_request_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_action_request_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.session , packet1.target_session , packet1.request_id , packet1.epoch , packet1.action , packet1.value );
    mavlink_msg_fins_action_request_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_fins_action_request_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_action_request_send(MAVLINK_COMM_1 , packet1.session , packet1.target_session , packet1.request_id , packet1.epoch , packet1.action , packet1.value );
    mavlink_msg_fins_action_request_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("FINS_ACTION_REQUEST") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_FINS_ACTION_REQUEST) != NULL);
#endif
}

static void mavlink_test_fins_action_ack(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_FINS_ACTION_ACK >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_fins_action_ack_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,963498296,963498504,77,144,211
    };
    mavlink_fins_action_ack_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.session = packet_in.session;
        packet1.target_session = packet_in.target_session;
        packet1.request_id = packet_in.request_id;
        packet1.epoch = packet_in.epoch;
        packet1.action = packet_in.action;
        packet1.result = packet_in.result;
        packet1.reason = packet_in.reason;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_FINS_ACTION_ACK_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_FINS_ACTION_ACK_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_action_ack_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_fins_action_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_action_ack_pack(system_id, component_id, &msg , packet1.session , packet1.target_session , packet1.request_id , packet1.epoch , packet1.action , packet1.result , packet1.reason );
    mavlink_msg_fins_action_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_action_ack_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.session , packet1.target_session , packet1.request_id , packet1.epoch , packet1.action , packet1.result , packet1.reason );
    mavlink_msg_fins_action_ack_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_fins_action_ack_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_action_ack_send(MAVLINK_COMM_1 , packet1.session , packet1.target_session , packet1.request_id , packet1.epoch , packet1.action , packet1.result , packet1.reason );
    mavlink_msg_fins_action_ack_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("FINS_ACTION_ACK") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_FINS_ACTION_ACK) != NULL);
#endif
}

static void mavlink_test_fins_aux_setpoint(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_FINS_AUX_SETPOINT >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_fins_aux_setpoint_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,93372036854776815ULL,963498712,963498920,18899,235,46
    };
    mavlink_fins_aux_setpoint_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.session = packet_in.session;
        packet1.target_session = packet_in.target_session;
        packet1.source_us = packet_in.source_us;
        packet1.epoch = packet_in.epoch;
        packet1.sequence = packet_in.sequence;
        packet1.valid_ms = packet_in.valid_ms;
        packet1.cam_yaw = packet_in.cam_yaw;
        packet1.cam_pitch = packet_in.cam_pitch;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_FINS_AUX_SETPOINT_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_FINS_AUX_SETPOINT_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_aux_setpoint_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_fins_aux_setpoint_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_aux_setpoint_pack(system_id, component_id, &msg , packet1.session , packet1.target_session , packet1.source_us , packet1.epoch , packet1.sequence , packet1.valid_ms , packet1.cam_yaw , packet1.cam_pitch );
    mavlink_msg_fins_aux_setpoint_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_aux_setpoint_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.session , packet1.target_session , packet1.source_us , packet1.epoch , packet1.sequence , packet1.valid_ms , packet1.cam_yaw , packet1.cam_pitch );
    mavlink_msg_fins_aux_setpoint_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_fins_aux_setpoint_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_aux_setpoint_send(MAVLINK_COMM_1 , packet1.session , packet1.target_session , packet1.source_us , packet1.epoch , packet1.sequence , packet1.valid_ms , packet1.cam_yaw , packet1.cam_pitch );
    mavlink_msg_fins_aux_setpoint_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("FINS_AUX_SETPOINT") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_FINS_AUX_SETPOINT) != NULL);
#endif
}

static void mavlink_test_fins_telemetry(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_FINS_TELEMETRY >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_fins_telemetry_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,963498296,157.0,{ 185.0, 186.0, 187.0, 188.0 },{ 297.0, 298.0, 299.0, 300.0, 301.0, 302.0, 303.0, 304.0 },{ 521.0, 522.0, 523.0 },{ 605.0, 606.0, 607.0 },{ 689.0, 690.0, 691.0 }
    };
    mavlink_fins_telemetry_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.session = packet_in.session;
        packet1.source_us = packet_in.source_us;
        packet1.valid_mask = packet_in.valid_mask;
        packet1.voltage = packet_in.voltage;
        
        mav_array_memcpy(packet1.pressure, packet_in.pressure, sizeof(float)*4);
        mav_array_memcpy(packet1.rpm, packet_in.rpm, sizeof(float)*8);
        mav_array_memcpy(packet1.accel, packet_in.accel, sizeof(float)*3);
        mav_array_memcpy(packet1.gyro, packet_in.gyro, sizeof(float)*3);
        mav_array_memcpy(packet1.network, packet_in.network, sizeof(float)*3);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_FINS_TELEMETRY_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_FINS_TELEMETRY_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_telemetry_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_fins_telemetry_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_telemetry_pack(system_id, component_id, &msg , packet1.session , packet1.source_us , packet1.valid_mask , packet1.voltage , packet1.pressure , packet1.rpm , packet1.accel , packet1.gyro , packet1.network );
    mavlink_msg_fins_telemetry_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_telemetry_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.session , packet1.source_us , packet1.valid_mask , packet1.voltage , packet1.pressure , packet1.rpm , packet1.accel , packet1.gyro , packet1.network );
    mavlink_msg_fins_telemetry_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_fins_telemetry_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_fins_telemetry_send(MAVLINK_COMM_1 , packet1.session , packet1.source_us , packet1.valid_mask , packet1.voltage , packet1.pressure , packet1.rpm , packet1.accel , packet1.gyro , packet1.network );
    mavlink_msg_fins_telemetry_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("FINS_TELEMETRY") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_FINS_TELEMETRY) != NULL);
#endif
}

static void mavlink_test_finsrov(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_timesync(system_id, component_id, last_msg);
    mavlink_test_fins_capabilities(system_id, component_id, last_msg);
    mavlink_test_fins_status(system_id, component_id, last_msg);
    mavlink_test_fins_odometry(system_id, component_id, last_msg);
    mavlink_test_fins_control_setpoint(system_id, component_id, last_msg);
    mavlink_test_fins_action_request(system_id, component_id, last_msg);
    mavlink_test_fins_action_ack(system_id, component_id, last_msg);
    mavlink_test_fins_aux_setpoint(system_id, component_id, last_msg);
    mavlink_test_fins_telemetry(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // FINSROV_TESTSUITE_H
