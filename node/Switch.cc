/*
 * Switch.cc
 *
 *  Created on: 05.08.2019
 *      Author: hari_pr
 */
#include <omnetpp.h>
#include "Packet_m.h"
#include "Flit_m.h"
using namespace omnetpp;

class Switch : public cSimpleModule, public cListener
{
  private:


  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Switch);

void Switch::initialize()
{

}

void Switch::handleMessage(cMessage *msg)
{
    Flit *ft = check_and_cast<Flit *>(msg);
    // Get number of jumps remaining
    int length = ft->getAddressLength();
    int hopes = ft->getHopes();
    // If jumps are 0 we have arrived
    if (hopes == length) {
        EV << "Packet has arrived to destination" << endl;
    } else {
        int gate = ft->getAddress(hopes+1);
        ft->setHopes(hopes+1);
        int outGateIndex = gate;
        send(ft, "out", outGateIndex);
    }
}
