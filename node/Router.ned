package node;

module Router
{
    parameters:
        @display("i=block/routing;bgb=266,416");
    gates:
        inout port[];
    submodules:
        switch: Switch {
            parameters:
                @display("p=192,200");
            gates:
                in[sizeof(port)];
                out[sizeof(port)];
        }
        queue[sizeof(port)]: Queue {
            parameters:
                @display("p=80,200,column");
        }
    connections:
        for i=0..sizeof(port)-1 {
            port$i[i] --> switch.in[i];
            switch.out[i] --> queue[i].in;
            queue[i].out --> port$o[i];
        }
}
