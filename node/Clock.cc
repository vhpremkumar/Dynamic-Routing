/*
 * clock.cc
 *
 *  Created on: 02.08.2019
 *      Author: hari_pr
 */
#include <vector>
#include <omnetpp.h>
#include "Packet_m.h"
using namespace omnetpp;
class Clock: public cSimpleModule {
private:
    cMessage *timerMessage;
    simsignal_t clockSignal;
    unsigned long cycleCounter;
public:
    Clock();
    virtual ~Clock();
    unsigned long getCurrentCycle() const;
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};
Define_Module(Clock);
Clock::Clock()
    : timerMessage(nullptr)
{
}
Clock::~Clock() {
    cancelAndDelete(timerMessage);
}
void Clock::initialize(){
    cycleCounter = 0;
    clockSignal = registerSignal("clock");
    timerMessage = new cMessage("timer");
    scheduleAt(simTime(), timerMessage);
}
unsigned long Clock::getCurrentCycle() const {
    // Subtract 1 because the counter always contains the next cycle
    return cycleCounter - 1;
}
void Clock::handleMessage(cMessage *msg){
    ASSERT(msg == timerMessage);
    bubble(cycleCounter % 2 == 0 ? "tick" : "tock");
    emit(clockSignal, cycleCounter++);
    scheduleAt(simTime() + par("inter"), timerMessage);
}



