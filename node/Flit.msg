//
// Represents a flit in the network.
//

packet Flit
{
    int address[10];
    int addressLength;
    int data[1024];
    int hopes;
    int type;
    int type_packet;
    int sourceId;
    int destinationId;
    int size;
    int uniqueId;
    int sendData[7];
    int receiveData[7];
    simtime_t flitCreationTime;
}
