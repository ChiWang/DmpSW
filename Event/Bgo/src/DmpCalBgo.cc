/*
 *  $Id: DmpCalBgo.cc, 2014-04-04 13:55:38 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 04/04/2014
*/

#include "TClonesArray.h"

#include "DmpCalBgo.h"
#include "DmpDetectorBgo.h"

//-------------------------------------------------------------------
DmpCalBgoPMT::DmpCalBgoPMT(){
  fPedDy2[0]  = -1; fPedDy2[1]  = -1;
  fPedDy5[0]  = -1; fPedDy5[1]  = -1;
  fPedDy8[0]  = -1; fPedDy8[1]  = -1;
  fRelDy25[0] = -1; fRelDy25[1] = -1;
  fRelDy58[0] = -1; fRelDy58[1] = -1;
}

//-------------------------------------------------------------------
DmpCalBgo::DmpCalBgo()
 :fUsedDate_Ped("no"),
  fUsedDate_Mip("no"),
  fUsedDate_Rel("no"),
  fBarSet(0),
  fRefBarSet(0)
{
  fBarSet = new TClonesArray("DmpCalBgoBar",300);
  fRefBarSet = new TClonesArray("DmpCalBgoBar",30);
  int nBar=DmpDetector::Bgo::kPlaneNo*2*DmpDetector::Bgo::kBarNo;
  for(int i=0;i<nBar;++i){
    fBarSet->New(i);
  }
  int nRefBar=DmpDetector::Bgo::kPlaneNo*2*DmpDetector::Bgo::kRefBarNo;
  for(short i=0;i<nRefBar;++i){
    fRefBarSet->New(i);
  }
}

//-------------------------------------------------------------------
DmpCalBgo::~DmpCalBgo(){
}

//-------------------------------------------------------------------
DmpCalBgoBar* DmpCalBgo::GetBar(const int &SDID)const{
  // get one bar;
  return (DmpCalBgoBar*)fBarSet->ConstructedAt(SDID%100*DmpDetector::Bgo::kBarNo+SDID/100);
}

//-------------------------------------------------------------------
DmpCalBgoBar* DmpCalBgo::GetRefBar(const short &layer, const short &side)const{
  // get one Ref. bar;
  return (DmpCalBgoBar*)fBarSet->ConstructedAt(layer*DmpDetector::Bgo::kRefBarNo+side);
}


//#include <boost/filesystem/path.hpp>
  //boost::filesystem::path inpath(GetInData());


