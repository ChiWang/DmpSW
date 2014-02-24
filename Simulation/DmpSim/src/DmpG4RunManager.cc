// Description: Re-implementation of the G4RunManager
//
// Author(s):
//  - creation by X.Wu, 19/10/2013

#include "DmpG4RunManager.hh"
#include "DmpSimuPrimaryGeneratorAction.hh"

#include "G4UImanager.hh"

void DmpG4RunManager::ProcessOneEvent(G4int i_event)
{
  currentEvent = GenerateEvent(i_event);
  DmpSimuPrimaryGeneratorAction* dmpSimuPrimaryGeneratorAction = (DmpSimuPrimaryGeneratorAction*) GetUserPrimaryGeneratorAction();
  //bool genOnly = dmpSimuPrimaryGeneratorAction->GenOnly(); 	
  bool useGenFilter = dmpSimuPrimaryGeneratorAction->UseGenFilter(); 	
  //if(!genOnly) {
  if(!useGenFilter) eventManager->ProcessOneEvent(currentEvent);
  else {
    if(dmpSimuPrimaryGeneratorAction->PassGenFilter()) eventManager->ProcessOneEvent(currentEvent);
  }
  //}
  AnalyzeEvent(currentEvent);
  UpdateScoring();
  if(i_event<n_select_msg) G4UImanager::GetUIpointer()->ApplyCommand(msgText);
}

/***
G4RunManager* DmpG4RunManager::Instance(G4bool genOnly) 
{
  if(fRunManager) {
    G4Exception("DmpG4RunManager::Instance()", "Run0031",
                FatalException, "G4RunManager constructed twice.");
  }
  else {
    if (!genOnly)
      fRunManager = new G4RunManager();
    else {
      fRunManager = new DmpG4RunManager();
      (DmpG4RunManager*) fRunManager->SetGenOnly(genOnly);
    }
  }
  return fRunManager;
}
***/
