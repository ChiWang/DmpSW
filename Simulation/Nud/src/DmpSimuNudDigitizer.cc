// Description: This class hinerits from G4VDigitizerModule. It is used to
// perform the digitization of the PSD  
//
// Author(s):
//  - added by Tiekuang Dong 2012/12/23

#include "DmpSimuNudDigitizer.hh"

//#include "DmpSimuPsdDigitizerMessenger.hh"
#include "DmpSimuNudDigi.hh"
#include "DmpSimuNudHit.hh"

#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4DigiManager.hh"
#include "G4ios.hh"

#include "G4RunManager.hh"
#include "DmpDetectorConstruction.hh"

#include <vector>

DmpSimuNudDigitizer::DmpSimuNudDigitizer(G4String name)
  :G4VDigitizerModule(name)

{

 // G4String colName = "NUDDigitsCollection"; // tkdong
 // collectionName.push_back(colName); // tkdong

G4String colName0 = "NUDDigitsCollection0";
G4String colName1 = "NUDDigitsCollection1";
G4String colName2 = "NUDDigitsCollection2";
G4String colName3 = "NUDDigitsCollection3";
collectionName.push_back(colName0);
collectionName.push_back(colName1);
collectionName.push_back(colName2);
collectionName.push_back(colName3);




  //PSDThreshold = 15*keV;
  NUDThreshold = 0.01*keV;

  //create a messenger for this class
  //digiMessenger = new DmpSimuPsdDigitizerMessenger(this);

  G4RunManager* runManager = G4RunManager::GetRunManager();
  dmpDetector =
    (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());

}

DmpSimuNudDigitizer::~DmpSimuNudDigitizer()
{
  //delete digiMessenger;
}

void DmpSimuNudDigitizer::Digitize()
{

  DigitsCollection0 = new DmpSimuNudDigitsCollection
  	("DmpSimupNudDigitizer","NUDDigitsCollection0"); // to create the PSD Digi Collection

  G4DigiManager* DigiMan = G4DigiManager::GetDMpointer();
  
  G4int AHCID0; // PSDHitCollection

  AHCID0 = DigiMan->GetHitsCollectionID("NUDHitCollection0");  
  DmpSimuNudHitsCollection* AHC0 = 0;
  AHC0 = (DmpSimuNudHitsCollection*)
		 (DigiMan->GetHitsCollection(AHCID0));


  if (AHC0)
    {
      G4int n_hit = AHC0->entries();
      
      for (G4int i=0;i<n_hit;i++)
	{
	  G4double energy = (*AHC0)[i]->GetEdep();
	 // G4int type = (*AHC0)[i]->GetStripNumber();
	  
	  // digi generation only if energy deposit greater than 0.
	  
	  if (energy>NUDThreshold)
	    {
	      DmpSimuNudDigi* Digi = new DmpSimuNudDigi();
	    //  Digi->SetStripNumber(type);
	      Digi->SetEnergy(energy);
	      DigitsCollection0->insert(Digi);	
	    }  
	  
	}
    }

  if (AHC0){
    G4cout << "Number of NUD digits in this event =  " 
	   << DigitsCollection0->entries()  
	   << G4endl;
  }
  
  StoreDigiCollection(DigitsCollection0);    
 

DigitsCollection1 = new DmpSimuNudDigitsCollection
  	("DmpSimupNudDigitizer","NUDDigitsCollection1"); // to create the PSD Digi Collection

 // G4DigiManager* DigiMan = G4DigiManager::GetDMpointer();
  
  G4int AHCID1; // PSDHitCollection

  AHCID1= DigiMan->GetHitsCollectionID("NUDHitCollection1");  
  DmpSimuNudHitsCollection* AHC1 = 0;
  AHC1= (DmpSimuNudHitsCollection*)
		 (DigiMan->GetHitsCollection(AHCID1));


  if (AHC1)
    {
      G4int n_hit = AHC1->entries();
      
      for (G4int i=0;i<n_hit;i++)
	{
	  G4double energy = (*AHC1)[i]->GetEdep();
	//  G4int type = (*AHC1)[i]->GetStripNumber();
	  
	  // digi generation only if energy deposit greater than 0.
	  
	  if (energy>NUDThreshold)
	    {
	      DmpSimuNudDigi* Digi = new DmpSimuNudDigi();
	  //    Digi->SetStripNumber(type);
	      Digi->SetEnergy(energy);
	      DigitsCollection1->insert(Digi);	
	    }  
	  
	}
    }

  if (AHC1){
    G4cout << "Number of NUD digits in this event =  " 
	   << DigitsCollection1->entries()  
	   << G4endl;
  }
  
  StoreDigiCollection(DigitsCollection1);    


DigitsCollection2 = new DmpSimuNudDigitsCollection
  	("DmpSimupNudDigitizer","NUDDigitsCollection2"); // to create the PSD Digi Collection

//  G4DigiManager* DigiMan = G4DigiManager::GetDMpointer();
  
  G4int AHCID2; // PSDHitCollection

  AHCID2 = DigiMan->GetHitsCollectionID("NUDHitCollection2");  
  DmpSimuNudHitsCollection* AHC2 = 0;
  AHC2 = (DmpSimuNudHitsCollection*)
		 (DigiMan->GetHitsCollection(AHCID2));


  if (AHC2)
    {
      G4int n_hit = AHC2->entries();
      
      for (G4int i=0;i<n_hit;i++)
	{
	  G4double energy = (*AHC2)[i]->GetEdep();
	//  G4int type = (*AHC2)[i]->GetStripNumber();
	  
	  // digi generation only if energy deposit greater than 0.
	  
	  if (energy>NUDThreshold)
	    {
	      DmpSimuNudDigi* Digi = new DmpSimuNudDigi();
	 //     Digi->SetStripNumber(type);
	      Digi->SetEnergy(energy);
	      DigitsCollection2->insert(Digi);	
	    }  
	  
	}
    }

  if (AHC2){
    G4cout << "Number of NUD digits in this event =  " 
	   << DigitsCollection2->entries()  
	   << G4endl;
  }
  
  StoreDigiCollection(DigitsCollection2);    


DigitsCollection3 = new DmpSimuNudDigitsCollection
  	("DmpSimupNudDigitizer","NUDDigitsCollection3"); // to create the PSD Digi Collection

 // G4DigiManager* DigiMan = G4DigiManager::GetDMpointer();
  
  G4int AHCID3; // PSDHitCollection

  AHCID3 = DigiMan->GetHitsCollectionID("NUDHitCollection3");  
  DmpSimuNudHitsCollection* AHC3 = 0;
  AHC3 = (DmpSimuNudHitsCollection*)
		 (DigiMan->GetHitsCollection(AHCID3));


  if (AHC3)
    {
      G4int n_hit = AHC3->entries();
      
      for (G4int i=0;i<n_hit;i++)
	{
	  G4double energy = (*AHC3)[i]->GetEdep();
	//  G4int type = (*AHC3)[i]->GetStripNumber();
	  
	  // digi generation only if energy deposit greater than 0.
	  
	  if (energy>NUDThreshold)
	    {
	      DmpSimuNudDigi* Digi = new DmpSimuNudDigi();
	  //    Digi->SetStripNumber(type);
	      Digi->SetEnergy(energy);
	      DigitsCollection3->insert(Digi);	
	    }  
	  
	}
    }

  if (AHC3){
    G4cout << "Number of NUD digits in this event =  " 
	   << DigitsCollection3->entries()  
	   << G4endl;
  }
  
  StoreDigiCollection(DigitsCollection3);    



}









