// Description: This class hinerits from G4VUserPrimaryGeneratorAction. It is used to
// generate input particles for G4 simulation
//
// Author(s):
//  - creation by X.Wu, 11/07/2013

#include "G4RunManager.hh"
#include "DmpSimPrimaryGeneratorAction.hh"

#include "DmpSimDetectorConstruction.hh"
#include "DmpSimPrimaryGeneratorMessenger.hh"

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"

DmpSimPrimaryGeneratorAction::DmpSimPrimaryGeneratorAction()
  :rndmFlag("off"),nSourceType(0),nSpectrumType(0)
{
  G4RunManager* runManager = G4RunManager::GetRunManager();
  dmpDetector =
    (DmpSimDetectorConstruction*)(runManager->GetUserDetectorConstruction());


  //create a messenger for this class
  gunMessenger = new DmpSimPrimaryGeneratorMessenger(this);

  G4int n_particle = 1;
  particleGun  = new G4ParticleGun(n_particle);     
  // default particle kinematic  
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="e-");
  particleGun->SetParticleDefinition(particle);
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,-1.));
  particleGun->SetParticleEnergy(5000.*MeV); //default to 5 GeV
  G4double position = 0.5*(dmpDetector->GetWorldSizeZ()); //origin is the ceter of the payload
  particleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,position));
  //particleSource = new G4GeneralParticleSource();

}

DmpSimPrimaryGeneratorAction::~DmpSimPrimaryGeneratorAction()
{
  delete particleGun;
  //delete particleSource;
  delete gunMessenger;

}

void DmpSimPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
   if (sourceGen)
    {

      //this function is called at the begining of event
      //G4double z0 = 0.5*(dmpDetector->GetWorldSizeZ());
      G4double z0 = 29.*cm; //just above the top layer of silicon
      G4double x0 = 0.*cm, y0 = 0.*cm;
  
      G4ThreeVector pos0;
      G4ThreeVector dir0;
      G4ThreeVector vertex0 = G4ThreeVector(x0,y0,z0);
      
      dir0 = G4ThreeVector(0.,0.,-1.);
      
      G4double theta, phi, y, f;
      
      G4double xy = dmpDetector->GetWorldSizeXY();
      G4double z = dmpDetector->GetWorldSizeZ();
      if (dVertexRadius > xy*0.5)
	{ 
	  G4cout << "vertexRadius too big " << G4endl;
	  G4cout << "vertexRadius setted to " << xy*0.45 << G4endl;
	  dVertexRadius = xy*0.45;
	}
      
      if (dVertexRadius > z*0.5)
	{ 
	  G4cout << "vertexRadius too high " << G4endl;
	  G4cout << "vertexRadius setted to " << z*0.45 << G4endl;
	  dVertexRadius = z*0.45;
	}

      switch(nSourceType) {
      case 0:
	//shooting vertically at the center of the payload, useless for tracker
	particleGun->SetParticlePosition(vertex0);
	particleGun->SetParticleMomentumDirection(dir0);
	break;
      case 1:
	//from GammaRayTel
	// GS: Generate random position on the 4PIsphere to create a unif. distrib.
	// GS: on the sphere
	phi = G4UniformRand() * twopi;
	do {
	  y = G4UniformRand()*1.0;
	  theta = G4UniformRand() * pi;
	  f = std::sin(theta);
	} while (y > f);
	vertex0 = G4ThreeVector(1.,0.,0.);
	vertex0.setMag(dVertexRadius);
	vertex0.setTheta(theta);
	vertex0.setPhi(phi);
	particleGun->SetParticlePosition(vertex0);
	
	dir0 = G4ThreeVector(1.,0.,0.);
	do {
	  phi = G4UniformRand() * twopi;
	  do {
	    y = G4UniformRand()*1.0;
	    theta = G4UniformRand() * pi;
	    f = std::sin(theta);
	  } while (y > f);
	  dir0.setPhi(phi);
	  dir0.setTheta(theta);
	} while (vertex0.dot(dir0) >= -0.7 * vertex0.mag());
	particleGun->SetParticleMomentumDirection((G4ParticleMomentum)dir0);
	break;
      case 2:
	// Generate random position on the upper semi-sphere z>0
	//   random polar angle 135-180 degree (90-45 incident angle) 

	vertex0.setX(G4UniformRand()*2.0*dVertexRadius - dVertexRadius);
	vertex0.setY(G4UniformRand()*2.0*dVertexRadius - dVertexRadius);
	vertex0.setZ(z0);

	dir0 = particleGun->GetParticleMomentumDirection();
	theta = pi - G4UniformRand() * (3*pi/12);
	dir0.setTheta(theta);
	phi = G4UniformRand() * twopi;
	dir0.setPhi(phi);
	particleGun->SetParticleMomentumDirection((G4ParticleMomentum)dir0);
	//G4cout << " 0000PrimaryGeneratorAction: direction " << diran.x() << " "  << diran.y() << " " << diran.z() << G4endl;
	particleGun->SetParticlePosition(vertex0);	
	break;      
      case 3:
	// Generate random position on the upper semi-sphere z>0 to create a unif. distrib  on a plane

	vertex0.setX(G4UniformRand()*2.0*dVertexRadius - dVertexRadius);
	vertex0.setY(G4UniformRand()*2.0*dVertexRadius - dVertexRadius);
	vertex0.setZ(z0);

	G4ParticleMomentum dir15 = particleGun->GetParticleMomentumDirection();
	dir15.setTheta(pi);
	phi = G4UniformRand() * twopi;
	dir15.setPhi(phi);
	particleGun->SetParticleMomentumDirection(dir15);
	particleGun->SetParticlePosition(vertex0);
	break;      
      }
      
      G4double pEnergy;
      
      switch(nSpectrumType) {
      case 0:
	break;
      case 1:
	break;
      case 2:
	do {
	  y = G4UniformRand()*100000.0;
	  pEnergy = G4UniformRand() * 10. * GeV;
	  f = std::pow(pEnergy * (1/GeV), -4.);
	} while (y > f);
	
	particleGun->SetParticleEnergy(pEnergy);
	
	break;
      case 3:
	break;
      }
      
      particleGun->GeneratePrimaryVertex(anEvent);
    }
   else
     {
       //particleSource->GeneratePrimaryVertex(anEvent);
     }
   
}









