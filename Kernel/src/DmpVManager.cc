/*=====================================================================
 *   File:   DmpVManager.cc
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  13/12/2013   12:08:19
=====================================================================*/

#include <iostream>
#include "TSystem.h"

#include "DmpVManager.hh"
#include "DmpEvtHeader.hh"
#include "DmpVEvtSubDet.hh"

//------------------------------------------------------------------------------
DmpVManager::DmpEPhase  DmpVManager::fPhase=kBT2012;

//------------------------------------------------------------------------------
DmpVManager::DmpVManager()
 :fInDataPath("./"),
  fOutDataPath("./"),
  fDataName("")
{
  fHeader = new DmpEvtHeader();
  DmpVEvtSubDet::SetEventHeader(fHeader);

  std::string  ph;
  std::cout<<"\nWhich phase {kBT2012|kCT2013|kFinal}?\t";
  std::cin>>ph;
  if (ph=="kBT2012") {
    fPhase=kBT2012;
  } else if (ph=="kCT2013") {
    fPhase=kBT2012;
  } else{
    fPhase=kFinal;
  }
}

//------------------------------------------------------------------------------
DmpVManager::~DmpVManager(){
  delete fHeader;
}

//------------------------------------------------------------------------------
void DmpVManager::SetInDataPath(TString path){
  if (path.EndsWith("/")) {
    fInDataPath = path;
  } else {
    fInDataPath = path + "/";
  }
}

//------------------------------------------------------------------------------
void DmpVManager::SetOutDataPath(TString path){
  if (path.EndsWith("/")) {
    fOutDataPath = path;
  } else {
    fOutDataPath = path + "/";
  }
  gSystem->MakeDirectory(fOutDataPath);
}

//------------------------------------------------------------------------------
Int_t DmpVManager::GetDynodeIDBgo(Short_t L,Short_t B,Short_t S,Short_t D){
  return L*10000+B*100+S*10+D;
}

