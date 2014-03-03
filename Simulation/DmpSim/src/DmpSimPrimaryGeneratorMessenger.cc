// Description: This class hinerits from G4UImessenger. It is used to
// pass user command to DmpSimuPrimaryGeneratorAction
//
// Author(s):
//  - creation by X.Wu, 11/07/2013

#include "DmpSimuPrimaryGeneratorMessenger.hh"

#include "DmpSimuPrimaryGeneratorAction.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"

DmpSimuPrimaryGeneratorMessenger::DmpSimuPrimaryGeneratorMessenger
(DmpSimuPrimaryGeneratorAction* action)
  :dmpSimuPrimaryGeneratorAction(action)
{ 
  //not used
  RndmCmd = new G4UIcmdWithAString("/gun/random",this);
  RndmCmd->SetGuidance("Shoot randomly the incident particle.");
  RndmCmd->SetGuidance("  Choice : on(default), off");
  RndmCmd->SetParameterName("choice",true);
  RndmCmd->SetDefaultValue("on");
  RndmCmd->SetCandidates("on off");
  RndmCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SourceTypeCmd = new G4UIcmdWithAnInteger("/gun/sourceType",this);
  SourceTypeCmd->SetGuidance("Select the type of incident flux.");
  SourceTypeCmd->SetGuidance("  Choice : 0(default)(Beam in the center), 1(isotropic sphere), 2(isotropic sphere z>0), 3(parallel beam from a plae above )");
  SourceTypeCmd->SetParameterName("choice",true);
  SourceTypeCmd->SetDefaultValue((G4int)-1);
  SourceTypeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  VertexRadiusCmd = new G4UIcmdWithADoubleAndUnit("/gun/vertexRadius",this);
  VertexRadiusCmd->SetGuidance("Radius (and unit) of sphere for vertices of incident flux.");
  VertexRadiusCmd->SetParameterName("choice",true);
  VertexRadiusCmd->SetDefaultValue((G4double)1.*cm);
  VertexRadiusCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  SpectrumTypeCmd = new G4UIcmdWithAnInteger("/gun/spectrumType",this);
  SpectrumTypeCmd->SetGuidance("Select the type of incident spectrum.");
  SpectrumTypeCmd->SetGuidance("  Choice : 0 (MoneEne@100GeV), 1(), 2(E^{-gamma}), 3()");
  SpectrumTypeCmd->SetParameterName("choice",true);
  SpectrumTypeCmd->SetDefaultValue((G4int)-1);
  SpectrumTypeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SourceGenCmd = new G4UIcmdWithAnInteger("/gun/sourceGen",this);
  SourceGenCmd->SetGuidance("Select the native Generation");
  SourceGenCmd->SetGuidance("  Choice : 0(native), 1(GPS)");
  SourceGenCmd->SetParameterName("choice",true);
  SourceGenCmd->SetDefaultValue((G4int)1);
  SourceGenCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  /*
  GenerationOnlyCmd = new G4UIcmdWithABool("/gun/GenerationOnly",this);
  GenerationOnlyCmd->SetGuidance("Only run generation, no simulation");
  GenerationOnlyCmd->SetGuidance("  Choice : true, false");
  GenerationOnlyCmd->SetParameterName("GenerationOnly",false);
  GenerationOnlyCmd->SetDefaultValue((G4bool)false);
  GenerationOnlyCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  
  */
  UseGenFilterCmd = new G4UIcmdWithABool("/gun/UseGenFilter",this);
  UseGenFilterCmd->SetGuidance("Use gneration filter");
  UseGenFilterCmd->SetGuidance("  Choice : true, false");
  UseGenFilterCmd->SetParameterName("UseGenFilter",false);
  UseGenFilterCmd->SetDefaultValue((G4bool)false);
  UseGenFilterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  FilterShadowedCmd = new G4UIcmdWithABool("/gun/filter/FilterShadowed",this);
  FilterShadowedCmd->SetGuidance("Filter particles blocked by the Earth shadow");
  FilterShadowedCmd->SetGuidance("  Choice : true, false");
  FilterShadowedCmd->SetParameterName("FilterShadowed",false);
  FilterShadowedCmd->SetDefaultValue((G4bool)false);
  FilterShadowedCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  FilterUpwardCmd = new G4UIcmdWithABool("/gun/filter/FilterUpward",this);
  FilterUpwardCmd->SetGuidance("Filter particles going upward to the detector");
  FilterUpwardCmd->SetGuidance("  Choice : true, false");
  FilterUpwardCmd->SetParameterName("FilterUpward",false);
  FilterUpwardCmd->SetDefaultValue((G4bool)false);
  FilterUpwardCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  FilterBelowBGOCmd = new G4UIcmdWithABool("/gun/filter/FilterBelowBGO",this);
  FilterBelowBGOCmd->SetGuidance("Filter particles coming below the BGO");
  FilterBelowBGOCmd->SetGuidance("  Choice : true, false");
  FilterBelowBGOCmd->SetParameterName("FilterBelowBGO",false);
  FilterBelowBGOCmd->SetDefaultValue((G4bool)false);
  FilterBelowBGOCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  SetPartcilePosCmd = new G4UIcmdWith3VectorAndUnit("/gun/setParticlePosition", this);
  SetPartcilePosCmd->SetGuidance("Set position of point particle source (cm)");
  SetPartcilePosCmd->SetParameterName("x","y","z",true,true);
  SetPartcilePosCmd->SetDefaultUnit("cm");


  SetPartcileMomDirCmd = new G4UIcmdWith3VectorAndUnit("/gun/setParticleMomentumDirection", this);
  SetPartcileMomDirCmd->SetGuidance("Set orientation of point particle source");
  SetPartcileMomDirCmd->SetParameterName("Px","Py","Pz",true,true);
  SetPartcileMomDirCmd->SetRange("Px !=0 || Py != 0 || Pz !=0 ");
  SetPartcileMomDirCmd->SetDefaultUnit("GeV");

}

DmpSimuPrimaryGeneratorMessenger::~DmpSimuPrimaryGeneratorMessenger()
{
  delete RndmCmd;
  delete SourceTypeCmd;
  delete VertexRadiusCmd;
  delete SpectrumTypeCmd;
  delete SourceGenCmd;
  //delete GenerationOnlyCmd;
  delete UseGenFilterCmd;
  delete FilterShadowedCmd;
  delete FilterUpwardCmd;
  delete FilterBelowBGOCmd;
  delete SetPartcilePosCmd;
  delete SetPartcileMomDirCmd;
}

void DmpSimuPrimaryGeneratorMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{ 
  if( command == RndmCmd )
    { dmpSimuPrimaryGeneratorAction->SetRndmFlag(newValue);}
  
  if( command == SourceTypeCmd )
    //{ dmpSimuPrimaryGeneratorAction->SetSourceType(SourceTypeCmd->GetNewIntValue(newValue));}
    { dmpSimuPrimaryGeneratorAction->SetupSourceType(SourceTypeCmd->GetNewIntValue(newValue));}
  
  if( command == VertexRadiusCmd )
    { dmpSimuPrimaryGeneratorAction->SetVertexRadius(VertexRadiusCmd->GetNewDoubleValue(newValue));}
  
  if( command == SpectrumTypeCmd )
    //{ dmpSimuPrimaryGeneratorAction->SetSpectrumType(SpectrumTypeCmd->GetNewIntValue(newValue));}
    { dmpSimuPrimaryGeneratorAction->SetupSpectrumType(SpectrumTypeCmd->GetNewIntValue(newValue));}

  if( command == SourceGenCmd )
    { dmpSimuPrimaryGeneratorAction->SetSourceGen(SourceGenCmd->GetNewIntValue(newValue));}

  /*
  if( command == GenerationOnlyCmd )
    { dmpSimuPrimaryGeneratorAction->SetGenOnly(GenerationOnlyCmd->GetNewBoolValue(newValue)); }
  */
  if( command == UseGenFilterCmd )
    { dmpSimuPrimaryGeneratorAction->SetUseGenFilter(UseGenFilterCmd->GetNewBoolValue(newValue)); }
                                      
  if( command == FilterShadowedCmd )
    { dmpSimuPrimaryGeneratorAction->SetFilterShadowed(FilterShadowedCmd->GetNewBoolValue(newValue)); }

  if( command == FilterUpwardCmd )
    { dmpSimuPrimaryGeneratorAction->SetFilterUpward(FilterUpwardCmd->GetNewBoolValue(newValue)); }

  if( command == FilterBelowBGOCmd )
    { dmpSimuPrimaryGeneratorAction->SetFilterBelowBGO(FilterBelowBGOCmd->GetNewBoolValue(newValue)); }

  if( command == SetPartcilePosCmd)
    { dmpSimuPrimaryGeneratorAction->SetParticleCenterCoords(SetPartcilePosCmd->GetNew3VectorValue(newValue));}

  if( command == SetPartcileMomDirCmd)
    { dmpSimuPrimaryGeneratorAction->SetParticleMomDirection(SetPartcileMomDirCmd->GetNew3VectorValue(newValue));}
}













