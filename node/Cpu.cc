/*
 * Cpu.cc
 *
 *  Created on: 02.08.2019
 *      Author: hari_pr
 */
#include <vector>
#include <omnetpp.h>
#include "Packet_m.h"
#include "Flit_m.h"
#include "Encoder.h"

using namespace omnetpp;

class Cpu : public cSimpleModule, public cListener
{
  private:
    int timeCounterHb;
    int timeCounterFast;
    int timeCounterMedium;
    int timeCounterSlow;
    int totalReceived[7];
    int totalSent[7];
    simsignal_t endToEndDelaySignal;
    simsignal_t sourceAddressSignal;
    simsignal_t destinationAddressSignal;
    simsignal_t weightMatrix01signal;
    simsignal_t weightMatrix10signal;
    simsignal_t weightMatrix02signal;
    simsignal_t weightMatrix20signal;
    simsignal_t weightMatrix05signal;
    simsignal_t weightMatrix50signal;
    simsignal_t weightMatrix06signal;
    simsignal_t weightMatrix60signal;
    simsignal_t weightMatrix12signal;
    simsignal_t weightMatrix21signal;
    simsignal_t weightMatrix23signal;
    simsignal_t weightMatrix32signal;
    simsignal_t weightMatrix34signal;
    simsignal_t weightMatrix43signal;
    simsignal_t weightMatrix35signal;
    simsignal_t weightMatrix53signal;
    simsignal_t weightMatrix36signal;
    simsignal_t weightMatrix63signal;
    simsignal_t weightMatrix45signal;
    simsignal_t weightMatrix54signal;
  public:
    Cpu();
    virtual ~Cpu();
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void receiveSignal(cComponent* source, simsignal_t signalID, unsigned long l, cObject* details) override;
    virtual void sendHeartBeat();
    virtual void sendFast();
    virtual void sendMedium();
    virtual void sendSlow();
    virtual void handleHbRequest(Packet* packet);
    virtual void handleHbReply(Packet* packet);
    virtual void handleData(Packet* packet);
    virtual void handleHbInit(Packet* packet);
    virtual void serializeMatrix(Packet* packet);
    virtual void deserializeMatrix(Packet* packet);
    virtual void printSerializeMatrix(Packet* packet);
    virtual void printDeserializeMatrix(Packet* packet);
    virtual void resetBuffer();
};

Define_Module(Cpu);
Cpu::Cpu()
{
    resetBuffer();
}

Cpu::~Cpu()
{
}

void Cpu::initialize()
{
   // subscribe to clock signal
   getSimulation()->getSystemModule()->subscribe("clock", this);
   endToEndDelaySignal = registerSignal("endToEndDelay");
   sourceAddressSignal = registerSignal("sourceAddress");
   destinationAddressSignal = registerSignal("destinationAddress");
   weightMatrix01signal = registerSignal("weightMatrix01");
   weightMatrix10signal = registerSignal("weightMatrix10");
   weightMatrix02signal = registerSignal("weightMatrix02");
   weightMatrix20signal = registerSignal("weightMatrix20");
   weightMatrix05signal = registerSignal("weightMatrix05");
   weightMatrix50signal = registerSignal("weightMatrix50");
   weightMatrix06signal = registerSignal("weightMatrix06");
   weightMatrix60signal = registerSignal("weightMatrix60");
   weightMatrix12signal = registerSignal("weightMatrix12");
   weightMatrix21signal = registerSignal("weightMatrix21");
   weightMatrix23signal = registerSignal("weightMatrix23");
   weightMatrix32signal = registerSignal("weightMatrix32");
   weightMatrix34signal = registerSignal("weightMatrix34");
   weightMatrix43signal = registerSignal("weightMatrix43");
   weightMatrix35signal = registerSignal("weightMatrix35");
   weightMatrix53signal = registerSignal("weightMatrix53");
   weightMatrix36signal = registerSignal("weightMatrix36");
   weightMatrix63signal = registerSignal("weightMatrix63");
   weightMatrix45signal = registerSignal("weightMatrix45");
   weightMatrix54signal = registerSignal("weightMatrix54");
   timeCounterHb = 0;
   timeCounterFast = 0;
   timeCounterMedium = 0;
   timeCounterSlow = 0;
//   WATCH(timeCounterHb);
   if (par("sendMsgOnInit").boolValue() == true) {
        Packet *hb = new Packet("packet");
        hb->setType(3);
        scheduleAt(0, hb);
   }
}
void Cpu::handleMessage(cMessage *msg)
{
    Packet* packet = (Packet*) msg;
    int type = packet->getType();
    switch (type) {
        case 0: // data
            handleData(packet);
        break;
        case 1: // HB request
            handleHbRequest(packet);
        break;
        case 2: // HB reply
            handleHbReply(packet);
        break;
        case 3: // HB reply
            handleHbInit(packet);
        break;
    }
}
void Cpu::receiveSignal(cComponent* source, simsignal_t signalID, unsigned long l, cObject* details)
{
    if(signalID == registerSignal("clock")) {
            timeCounterHb++;
            timeCounterFast++;
            timeCounterMedium++;
            timeCounterSlow++;
            //25us
            if (timeCounterHb == 500){
                sendHeartBeat();
                timeCounterHb = 0;
            }

            if ((uniform(0,9999) < 3000) && (timeCounterFast >20)){
                sendFast();
                timeCounterFast = 0;
            }

            if ((uniform(0,9999) < 1000) && (timeCounterMedium > 50)){
                sendMedium();
                timeCounterMedium = 0;
            }

            if ((uniform(0,9999) < 100) && (timeCounterSlow > 100)){
                sendSlow();
                timeCounterSlow = 0;
            }
    }
}
void Cpu::sendHeartBeat()
{
    if (par("sendMsgOnInit").boolValue() == true){
        Enter_Method("sendHeartBeat()");
        for (int i = 0; i < 7; i++){
            Encoder* encoder = static_cast<Encoder *>(this->getParentModule()->getSubmodule("encoder"));
            encoder->updateWeightMatrix(i, 0 , totalReceived[i]);
            resetBuffer();
        }
        Encoder* encoder = static_cast<Encoder *>(this->getParentModule()->getSubmodule("encoder"));
        encoder->updateSelfMatrix();
        emit(weightMatrix01signal, encoder->network->topology[0][1]);
        emit(weightMatrix10signal, encoder->network->topology[1][0]);
        emit(weightMatrix02signal, encoder->network->topology[0][2]);
        emit(weightMatrix20signal, encoder->network->topology[2][0]);
        emit(weightMatrix05signal, encoder->network->topology[0][5]);
        emit(weightMatrix50signal, encoder->network->topology[5][0]);
        emit(weightMatrix06signal, encoder->network->topology[0][6]);
        emit(weightMatrix60signal, encoder->network->topology[6][0]);
        emit(weightMatrix12signal, encoder->network->topology[1][2]);
        emit(weightMatrix21signal, encoder->network->topology[2][1]);
        emit(weightMatrix23signal, encoder->network->topology[2][3]);
        emit(weightMatrix32signal, encoder->network->topology[3][2]);
        emit(weightMatrix34signal, encoder->network->topology[3][4]);
        emit(weightMatrix43signal, encoder->network->topology[4][3]);
        emit(weightMatrix35signal, encoder->network->topology[3][5]);
        emit(weightMatrix53signal, encoder->network->topology[5][3]);
        emit(weightMatrix36signal, encoder->network->topology[3][6]);
        emit(weightMatrix63signal, encoder->network->topology[6][3]);
        emit(weightMatrix45signal, encoder->network->topology[4][5]);
        emit(weightMatrix54signal, encoder->network->topology[5][4]);
        Packet *pk1 = new Packet("packet");
        pk1->setSrcAddr(0);
        pk1->setByteLength(4);
        pk1->setDestAddr(1);
        pk1->setType(1);
        serializeMatrix(pk1);
        send(pk1,"out");

        Packet *pk2 = new Packet("packet");
        pk2->setSrcAddr(0);
        pk2->setByteLength(4);
        pk2->setDestAddr(2);
        pk2->setType(1);
        serializeMatrix(pk2);
        send(pk2,"out");

        Packet *pk3 = new Packet("packet");
        pk3->setSrcAddr(0);
        pk3->setByteLength(4);
        pk3->setDestAddr(3);
        pk3->setType(1);
        serializeMatrix(pk3);
        send(pk3,"out");

        Packet *pk4 = new Packet("packet");
        pk4->setSrcAddr(0);
        pk4->setByteLength(4);
        pk4->setDestAddr(4);
        pk4->setType(1);
        serializeMatrix(pk4);
        send(pk4,"out");

        Packet *pk5 = new Packet("packet");
        pk5->setSrcAddr(0);
        pk5->setByteLength(4);
        pk5->setDestAddr(5);
        pk5->setType(1);
        serializeMatrix(pk5);
        send(pk5,"out");

        Packet *pk6 = new Packet("packet");
        pk6->setSrcAddr(0);
        pk6->setByteLength(4);
        pk6->setDestAddr(6);
        pk6->setType(1);
        serializeMatrix(pk6);
        send(pk6,"out");
        encoder->resetMatrix(); //set matrix to 0
    }
}
void Cpu::sendFast()
{
    if ((int)par("address") == intuniform(0,6)){
        Packet *pk = new Packet("packet");
        pk->setSrcAddr((int)par("address"));
        pk->setByteLength(intuniform(5,10));
        pk->setDestAddr(intuniform(0,6));
        pk->setType(0);
        pk->setCreationTime(simTime());
        totalSent[pk->getDestAddr()] += pk->getByteLength();
        take(pk);
        send(pk,"out");
    }
}
void Cpu::sendMedium()
{
    if ((int)par("address") == intuniform(0,6)){
          Packet *pk = new Packet("packet");
          pk->setSrcAddr((int)par("address"));
          pk->setByteLength(intuniform(10,20));
          pk->setDestAddr(intuniform(0,6));
          pk->setType(0);
          pk->setCreationTime(simTime());
          totalSent[pk->getDestAddr()] += pk->getByteLength();
          take(pk);
          send(pk,"out");
      }
}
void Cpu::sendSlow()
{
    if ((int)par("address") == intuniform(0,6)){
          Packet *pk = new Packet("packet");
          pk->setSrcAddr((int)par("address"));
          pk->setByteLength(intuniform(50,100));
          pk->setDestAddr(intuniform(0,6));
          pk->setType(0);
          pk->setCreationTime(simTime());
          totalSent[pk->getDestAddr()] += pk->getByteLength();
          take(pk);
          send(pk,"out");
      }
}
void Cpu::handleHbInit(Packet* packet)
{
    if (par("sendMsgOnInit").boolValue() == true){
        sendHeartBeat();
    }
}
void Cpu::handleHbRequest(Packet* packet)
{
    int source = packet->getDestAddr();
    int destination = 0;
    int size = packet->getByteLength();
    if (source != destination) {
        if ((int)par("address") == source){
            deserializeMatrix(packet);
            Packet *packet = new Packet("packet");
            packet->setSrcAddr(source);
            packet->setByteLength(size);
            packet->setDestAddr(destination);
            packet->setType(2);
            for (int i = 0; i<7;i++){
                packet->setReceiveData(i,totalReceived[i]);
                packet->setSendData(i,totalSent[i]);
            }
            serializeMatrix(packet);
            resetBuffer();
            take(packet);
            send(packet,"out");
        }
    }
}
void Cpu::handleHbReply(Packet* packet)
{
    int source = packet->getSrcAddr();
    if ((int)par("address") != source){
        EV << "Information from: " << source<<endl;
        for (int i = 0; i < 7; i++){
            Encoder* encoder = static_cast<Encoder *>(this->getParentModule()->getSubmodule("encoder"));
            encoder->updateWeightMatrix(i, source , packet->getReceiveData(i));
        }
    }
}
void Cpu::handleData(Packet* packet)
{
    int source = packet->getSrcAddr();
    int destination = packet->getDestAddr();
    emit(endToEndDelaySignal, simTime() - packet->getCreationTime());
    emit(sourceAddressSignal, source);
    emit(destinationAddressSignal, destination);
    totalReceived[packet->getSrcAddr()] += packet->getByteLength();
    EV << "Total data Received by : "<<destination<<" from : "<<source<<" is "<<totalReceived[source]<<endl;
}
void Cpu::serializeMatrix(Packet* packet)
{
    for (size_t ii = 0; ii < 7; ii++){
       for(size_t jj = 0; jj < 7; jj++){
           Encoder* encoder = static_cast<Encoder *>(this->getParentModule()->getSubmodule("encoder"));
           Network* network = encoder->network;
           int data = network->topology[ii][jj];
           packet->setData((ii*7+jj),data);
       }
    }
    printSerializeMatrix(packet);
}
void Cpu::deserializeMatrix(Packet* packet)
{
    for (size_t ii = 0; ii < 7; ii++) {
        for (size_t jj = 0; jj < 7; jj++) {
            Encoder* encoder = static_cast<Encoder *>(this->getParentModule()->getSubmodule("encoder"));
            Network* network = encoder->network;
            network->topology[ii][jj] = packet->getData((ii*7+jj));
        }
    }
    printDeserializeMatrix(packet);
}
void Cpu::printSerializeMatrix(Packet* packet)
{
    for (size_t ii = 0; ii < 49; ii++){
        EV << "Matrix is :" << packet->getData(ii) <<endl;
    }
}
void Cpu::printDeserializeMatrix(Packet* packet)
{
    for (size_t ii = 0; ii < 7; ii++){
        for (size_t jj = 0; jj < 7; jj++) {
            EV << "Deserialized Matrix :" << packet->getData(ii*7+jj) <<endl;
        }
    }
}
void Cpu::resetBuffer()
{
    for (int i = 0; i < 7; i++){
        totalSent[i] = 0;
        totalReceived[i] = 0;
        EV << "Total Sent after reset is :" << totalSent[i]<<endl;
        EV << "Total Received after reset is :" << totalReceived[i] <<endl;
    }
}







