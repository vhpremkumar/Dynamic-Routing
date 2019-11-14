/*
 * Encoder.h
 *
 *  Created on: 16.08.2019
 *      Author: hari_pr
 */

#ifndef NODE_ENCODER_H_
#define NODE_ENCODER_H_
#include <vector>
#include <omnetpp.h>
#include "Packet_m.h"
#include "Flit_m.h"
using namespace omnetpp;


class Network: public cSimpleModule{
    public:
        Network(){
        }
        int topology[7][7] =  { {0, 1, 1, 0, 0, 1, 1},
                                {1, 0, 1, 0, 0, 0, 0},
                                {1, 1, 0, 1, 0, 0, 0},
                                {0, 0, 1, 0, 1, 1, 1},
                                {0, 0, 0, 1, 0, 1, 0},
                                {1, 0, 0, 1, 1, 0, 0},
                                {1, 0, 0, 1, 0, 0, 0},
                              };
        int temptopology[7][7] = { {0, 1, 1, 0, 0, 1, 1},
                                   {1, 0, 1, 0, 0, 0, 0},
                                   {1, 1, 0, 1, 0, 0, 0},
                                   {0, 0, 1, 0, 1, 1, 1},
                                   {0, 0, 0, 1, 0, 1, 0},
                                   {1, 0, 0, 1, 1, 0, 0},
                                   {1, 0, 0, 1, 0, 0, 0},
                                 };
};

class Link {

    private:
        int source;
        int destination;
        int ogate;
        double weight;
        Network * network;
    public:
        Link(int _source, int _destination, Network * network) {
            this->source = _source;
            this->destination = _destination;
            this->network = network;
            switch(this->source) {
                case 0:
                    if (this->destination == 1){
                        this->ogate = 1;
                    } else if (this->destination == 2){
                        this->ogate = 2;
                    } else if (this->destination == 5){
                        this->ogate = 3;
                    } else if (this->destination == 6){
                        this->ogate = 4;
                    }
                    break;
                case 1:
                    if (this->destination == 0){
                        this->ogate = 1;
                    } else if (this->destination == 2){
                        this->ogate = 2;
                    }
                    break;
                case 2:
                    if (this->destination == 0){
                        this->ogate = 1;
                    } else if (this->destination == 1){
                        this->ogate = 2;
                    } else if (this->destination == 3){
                        this->ogate = 3;
                    }
                    break;
                case 3:
                    if (this->destination == 2){
                        this->ogate = 1;
                    } else if (this->destination == 4){
                        this->ogate = 2;
                    } else if (this->destination == 5){
                        this->ogate = 3;
                    } else if (this->destination == 6){
                        this->ogate = 4;
                    }
                    break;
                case 4:
                    if (this->destination == 3){
                        this->ogate = 1;
                    } else if (this->destination == 5){
                        this->ogate = 2;
                    }
                    break;
                case 5:
                   if (this->destination == 0){
                       this->ogate = 1;
                   } else if (this->destination == 3){
                       this->ogate = 2;
                   } else if (this->destination == 4){
                       this->ogate = 3;
                   }
                   break;
                case 6:
                    if (this->destination == 0){
                        this->ogate = 1;
                    } else if (this->destination == 3){
                        this->ogate = 2;
                    }
                    break;
            }
         }
        double get_weight() {
            return this->weight;
        }
        void set_weight(double weight) {
            this->weight = weight;
        }
        int get_output_gate() {
            return this->ogate;
        }
        void set_output_gate(int ogate) {
            this->ogate = ogate;
        }
        int get_source() {
            return this->source;
        }
        int get_destination() {
            return this->destination;
        }
        Network * get_network() {
            return this->network;
        }
};

class Route {
    public:
        Route(){ }
        void addLink(Link* link) {
            this->links.push_back(link);
        }
        std::vector<Link*> links;
};

class Encoder : public cSimpleModule
{
  public:
    int id;
    Network * network;
  public:
    Encoder();
    virtual ~Encoder();
    std::vector<Route *> getRoutes(int source, int destination);
    Route* getOptimalRoute(int source, int destination);
    void updateWeightMatrix(int source, int destination, int dataSent);
    void resetMatrix();
    void updateSelfMatrix();
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void printRoutes();
    void printOptimalRoute(Route* route);
    std::vector<std::vector<std::vector<Route * > > > routingTable;
};
#endif /* NODE_ENCODER_H_ */
