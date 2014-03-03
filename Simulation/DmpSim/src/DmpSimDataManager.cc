/*
 *  $Id: DmpSimDataManager.cc, 2014-02-25 16:33:22 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#include <time.h>
#include "G4Run.hh"

#include "TFile.h"
#include "TTree.h"

#include "DmpSimDataManager.h"

DmpDataManager* DmpDataManager::fInstance = 0;

DmpDataManager* GetInstance(){
  if (fInstance == 0){
    fInstance = new DmpDataManager();
  }
  return fInstance;
}

void DmpDataManager::Clear(){
  if(fInstance != 0){
    delete fInstance;
    fInstance = 0;
  }
}

//-------------------------------------------------------------------
DmpDataManager::DmpDataManager()
 :fTree(0),
  fEvtRaw(0)
{
  fEvtRaw = new DmpEvtRaw();
}

DmpDataManager::~DmpDataManager(){
  delete fEvtRaw;
  delete fInstance;
}

//-------------------------------------------------------------------
void DmpDataManager::BookFile(const G4Run *aRun){
  fTree = new TTree("Simulation","DAMPESimulation");
  fTree->Branch("RawEvent","DmpEvtRaw",&fEvtRaw,32000,2);
  fTree->Branch("EventSource","DmpEvtSimSource",&fSimSource,32000,2);
}

void SaveFile(){
  char name[100];
  {
  time_t now;
  struct tm *p;
  time(&now);
  p = localtime(&now);
  strftime(name,99,"DmpSim_%Y%m%d%H%M%S",p);
  }
  TFile *aFile = new TFile(name,"recreate");
  fTree->Write();
  aFile->Close();
  delete aFile;
}

void FillEvent(const G4Event *aEvent){
  fTree->Fill();
}

