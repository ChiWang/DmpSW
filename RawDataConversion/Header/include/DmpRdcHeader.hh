/*=============================================================================
#       FileName :          DmpRdcHeader.hh
#       Version  :          0.0.1
#       Author   :          USTC    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-08-04   11:06:08
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-08-16   15:26:06
=============================================================================*/

#ifndef DmpRdcHeader_H
#define DmpRdcHeader_H

#include "DmpRdcVBasic.hh"

class DmpEvtHeaderRaw;

class DmpRdcHeader : public DmpRdcVBasic {
 public:
  DmpRdcHeader();
  ~DmpRdcHeader();
  void  Initialize();
  Bool_t    Conversion(ifstream* HexData);
  DmpEvtHeaderRaw*  GetEventPointer() const   {return fEvt;}

 private:
  DmpEvtHeaderRaw*  fEvt;

};

#endif


