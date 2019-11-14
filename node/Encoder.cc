/*
 * Encoder.cc
 *
 *  Created on: 05.08.2019
 *      Author: hari_pr
 */

#include "Encoder.h"

Define_Module(Encoder);
Encoder::Encoder()
{
    this->network = new Network();
    for (int i = 0; i < 7; i++) {
        std::vector<std::vector<Route * > > temp;
        for (int j = 0; j < 7; j++ ) {
            temp.push_back(this->getRoutes(i, j));
        }
        routingTable.push_back(temp);
    }
    printRoutes();
}
Encoder::~Encoder()
{

}
void Encoder::initialize()
{

}
void Encoder::handleMessage(cMessage *msg)
{
    Packet *pk = check_and_cast<Packet*>(msg);
    int size = pk->getByteLength();
    int source = pk->getSrcAddr();
    int destination = pk->getDestAddr();
    simtime_t creationTime = pk->getCreationTime();
    int uniqueId = id + source*1000;
    id = (id + 1)%100;
    for(int i = 0; i < size; i++)
        {
            Flit *ft = new Flit();
            if (i == 0) {
                ft->setType(0);
            } else if ( i == size - 1) {
                ft->setType(2);
            } else {
                ft->setType(1);
            }
            ft->setType_packet(pk->getType());
            ft->setHopes(0);
            ft->setUniqueId(uniqueId);
            ft->setSourceId(source);
            ft->setDestinationId(destination);
            for (int i = 0; i<7;i++){
                ft->setReceiveData(i,pk->getReceiveData(i));
                ft->setSendData(i,pk->getSendData(i));
            }
            ft->setSize(size);
            for (int j = 0; j < pk->getDataArraySize(); j++) {
                ft->setData(j,pk->getData(j));
            }
            if (ft->getType_packet() == 0){
                ft->setFlitCreationTime(creationTime);
            }
            if ((ft->getSourceId() == source) && (source != destination)){
                if ((ft->getType_packet() == 1) && (destination == 1)){
                    ft->setKind(0);
                }
                else if ((ft->getType_packet() == 1) && (destination == 2)){
                    ft->setKind(1);
                }
                else if ((ft->getType_packet() == 1) && (destination == 3)){
                    ft->setKind(2);
                }
                else if ((ft->getType_packet() == 1) && (destination == 4)){
                    ft->setKind(3);
                }
                else if ((ft->getType_packet() == 1) && (destination == 5)){
                    ft->setKind(4);
                }
                else if ((ft->getType_packet() == 1) && (destination == 6)){
                    ft->setKind(5);
                }
                else if ((ft->getType_packet() == 2) && (source == 1)){
                    ft->setKind(0);
                }
                else if ((ft->getType_packet() == 2) && (source == 2)){
                    ft->setKind(1);
                }
                else if ((ft->getType_packet() == 2) && (source == 3)){
                    ft->setKind(2);
                }
                else if ((ft->getType_packet() == 2) && (source == 4)){
                    ft->setKind(3);
                }
                else if ((ft->getType_packet() == 2) && (source == 5)){
                    ft->setKind(4);
                }
                else if ((ft->getType_packet() == 2) && (source == 6)){
                    ft->setKind(5);
                }
                else if ((ft->getType_packet() == 0) && (source % 2 == 0)){
                    ft->setKind(6);
                }
                else if ((ft->getType_packet() == 0) && (source % 2 != 0)){
                    ft->setKind(7);
                }
                auto route = getOptimalRoute(source, destination);
                int addressSize = route->links.size();
                ft->setAddressLength(addressSize+2);
                ft->setAddress(0, 0);
                for (int j = 0; j < route->links.size(); j++){
                    int gates = route->links[j]->get_output_gate();
                    ft->setAddress((j+1),gates);
                }
                ft->setAddress((route->links.size()+1), 0);
                send(ft, "out");
            }
    }
}
std::vector<Route *> Encoder::getRoutes(int source, int destination) {
    std::vector<Route *> allRoutes;
    if (source == destination) {
        Route * route = new Route();
        allRoutes.push_back(route);
    }
    else {
        if (this->network->topology[source][destination]) {
            Route * route = new Route();
            route->addLink(new Link(source, destination, this->network));
            allRoutes.push_back(route);
        } else {
            Route * route = new Route();
            allRoutes.push_back(route);
        }
        std::vector<int> hop1;
        for (int i = 0; i < 7; i++) {
            if (this->network->topology[source][i]) {
                if (i != destination) {
                    hop1.push_back(i);
                }
            }
        }
        if (hop1.size() > 0) {
            for (int i = 0; i < hop1.size(); i++) {
                int temp_i = hop1[i];
                if (temp_i != source) {
                    if (this->network->topology[temp_i][destination]) {
                        Route * route = new Route();
                        route->addLink(new Link(source, temp_i, this->network));
                        route->addLink(new Link(temp_i, destination, this->network));
                        allRoutes.push_back(route);
                    }
                    std::vector<int> hop2;
                    for (int j = 0; j < 7; j++) {
                        if (this->network->topology[temp_i][j]) {
                            if (j != source) {
                                hop2.push_back(j);
                            }
                        }
                    }
                    for (int j = 0; j < hop2.size(); j++) {
                        int temp_j = hop2[j];
                        if (this->network->topology[temp_j][destination]) {
                            Route * route = new Route();
                            route->addLink(new Link(source, temp_i, this->network));
                            route->addLink(new Link(temp_i, temp_j, this->network));
                            route->addLink(new Link(temp_j, destination, this->network));
                            allRoutes.push_back(route);
                        }
                    }
                } else {

                }
            }
        }
    }
    return allRoutes;
}
Route* Encoder::getOptimalRoute(int source, int destination)
{
    Route* bestRoute;
        double prev_score = 1000000;
        for (int i = 0; i< routingTable[source][destination].size(); i++)
        {
            Route* intRoute  = routingTable[source][destination][i];
            int score = 0;
            for (int j = 0; j < intRoute->links.size(); j++) {
                score += network->topology[intRoute->links[j]->get_source()][intRoute->links[j]->get_destination()];
            }
            if (score < prev_score){
                prev_score = score;
                if (intRoute->links.size() == 0){
                   prev_score = 1000000;
               }
                bestRoute = intRoute;
            }
        }
        printOptimalRoute(bestRoute);
        return bestRoute;
}

void Encoder::printRoutes()
{
    //iterate routingTable and print
    for (int i=0; i < routingTable.size(); i++){
        for (int j=0; j<routingTable[i].size(); j++){
            for (int k=0; k<routingTable[i][j].size(); k++) {
                for (int l=0; l < routingTable[i][j][k]->links.size(); l++){
                        EV << "s " << routingTable[i][j][k]->links[l]->get_source() << " ";
                        EV << "d " << routingTable[i][j][k]->links[l]->get_destination() << " ";
                        EV << "go " << routingTable[i][j][k]->links[l]->get_output_gate() << " ";
                }
                EV << endl;
            }
            EV << endl;
        }
    }

}
void Encoder::printOptimalRoute(Route* route)
{
    for (int l=0; l < route->links.size(); l++){
            EV << "s " << route->links[l]->get_source() << " ";
            EV << "d " << route->links[l]->get_destination() << " ";
            EV << "go " << route->links[l]->get_output_gate() << " ";
    }
    EV << endl;
}
void Encoder::updateWeightMatrix(int source, int destination, int dataSent)
{
    Route* route = getOptimalRoute(source, destination);
    for (int i = 0; i < route->links.size(); i++){
        EV << "Putting: " << dataSent << "in link: " << route->links[i]->get_source() << " " << route->links[i]->get_destination()<<endl;
        network->temptopology[route->links[i]->get_source()][route->links[i]->get_destination()] += dataSent;
    }
}
void Encoder::resetMatrix()
{
    for (size_t ii = 0; ii < 7; ii++){
        for(size_t jj = 0; jj < 7; jj++){
            network->temptopology[ii][jj] = 0;
        }
    }
}

void Encoder::updateSelfMatrix()
{
    for (size_t ii = 0; ii < 7; ii++){
        for(size_t jj = 0; jj < 7; jj++){
            network->topology[ii][jj] = network->temptopology[ii][jj];
        }
    }
}

