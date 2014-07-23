/*
 *  $Id: DmpRdcAlgBT2012.h, 2014-05-27 23:43:46 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 27/05/2014
*/

#ifndef DmpRdcAlgBT2012_H
#define DmpRdcAlgBT2012_H

#include <fstream>

#include "DmpVAlg.h"

class TClonesArray;
class DmpEvtRdcHeader;

class DmpRdcAlgBT2012 : public DmpVAlg{
/*
 *  DmpRdcAlgBT2012
 *
 */
public:
  DmpRdcAlgBT2012();
  ~DmpRdcAlgBT2012();
  void Set(const std::string&,const std::string&);
  bool Initialize();
  bool ProcessThisEvent();
  bool Finalize();

private:    // for all
  std::string       fInDataName;    // input data name
  std::ifstream     fFile;          // in data stream
  DmpEvtRdcHeader   *fEvtHeader;    // save me
  bool ProcessThisEventHeader();    // convert event header

private:    // Bgo
  TClonesArray      *fBgoBarSet;    // Bgo outdata
  std::string       fCNCTPathBgo;   // connector path
  std::map<int,int> fMapBgo;        // map of Bgo connector
  bool              fCNCTDoneBgo;   // setup connector succeed
  short             fFEETypeBgo;    // fee type of Bgo
  short             fFEENoBgo;      // FEE number of Bgo
  void InitializeBgo();
  bool ProcessThisEventBgo();
  void AppendSignalBgo(const int&,const int&);

private:    // Psd
  TClonesArray      *fPsdStripSet;
  std::string       fCNCTPathPsd;
  std::map<int,int> fMapPsd;
  bool              fCNCTDonePsd;
  short             fFEETypePsd;
  short             fFEENoPsd;
  void InitializePsd();
  bool ProcessThisEventPsd();
  void AppendSignalPsd(const int&,const int&);
  //bool FinalizePsd();

private:    // Nud
  TClonesArray      *fNudBlockSet;
  std::string       fCNCTPathNud;
  std::map<int,int> fMapNud;
  bool              fCNCTDoneNud;
  short             fFEETypeNud;
  void InitializeNud();
  bool ProcessThisEventNud();
  void AppendSignalNud(const int&,const int&);

private:    // Stk
  TClonesArray      *fStkLadderSet;
  std::string       fCNCTPathStk;
  std::map<int,int> fMapStk;
  bool              fCNCTDoneStk;
  short             fFEETypeStk;
  short             fFEENoStk;
  void InitializeStk();
  bool ProcessThisEventStk();
  void AppendSignalStk(const int&,const int&);

};

#endif


