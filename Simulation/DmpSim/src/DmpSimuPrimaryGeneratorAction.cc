// Description: This class hinerits from G4VUserPrimaryGeneratorAction. It is used to
// generate input particles for G4 simulation
//
// Author(s):
//  - creation by X.Wu, 11/07/2013

#include "DmpG4RunManager.hh"
#include "DmpSimuPrimaryGeneratorAction.hh"


#include "DmpDetectorConstruction.hh"
#include "DmpSimuPrimaryGeneratorMessenger.hh"
//#include "DmpRootNtupleManager.hh"
//#include "DmpSimuPrimariesNtupleMaker.hh"

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"


#include "G4Material.hh"


#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"


#include "TTree.h"

DmpSimuPrimaryGeneratorAction::DmpSimuPrimaryGeneratorAction()
  :rndmFlag("off"),nSourceType(0),nSpectrumType(0),useGenFilter(false),passGenFilter(true),
   filterShadowed(false),filterUpward(false),filterBelowBGO(false),nFilterRejected(0),nGenerated(0)
{
  runManager = (DmpG4RunManager*) G4RunManager::GetRunManager();
  dmpDetector = (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());

  BgoTopZ = dmpDetector->GetBGOCenter() + dmpDetector->GetBGOSizeZ()/2.;

  //create a messenger for this class
  gunMessenger = new DmpSimuPrimaryGeneratorMessenger(this);

  G4int n_particle = 1;
  particleGun  = new G4ParticleGun(n_particle);     
  // default particle kinematic  
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="e-");
  particleGun->SetParticleDefinition(particle);
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  particleGun->SetParticleEnergy(5000.*MeV); //default to 5 GeV
  G4double position = -0.5*(dmpDetector->GetWorldSizeZ()); //origin is the ceter of the payload
  particleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,position));


  particleSource = new G4GeneralParticleSource();
  particleSource->SetNumberOfParticles(n_particle);
  particleSource->SetParticleDefinition(particle);


  G4double PayLoadSizeZ = (dmpDetector->GetPayloadSizeZ());
  G4double PayLoadSizeXY = (dmpDetector->GetPayloadSizeXY());
  G4cout << "PayLoadSize x, y, z  XY:" << PayLoadSizeXY << " Z:" <<PayLoadSizeZ << G4endl;
  G4cout << "Top of BGO at z = " << BgoTopZ << G4endl;
  G4ThreeVector dir0; 
  dir0 = G4ThreeVector(0.,0.,1.);

  posDist = new G4SPSPosDistribution();
  posDist = particleSource->GetCurrentSource()->GetPosDist();
  angDist = new G4SPSAngDistribution();
  angDist = particleSource->GetCurrentSource()->GetAngDist();
  
  //default setting
  posDist->SetPosDisType("Point");  //  Point, Plane, Surface or Volume source
  posDist->SetCentreCoords(G4ThreeVector(+13.75, +13.75, -(PayLoadSizeZ/2.)));
  angDist->SetParticleMomentumDirection(G4ThreeVector(0., 0., -1.));

  eneDist = new G4SPSEneDistribution();
  eneDist = particleSource->GetCurrentSource()->GetEneDist() ;
    
  //default setting
  eneDist->SetEnergyDisType("Mono");
  eneDist->SetMonoEnergy(5.0*GeV);

  rndDist = new G4SPSRandomGenerator();

}

DmpSimuPrimaryGeneratorAction::~DmpSimuPrimaryGeneratorAction()
{
  G4cout << "DmpSimuPrimaryGeneratorAction: number of event generated = " << nGenerated      << G4endl;
  G4cout << "                               number of event rejected by filter = " << nFilterRejected << G4endl;

  delete particleGun;
  delete particleSource;
  delete gunMessenger;
  
}

void DmpSimuPrimaryGeneratorAction::SetupSourceType(G4int val)
{
  nSourceType   = val;

  //get (updated) payload size again here
  G4double PayLoadSizeZ = (dmpDetector->GetPayloadSizeZ());
  G4double PayLoadSizeXY = (dmpDetector->GetPayloadSizeXY());
  G4cout << "PayLoadSize x, y, z  XY:" << PayLoadSizeXY << " Z:" <<PayLoadSizeZ << G4endl;
 


  G4double r0 = dVertexRadius;
  if (r0 < 1){
    r0 = std::max(0.5*PayLoadSizeXY,0.5*PayLoadSizeZ)+50.; //mm
  }
  SetVertexRadius(r0);
  G4cout << "Generation Sphere radius " << r0 << G4endl;    
  G4ThreeVector dir0; 
  dir0 = G4ThreeVector(0.,0.,1.);
  switch(nSourceType) {
  case 0:
    //shooting vertically at the center of the payload. The is an offset of +13.75mmin X and Y to center the cal bars
    // /gps/pos/centre +13.75 +13.75 +370 mm
    // /gps/direction 0 0 -1
    // /gps/pos/type Point
    posDist->SetPosDisType("Point");  //  Point, Plane, Surface or Volume source
    posDist->SetCentreCoords(G4ThreeVector(+13.75, +13.75, -(PayLoadSizeZ/2.)));
    angDist->SetParticleMomentumDirection(dir0);
    break;
  case 1:
    // Case 1  Generate random position on the 4PIsphere to create a unif. distrib. Particles enter into the generetaion sphere
    // set position distribution    
    posDist->SetPosDisType("Surface");  //  Point, Plane, Surface or Volume source
    posDist->SetPosDisShape("Sphere");//    Allows the user to choose the particular shape they wish for the     position distribution. Choices are Square, Circle, Ellipse, Rectangle,    Sphere, Ellipsoid, Cylinder, Parallelepiped.
    posDist->SetCentreCoords(G4ThreeVector(0., 0., 0.)); // center of the world
    posDist->SetRadius(r0);
    //G4cout << "Generation Sphere radius " << posDist->GetRadius() << G4endl;    
    angDist->SetAngDistType("iso");  // Used to set the type of angular distribution wanted. Arguments    are iso, cos, beam  and user for isotropic, cosine-law, beam and user-define respectively.
    angDist->SetMinTheta(0. * rad);
    angDist->SetMaxTheta(pi/2. * rad);    
    angDist->SetMinPhi(0.*rad);
    angDist->SetMaxPhi(twopi *rad);
    break;	 
  case 2:
    // Generate random position on the 2PIsphere to create a unif. distrib over the detector . Particles enter into the generetaion sphere
    // Not implemeted yet due to problem with half worlds
    posDist->SetPosDisType("Surface");  //  Point, Plane, Surface or Volume source
    posDist->SetPosDisShape("Sphere");//    Allows the user to choose the particular shape they wish for the     position distribution. Choices are Square, Circle, Ellipse, Rectangle,    Sphere, Ellipsoid, Cylinder, Parallelepiped.
    posDist->SetCentreCoords(G4ThreeVector(0., 0., 0.)); // center of the world
    posDist->SetRadius(r0);
    //G4cout << "Generation Sphere radius " << posDist->GetRadius() << G4endl;

    /* Command for UI  
      /gps/hist/type biaspt
      /gps/hist/point 0.  0.0
      /gps/hist/point 0.5 1.0
      /gps/hst/point 1.0 0.0  
    */
    rndDist->SetPosThetaBias(G4ThreeVector(0.0, 0.));
    rndDist->SetPosThetaBias(G4ThreeVector(0.5, 1.));
    rndDist->SetPosThetaBias(G4ThreeVector(1.0, 0.));
    rndDist->GenRandPosTheta();
    posDist->SetBiasRndm(rndDist);

    angDist->SetAngDistType("iso");  // Used to set the type of angular distribution wanted. Arguments    are iso, cos, beam  and user for isotropic, cosine-law, beam and user-define respectively.
    angDist->SetMinTheta(0. * rad);
    angDist->SetMaxTheta(pi/2. * rad);    
    angDist->SetMinPhi(0.*rad);
    angDist->SetMaxPhi(twopi *rad);      
    break;
  case 3:
    // generate downgoing particle generate uniformly in a plane over the detector
    // ##/gps/pos/type Plane
    // ##/gps/pos/shape Rectangle
    // ##/gps/pos/centre 0 0 +370 mm
    // ##/gps/pos/rot1 0 1 0
    // ##/gps/pos/rot2 1 0 0
    // ##/gps/pos/halfx 380 mm
    // ##/gps/pos/halfy 380 mm
    // ##/gps/direction 0 0 -1
    posDist->SetPosDisType("Plane");  //  Point, Plane, Surface or Volume source
    posDist->SetPosDisShape("Rectangle");
    posDist->SetCentreCoords(G4ThreeVector(0, 0, -(PayLoadSizeZ/2.)));
    posDist->SetPosRot1(G4ThreeVector(0, 1, 0));
    posDist->SetPosRot2(G4ThreeVector(1, 0, 0));
    posDist->SetHalfX(PayLoadSizeXY/2.);
    posDist->SetHalfY(PayLoadSizeXY/2.);
    angDist->SetParticleMomentumDirection(dir0);
    break;

  case 4:
    // generate Random position on a box surrounding the payload
    posDist->SetPosDisType("Surface");  //  Point, Plane, Surface or Volume source
    posDist->SetPosDisShape("Para");//    Allows the user to choose the particular shape they wish for the     position distribution. Choices are Square, Circle, Ellipse, Rectangle,    Sphere, Ellipsoid, Cylinder, Parallelepiped.
    posDist->SetCentreCoords(G4ThreeVector(0., 0., 0.)); // center of the world
    posDist->SetHalfX(1.1*PayLoadSizeXY/2.);
    posDist->SetHalfY(1.1*PayLoadSizeXY/2.);
    posDist->SetHalfZ(1.1*PayLoadSizeZ/2.);
    angDist->SetAngDistType("iso");  // Used to set the type of angular distribution wanted. Arguments    are iso, cos, beam  and user for isotropic, cosine-law, beam and user-define respectively.
    angDist->SetMinTheta(0. * rad);
    angDist->SetMaxTheta(pi/2. * rad);    
    angDist->SetMinPhi(0.*rad);
    angDist->SetMaxPhi(twopi *rad);
    break;  

  case 5:
    // Case 5  Generate random position inside the 4PIsphere to create a unif. distrib.-1<Cos8Theta)<-1
    // set position distribution    
    posDist->SetPosDisType("Volume");  //  Point, Plane, Surface or Volume source
    posDist->SetPosDisShape("Sphere");//    Allows the user to choose the particular shape they wish for the     position distribution. Choices are Square, Circle, Ellipse, Rectangle,    Sphere, Ellipsoid, Cylinder, Parallelepiped.
    posDist->SetCentreCoords(G4ThreeVector(0., 0., 0.)); // center of the world
    posDist->SetRadius(r0);
    //G4cout << "Generation Sphere radius " << posDist->GetRadius() << G4endl;    
    angDist->SetAngDistType("iso");  // Used to set the type of angular distribution wanted. Arguments    are iso, cos, beam  and user for isotropic, cosine-law, beam and user-define respectively.

    angDist->SetMinPhi(0.*rad);
    angDist->SetMaxPhi(twopi *rad);
    break;
  case 6:
    // Case 6  Generate random position inside the 4PIsphere to create a unif. distrib.-1<Cos8Theta)<0
    // set position distribution    
    posDist->SetPosDisType("Volume");  //  Point, Plane, Surface or Volume source
    posDist->SetPosDisShape("Sphere");//    Allows the user to choose the particular shape they wish for the     position distribution. Choices are Square, Circle, Ellipse, Rectangle,    Sphere, Ellipsoid, Cylinder, Parallelepiped.
    posDist->SetCentreCoords(G4ThreeVector(0., 0., 0.)); // center of the world
    posDist->SetRadius(r0);
    //G4cout << "Generation Sphere radius " << posDist->GetRadius() << G4endl;    
    angDist->SetAngDistType("iso");  // Used to set the type of angular distribution wanted. Arguments    are iso, cos, beam  and user for isotropic, cosine-law, beam and user-define respectively.
    // /gps/ang/mintheta 0 rad 
    // /gps/ang/maxtheta pi/2. rad
    angDist->SetMinTheta(0. * rad);
    angDist->SetMaxTheta(pi/2. * rad);        
    angDist->SetMinPhi(0.*rad);
    angDist->SetMaxPhi(twopi *rad);
    break;
case 7:
    // Case 7  Generate random position inside half sphere sphere to create a unif. distrib. -1<Cos8Theta)<0
    // set position distribution    
    posDist->SetPosDisType("Volume");  //  Point, Plane, Surface or Volume source
    posDist->SetPosDisShape("Sphere");//    Allows the user to choose the particular shape they wish for the     position distribution. Choices are Square, Circle, Ellipse, Rectangle,    Sphere, Ellipsoid, Cylinder, Parallelepiped.
    posDist->SetCentreCoords(G4ThreeVector(0., 0., 0.)); // center of the world
    posDist->SetRadius(r0);
    rndDist->ReSetHist("biasz");
    rndDist->SetZBias(G4ThreeVector(1.0, 1.));
    rndDist->SetZBias(G4ThreeVector(0.5, 0.));
    rndDist->SetZBias(G4ThreeVector(0.0, 1.));
    rndDist->GenRandZ();
    posDist->SetBiasRndm(rndDist);

    //G4cout << "Generation Sphere radius " << posDist->GetRadius() << G4endl;    
    angDist->SetAngDistType("iso");  // Used to set the type of angular distribution wanted. Arguments    are iso, cos, beam  and user for isotropic, cosine-law, beam and user-define respectively.
    
    // /gps/ang/mintheta 0 rad 
    // /gps/ang/maxtheta pi/2. rad
    angDist->SetMinTheta(0. * rad);
    angDist->SetMaxTheta(pi/2. * rad);        
    angDist->SetMinPhi(0.*rad);
    angDist->SetMaxPhi(twopi *rad);
    break;



  default:
    break;
  }
  
}

void DmpSimuPrimaryGeneratorAction::SetupSpectrumType(G4int val)
{
  nSpectrumType = val;

  //G4cout << "Init nSpectrumType " << nSpectrumType << G4endl; 
  switch(nSpectrumType) {    
  case 0:
    eneDist->SetEnergyDisType("Mono");
    eneDist->SetMonoEnergy(100.0*GeV);
    break;
  case 1:
    break;
  case 2:
    // Power law spectrum with spectral index at -1 from 100MeV to 10 TeV
    eneDist->SetEnergyDisType("Pow"); //The arguments  are Mono (mono-energetic), Lin (linear), Pow (power-law), Exp  (exponential), Gauss (gaussian), Brem (bremsstrahlung), BBody (black-body), Cdg    (cosmic diffuse gamma-ray), User (user-defined), Arb (arbitrary  point-wise), Epn (energy per nucleon).
    // sets alpha for a power-law distribution.
      eneDist->SetAlpha(-1);
      eneDist->SetEmin(100*MeV);
      eneDist->SetEmax(10*TeV);
      break;
  default:
    break;    
  }

}

void DmpSimuPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

  G4double z0 = 29.*cm; //just above the top layer of silicon
  G4double x0 = 0.*cm, y0 = 0.*cm;
  G4ThreeVector pos0;
  G4ThreeVector dir0;
  G4ThreeVector vertex0 = G4ThreeVector(x0,y0,z0);      
  dir0 = G4ThreeVector(0.,0.,1.);
  G4double theta, phi, y, f;
  G4double xy = dmpDetector->GetWorldSizeXY();
  G4double z = dmpDetector->GetWorldSizeZ();
  G4double PayLoadSizeZ = (dmpDetector->GetPayloadSizeZ());
  G4double PayLoadSizeXY = (dmpDetector->GetPayloadSizeXY());       
  G4double r0 = sqrt(2*pow(0.5*PayLoadSizeXY,2)+pow(0.5*PayLoadSizeZ,2));
    
    
  switch(sourceGen){
  case 0:
    //this function is called at the begining of event
    //G4double z0 = 0.5*(dmpDetector->GetWorldSizeZ());
   
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
      
    break;
    
  case 1:
             
    //G4cout << "loop nSpectrumType " << nSpectrumType << G4endl; 

    
    particleSource->GeneratePrimaryVertex(anEvent);


    double pv_x = anEvent->GetPrimaryVertex(0)->GetPosition().x();
    double pv_y = anEvent->GetPrimaryVertex(0)->GetPosition().y();
    double pv_z = anEvent->GetPrimaryVertex(0)->GetPosition().z();
    double pvpart_px   = anEvent->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().x();
    double pvpart_py   = anEvent->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().y();
    double pvpart_pz   = anEvent->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().z();
    

    G4double R = dVertexRadius;
    if (R < 1){
      R = std::max(0.5*PayLoadSizeXY,0.5*PayLoadSizeZ)+50.; //mm
    }
    double den=1;
    double b,c; 
    double t1,t2,t;
    double x=pv_x;
    double y=pv_y;
    double z=pv_z;

    // If the particles are produced inside a sphere (case 5, 6, 7) the launch point is projected back on the sphere surface
    
    if(nSourceType == 5 || nSourceType == 6 || nSourceType == 7 ){
  
        
      den = (pvpart_px*pvpart_px+pvpart_py*pvpart_py+pvpart_pz*pvpart_pz);
      if(den<=0){
	break;
      }
      b = (pv_x*pvpart_px + pv_y*pvpart_py + pv_z*pvpart_pz)/den;
      c = (pv_x*pv_x + pv_y*pv_y  + pv_z*pv_z - R*R)/den;
      if(b*b-c < 0){
	break;
      }
      t1 = -b+sqrt(b*b-c);
      t2 = -b-sqrt(b*b-c);
      
      if(t1<0){
	t=t1;
      }
      if(t2<0){
	t=t2;
      }
      
      x= pv_x + pvpart_px *t;
      y= pv_y + pvpart_py *t;
      z = pv_z + pvpart_pz *t;
      anEvent->GetPrimaryVertex(0)->SetPosition(x,y,z);
      //G4cout << "b: " <<b <<" c:" << c <<G4endl;
      //G4cout << "t: "<< t <<" x: " << x<< " y: " << y <<  " z: " << z << " R:" << sqrt(x*x+y*y+z*z)<<G4endl;
    }
   





    ++nGenerated;
    
    /*
    //fill ntuple if only generation is run, otherwise it is filled by EventAction
    if(genOnly) {
      if(dmpRootNtupleManager->GetGenTree()) {
	DmpSimuPrimariesNtupleMaker* dmpSimuPrimariesNtupleMaker = 
	  dmpRootNtupleManager->GetDmpSimuPrimariesNtupleMaker();
	dmpSimuPrimariesNtupleMaker->FillEvent(anEvent);
	dmpRootNtupleManager->GetGenTree()->Fill();
      }
    }*/


    if(useGenFilter) runGenFilter(anEvent);

    break;
  }

}

void DmpSimuPrimaryGeneratorAction::runGenFilter(G4Event* evt)
{
  passGenFilter = true;

  double pv_x = evt->GetPrimaryVertex(0)->GetPosition().x();
  double pv_y = evt->GetPrimaryVertex(0)->GetPosition().y();
  double pv_z = evt->GetPrimaryVertex(0)->GetPosition().z();
  G4ThreeVector primVtx = G4ThreeVector(pv_x,pv_y,pv_z);

  double pvpart_px   = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().x();
  double pvpart_py   = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().y();
  double pvpart_pz   = evt->GetPrimaryVertex(0)->GetPrimary(0)->GetMomentum().z();

  G4ThreeVector vecPrim = G4ThreeVector(pvpart_px,pvpart_py,pvpart_pz);
  double thetaPrim  = vecPrim.theta()*180/pi;

  //remove particle shadowed by the Earth
  if(filterShadowed && thetaPrim<74.) passGenFilter = false; 

  //remove particle going upward
  if(filterUpward && thetaPrim<90.)   passGenFilter = false; 

  //remove particle starting below Bgo
  if(filterBelowBGO && pv_z<BgoTopZ)  passGenFilter = false; 

  if(!passGenFilter) ++nFilterRejected;

  return;
}




