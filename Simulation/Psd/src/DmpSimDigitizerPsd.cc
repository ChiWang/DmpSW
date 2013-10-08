// Description: This class hinerits from G4VDigitizerModule. It is used to
// perform the digitization of the PSD  
//
// Author(s):
//  - creation by X.Wu, 14/07/2013

#include "DmpSimDigitizerPsd.hh"

//#include "DmpSimDigitizerMessengerPsd.hh"
#include "DmpSimDigPsd.hh"
#include "DmpSimHitPsd.hh"

#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4DigiManager.hh"
#include "G4ios.hh"

#include "G4RunManager.hh"
#include "DmpSimDetectorConstruction.hh"

#include <vector>

DmpSimDigitizerPsd::DmpSimDigitizerPsd(G4String name)
  :G4VDigitizerModule(name)

{

  G4String colName = "PSDDigitsCollection";
  collectionName.push_back(colName);
  //PSDThreshold = 15*keV;
  PSDThreshold = 0.01*keV;

  //create a messenger for this class
  //digiMessenger = new DmpSimDigitizerMessengerPsd(this);

  G4RunManager* runManager = G4RunManager::GetRunManager();
  dmpDetector =
    (DmpSimDetectorConstruction*)(runManager->GetUserDetectorConstruction());

}

DmpSimDigitizerPsd::~DmpSimDigitizerPsd()
{
  //delete digiMessenger;
}

void DmpSimDigitizerPsd::Digitize()
{

  DigitsCollection = new DmpSimDigitsCollection
  	("DmpSimupPsdDigitizer","PSDDigitsCollection"); // to create the PSD Digi Collection

  G4DigiManager* DigiMan = G4DigiManager::GetDMpointer();
  
  G4int AHCID; // PSDHitCollection

  AHCID = DigiMan->GetHitsCollectionID("PSDHitCollection");  
  DmpSimHitPsdsCollection* AHC = 0;
  AHC = (DmpSimHitPsdsCollection*)
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
	      DmpSimDigPsd* Digi = new DmpSimDigPsd();
	      Digi->SetStripNumber(type);
	      Digi->SetEnergy(energy);
	      DigitsCollection->insert(Digi);	
	    }  
	  
	}
    }

  if (AHC){
    G4cout << "Number of PSD digits in this event =  " 
	   << DigitsCollection->entries()  
	   << G4endl;
  }
  
  StoreDigiCollection(DigitsCollection);    
  
}









