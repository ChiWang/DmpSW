/*
 *  $Id: DmpCalBgoDataManager.h, 2014-05-16 01:53:27 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 04/04/2014
*/

#ifndef DmpCalBgoDataManager_H
#define DmpCalBgoDataManager_H

#include "DmpVDataManager.h"

class TClonesArray;
class DmpCalBgoMSD;

class DmpCalBgoDataManager : public DmpVDataManager{
public:
  static DmpCalBgoDataManager* GetInstance(){
    static DmpCalBgoDataManager instance;
    return &instance;
  }
  ~DmpCalBgoDataManager();
  bool InputData(const std::string&);
  bool InputData(const std::string&, const std::string&);   // Agrv_0 = *.dat, Agrv_1 = *.root
  void Initialize();
  void BookBranch();

private:
  DmpCalBgoDataManager();

public:
  TTree         *gInDataTree;   // in data
  DmpCalBgoMSD* GetBgoMSD(const int &SDID,const short &side=0)const;
  /*
   *  if SDID = LayerID*100 + BarID (>100)
   *    return a normal bar.
   *
   *  if SDID = LayerID (<100)
   *    return a Ref. bar (use side to choose which one)
   *
   */

private:
  TClonesArray   *fBgoMSDSet;       // construct all MSD of Bgo

};

//-------------------------------------------------------------------
extern DmpCalBgoDataManager *gDataMgr;

#endif


