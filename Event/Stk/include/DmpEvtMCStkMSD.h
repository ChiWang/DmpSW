/*
 *  $Id: DmpEvtMCStkMSD.h, 2014-06-09 11:12:27 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/12/2013
*/

#ifndef DmpEvtMCStkMSD_H
#define DmpEvtMCStkMSD_H

#include <map>
#include "TObject.h"

class DmpEvtMCStkMSD : public TObject{
/*
 *  DmpEvtMCStkMSD
 *
 *      This class used to descrip a Stk strip.
*/
public:
  DmpEvtMCStkMSD();
  ~DmpEvtMCStkMSD();
  void  SetSDID(const int &id)   {fSDID = id;}
  int   GetSDID() const {return fSDID;}
  void  AddG4Hit(const double &e, const int &trackID, bool isBackTrack=false);
  double GetTotalEnergy(short type=0) const;

private:
  int       fSDID;          // Stk strip ID. fSDID =  layerID*100000 +block*10000 + ladder*1000 + stripID
  std::map<int,double>   fFwdTrack;     // forward track. key is ID, value is total energy(unit MeV) deposited in this strip
  std::map<int,double>   fBwdTrack;     // backward track. key is ID, value is total energy(unit MeV) deposited in this strip

  ClassDef(DmpEvtMCStkMSD,1)
};

#endif


