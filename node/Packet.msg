//
// Represents a packet in the network.
//
packet Packet
{
    int srcAddr @packetData;
    int destAddr @packetData;
    int type @packetData; // 0: data, 1: hb-req, 2: hb-res, 3: hb-init  
    int data[1024] @packetData;   
    int sendData[7] @packetData;  // 1 2 3 4
    int receiveData[7]@packetData; // 1 2 3 4
    simtime_t creationTime;@packetData;
}

