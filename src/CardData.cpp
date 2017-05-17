#include "CardData.h"

void bencleanup (void *data, void *hint) {
  //  free (data);
}

CardData::~CardData(){
  //    std::cout<<" c d 1"<<std::endl;                                               
  //delete[] PMTID;
  //PMTID=0;
  // std::cout<<" c d 2"<<std::endl;                                                  
  delete[] Data;
  Data=0;
  
  delete[] triggerCounts;
  triggerCounts=0;

  delete[] Rates;
  Rates=0;
//std::cout<<" c d 3"<<std::endl;                                                   

}
