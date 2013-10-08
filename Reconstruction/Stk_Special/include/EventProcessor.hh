#ifndef EventProcessor_h
#define EventProcessor_h

#include <vector>
#include <string>

#include <TLorentzVector.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TBranch.h>

#include "EventReader.hh"

class StkRecManager;

class EventProcessor : public EventReader {

 public:

  enum ParticleType { kProton = 0,
		      kElectron,
		      kPhoton,
		      kUnkown};

  EventProcessor(TChain* chain); 
  virtual ~EventProcessor() {}

  void setParticleType(ParticleType type) {m_partType = type;}
  ParticleType  getParticleType()         {return m_partType;}
  
  void init();             //sets branch addresses
  void init(TFile* hFile); //sets branch addresses and histogram file
  void loop(int nevent, int istart);   //looping over events
  void finalize();         //write and close histogram file

  StkRecManager* GetStkRecManager() { return m_stkRecManager; }

 private:

  TFile* m_hFile;
  ParticleType m_partType; 

  StkRecManager* m_stkRecManager;

};

#endif
