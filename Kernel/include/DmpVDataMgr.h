/*
 *  $Id: DmpVDataMgr.h, 2014-04-12 17:22:37 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpVDataMgr_H
#define DmpVDataMgr_H

class TTree;

class DmpVDataMgr{
/* 
 *  DmpVDataMgr
 *
 *  All data manager classes inherite from this class
 *
 *  Example: DmpRdcDataManger.h or DmpSimSvcDataMgr.h
 *
 */
public:
  DmpVDataMgr();
  virtual ~DmpVDataMgr();

  virtual void BookBranch()=0;
  virtual void FillEvent();
  virtual void ResetEvent()=0;
  virtual void SaveOutput();  // save output, for one indata
  virtual bool InputData(const std::string &n) {fInData = n; return true;}

public:
  std::string GetOutDataPath() const    {return fOutDataPath;}
  std::string GetOutDataName() const    {return fOutDataName;}

protected:
  void SetOutDataPath(const std::string&);
  void AppendDataNote(const std::string &n) {fNote = n;}
  void SetPackageID(const std::string &n) {fPgkID += n;}

private:
  void SetOutDataName();
  std::string TimeStamp();

protected:
  TTree         *fOutDataTree;  // create and delete in concrete data manager class

private:
  std::string   fInData;        // path + name. For one data
  std::string   fOutDataPath;   // for all output datas
  std::string   fOutDataName;   //
  std::string   fPgkID;         // package id, add this in out data name
  std::string   fNote;          // add note in the out data name
};

#endif


