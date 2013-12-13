/*=============================================================================
#       FileName :          DmpFileManager.hh
#       Version  :          0.0.1
#       Author   :          DAMPE software group
#                           Chi WANG    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-17   17:21:22
#
#------------------------------------------------------------------------------
#       Description  :
#           1)  access to Database
#           2)  input output method
#           3)  Book tree, save root file
#
#------------------------------------------------------------------------------
#       History  :
#           2013/11/07  inherit from TObject.   Chi.WANG
#                                          Update:  2013-11-11   09:08:48
=============================================================================*/

#ifndef DmpFileManager_H
#define DmpFileManager_H

#include "TObject.h"
#include "TString.h"

class DmpFileManager : virtual public TObject{
/*
 * DmpFileManager
 *
 *  
 *
*/
 public:
  DmpFileManager();
  virtual ~DmpFileManager();
  virtual Bool_t Core()=0;

  void    SetInDataPath(TString);
  void    SetOutDataPath(TString);
  void    SetDataName(TString name) {fDataName = name;}
  TString GetInDataPath() const     {return fInDataPath;}
  TString GetOutDataPath() const    {return fOutDataPath;}

 protected:
  TString   fInDataPath;
  TString   fOutDataPath;
  TString   fDataName;
  
  ClassDef(DmpFileManager,0)

};

#endif


