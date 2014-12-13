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
#include "DmpDetectorBgo.h"

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
  /*
  fRawDataEvtHeader = dynamic_cast<DmpEvtRdcHeader*>(gDataBuffer->ReadObject("Event/Rdc/EventHeader"));
  if(0 == fRawDataEvtHeader){
    DmpLogError<<"[DmpAlgCalBgoPed::Initialize] didn't find data \'Event/Rdc/EventHeader\'"<<DmpLogEndl;
    fIniStatus = false;
    return fIniStatus;
  }
  */
  fRawDataBgo = dynamic_cast<TClonesArray*>(gDataBuffer->ReadObject("Event/Rdc/Bgo"));
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
      Dmp1DMapTH1F aPedMapBar;
      fPedHist.insert(std::make_pair(l*100+b,aPedMapBar));
      for(short s=0;s<DmpDetector::Bgo::kSideNo;++s){
        for(short d=0;d<DmpDetector::Bgo::kDyNo;++d){
          char name[50];
          snprintf(name,50,"BgoPed_Bar%04d_Dy%02d",l*100+b,s*10+d*3+2);
          fPedHist[l*100+b].insert(std::make_pair(s*10+d*3+2,new TH1F(name,name,1000,-500,1500)));
        }
      }
    }
  }
  return fIniStatus;
}

//-------------------------------------------------------------------
bool DmpAlgCalBgoPed::ProcessThisEvent(){
  DmpEvtRdcBgoBar  *aBar=0;
  short nBars = fRawDataBgo->GetEntriesFast();
  for(short barID=0;barID<nBars;++barID){
    aBar = dynamic_cast<DmpEvtRdcBgoBar*>(fRawDataBgo->At(barID));
    short globalBarID = aBar->GetGlobalBarID();
    std::vector<short> dynodeID = aBar->GetDynodeID();
    std::cout<<"\nglobalBarID = "<<globalBarID;
    for(short i=0;i<dynodeID.size();++i){
      std::cout<<"\ti = "<<dynodeID[i]<<" v = "<<aBar->GetSignal(dynodeID[i]);
      fPedHist[globalBarID][dynodeID[i]]->Fill(aBar->GetSignal(dynodeID[i]));
    }
    std::cout<<std::endl;
  }
  return true;
}

//-------------------------------------------------------------------
#include <TFile.h>
bool DmpAlgCalBgoPed::Finalize(){
  fCalDataBgo->Delete();
  TFile *histRootFile = new TFile(fHistRootFileName,"recreate");
  for(Dmp2DMapTH1F::iterator aBarMap=fPedHist.begin();aBarMap!=fPedHist.end();++aBarMap){
    short globalBarID = aBarMap->first;
    for(Dmp1DMapTH1F::iterator it=aBarMap->second.begin();it!=aBarMap->second.end();++it){
      fPedHist[globalBarID][it->first]->Write();
// *
// *  TODO: fit and save output data 
// *
      delete fPedHist[globalBarID][it->first];
    }
  }
  delete histRootFile;
  return true;
}


