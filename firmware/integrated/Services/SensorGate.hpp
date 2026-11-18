// SPDX-License-Identifier: MPL-2.0
#pragma once
#include <cstddef>
#include <cstdint>
namespace fins {
// Validate every block before calling the inherited H30 decoder, which assumes
// complete payloads. Only a sample containing accel, gyro AND quaternion is fresh.
inline bool validH30(const uint8_t* data,size_t length) {
    if(length<7 || length>100 || data[0]!=0x59 || data[1]!=0x53) return false;
    uint8_t c1=0,c2=0;
    for(size_t i=2;i<length-2;++i) {c1+=data[i];c2+=c1;}
    if(c1!=data[length-2] || c2!=data[length-1]) return false;
    bool accel=false,gyro=false,quat=false;
    for(size_t i=5;i<length-2;) {
        if(i+2>length-2 || i+2+data[i+1]>length-2) return false;
        const auto kind=data[i], n=data[i+1];
        if((kind==0x10 || kind==0x20) && n!=12) return false;
        if(kind==0x41 && n!=16) return false;
        accel |= kind==0x10;gyro |= kind==0x20;quat |= kind==0x41;i+=2+n;
    }
    return accel && gyro && quat;
}
inline bool fresh(uint32_t now,uint32_t source,uint32_t maximum,bool valid) {
    return valid && static_cast<uint32_t>(now-source)<maximum;
}
}
