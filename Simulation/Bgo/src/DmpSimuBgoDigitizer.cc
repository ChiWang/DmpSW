// Description: This class hinerits from G4VDigitizerModule. It is used to
// perform the digitization of the BGO  
//
// Author(s):
//  - creation by X.Wu, 14/07/2013

#include "DmpSimuBgoDigitizer.hh"

//#include "DmpSimuBgoDigitizerMessenger.hh"
#include "DmpSimuBgoDigi.hh"
#include "DmpSimuBgoHit.hh"

#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4DigiManager.hh"
#include "G4ios.hh"

#include "G4RunManager.hh"
#include "DmpDetectorConstruction.hh"

#include <vector>

DmpSimuBgoDigitizer::DmpSimuBgoDigitizer(G4String name)
  :G4VDigitizerModule(name)

{

  G4String colName = "BGODigitsCollection";
  collectionName.push_back(colName);
  BGOThreshold = 0.0*keV;

  //create a messenger for this class
  //digiMessenger = new DmpSimuBgoDigitizerMessenger(this);

  G4RunManager* runManager = G4RunManager::GetRunManager();
  dmpDetector =
    (DmpDetectorConstruction*)(runManager->GetUserDetectorConstruction());

}

DmpSimuBgoDigitizer::~DmpSimuBgoDigitizer()
{
  //delete digiMessenger;
}

void DmpSimuBgoDigitizer::Digitize()
{

  DigitsCollection = new DmpSimuBgoDigitsCollection
  	("DmpSimupBgoDigitizer","BGODigitsCollection"); // to create the PSD Digi Collection

  G4DigiManager* DigiMan = G4DigiManager::GetDMpointer();
  
  G4int CHCID; // BGOHitCollection

  CHCID = DigiMan->GetHitsCollectionID("BGOHitCollection");
  DmpSimuBgoHitsCollection* CHC = 0;
  CHC = (DmpSimuBgoHitsCollection*)
		 (DigiMan->GetHitsCollection(CHCID));

  if (CHC)
    {
      G4int n_hit = CHC->entries();
      
      for (G4int i=0;i<n_hit;i++)
	{
	  G4double energy = (*CHC)[i]->GetEdepCAL();
	  G4int type      = (*CHC)[i]->GetCALBarNumber();
	  if (energy>BGOThreshold)
	    {
	      DmpSimuBgoDigi* Digi = new DmpSimuBgoDigi();
	      Digi->SetBarNumber(type);
	      Digi->SetEnergy(energy);
	      DigitsCollection->insert(Digi);	
	    }  
	}
    }
/***  
    if (CHC){
    G4cout << "Number of BGO digits in this event =  " 
	   << DigitsCollection->entries()  
	   << G4endl;
  }
  ***/
  StoreDigiCollection(DigitsCollection);    
  
}









