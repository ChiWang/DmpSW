// Description: ntuple maker for the STK
//
// Author(s):
//  - creation by X.Wu, 15/07/2013

#include "DmpSimuPrimariesEventMaker.hh"

#include "TTree.h"

DmpSimuPrimariesEventMaker::DmpSimuPrimariesEventMaker()
  :tree(0)
{
  //set debugEvent to a particular event number for debug printout  
  //debugEvent = -1; //-1 is all events
  debugEvent = -100; //-100 no event
}

DmpSimuPrimariesEventMaker::~DmpSimuPrimariesEventMaker()
{
}

void DmpSimuPrimariesEventMaker::book(const G4Run* aRun, TTree* aTree)
{ 
 
  tree = aTree;
  dmpSimuPrimariesEvent = new DmpEvtSimuPrimaries();
  tree->Branch("DmpEvtSimuPrimaries", "DmpEvtSimuPrimaries",  &dmpSimuPrimariesEvent);
}

void DmpSimuPrimariesEventMaker::beginEvent(const G4Event* evt)
{
  //set event number
  eventNumber = evt->GetEventID();
  dmpSimuPrimariesEvent->Reset();

 //clear all ntuple data vectors here
}

void DmpSimuPrimariesEventMaker::FillStep(const G4Step* aStep)
{
}

void DmpSimuPrimariesEventMaker::FillEvent(const G4Event* evt)
{  
  
  if(eventNumber == debugEvent || debugEvent == -1) {
    G4int nVertex = evt->GetNumberOfPrimaryVertex();
    G4cout << " Number of PrimaryVertex: " << nVertex << G4endl;
    for ( G4int j = 0; j < nVertex; j++) { 
      evt->GetPrimaryVertex(j)->Print();
      G4cout << "   vetex " << j << " position " << evt->GetPrimaryVertex(j)->GetPosition() << G4endl;
      G4int nPart =  evt->GetPrimaryVertex(j)->GetNumberOfParticle(); 
      G4cout << "   Number of PrimaryParticles in this vertex: " << nPart << G4endl;
      for ( G4int i = 0; i < nPart; i++) {
	G4cout << "   particle " << i << " momentum " << evt->GetPrimaryVertex(j)->GetPrimary(i)->GetMomentum() << G4endl;
      }
    }
  }
  
  dmpSimuPrimariesEvent->npv   = evt->GetNumberOfPrimaryVertex();
  if(dmpSimuPrimariesEvent->npv>1) G4cout << " WARNING: Number of PrimaryVertex more than 1: " << dmpSimuPrimariesEvent->npv << G4endl;

  dmpSimuPrimariesEvent->pv_x = evt->GetPrimaryVertex(0)->GetPosition().x();
  dmpSimuPrimariesEvent->pv_y = evt->GetPrimaryVertex(0)->GetPosition().y();
  dmpSimuPrimariesEvent->pv_z = evt->GetPrimaryVertex(0)->GetPosition().z();

  // Spherical coordinate - Fabio September 2013
  dmpSimuPrimariesEvent->pv_r =  sqrt(pow(dmpSimuPrimariesEvent->pv_x,2)+pow(dmpSimuPrimariesEvent->pv_y,2)+pow(dmpSimuPrimariesEvent->pv_z,2));
  dmpSimuPrimariesEvent->pv_theta = acos(dmpSimuPrimariesEvent->pv_z/dmpSimuPrimariesEvent->pv_r)*180./pi;;
  dmpSimuPrimariesEvent->pv_phi = atan2(dmpSimuPrimariesEvent->pv_y,dmpSimuPrimariesEvent->pv_x)*180./pi;

  dmpSimuPrimariesEvent->npvpart   =  evt->GetPrimaryVertex(0)->GetNumberOfParticle();
  if(dmpSimuPrimariesEvent->npvpart>1) G4cout << " WARNING: Number of PrimaryParticle more than 1: " << dmpSimuPrimariesEvent->npvpart << G4endl;

  dmpSimuPrimariesEvent->pvpart_px   = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().x();
  dmpSimuPrimariesEvent->pvpart_py   = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().y();
  dmpSimuPrimariesEvent->pvpart_pz   = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().z();
  
  // Direction cosines - Fabio September 2013
  G4double momentum;
  momentum = sqrt(pow(dmpSimuPrimariesEvent->pvpart_px,2)+pow(dmpSimuPrimariesEvent->pvpart_py,2)+pow(dmpSimuPrimariesEvent->pvpart_pz,2));
  dmpSimuPrimariesEvent->pvpart_cosx   = dmpSimuPrimariesEvent->pvpart_px/momentum;
  dmpSimuPrimariesEvent->pvpart_cosy   = dmpSimuPrimariesEvent->pvpart_py/momentum;
  dmpSimuPrimariesEvent->pvpart_cosz   = dmpSimuPrimariesEvent->pvpart_pz/momentum;

  // Unit vectors in the spherical coordinate system
  G4double urpart[3], uthetapart[3], uphipart[3];
  
  // unit vector pointing towards increasing radial coordinate 
  urpart[0] = sin(dmpSimuPrimariesEvent->pv_theta*pi/180.0) * cos(dmpSimuPrimariesEvent->pv_phi*pi/180.0);
  urpart[1] = sin(dmpSimuPrimariesEvent->pv_theta*pi/180.0) * sin(dmpSimuPrimariesEvent->pv_phi*pi/180.0);
  urpart[2] = cos(dmpSimuPrimariesEvent->pv_theta*pi/180.0);

  // unit vector pointing towards increasing colatitudes
  uthetapart[0] = cos(dmpSimuPrimariesEvent->pv_theta*pi/180.0) * cos(dmpSimuPrimariesEvent->pv_phi*pi/180.0);
  uthetapart[1] = cos(dmpSimuPrimariesEvent->pv_theta*pi/180.0) * sin(dmpSimuPrimariesEvent->pv_phi*pi/180.0);
  uthetapart[2] = -sin(dmpSimuPrimariesEvent->pv_theta*pi/180.0);

  // unit vector pointing towards increasing phi
  uphipart[0] = -sin(dmpSimuPrimariesEvent->pv_phi*pi/180.0);
  uphipart[1] = cos(dmpSimuPrimariesEvent->pv_phi*pi/180.0);
  uphipart[2] = 0.0;

  // make normalizations of unit vectors (perhaps redundant, vectors should be properly normalized)

  G4double urnorm=0.0, uthetanorm=0.0, uphinorm=0.0;
  for (int k=0; k<3; k++){
    urnorm += pow(urpart[k], 2);
    uthetanorm += pow(uthetapart[k], 2);
    uphinorm += pow(uphipart[k], 2);
  }
  urnorm = sqrt(urnorm);
  uthetanorm = sqrt(uthetanorm);
  uphinorm = sqrt(uphinorm);
  for (int k=0; k<3; k++){
    urpart[k] = urpart[k] / urnorm;
    uthetapart[k] = uthetapart[k] / uthetanorm;
    uphipart[k] = uphipart[k] / uphinorm;
  }


  // Zenith and azimuth angles
  G4double czen, cazi, sazi;
  
  // zenith angle cosine
  czen = -(dmpSimuPrimariesEvent->pvpart_cosx * urpart[0] + dmpSimuPrimariesEvent->pvpart_cosy * urpart[1] + dmpSimuPrimariesEvent->pvpart_cosz * urpart[2]);
  // azimuth angle cosine and sine
  cazi = -(dmpSimuPrimariesEvent->pvpart_cosx * uphipart[0] + dmpSimuPrimariesEvent->pvpart_cosy * uphipart[1] + dmpSimuPrimariesEvent->pvpart_cosz * uphipart[2]);
  sazi = -(dmpSimuPrimariesEvent->pvpart_cosx * uthetapart[0] + dmpSimuPrimariesEvent->pvpart_cosy * uthetapart[1] + dmpSimuPrimariesEvent->pvpart_cosz * uthetapart[2]);

  dmpSimuPrimariesEvent->pvpart_zenith = acos(czen) * 180.0/pi;
  dmpSimuPrimariesEvent->pvpart_azimuth = atan2(sazi, cazi) * 180.0/pi;

  dmpSimuPrimariesEvent->pvpart_ekin = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetKineticEnergy();
  dmpSimuPrimariesEvent->pvpart_q    = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetCharge();
  dmpSimuPrimariesEvent->pvpart_pdg  = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetPDGcode();
  dmpSimuPrimariesEvent->pvpart_geocut = 1;
  dmpSimuPrimariesEvent->pv_fluxw = 1.;

}






