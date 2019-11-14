/*
 * Queue.cc
 *
 *  Created on: 05.08.2019
 *      Author: hari_pr
 */
#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "Flit_m.h"

using namespace omnetpp;

class Queue : public cSimpleModule, public cListener
{
  private:
   cQueue *queue;
  public:
    bool isBusy;
    bool isBlocked;
    int byWho;
    void blockQueue(int id)
    {
        isBlocked = true;
        byWho = id;
    }
    Queue();
    virtual ~Queue();
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void refreshDisplay() const override;
    virtual void popQueueAndSend();
    virtual void receiveSignal(cComponent* source, simsignal_t signalID, unsigned long l, cObject* details) override;
};

Define_Module(Queue);

Queue::Queue():
    queue(nullptr), isBusy(false), isBlocked(false)
{
    isBusy = false;
    isBlocked = false;
    byWho = 100;
}
Queue::~Queue()
{

}
void Queue::initialize()
{
    // subscribe to clock signal
    getSimulation()->getSystemModule()->subscribe("clock", this);
    // Initialize the queue
    queue = new cPacketQueue;
}
void Queue::handleMessage(cMessage *msg)
{
   // put message in the queue
   queue->insert((cPacket*)msg);
   isBusy = true;
}
void Queue::popQueueAndSend()
{
    Flit* msg = (Flit*)queue->get(0);
    int nextGate = msg->getAddress(msg->getHopes()+1);
    cModule* nextNode = gate("out")->getPathEndGate()->getOwnerModule()->getParentModule();
    Queue* nextQueue = nullptr;
    if (!nextNode->getSubmodule("cpu",0)) {
        nextQueue = (Queue*)nextNode->getSubmodule("queue", nextGate);
    }
    if (nextQueue != nullptr) {
    if (!nextQueue->isBlocked || (nextQueue->isBlocked && nextQueue->byWho == msg->getUniqueId())) {
        isBusy = false;
        if (msg->getType() == 0) {
            isBlocked = true;
            byWho = msg->getUniqueId();
            nextQueue->blockQueue(msg->getUniqueId());
        } else if (msg->getType() == 2 && this->byWho == msg->getUniqueId()) {
            isBlocked = false;
        }
        cPacket* msg = (cPacket*)queue->pop();
        take(msg);
        send(msg, "out");
    }
    }
    else {
        if(this->getParentModule()->getId() == 1){
        }
        if (msg->getType() == 0) {
            isBlocked = true;
            byWho = msg->getUniqueId();
        } else if (msg->getType() == 2 && this->byWho == msg->getUniqueId()) {
            isBlocked = false;
        }
        cPacket* msg = (cPacket*)queue->pop();
        take(msg);
        send(msg, "out");
    }
}
void Queue::receiveSignal(cComponent* source, simsignal_t signalID, unsigned long l, cObject* details)
{
    if(signalID == registerSignal("clock")) {
        if(queue->isEmpty()) {
            // do nothing
        }
        else {
            popQueueAndSend();
        }
    }
}
void Queue::refreshDisplay() const
{
    getDisplayString().setTagArg("t", 0, isBlocked ? "blocked" : "idle");
}

