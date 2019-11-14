package networks;
import node.Router;
import node.App;
import node.Clock;
import ned.DatarateChannel;

// Random Network Topology of 7 nodes

network Network
{
    @display("bgb=819,513");
    types:
        channel C extends DatarateChannel
        {
            delay = 0.1us; //set clock 50 ns
            datarate = 50Mbps;
        }
    submodules:
        clock: Clock {
            @display("p=736.208,41.36");
        }
        app0: App {
            parameters:
                address = 0;
                sendMsgOnInit = default(true);
                @display("p=29.986,229.548");
        }
        app1: App {
            parameters:
                address = 1;
                sendMsgOnInit = default(false);
                @display("p=198.528,51.7");
        }
        app2: App {
            parameters:
                address = 2;
                @display("p=438.41602,51.7");
                sendMsgOnInit = default(false);
        }
        app3: App {
            parameters:
                address = 3;
                @display("p=644.182,229.548");
                sendMsgOnInit = default(false);
        }
        app4: App {
            parameters:
                address = 4;
                @display("p=438.41602,427.04202");
                sendMsgOnInit = default(false);
        }
        app5: App {
            parameters:
                address = 5;
                @display("p=198.528,427.04202");
                sendMsgOnInit = default(false);
        }
        app6: App {
            parameters:
                address = 6;
                @display("p=385.682,179.916");
                sendMsgOnInit = default(false);
        }
        router0: Router {
            @display("p=112.706,229.548");
        }
        router1: Router {
            @display("p=198.528,127.18201");
        }
        router2: Router {
            @display("p=438.41602,127.18201");
        }
        router3: Router {
            @display("p=551.122,229.548");
        }
        router4: Router {
            @display("p=438.41602,342.254");
        }
        router5: Router {
            @display("p=198.528,342.254");
        }
        router6: Router {
            @display("p=324.676,229.548");
        }
    connections:
        app0.net <--> router0.port++;
        app1.net <--> router1.port++;
        app2.net <--> router2.port++;
        app3.net <--> router3.port++;
        app4.net <--> router4.port++;
        app5.net <--> router5.port++;
        app6.net <--> router6.port++;
        router0.port++ <--> C <--> router1.port++;
        router0.port++ <--> C <--> router2.port++;
        router0.port++ <--> C <--> router5.port++;
        router0.port++ <--> C <--> router6.port++;
        router1.port++ <--> C <--> router2.port++;
        router2.port++ <--> C <--> router3.port++;
        router3.port++ <--> C <--> router4.port++;
        router3.port++ <--> C <--> router5.port++;
        router3.port++ <--> C <--> router6.port++;
        router4.port++ <--> C <--> router5.port++;
}


