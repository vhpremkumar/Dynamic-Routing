package node;

//
// Application model to generate traffic for the network.
//
simple Cpu
{
    parameters:
        int address;  // local node address 
        bool sendMsgOnInit; 
        @signal[endToEndDelay](type="simtime_t"); 
        @signal[sourceAddress](type="long");
        @signal[destinationAddress](type="long");
        @signal[weightMatrix01](type="long");  
        @signal[weightMatrix10](type="long");
        @signal[weightMatrix02](type="long");
        @signal[weightMatrix20](type="long");  
        @signal[weightMatrix05](type="long");  
        @signal[weightMatrix50](type="long");
        @signal[weightMatrix06](type="long");  
        @signal[weightMatrix60](type="long");  
        @signal[weightMatrix12](type="long");  
        @signal[weightMatrix21](type="long");  
        @signal[weightMatrix23](type="long");       
        @signal[weightMatrix32](type="long");
        @signal[weightMatrix34](type="long");  
        @signal[weightMatrix43](type="long");    
        @signal[weightMatrix35](type="long");    
        @signal[weightMatrix53](type="long");    
        @signal[weightMatrix36](type="long");    
        @signal[weightMatrix63](type="long");    
        @signal[weightMatrix45](type="long");    
        @signal[weightMatrix54](type="long"); 
        @statistic[endToEndDelay](title="end-to-end delay of arrived packets";unit=s;record=timeavg,count,sum,mean,vector,stats,histogram,min,max);         
        @statistic[sourceAddress](title="source address of arrived packets";record=vector);
        @statistic[sourceAddress](title="destination address of arrived packets";record=vector);
        @statistic[weightMatrix01](title="Weight Matrix 01";unit=bytes;record=timeavg,count,sum,mean,vector,stats,histogram);
        @statistic[weightMatrix10](title="Weight Matrix 10";unit=bytes;record=timeavg,count,sum,mean,vector,stats,histogram);
        @statistic[weightMatrix02](title="Weight Matrix 02";unit=bytes;record=timeavg,count,sum,mean,vector,stats,histogram);
        @statistic[weightMatrix20](title="Weight Matrix 20";unit=bytes;record=timeavg,count,sum,mean,vector,stats,histogram);
        @statistic[weightMatrix05](title="Weight Matrix 05";unit=bytes;record=timeavg,count,sum,mean,vector,stats,histogram);
        @statistic[weightMatrix50](title="Weight Matrix 50";unit=bytes;record=timeavg,count,sum,mean,vector,stats,histogram);
        @statistic[weightMatrix06](title="Weight Matrix 06";unit=bytes;record=timeavg,count,sum,mean,vector,stats,histogram);
        @statistic[weightMatrix60](title="Weight Matrix 60";unit=bytes;record=timeavg,count,sum,mean,vector,stats,histogram);
        @statistic[weightMatrix12](title="Weight Matrix 12";unit=bytes;record=timeavg,count,sum,mean,vector,stats,histogram);
        @statistic[weightMatrix21](title="Weight Matrix 21";unit=bytes;record=timeavg,count,sum,mean,vector,stats,histogram);
        @statistic[weightMatrix23](title="Weight Matrix 23";unit=bytes;record=timeavg,count,sum,mean,vector,stats,histogram);
        @statistic[weightMatrix32](title="Weight Matrix 32";unit=bytes;record=timeavg,count,sum,mean,vector,stats,histogram);
        @statistic[weightMatrix34](title="Weight Matrix 34";unit=bytes;record=timeavg,count,sum,mean,vector,stats,histogram);
        @statistic[weightMatrix43](title="Weight Matrix 43";unit=bytes;record=timeavg,count,sum,mean,vector,stats,histogram);
        @statistic[weightMatrix35](title="Weight Matrix 35";unit=bytes;record=timeavg,count,sum,mean,vector,stats,histogram);
        @statistic[weightMatrix53](title="Weight Matrix 53";unit=bytes;record=timeavg,count,sum,mean,vector,stats,histogram);
        @statistic[weightMatrix36](title="Weight Matrix 36";unit=bytes;record=timeavg,count,sum,mean,vector,stats,histogram);
        @statistic[weightMatrix63](title="Weight Matrix 63";unit=bytes;record=timeavg,count,sum,mean,vector,stats,histogram);
        @statistic[weightMatrix45](title="Weight Matrix 45";unit=bytes;record=timeavg,count,sum,mean,vector,stats,histogram);
        @statistic[weightMatrix54](title="Weight Matrix 54";unit=bytes;record=timeavg,count,sum,mean,vector,stats,histogram);
    gates:
        input in;
        output out;
}


