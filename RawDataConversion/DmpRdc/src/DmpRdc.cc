/*=============================================================================
#       FileName :          DmpRdc.cc
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-08-07   10:52:13
#
#------------------------------------------------------------------------------
#       Description  :
#           This file only implement functions of manager, functions of sub-detector in ../sub-det/src/*.cc
#           closed TriggerMatch()
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-07   00:57:47
=============================================================================*/

#include <iostream>

#include "TFile.h"
#include "TTree.h"

#include "DmpRdc.hh"

#include "DmpEvtHeader.hh"
#include "DmpEvtPsdRaw.hh"
#include "DmpEvtStkRaw.hh"
#include "DmpEvtBgoRaw.hh"
#include "DmpEvtNudRaw.hh"

ClassImp(DmpRdc)

//------------------------------------------------------------------------------
DmpRdc* DmpRdc::fInstance = 0;
//------------------------------------------------------------------------------
#ifdef Dmp_DEBUG
TString DmpRdc::fConnectorPath="../DetectorCondition/Connector";
#endif
#ifdef Dmp_RELEASE
TString DmpRdc::fConnectorPath="Absolute path of /prefix/share/connector";
#endif

//------------------------------------------------------------------------------
DmpRdc* DmpRdc::GetInstance(){
  if (fInstance == 0 ){
    fInstance = new DmpRdc();
  }
  return fInstance;
}

//------------------------------------------------------------------------------
void DmpRdc::Clear(){
  if (fInstance != 0 ){
    delete fInstance;
    fInstance = 0;
  }
  std::cout<<"\nDelete DmpRdc Manager"<<std::endl;
}

//------------------------------------------------------------------------------
Bool_t DmpRdc::Core(){

  fHexData = new ifstream(fInDataPath+fDataName,std::ios::in|std::ios::binary);
  if (!fHexData->good()) {
    std::cout<<"\n\t---->Warning: open "<<fInDataPath+fDataName<<" failed"<<std::endl;
    return false;
  } else {
    std::cout<<"\n\t---->Reading "<<fInDataPath+fDataName<<std::endl;
  }

  fTree = new TTree("Dampe_raw","raw_event");
  fTree->Branch("Header","DmpEvtHeader",&fHeader);
  fTree->Branch("Psd","DmpEvtPsdRaw",&fPsd);
  fTree->Branch("Stk","DmpEvtStkRaw",&fStk);
  fTree->Branch("Bgo","DmpEvtBgoRaw",&fBgo);
  fTree->Branch("Nud","DmpEvtNudRaw",&fNud);

  //loop of event package. set the order of sub-detector as the order of FEE in fDataName
  for (Long64_t nEvt=0;!fHexData->eof();++nEvt) {

    if (ConversionHeader()) continue;
    if (ConversionPsd()) continue;
    if (ConversionStk()) continue;
    if (ConversionBgo()) continue;
    if (ConversionNud()) continue;

    if (TriggerMatch()) {
      fHeader->CountEvent();
      fTree->Fill();
#ifdef Dmp_DEBUG
      std::cout<<"Fill event "<<std::dec<<fHeader->GetEventID()<<std::endl<<std::endl;
#endif
    } else {
      continue;
    }
  }

  fDataName.ReplaceAll(".dat","-raw.root");
  TFile *outRootFile = new TFile(fOutDataPath+fDataName,"RECREATE");
  fTree->Write();
  outRootFile->Close();
  delete outRootFile;
  fHeader->Reset();      // reset event ID, waiting next input data file
  fHexData->close();
  delete fHexData;
  return true;
}

//------------------------------------------------------------------------------
DmpRdc::DmpRdc()
 :fPsd(0),
  fStk(0),
  fBgo(0),
  fNud(0)
{
  fPsd = new DmpEvtPsdRaw();
  fStk = new DmpEvtStkRaw();
  fBgo = new DmpEvtBgoRaw();
  fNud = new DmpEvtNudRaw();
  fTrigger.insert(std::make_pair("Header",0));
  fTrigger.insert(std::make_pair("Psd",0));
  fTrigger.insert(std::make_pair("Stk",0));
  fTrigger.insert(std::make_pair("Bgo",0));
  fTrigger.insert(std::make_pair("Nud",0));
}

//------------------------------------------------------------------------------
DmpRdc::~DmpRdc(){
  delete fPsd;
  delete fStk;
  delete fBgo;
  delete fNud;
}

//------------------------------------------------------------------------------
Bool_t DmpRdc::TriggerMatch() {
  if (fTrigger["Bgo"] == fTrigger["Psd"] && fTrigger["Bgo"] == fTrigger["Stk"] && fTrigger["Bgo"] == fTrigger["Nud"] && fTrigger["Bgo"] == fTrigger["Header"]) {
  return true;
  } else {
    std::cerr<<"\t\ttrigger not match\n"<<std::endl;
    std::cerr<<"Header = "<<fTrigger["Header"]<<"\tPsd = "<<fTrigger["Psd"]<<"\tStk = "<<fTrigger["Stk"]<<"\tBgo = "<<fTrigger["Nud"]<<std::endl;
  }
  return true;
}

//------------------------------------------------------------------------------
Bool_t DmpRdc::ConversionHeader(){
#ifdef Dmp_DEBUG
  std::cout<<"\t\t\tEvent Conversion:\tHeader"<<std::endl;
#endif
  Short_t tmp=0;
  fHexData->read((char*)(&tmp),1);
  if (tmp!=0xe2)    return false;
  fHexData->read((char*)(&tmp),1);
  if (tmp!=0x25)    return false;
  fHexData->read((char*)(&tmp),1);
  if (tmp!=0x08)    return false;
  fHexData->read((char*)(&tmp),1);
  if (tmp!=0x13) {
    std::cout<<"\t\t\t\t----> Searching 0xe225 0813"<<std::endl;
    return false;
  } else {
    fHeader->CountPackage();
  }
  fHexData->read((char*)(&tmp),1);           //this needed
  fHexData->read((char*)(&fTrigger["Header"]),1);
  fHexData->read((char*)(&tmp),1);           //Datalongth
  fHexData->read((char*)(&tmp),1);           //Datalongth

  static Short_t time[8], i;       // 8 bytes, recored time
  for (i=0;i<8;++i) {
    time[i]=0;
    fHexData->read((char*)(&time[i]),1);
  }

  fHeader->SetTime(time,8);
#ifdef Dmp_DEBUG
std::cout<<"\t\ttrigger = "<<fTrigger["Header"]<<"\tPcg = "<<fHeader->GetPackageID()<<std::endl;
#endif

  return true;
}

