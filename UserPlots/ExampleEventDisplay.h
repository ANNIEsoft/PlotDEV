#ifndef EXAMPLEEVENTDISPLAY_H
#define EXAMPLEEVENTDISPLAY_H

#include <string>
#include <iostream>
#include <Plot.h>

#include <TCanvas.h>
#include <TH2F.h>

class ExampleEventDisplay: public Plot {
  
 public:
  
  ExampleEventDisplay();
  bool Initialise(Store* variables, std::map<int, std::map<int,PMT> >* PMInfo, std::vector<std::string>* SlackErrors);
  bool Execute(std::vector<CardData*> *data);
  bool Finalise();
  
  
 private:

  std::map<int,std::map<int,PMT> >* PMTinfo;
  std::vector<std::string>* Slackerrors;
  std::string outpath;
   
  TCanvas* canvas;

};

#endif
