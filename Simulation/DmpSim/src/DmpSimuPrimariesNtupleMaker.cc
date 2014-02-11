// Description: ntuple maker for the STK
//
// Author(s):
//  - creation by X.Wu, 15/07/2013

#include "G4Event.hh"
#include "G4Run.hh"
#include "DmpSimuPrimariesNtupleMaker.hh"

#include "TTree.h"

DmpSimuPrimariesNtupleMaker::DmpSimuPrimariesNtupleMaker()
  :tree(0)
{
  //set debugEvent to a particular event number for debug printout  
  //debugEvent = -1; //-1 is all events
  //debugEvent = -100; //-100 no event
}

DmpSimuPrimariesNtupleMaker::~DmpSimuPrimariesNtupleMaker()
{
}

void DmpSimuPrimariesNtupleMaker::book(const G4Run* aRun, TTree* aTree)
{
  tree = aTree;
 //book ntuple branches and define ntuple data vectors here 
 tree->Branch("tt_npv",       &tt_npv,     "tt_npv/i"  );
 //tree->Branch("tt_npvpart",   &tt_npv,     "tt_npvpart/i");
 tree->Branch("tt_pv_x",      &tt_pv_x);
 tree->Branch("tt_pv_y",      &tt_pv_y);
 tree->Branch("tt_pv_z",      &tt_pv_z);
 tree->Branch("tt_pv_r",      &tt_pv_r);
 tree->Branch("tt_pv_theta",  &tt_pv_theta);
 tree->Branch("tt_pv_phi",    &tt_pv_phi);
 tree->Branch("tt_pvpart_px", &tt_pvpart_px  );
 tree->Branch("tt_pvpart_py", &tt_pvpart_py  );
 tree->Branch("tt_pvpart_pz", &tt_pvpart_pz  );
 // direction cosine Fabio Sept 2013
 tree->Branch("tt_pvpart_cosx", &tt_pvpart_cosx  );
 tree->Branch("tt_pvpart_cosy", &tt_pvpart_cosy  );
 tree->Branch("tt_pvpart_cosz", &tt_pvpart_cosz  );
 // Zenuth  azimuth
 tree->Branch("tt_pvpart_zenith", &tt_pvpart_zenith );
 tree->Branch("tt_pvpart_azimuth", &tt_pvpart_azimuth );

 tree->Branch("tt_pvpart_ekin",&tt_pvpart_ekin);
 tree->Branch("tt_pvpart_q",  &tt_pvpart_q   );
 tree->Branch("tt_pvpart_pdg",&tt_pvpart_pdg );
}

void DmpSimuPrimariesNtupleMaker::beginEvent(const G4Event* evt)
{
  //set event number
  eventNumber = evt->GetEventID();
 //clear all ntuple data vectors here
}

void DmpSimuPrimariesNtupleMaker::FillEvent(const G4Event* evt)
{
/*
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
*/
  tt_npv   = evt->GetNumberOfPrimaryVertex();
  if(tt_npv>1) G4cout << " WARNING: Number of PrimaryVertex more than 1: " << tt_npv << G4endl;

  tt_pv_x = evt->GetPrimaryVertex(0)->GetPosition().x();
  tt_pv_y = evt->GetPrimaryVertex(0)->GetPosition().y();
  tt_pv_z = evt->GetPrimaryVertex(0)->GetPosition().z();

  // Spherical coordinate - Fabio September 2013
  tt_pv_r =  sqrt(pow(tt_pv_x,2)+pow(tt_pv_y,2)+pow(tt_pv_z,2));
  tt_pv_theta = acos(tt_pv_z/tt_pv_r)*180./pi;;
  tt_pv_phi = atan2(tt_pv_y,tt_pv_x)*180./pi;

  tt_npvpart   =  evt->GetPrimaryVertex(0)->GetNumberOfParticle(); 
  if(tt_npvpart>1) G4cout << " WARNING: Number of PrimaryParticle more than 1: " << tt_npvpart << G4endl;

  tt_pvpart_px   = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().x();
  tt_pvpart_py   = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().y();
  tt_pvpart_pz   = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().z();
  
  // Direction cosines - Fabio September 2013
  G4double momentum;
  momentum = sqrt(pow(tt_pvpart_px,2)+pow(tt_pvpart_py,2)+pow(tt_pvpart_pz,2));
  tt_pvpart_cosx   = tt_pvpart_px/momentum;
  tt_pvpart_cosy   = tt_pvpart_py/momentum;
  tt_pvpart_cosz   = tt_pvpart_pz/momentum;

  // Unit vectors in the spherical coordinate system
  G4double urpart[3], uthetapart[3], uphipart[3];
  
  // unit vector pointing towards increasing radial coordinate 
  urpart[0] = sin(tt_pv_theta*pi/180.0) * cos(tt_pv_phi*pi/180.0);
  urpart[1] = sin(tt_pv_theta*pi/180.0) * sin(tt_pv_phi*pi/180.0);
  urpart[2] = cos(tt_pv_theta*pi/180.0);

  // unit vector pointing towards increasing colatitudes
  uthetapart[0] = cos(tt_pv_theta*pi/180.0) * cos(tt_pv_phi*pi/180.0);
  uthetapart[1] = cos(tt_pv_theta*pi/180.0) * sin(tt_pv_phi*pi/180.0);
  uthetapart[2] = -sin(tt_pv_theta*pi/180.0);

  // unit vector pointing towards increasing phi
  uphipart[0] = -sin(tt_pv_phi*pi/180.0);
  uphipart[1] = cos(tt_pv_phi*pi/180.0);
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
  czen = -(tt_pvpart_cosx * urpart[0] + tt_pvpart_cosy * urpart[1] + tt_pvpart_cosz * urpart[2]);
  // azimuth angle cosine and sine
  cazi = -(tt_pvpart_cosx * uphipart[0] + tt_pvpart_cosy * uphipart[1] + tt_pvpart_cosz * uphipart[2]);
  sazi = -(tt_pvpart_cosx * uthetapart[0] + tt_pvpart_cosy * uthetapart[1] + tt_pvpart_cosz * uthetapart[2]);

  tt_pvpart_zenith = acos(czen) * 180.0/pi;
  tt_pvpart_azimuth = atan2(sazi, cazi) * 180.0/pi;

  tt_pvpart_ekin = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetKineticEnergy();  //??? no this function??
  tt_pvpart_q    = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetCharge();
  tt_pvpart_pdg  = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetPDGcode();
}

