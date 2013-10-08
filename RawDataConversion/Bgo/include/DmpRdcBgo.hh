/*=============================================================================
#       FileName :          DmpRdcBgo.hh
#       Version  :          0.0.1
#       Author   :          USTC    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-08-04   09:56:27
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-06   15:44:06
=============================================================================*/

#ifndef DmpRdcBgo_H
#define DmpRdcBgo_H

#include <map>
#include "DmpRdcVBasic.hh"

class DmpEvtBgoRaw;

class DmpRdcBgo : public DmpRdcVBasic {
 public:
  DmpRdcBgo();
  ~DmpRdcBgo();
  Bool_t  SetConnector();                   // set std::map<Int_t,Shor_t*> Connector.
  Bool_t  Conversion(ifstream* HexData);
  DmpEvtBgoRaw*   GetEventPointer()  const  {return fEvt;}

 private:
  DmpEvtBgoRaw* fEvt;

  std::map<Int_t, Short_t*>  Connector;     //! FEE 2 Detector       
    //Connector[FEEID*1000+ChannelID][0]    Layer ID                 
    //Connector[FEEID*1000+ChannelID][1]    Bar ID                   
    //Connector[FEEID*1000+ChannelID][2]    Side ID                  
    //Connector[FEEID*1000+ChannelID][3]    Dy ID 
};

#endif

