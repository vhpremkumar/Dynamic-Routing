package node;

//
// Application model to generate traffic for the network.
//
module App
{
    parameters:
        int address;  // local node address
        bool sendMsgOnInit; // set true to for master node
        @display("i=block/browser");      
    gates:
        inout net;
    submodules:
        cpu: Cpu {
            parameters:
                @display("p=190,200");
                address = address;
        }
        queue: Queue {
            parameters:
                @display("p=54,200,column");
        }
        encoder: Encoder {
            parameters:
                @display("p=123,200");
                address = address;
        }
        decoder: Decoder {
            parameters:
                @display("p=257,200");
        }
    connections:
        net$i --> decoder.in;
        decoder.out --> cpu.in;
        cpu.out --> encoder.in;
        encoder.out --> queue.in;
        queue.out --> net$o;
}


