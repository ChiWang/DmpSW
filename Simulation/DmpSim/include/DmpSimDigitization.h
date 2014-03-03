#ifndef DmpSimuDigitization_h
#define DmpSimuDigitization_h 1

#include "G4VDigitizerModule.hh"
#include "DmpSimuStkDigi.hh"
#include "DmpSimuPsdDigi.hh"
#include "globals.hh"

class DmpSimuDigitization : public G4VDigitizerModule
{
public:
  
  DmpSimuDigitization(G4String name);
  ~DmpSimuDigitization();
  
  void Digitize();

private:
  
  DmpSimuStkDigitsCollection*  DigitsCollection;
  DmpSimuPsdDigitsCollection*  PSDDigitsCollection;

};

#endif








