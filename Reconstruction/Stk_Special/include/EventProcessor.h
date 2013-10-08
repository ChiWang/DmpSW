#ifndef EventProcessor_h
#define EventProcessor_h

#include <vector>
#include <string>

#include <TLorentzVector.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TBranch.h>

#include "EventReader.h"

class StkRecManager;

class EventProcessor : public EventReader {

 public:

  enum ParticleType { kProton = 0,
		      kElectron,
		      kPhoton,
		      kUnkown};

  static bool  flag_isMC;
  static int   flag_dumpEvt; //-1: no dump; -100: dump all events

  EventProcessor(TTree * tree = 0); 
  //EventProcessor(TChain* chain); 
  virtual ~EventProcessor() {}

  void setParticleType(ParticleType type) {m_partType = type;}
  ParticleType  getParticleType()         {return m_partType;}
  
  void init(TFile* hFile); //sets branch addresses and histogram file
  void finalize();         //write and close histogram file

  virtual void    Begin(TTree *tree);
  virtual Bool_t  Process(Long64_t entry);
  //virtual void    Terminate();

  StkRecManager* GetStkRecManager() { return m_stkRecManager; }

 private:

  TFile* m_hFile;
  ParticleType m_partType; 

  StkRecManager* m_stkRecManager;

};

#endif
