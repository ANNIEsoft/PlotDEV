#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <string>
#include <iostream>
#include <Plot.h>

class Template: public Plot {
  
 public:
  
  Template();
  bool Initialise(Store* variables, std::map<int, std::map<int,PMT> >* PMInfo, std::vector<std::string>* SlackErrors);
  bool Execute(std::vector<CardData*> *data);
  bool Finalise();
  
  
 private:

  std::map<int,std::map<int,PMT> >* PMTinfo;
  std::vector<std::string>* Slackerrors;
  std::string outpath;
   
};

#endif
