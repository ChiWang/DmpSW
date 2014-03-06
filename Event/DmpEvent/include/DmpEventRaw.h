/*
 *  $Id: DmpEventRaw.h, 2014-03-04 10:39:09 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 25/02/2014
*/

#include "TObject.h"

class TClonesArray;
class DmpSimDataManager;
class DmpEvtHeader;

class DmpEventRaw : public TObject{
/*
 *  DmpEventRaw
 *
 *  use this to book branch of RawDataConversion(output is Raw.root), only save all ADC information
 *  at the begining of Reconstruction will use the Raw.root and update the Hits information then save the opend root file
 *  (the sturctures of input and output root files of are the same)
 *
 *  Simulation will also use this class to book the branch, and the output of Simulation has the information of Hits
 *
 */
  friend class DmpSimDataManager;  //! let Manager control all data members here 
public:
  DmpEventRaw();
  ~DmpEventRaw();

private:
  DmpEvtHeader      *fEvtHeader;
//*  TODO: add hits of Psd, Stk and Nud
  //TClonesArray      *fPsdHits;  //->
  //TClonesArray      *fStkHits;  //->
  TClonesArray      *fBgoHits;  //->
  //TClonesArray      *fNudHits;  //->

  ClassDef(DmpEventRaw,1)
};

