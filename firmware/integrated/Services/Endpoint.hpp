// SPDX-License-Identifier: MPL-2.0
// Portable execution endpoint. Used unchanged by the A-board and host harness.
#pragma once
#include <array>
#include <cmath>
#include <cstdint>
#include <cstring>
#include "finsrov/mavlink.h"

namespace fins {
struct Control {
    uint64_t client=0;
    uint32_t epoch=0, faults=0;
    uint8_t mode=0;
    bool armed=false, hold=false, active=false;
    float yaw=0, forward=0, left=0, down=0, up=0, depth=0;
};
class Endpoint {
public:
    using Apply = bool (*)(const Control&);
    using Send = void (*)(const uint8_t*, uint16_t);
    Control state{};
    Endpoint(uint64_t boot, Apply apply, Send send, bool depth_hold=false):boot_(boot),apply_(apply),send_(send),depth_hold_(depth_hold) {}
    void feed(const uint8_t* data, size_t length, uint64_t now) {
        tick(now);
        for(size_t i=0;i<length;++i) {
            mavlink_message_t message{}; mavlink_status_t status{};
            if(mavlink_frame_char_buffer(&rx_, &rx_status_, data[i], &message, &status)==MAVLINK_FRAMING_OK)
                receive(message,now);
        }
    }
    void tick(uint64_t now) {
        if(state.mode && now>=deadline_) stop(1);
    }
    void stop(uint32_t fault) {
        state.mode=0; state.armed=false; state.faults=fault;
        clear(state); apply_(state);
    }
    void status() {
        mavlink_message_t m{};
        mavlink_msg_fins_status_pack(1,1,&m,boot_,state.client,state.epoch,state.faults,
            state.depth,state.mode,state.armed,state.hold,0,0);
        transmit(m);
    }
    uint64_t session() const { return boot_; }
    void transmit(mavlink_message_t& m) {
        uint8_t data[MAVLINK_MAX_PACKET_LEN];
        send_(data,mavlink_msg_to_send_buffer(data,&m));
    }
private:
    struct Cached { bool used=false; mavlink_fins_action_request_t request{}; mavlink_fins_action_ack_t ack{}; };
    std::array<Cached,32> cache_{};
    std::array<uint32_t,6> latest_{};
    std::array<bool,6> seen_{};
    size_t next_=0;
    uint64_t boot_,deadline_=0;
    uint32_t sequence_=0;
    bool have_sequence_=false;
    Apply apply_; Send send_;
    bool depth_hold_;
    mavlink_message_t rx_{}; mavlink_status_t rx_status_{};
    static bool newer(uint32_t a,uint32_t b) {return static_cast<int32_t>(a-b)>0;}
    static void clear(Control& s) {s.yaw=s.forward=s.left=s.down=s.up=0; s.hold=false;s.active=false;}
    void ack(const mavlink_fins_action_ack_t& a) {
        mavlink_message_t m{}; mavlink_msg_fins_action_ack_encode(1,1,&m,&a); transmit(m);
    }
    void receive(const mavlink_message_t& m,uint64_t now) {
        if(m.msgid==MAVLINK_MSG_ID_TIMESYNC) {
            mavlink_timesync_t t{}; mavlink_msg_timesync_decode(&m,&t);
            if(t.tc1==0) {mavlink_message_t out{}; mavlink_msg_timesync_pack(1,1,&out,static_cast<int64_t>(now*1000),t.ts1); transmit(out);}
            return;
        }
        if(m.msgid==MAVLINK_MSG_ID_FINS_CAPABILITIES) {
            mavlink_fins_capabilities_t c{}; mavlink_msg_fins_capabilities_decode(&m,&c);
            if(c.mode_mask || c.protocol_version!=1 || !c.session) return;
            if(state.client!=c.session) {
                stop(0); state=Control{}; state.client=c.session;
                cache_={}; seen_={}; next_=0; have_sequence_=false;
            }
            mavlink_message_t out{};
            // Depth hold implemented; physical gimbal/light mapping not confirmed.
            mavlink_msg_fins_capabilities_pack(1,1,&out,boot_,1,7,depth_hold_ ? 1 : 0,0); transmit(out); status(); return;
        }
        if(m.msgid==MAVLINK_MSG_ID_FINS_ACTION_REQUEST) {
            mavlink_fins_action_request_t r{}; mavlink_msg_fins_action_request_decode(&m,&r);
            if(!state.client || r.session!=state.client || r.target_session!=boot_) return;
            for(const auto& c:cache_) if(c.used && c.request.request_id==r.request_id) {
                if(c.request.action==r.action && c.request.value==r.value && c.request.epoch==r.epoch) ack(c.ack);
                return;
            }
            uint8_t result=FINS_RESULT_ACCEPTED,reason=FINS_REASON_NONE;
            Control proposed=state;
            if(r.action>=latest_.size() || r.action==0) {result=FINS_RESULT_INVALID;reason=FINS_REASON_BAD_VALUE;}
            else if(seen_[r.action] && !newer(r.request_id,latest_[r.action])) {result=FINS_RESULT_INVALID;reason=FINS_REASON_STALE_REQUEST;}
            else if(r.action==FINS_ACTION_SET_ARMED && r.value==0) {proposed.armed=false;clear(proposed);}
            else if(r.action==FINS_ACTION_SET_MODE) {
                if(r.value>2 || !newer(r.epoch,state.epoch)) {result=FINS_RESULT_INVALID;reason=FINS_REASON_BAD_GENERATION;}
                else {proposed.mode=r.value; proposed.epoch=r.epoch; proposed.faults=0;clear(proposed);}
            } else if(r.epoch!=state.epoch) {result=FINS_RESULT_INVALID;reason=FINS_REASON_BAD_GENERATION;}
            else if(r.action==FINS_ACTION_SET_ARMED && r.value==1 && state.mode!=0) proposed.armed=true;
            else {result=FINS_RESULT_REJECTED;reason=FINS_REASON_BAD_VALUE;}
            if(result==FINS_RESULT_ACCEPTED) {
                if(apply_(proposed)) {
                    state=proposed;
                    if(r.action==FINS_ACTION_SET_MODE) {deadline_=now+200000; have_sequence_=false;}
                } else {result=FINS_RESULT_REJECTED;reason=FINS_REASON_SWITCH_DENIED;}
            }
            if(r.action<latest_.size() && (!seen_[r.action] || newer(r.request_id,latest_[r.action]))) {latest_[r.action]=r.request_id;seen_[r.action]=true;}
            mavlink_fins_action_ack_t a{};
            a.session=boot_;a.target_session=r.session;a.request_id=r.request_id;a.epoch=r.epoch;
            a.action=r.action;a.result=result;a.reason=reason;
            cache_[next_]={true,r,a};next_=(next_+1)%cache_.size();ack(a);status();return;
        }
        if(m.msgid!=MAVLINK_MSG_ID_FINS_CONTROL_SETPOINT) return;
        mavlink_fins_control_setpoint_t p{}; mavlink_msg_fins_control_setpoint_decode(&m,&p);
        if(!state.client || p.session!=state.client || p.target_session!=boot_ || p.epoch!=state.epoch || !state.mode) return;
        if((have_sequence_ && !newer(p.sequence,sequence_)) || p.valid_ms==0 || p.valid_ms>200 || p.source_us>now+50000) return;
        const uint64_t expires=p.source_us+static_cast<uint64_t>(p.valid_ms)*1000;
        if(expires<=now || expires<p.source_us) return;
        const float values[]={p.yaw,p.forward,p.left,p.down,p.up,p.depth_target};
        for(float v:values) if(!std::isfinite(v)) return;
        if(std::fabs(p.yaw)>1 || std::fabs(p.forward)>1 || std::fabs(p.left)>1 || p.down<0 || p.down>1 || p.up<0 || p.up>1 || p.depth_target<0 || p.vertical_mode>1) return;
        if(p.vertical_mode && (!depth_hold_ || state.mode!=FINS_MODE_TRAJECTORY)) return;
        Control proposed=state;
        proposed.yaw=p.yaw;proposed.forward=p.forward;proposed.left=p.left;proposed.down=p.down;proposed.up=p.up;
        proposed.depth=p.depth_target;proposed.hold=p.vertical_mode && state.armed;
        proposed.active=state.armed;
        if(!state.armed) clear(proposed);
        if(apply_(proposed)) {state=proposed;sequence_=p.sequence;have_sequence_=true;deadline_=expires<now+200000 ? expires : now+200000;}
        else stop(2);
    }
};
} // namespace fins
