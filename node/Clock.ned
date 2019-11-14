package node;
//
// Clock module which emits a clock signal in regular intervals.
// Other modules can subscribe to this signal for synchronization.
//
simple Clock {
    parameters:
        @signal[clock](type=unsigned long);
        @display("i=device/clock");
        double inter @unit(s); // The interval between two clock signal emissions
}