/*
 *  $Id: DmpIOSvc.h, 2014-05-19 10:01:33 DAMPE $
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

  virtual void BookBranch()=0;
  virtual void SaveOutput();  // save output, for one indata

public:
  const std::string& GetOutDataPath() const {return fOutDataPath;}
  const std::string& GetOutDataName() const {return fOutDataName;}
  const std::string& InputData()    const   {return fInData;}

protected:
  virtual bool SetInputData(const std::string &n);
  void SetOutDataPath(const std::string&);
  void AppendDataNote(const std::string &n) {fNote = n;}
  void SetPackageID(const std::string &n) {fPgkID += n;}

private:
  void SetOutDataName();
  std::string TimeStamp();

protected:
  TTree         *fOutDataTree;  // create and delete in concrete data manager class

private:
  std::vector<std::string>      fInFileName;
  std::vector<TFile*>           fInRootFile;    // in root files pointer

  std::string   fOutDataPath;   // for all output datas
  std::string   fOutDataName;   //
  TFile         *fOutRootFile;  // output one root file

  std::string   fPgkID;         // package id, add this in out data name
  std::string   fNote;          // add note in the out data name
};

#endif


