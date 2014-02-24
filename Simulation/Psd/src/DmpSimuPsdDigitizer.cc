// Description: This class hinerits from G4VDigitizerModule. It is used to
// perform the digitization of the PSD  
//
// Author(s):
//  - creation by X.Wu, 14/07/2013

#include "DmpSimuPsdDigitizer.hh"

//#include "DmpSimuPsdDigitizerMessenger.hh"
#include "DmpSimuPsdDigi.hh"
#include "DmpSimuPsdHit.hh"

#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4DigiManager.hh"
#include "G4ios.hh"

#include "G4RunManager.hh"
#include "DmpDetectorConstruction.hh"

#include <vector>

DmpSimuPsdDigitizer::DmpSimuPsdDigitizer(G4String name)
  :G4VDigitizerModule(name)

{

  G4String colName = "PSDDigitsCollection";
  collectionName.push_back(colName);
  //PSDThreshold = 15*keV;
  PSDThreshold = 0.01*keV;

  //create a messenger for this class
  //digiMessenger = new DmpSimuPsdDigitizerMessenger(this);

  G4RunManager* runManager = G4RunManager::GetRunManager();
  dmpDetector =
    (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());

}

DmpSimuPsdDigitizer::~DmpSimuPsdDigitizer()
{
  //delete digiMessenger;
}

void DmpSimuPsdDigitizer::Digitize()
{

  DigitsCollection = new DmpSimuPsdDigitsCollection
  	("DmpSimupPsdDigitizer","PSDDigitsCollection"); // to create the PSD Digi Collection

  G4DigiManager* DigiMan = G4DigiManager::GetDMpointer();
  
  G4int AHCID; // PSDHitCollection

  AHCID = DigiMan->GetHitsCollectionID("PSDHitCollection");  
  DmpSimuPsdHitsCollection* AHC = 0;
  AHC = (DmpSimuPsdHitsCollection*)
		 (DigiMan->GetHitsCollection(AHCID));


  if (AHC)
    {
      G4int n_hit = AHC->entries();
      
      for (G4int i=0;i<n_hit;i++)
	{
	  G4double energy = (*AHC)[i]->GetEdep();
	  G4int type = (*AHC)[i]->GetStripNumber();
	  
      // digi generation only if energy deposit greater than 0.
	  
	  if (energy>PSDThreshold)
	    {
	      DmpSimuPsdDigi* Digi = new DmpSimuPsdDigi();
	      Digi->SetStripNumber(type);
	      Digi->SetEnergy(energy);
	      DigitsCollection->insert(Digi);	
	    }  
	  
	}
    }
/***
  if (AHC){
    G4cout << "Number of PSD digits in this event =  " 
	   << DigitsCollection->entries()  
	   << G4endl;
  }
  ***/
  StoreDigiCollection(DigitsCollection);    
  
}









