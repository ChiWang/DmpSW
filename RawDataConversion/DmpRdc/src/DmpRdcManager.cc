/*=====================================================================
 *   File:   DmpRdcManager.cc
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  15/12/2013   21:38:13
=====================================================================*/

#include <iostream>

#include "TFile.h"
#include "TTree.h"

#include "DmpRdcManager.hh"
#include "DmpEvtHeader.hh"
#include "DmpEvtPsdRaw.hh"
#include "DmpEvtStkRaw.hh"
#include "DmpEvtBgoRaw.hh"
#include "DmpEvtNudRaw.hh"

ClassImp(DmpRdcManager)

//------------------------------------------------------------------------------
DmpRdcManager* DmpRdcManager::fInstance = 0;
//------------------------------------------------------------------------------
#ifdef Dmp_DEBUG
TString DmpRdcManager::fConnectorPath="./share/Connector/TestBeam2012";
#endif
#ifdef Dmp_RELEASE
TString DmpRdcManager::fConnectorPath="Absolute path of /prefix/share/connector";
#endif

//------------------------------------------------------------------------------
DmpRdcManager* DmpRdcManager::GetInstance(){
  if (fInstance == 0 ){
    fInstance = new DmpRdcManager();
  }
  return fInstance;
}

//------------------------------------------------------------------------------
void DmpRdcManager::Clear(){
  if (fInstance != 0 ){
    delete fInstance;
    fInstance = 0;
  }
  std::cout<<"\nDelete DmpRdcManager Manager"<<std::endl;
}

//------------------------------------------------------------------------------
Bool_t DmpRdcManager::Core(){

  fHexData = new ifstream(fInDataPath+fDataName,std::ios::in|std::ios::binary);
  if (!fHexData->good()) {
    std::cerr<<"\nWarning: open "<<fInDataPath+fDataName<<" failed"<<std::endl;
    return false;
  } else {
    std::cout<<"\nReading "<<fInDataPath+fDataName<<std::endl;
  }

  fTree = new TTree("DAMPE_raw","raw data");
  fTree->Branch("Header","DmpEvtHeader",&fHeader);
  fTree->Branch("Psd","DmpEvtPsdRaw",&fPsd);
//  fTree->Branch("Stk","DmpEvtStkRaw",&fStk);
  fTree->Branch("Bgo","DmpEvtBgoRaw",&fBgo);
  fTree->Branch("Nud","DmpEvtNudRaw",&fNud);

  //loop of event package. set the order of sub-detector as the order of FEE in fDataName
  for (Long64_t nEvt=0;!fHexData->eof();++nEvt) {

//if (nEvt > 5) break;

    if ( !ConversionHeader() ) continue;
    if ( !ConversionPsd() ) continue;
    if ( !ConversionStk() ) continue;
    if ( !ConversionBgo() ) continue;
    if ( !ConversionNud() ) continue;
if (nEvt == 1) fHeader->ShowTime(0);

    if (TriggerMatch()) {
      fHeader->CountEvent();
      fTree->Fill();
#ifdef Dmp_DEBUG
std::cout<<"\tFill event "<<std::dec<<fHeader->GetEventID()<<std::endl;
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
DmpRdcManager::DmpRdcManager()
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
DmpRdcManager::~DmpRdcManager(){
  delete fPsd;
  delete fStk;
  delete fBgo;
  delete fNud;
}

//------------------------------------------------------------------------------
Bool_t DmpRdcManager::TriggerMatch() {
  if (fTrigger["Bgo"] == fTrigger["Psd"] && fTrigger["Bgo"] == fTrigger["Stk"] && fTrigger["Bgo"] == fTrigger["Nud"] && fTrigger["Bgo"] == fTrigger["Header"]) {
  return true;
  } else {
    std::cerr<<"Error: Triggers of Sub-detectors not match\n";
    std::cerr<<std::hex<<"\tHeader = "<<fTrigger["Header"]<<"\tPsd = "<<fTrigger["Psd"]<<"\tStk = "<<fTrigger["Stk"]<<"\tBgo = "<<fTrigger["Bgo"]<<"\tNud = "<<fTrigger["Nud"]<<std::endl;
  }
  return true;
}

//------------------------------------------------------------------------------
Bool_t DmpRdcManager::ConversionHeader(){
#ifdef Dmp_DEBUG
std::cerr<<"\n\tBegin Conversion:\n\t\t-->Header from "<<std::dec<<fHexData->tellg();
#endif
  static Short_t tmp=0;
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
  fHexData->read((char*)(&tmp),1);      //this needed
  fHexData->read((char*)(&fTrigger["Header"]),1);
  fHexData->read((char*)(&tmp),1);      //Datalength
  fHexData->read((char*)(&tmp),1);      //Datalength

  static Short_t time[8], i;            // 8 bytes for time
  for (i=0;i<8;++i) {
    time[i]=0;
    fHexData->read((char*)(&time[i]),1);
  }

  fHeader->SetTime(time,8);
#ifdef Dmp_DEBUG
std::cerr<<"\tto "<<std::dec<<fHexData->tellg()<<std::endl;
//std::cout<<"\t\ttrigger = "<<fTrigger["Header"]<<"\tPackage ID = "<<fHeader->GetPackageID()<<std::endl;
#endif

  return true;
}

