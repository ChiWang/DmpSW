/*
 *  $Id: DmpIOSvc.h, 2014-05-20 14:30:13 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpIOSvc_H
#define DmpIOSvc_H

#include "DmpVSvc.h"

class TFile;
class TTree;

class DmpIOSvc : public DmpVSvc{
/* 
 *  DmpIOSvc
 *
 */
public:
  DmpIOSvc();
  virtual ~DmpIOSvc();
  bool Initialize();
  bool Finalize();
  void Set(const std::string&,const std::string&);
  TTree*  BookTree();

private:
  void CreateOutDataName();
  std::string TimeStamp();

private:
  std::vector<std::string>      fInFileName;
  std::vector<TFile*>           fInRootFile;    // in root files pointer

  std::string   fOutDataPath;   // for all output datas
  std::string   fOutDataName;   //
  TFile         *fOutRootFile;  // output one root file
  TTree         *fOutDataTree;  // create and delete in concrete data manager class

  std::string   fPkgID;         // package id, add this in out data name
  std::string   fNote;          // add note in the out data name
};

#endif


