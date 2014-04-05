/*
 *  $Id: DmpCalBgoMetaData.cc, 2014-04-04 21:24:41 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 04/04/2014
*/

#include "TClonesArray.h"

#include "DmpCalBgoMetaData.h"
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
DmpCalBgoMetaData::DmpCalBgoMetaData()
 :fUsedDate_Ped("no"),
  fUsedDate_Mip("no"),
  fUsedDate_Rel("no"),
  fBarCollection(0),
  fRefBarCollection(0)
{
  fBarCollection = new TClonesArray("DmpCalBgoBar",300);
  fRefBarCollection = new TClonesArray("DmpCalBgoBar",30);
  int nBar=DmpDetector::Bgo::kPlaneNo*2*DmpDetector::Bgo::kBarNo;
  for(int i=0;i<nBar;++i){
    fBarCollection->New(i);
  }
  int nRefBar=DmpDetector::Bgo::kPlaneNo*2*DmpDetector::Bgo::kRefBarNo;
  for(short i=0;i<nRefBar;++i){
    fRefBarCollection->New(i);
  }
}

//-------------------------------------------------------------------
DmpCalBgoMetaData::~DmpCalBgoMetaData(){
}

//-------------------------------------------------------------------
DmpCalBgoBar* DmpCalBgoMetaData::GetBar(const int &SDID)const{
  // get one bar;
  return (DmpCalBgoBar*)fBarCollection->ConstructedAt(SDID%100*DmpDetector::Bgo::kBarNo+SDID/100);
}

//-------------------------------------------------------------------
DmpCalBgoBar* DmpCalBgoMetaData::GetRefBar(const short &layer, const short &side)const{
  // get one Ref. bar;
  return (DmpCalBgoBar*)fBarCollection->ConstructedAt(layer*DmpDetector::Bgo::kRefBarNo+side);
}


//#include <boost/filesystem/path.hpp>
  //boost::filesystem::path inpath(GetInData());


