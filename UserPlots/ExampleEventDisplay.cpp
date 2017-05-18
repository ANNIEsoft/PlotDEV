#include <ExampleEventDisplay.h>

ExampleEventDisplay::ExampleEventDisplay():Plot(){};


bool ExampleEventDisplay::Initialise(Store* variables, std::map<int, std::map<int, PMT> >* PMTInfo, std::vector<std::string>* SlackErrors){

  PMTinfo=PMTInfo;
  Slackerrors=SlackErrors;

  variables->Get("OutputPath",outpath);  // Get dynamic variables like this
 
  //Initialise plots and variables here
  
  canvas=new TCanvas("canvasEventDisplay","canvasEventDisplay",600,400);

  
  return true;
 
}


bool ExampleEventDisplay::Execute(std::vector<CardData*> *data){

  try{
    
    //Fill and draw plots here
    
    TH2D EventDisplay("EventDisplay","EventDisplay",10,0,10,10,0,10);
    
    for(int card=0; card<data->size(); card++){
      
      for(int channel=0; channel<data->at(card)->channels; channel++){
	
	long sum=0;
	
	for(int bin=(data->at(card)->buffersize * channel); bin<(data->at(card)->buffersize * (channel+1)); bin++){
	  
	  sum+=data->at(card)->Data[bin];
	  
	}
	
	EventDisplay.SetBinContent((*PMTinfo)[data->at(card)->CardID][channel].gx+1, (*PMTinfo)[data->at(card)->CardID][channel].gy+1, sum);
	
      }
      
      canvas->cd();
      EventDisplay.Draw("col");
      
      std::stringstream tmp;
      
      tmp<<outpath<<"EventDisplay" << std::setfill('0') << std::setw(2) << card << ".png";
      canvas->SaveAs(tmp.str().c_str());
      
    }
    
  }

  catch(...){

    Slackerrors->push_back("EventDisplay caused an error"); 
    return false;
  }
  
  
  return true; 
  
}


bool  ExampleEventDisplay::Finalise(){
  

  /// delete and cleaen up plots and variables here

  delete canvas;
  canvas=0;

  return true;

}
