
#ifndef DmpRdcPsd_H
#define DmpRdcPsd_H

#include <map>
#include "DmpRdcVBasic.hh"

class DmpEvtPsdRaw;

class DmpRdcPsd : public DmpRdcVBasic {
 public:
  DmpRdcPsd();
  ~DmpRdcPsd();
  Bool_t  SetConnector();
  Bool_t  Conversion(ifstream* HexData);
  DmpEvtPsdRaw*   GetEventPointer() const   {return fEvt;}

 private:
  DmpEvtPsdRaw*     fEvt;

  std::map<Int_t, Short_t*>  Connector;     //FEE 2 Detector       
    //Connector[FEEID*1000+ChannelID][0]     Layer ID                 
    //Connector[FEEID*1000+ChannelID][1]     Bar ID                   
    //Connector[FEEID*1000+ChannelID][2]     Side ID                  
    //Connector[FEEID*1000+ChannelID][3]     Dy ID 
};

#endif


