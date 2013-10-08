/*=============================================================================
#       FileName :          DmpRdcVBasic.cc
#       Version  :          0.0.1
#       Author   :          USTC    (ylzhang1@mail.ustc.edu.cn chiwang@mail.ustc.edu.cn zhzhy@mail.ustc.edu.cn)
#       Time     :          2013-08-06   10:09:08
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-04   00:50:24
=============================================================================*/

#include "TROOT.h"
#include "DmpRdcVBasic.hh"

#ifdef DEBUG
TString DmpRdcVBasic::fConnectorPath="../DetectorCondition/Connector/";
#endif
#ifdef RELEASE
TString DmpRdcVBasic::fConnectorPath="Absolute path of /prefix/share/connector";
#endif

DmpRdcVBasic::DmpRdcVBasic()
 :fTree(0),
  fDataLength(0),
  fTrigger(0)
{
}

DmpRdcVBasic::~DmpRdcVBasic(){
}

Bool_t DmpRdcVBasic::SetConnector(){
}

Bool_t DmpRdcVBasic::Conversion(ifstream* HexData){
  // read out fDataLength of HexData.
  Int_t tmp;
  for (Int_t n=0;n<fDataLength;++n) {
    HexData->read((char *) (&tmp), 1);
  }
}


