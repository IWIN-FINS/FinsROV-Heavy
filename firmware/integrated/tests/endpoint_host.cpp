// The exact board endpoint, driven through hex-framed serial bytes and fake time.
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Endpoint.hpp"
#include "SensorGate.hpp"
#include "IntegratedPID.hpp"
#include <cassert>
static bool ready=true;
static bool apply(const fins::Control& c) { return !c.armed || ready; }
static void send(const uint8_t* p,uint16_t n) {
    for(uint16_t i=0;i<n;++i) std::printf("%02x",p[i]);
    std::printf("\n");
}
int main() {
    IntegratedPID pid({0,1,0,100,100});float target=1,feedback=0;
    pid.SetTarget(&target);pid.SetFeedback({&feedback});pid.Calc();pid.Calc();
    pid.Reset();target=0;assert(pid.Calc()==0);
    assert(fins::fresh(20,0xfffffff0U,100,true));
    assert(!fins::fresh(100,0,100,true));
    assert(!fins::fresh(0,0,100,false));
    std::vector<uint8_t> sample{0x59,0x53,0,0,0};
    for(uint8_t id:{0x10,0x20,0x41}) {const uint8_t n=id==0x41?16:12;sample.push_back(id);sample.push_back(n);sample.resize(sample.size()+n,0);}
    uint8_t c1=0,c2=0;for(size_t i=2;i<sample.size();++i){c1+=sample[i];c2+=c1;}
    sample.push_back(c1);sample.push_back(c2);
    assert(fins::validH30(sample.data(),sample.size()));
    for(size_t size=0;size<sample.size();++size) assert(!fins::validH30(sample.data(),size));
    sample.back()^=1;assert(!fins::validH30(sample.data(),sample.size()));
    fins::Endpoint endpoint(1234567,apply,send,true);
    std::string line;
    while(std::getline(std::cin,line)) {
        std::istringstream in(line);uint64_t now=0;std::string hex;
        in>>now>>hex;
        if(hex=="notready") ready=false;
        else if(hex=="ready") ready=true;
        else if(hex!="tick") {
            std::vector<uint8_t> bytes;
            for(size_t i=0;i+1<hex.size();i+=2) bytes.push_back(static_cast<uint8_t>(std::stoul(hex.substr(i,2),nullptr,16)));
            endpoint.feed(bytes.data(),bytes.size(),now);
        }
        endpoint.tick(now); endpoint.status();
        std::printf(".\n");std::fflush(stdout);
    }
}
