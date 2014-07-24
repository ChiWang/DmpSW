/*
 *  $Id: DmpAlgCalBgoPed.cc, 2014-07-24 09:36:02 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/07/2014
*/

#include <stdio.h>

#include "TClonesArray.h"
#include "TH1F.h"

#include "DmpEvtRdcHeader.h"
#include "DmpEvtRdcBgoBar.h"
#include "DmpDataBgoBarPed.h"
#include "DmpAlgCalBgoPed.h"
#include "DmpDataBuffer.h"

//-------------------------------------------------------------------
DmpAlgCalBgoPed::DmpAlgCalBgoPed()
 :DmpVAlg("Cal/Bgo/Ped"),
  fRawDataEvtHeader(0),
  fRawDataBgo(0),
  fCalDataBgo(0)
{
}

//-------------------------------------------------------------------
DmpAlgCalBgoPed::~DmpAlgCalBgoPed(){
}

//-------------------------------------------------------------------
bool DmpAlgCalBgoPed::Initialize(){
  // read input data
  fRawDataEvtHeader = dynamic_cast<DmpEvtRdcHeader*>gDataBuffer->ReadObject("Event/Rdc/EventHeader");
  if(0 == fRawDataEvtHeader){
    DmpLogError<<"[DmpAlgCalBgoPed::Initialize] didn't find data \'Event/Rdc/EventHeader\'"<<DmpLogEndl;
    fIniStatus = false;
    return fIniStatus;
  }
  fRawDataBgo = dynamic_cast<TClonesArray*>gDataBuffer->ReadObject("Event/Rdc/Bgo");
  if(0 == fRawDataBgo){
    DmpLogError<<"[DmpAlgCalBgoPed::Initialize] didn't find data \'Event/Rdc/Bgo\'"<<DmpLogEndl;
    fIniStatus = false;
    return fIniStatus;
  }
  // create output data holder
  fCalDataBgo = new TClonesArray("DmpDataBgoBarPed",300);
  if(not gDataBuffer->RegisterObject("Calibration/Bgo/Pedestal",fCalDataBgo)){
    fIniStatus = false;
    return fIniStatus;
  }
  // create Hist map
  for(short l=0;l<DmpDetector::Bgo::kPlaneNo*2;++l){
    for(short b=0;b<(DmpDetector::Bgo::kBarNo+DmpDetector::Bgo::kRefBarNo);++b){
      for(short s=0;s<DmpDetector::Bgo::kSideNo;++s){
        for(short d=0;d<DmpDetector::Bgo::kDyNo;++d){
          char name[50];
          snprintf(name,50,"Bar%05d_Dy%02d",l*100+b,s*10+d);
          fPedHist.insert(std::make_pair(name,new TH1F(name,name,1000,-500,1500)));
        }
      }
    }
  }
  return fIniStatus;
}

//-------------------------------------------------------------------
bool DmpAlgCalBgoPed::ProcessThisEvent(){
  short nBars = fRawDataBgo->GetEntriesFast();
  DmpEvtRdcBgoBar  aBar = 0;
  for(short i=0;i<nBars;++i){
    aBar = dynamic_cast<DmpEvtRdcBgoBar*>(fRawDataBgo->At(i));
  }
  return true;
}

//-------------------------------------------------------------------
bool DmpAlgCalBgoPed::Finalize(){
  fCalDataBgo->Delete();
  return true;
 // save hist
}


