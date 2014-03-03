/*
 *  $Id: DmpSimDataManager.cc, 2014-02-25 16:33:22 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#include <time.h>

#include "TFile.h"
#include "TTree.h"

#include "G4Run.hh"

#include "DmpSimDataManager.h"

DmpSimDataManager* DmpSimDataManager::fInstance = 0;

DmpSimDataManager* GetInstance(){
  if (fInstance == 0){
    fInstance = new DmpSimDataManager();
  }
  return fInstance;
}

void DmpSimDataManager::Vanish(){
  if(fInstance != 0){
    delete fInstance;
    fInstance = 0;
  }
}

//-------------------------------------------------------------------
DmpSimDataManager::DmpSimDataManager()
 :fTree(0),
  fEvtRaw(0),
  fPrimaryParticle(0)
{
  fEvtRaw = new DmpEvtRaw();
  fPrimaryParticle = new DmpEvtSimPrimaryParticle();
}

DmpSimDataManager::~DmpSimDataManager(){
  delete fEvtRaw;
  delete fPrimaryParticle;
}

//-------------------------------------------------------------------
void DmpSimDataManager::BookFile(const G4Run *aRun){
  fTree = new TTree("Simulation","DAMPESimulation");
  fTree->Branch("RawEvent","DmpEvtRaw",&fEvtRaw,32000,2);
  fTree->Branch("EventSource","DmpEvtSimPrimaryParticle",&fPrimaryParticle,32000,2);
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

