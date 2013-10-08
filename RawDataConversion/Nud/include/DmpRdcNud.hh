
#ifndef DmpRdcNud_H
#define DmpRdcNud_H

#include <map>
#include "DmpRdcVBasic.hh"

class DmpEvtNudRaw;

class DmpRdcNud : public DmpRdcVBasic {
 public:
  DmpRdcNud();
  ~DmpRdcNud();
  Bool_t  SetConnector();
  Bool_t  Conversion(ifstream* HexData);
  DmpEvtNudRaw*   GetEventPointer() const   {return fEvt;}

 private:
  DmpEvtNudRaw* fEvt;

  std::map<Int_t, Short_t*>  Connector;     //FEE 2 Detector       
    //Connector[FEEID*100+ChannelID][0]     Layer ID                 
    //Connector[FEEID*100+ChannelID][1]     Bar ID                   
    //Connector[FEEID*100+ChannelID][2]     Side ID                  
    //Connector[FEEID*100+ChannelID][3]     Dy ID 
};

#endif


