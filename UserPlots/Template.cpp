#include <Template.h>

Template::Template():Plot(){};


bool Template::Initialise(Store* variables, std::map<int, std::map<int, PMT> >* PMTInfo, std::vector<std::string>* SlackErrors){

  PMTinfo=PMTInfo;
  Slackerrors=SlackErrors;

  variables->Get("OutputPath",outpath);  // Get dynamic variables like this
 
  //Initialise plots and variables here
  
  return true;
 
}


bool Template::Execute(std::vector<CardData*> *data){

  try{
  //fill and draw plots here  
  
  }
  catch(...){
    Slackerrors->push_back("My Plot caused an error");
    return false;
  }
  
  return true; 
  
}


bool  Template::Finalise(){
  

  /// delete and cleaen up plots and variables here

  return true;

}
