// Description: This class hinerits from EventReader. It is used to
// read data blocks from the DAMPE L2 ROOT ntuple and to manage the 
// sub-detectors reconstruction algorithms. 
//
// Author(s):
//  - creation by X.Wu, 07/09/2013

#include "EventProcessor.h"

#include "TMath.h"
#include "TH1F.h"
#include "TH2F.h"
#include <iostream>

#include "StkRecManager.h"

bool EventProcessor::flag_isMC = true;
int EventProcessor::flag_dumpEvt = -1; //-1: no dump; -100: dump all events

//EventProcessor::EventProcessor(TChain* chain) : EventReader(chain),  m_hFile(0),  m_partType(kProton) {
EventProcessor::EventProcessor(TTree * /*tree*/) : m_hFile(0),  m_partType(kProton) {
  if (flag_dumpEvt == -100) std::cout << "In EventProcessor Constructor " << std::endl;
}

void EventProcessor::Begin(TTree * /*tree*/)
{
  if (flag_dumpEvt == -100) std::cout << "In EventProcessor::Begin() " << std::endl;
}

void EventProcessor::init(TFile* hFile) {
  if (flag_dumpEvt == -100) std::cout << "In EventProcessor::init() " << std::endl;
  m_hFile = hFile;

  //initialize sub-detector reconstruction manager
  m_stkRecManager = new StkRecManager;
  m_stkRecManager->init(this);

}

Bool_t EventProcessor::Process(Long64_t entry) {
  if (flag_dumpEvt == -100) std::cout << "In EventProcessor::Process():  " << std::endl;

  m_entry = entry;   // current event 

  clearEventData();  // reset the input event data

  readEventInfo();   // read eventnumber, runnumber, etc
  if (flag_dumpEvt == -100) std::cout << "    current entry = " << entry << ", run = " << run() << ", event = " << event() << std::endl;

  if(flag_isMC) readPrimaries();   // read pv and pv_part

  if(flag_isMC) readStepPvtrack(); // read step_pvtrack
  if(flag_isMC) readStepBack();    // read step_back

  if(flag_isMC) readStepEle();     // read step_ele
  if(flag_isMC) readStepPos();     // read step_pos

  if(flag_isMC) readPvtrj();       // read pvtrj

  if(flag_isMC) readEle();         // read ele
  if(flag_isMC) readPos();         // read pos

  if(flag_isMC) readCal();         // read Cal

  if(flag_isMC) readSiHit();       // read SiHit
  if(flag_isMC) readSiDigit();     // read SiDigi

  m_stkRecManager->process();

  return kTRUE;
}

void EventProcessor::finalize() {
  if (flag_dumpEvt == -100) std::cout << "In EventProcessor::finalize() " << std::endl;
   m_hFile->Write();
   m_hFile->Close();

   //delete m_stkRecManager;
}
