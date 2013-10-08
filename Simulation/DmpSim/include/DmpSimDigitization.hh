#ifndef DmpSimDigitization_h
#define DmpSimDigitization_h 1

#include "G4VDigitizerModule.hh"
#include "DmpSimStkDigi.hh"
#include "DmpSimPsdDigi.hh"
#include "globals.hh"

class DmpSimDigitization : public G4VDigitizerModule
{
public:
  
  DmpSimDigitization(G4String name);
  ~DmpSimDigitization();
  
  void Digitize();

private:
  
  DmpSimStkDigitsCollection*  DigitsCollection;
  DmpSimPsdDigitsCollection*  PSDDigitsCollection;

};

#endif








