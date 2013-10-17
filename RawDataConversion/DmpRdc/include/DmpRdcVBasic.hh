/*=============================================================================
#       FileName :          DmpRdcVBasic.hh
#       Version  :          0.0.1
#       Author   :          USTC    (ylzhang1@mail.ustc.edu.cn chiwang@mail.ustc.edu.cn zhzhy@mail.ustc.edu.cn)
#       Time     :          2013-08-06   10:01:34
#
#------------------------------------------------------------------------------
#       Description  :
#           abstruct class, used by classes:
#           DmpRdcHeader
#           DmpRdcPsd
#           DmpRdcStk
#           DmpRdcBgo
#           DmpRdcNud
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-05   17:35:10
=============================================================================*/

#ifndef DmpRdcVBasic_H
#define DmpRdcVBasic_H

#include <fstream>      // Conversion(ifstream* HexData)

#include "TString.h"

class DmpRdcVBasic {
 public:
  DmpRdcVBasic();
  virtual ~DmpRdcVBasic();

  virtual Bool_t  SetConnector();                   // FEE <-> Detector connection
  virtual Bool_t  Conversion(ifstream* HexData);    // use this function at where start of current sub-detector data in whole Hex data(detector data) pipe
  inline Int_t  GetTrigger() const  {return fTrigger;}

 protected:
  Short_t    fDataLength;               // data length of current event of a sub-detector
  Short_t    fTrigger;                  // event trigger

 protected:
  static TString    fConnectorPath;     // connection files of FEE to Detector

};

#endif


