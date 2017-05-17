#include "Plot.h"
#include "Store.h"
#include "CardData.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
#include <string>

// Add your header here
#include "ExampleEventDisplay.h"

// Set size of test simulation here
#define CARDS 10
#define EVENTS 10

int main(){

  /////////////////// Dynamic Input Variables //////////////////////////////////////////////////////////////////////////////////////////
  //// Use the Store to pass any variables to your monitoring plot that you want dynamically set from the configuration file ///////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Store vars;
  vars.Set("OutputPath","./");
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  std::vector<std::string> SlackErrors;

  ///////////////////////////////////////// Creating PMT location map /////////////////////////////////////////////

  std::map<int,std::map<int,PMT> > PMTInfo; // PMT location map

  for(int card=0;card<CARDS;card++){
    for(int channel=0;channel<4;channel++){ 
      
      PMTInfo[card][channel].gx=card; 
      PMTInfo[card][channel].gy=channel;
      PMTInfo[card][channel].gz=1;
      PMTInfo[card][channel].card=card;
      PMTInfo[card][channel].channel=channel;
      PMTInfo[card][channel].PEDmean=300.0;
      PMTInfo[card][channel].PEDsigma=10.0;
	
	}
  }
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  

  //////////////////////////////////////////////////// Plots vector ////////////////////////////////////////////////////////
  std::vector<Plot*> plots;

   
  Plot *mytest = new ExampleEventDisplay();
  plots.push_back(mytest);

  // add your own plots by pushing them back here
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  for(int plotnum=0;plotnum<plots.size();plotnum++){  //looping over plots 

    plots.at(plotnum)->Initialise(&vars, &PMTInfo, &SlackErrors); // Initialising plots
  
  }

  

  for(int event=0;event<EVENTS;event++){ /// looping over simulated events

  
    std::vector<CardData*> data; /// Card Data vector
    

    ////////////////////////////// Simulating ADC output /////////////////////////////////////
    for(int card=0;card<CARDS;card++){  
      
      CardData *tmp=new CardData();
      
      tmp->LastSync=100;
      tmp->SequenceID=100;
      tmp->StartTimeSec=100;
      tmp->StartTimeNSec=100;
      tmp->StartCount=100;
      tmp->triggerNumber=1;
      tmp->triggerCounts=new uint64_t[4];                                                                                                            
      tmp->Rates= new uint32_t[4];                                                                                                                   
      tmp->CardID=card;
      tmp->channels=4; // eg number of connected PMTs                                                                                                
      tmp->buffersize=40000;
      tmp->eventsize=100;
      tmp->fullbuffsize=160000; // buffersize * num channels                                                                                        
      tmp->Data=new uint16_t[tmp->fullbuffsize];
      
      for(int d=0;d<16000;d++){
	
	tmp->Data[(d*10)]=300+(rand() %(10) + 1);
	tmp->Data[(d*10)+1]=300+(rand() %(10) + 1);
	tmp->Data[(d*10)+2]=300+(rand() %(5) + 2);
	tmp->Data[(d*10)+3]=300+(rand() %(5) + 2);
	tmp->Data[(d*10)+4]=300+(rand() %(5) + 2);
	tmp->Data[(d*10)+5]=300+(rand() %(2) + 4);
	tmp->Data[(d*10)+6]=300+(rand() %(2) + 4);
	tmp->Data[(d*10)+7]=300+(rand() %(2) + 4);
	tmp->Data[(d*10)+8]=300+(rand() %(2) + 4);
	tmp->Data[(d*10)+9]=300+(rand() %(2) + 4);
	
      }
      
      data.push_back(tmp); 
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////    


    
    for(int plotnum=0;plotnum<plots.size();plotnum++){  //looping over plots
      
      plots.at(plotnum)->Execute(&data); // Executing plots
      
    }
    
    /////////////////////////////////// Cleaning up event data ///////////////////////////// 
    for(int d=0;d<data.size();d++){
      
      delete data.at(d);
      data.at(d)=0;
    }

    data.clear();


    for(int message=0;message<SlackErrors.size();message++){

      std::cout<<"Message sent to slack: "<<SlackErrors.at(message)<<std::endl;
    }

    SlackErrors.clear();

    //////////////////////////////////////////////////////////////////////////////////////////


  }


  for(int plotnum=0;plotnum<plots.size();plotnum++){  //looping over plots

    plots.at(plotnum)->Finalise(); // Finalising plots

  }
  
  
  return 0;
  
}
