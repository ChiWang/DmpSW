
#ifndef DmpRdcStk_H
#define DmpRdcStk_H

#include <map>
#include "DmpRdcVBasic.hh"

class DmpEvtStkRaw;

class DmpRdcStk : public DmpRdcVBasic {
 public:
  DmpRdcStk();
  ~DmpRdcStk();
  Bool_t  SetConnector();
  Bool_t  Conversion(ifstream* HexData);
  DmpEvtStkRaw*   GetEventPointer() const   {return fEvt;}

 private:
  DmpEvtStkRaw*     fEvt;

  std::map<Int_t, Short_t*>  Connector;     //FEE 2 Detector       
    //Connector[FEEID*100+ChannelID][0]     Layer ID                 
    //Connector[FEEID*100+ChannelID][1]     Bar ID                   
    //Connector[FEEID*100+ChannelID][2]     Side ID                  
    //Connector[FEEID*100+ChannelID][3]     Dy ID 
};

#endif


