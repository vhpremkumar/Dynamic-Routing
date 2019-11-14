/*
 * Decoder.cc
 *
 *  Created on: 05.08.2019
 *      Author: hari_pr
 */

#include <vector>
#include <omnetpp.h>
#include "Packet_m.h"
#include "Flit_m.h"
using namespace omnetpp;

class Decoder : public cSimpleModule, public cListener
{
  private:

  public:
    Decoder();
    virtual ~Decoder();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Decoder);

Decoder::Decoder()
{
}
Decoder::~Decoder()
{
}
void Decoder::initialize()
{

}

void Decoder::handleMessage(cMessage *msg)
{
    Flit *ft = check_and_cast<Flit*>(msg);
    int size = ft->getSize();
    int source = ft->getSourceId();
    int destination = ft->getDestinationId();
    int type = ft->getType();
    int type_packet = ft->getType_packet();
    simtime_t creationTime = ft->getFlitCreationTime();
    if (type == 2){
        Packet *pk = new Packet("packet");
        pk->setSrcAddr(source);
        pk->setByteLength(size);
        pk->setDestAddr(destination);
        for (int i = 0; i<7;i++){
            pk->setReceiveData(i,ft->getReceiveData(i));
            pk->setSendData(i,ft->getSendData(i));
        }
        pk->setType(type_packet);
        if (type_packet == 0){
            pk->setCreationTime(creationTime);
        }
        for (int j = 0; j < pk->getDataArraySize(); j++) {
            pk->setData(j,ft->getData(j));
        }
        take(pk);
        send(pk,"out");
    }
    else{
        delete ft;
    }
}



