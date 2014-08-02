/*
 *  $Id: DmpRdcAlgEQM.h, 2014-08-02 21:33:05 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 01/08/2014
*/

#ifndef DmpRdcAlgEQM_H
#define DmpRdcAlgEQM_H

#include <fstream>
#include <vector>
#include "DmpRunMode.h"

class TClonesArray;
class DmpEvtHeader;

struct DmpRdcFeeData{
  DmpRdcFeeData():FeeID(-1),RunMode(DmpRunMode::kUnknow),Trigger(-1),CRCStatus(true){}
  short FeeID;
  short RunMode;
  short Trigger;
  std::map<short,int>   Signal; // key is channel id, value is ADC count
  bool CRCStatus;
};

class DmpRdcAlgEQM : public DmpVAlg{
/*
 *  DmpRdcAlgEQM
 *
 */

public:
  DmpRdcAlgEQM();
  ~DmpRdcAlgEQM();
  void Set(const std::string&,const std::string&);
  bool Initialize();
  bool ProcessThisEvent();
  bool Finalize();

private:
typedef std::map<short, DmpRdcFeeData>  DmpRdcFeeDataBuffer;
/*
 *  DmpRdcFeeDataBuffer
 * key:     Fee id
 * value:   object of DmpRdcFeeData
 */
typedef std::map<short, DmpRdcFeeDataBuffer>  DmpRdcSubDetDataBuffer;
/*
 *  DmpRdcSubDetDataBuffer
 * key:     package count
 *
 */
  std::string       fInDataName;    // input data name
  std::ifstream     fFile;          // in data stream
  DmpRdcSubDetDataBuffer  fHeaderBuffer;       // data buffer for event header
  DmpRdcSubDetDataBuffer  fBgoBuffer;          // data buffer for Bgo
  /*
   * key:
   *    event id
   * value:
   *    a vector of DmpRdcFeeDataBuffer
   */
  DmpRdcSubDetDataBuffer  fPsdBuffer;          // data buffer for Psd
  DmpRdcSubDetDataBuffer  fStkBuffer;          // data buffer for Stk
  DmpRdcSubDetDataBuffer  fNudBuffer;          // data buffer for Nud

private:
  bool ReadDataIntoDataBuffer();
  bool fActiveSubDet;   // set it false at the begin of ProcessThisEvent();
  DmpEvtHeader  *fEvtHeader;
  bool ProcessThisEventHeader(short);

private:
  TClonesArray      *fPsdStripSet;      // Psd outdata
  std::string       fCNCTPathPsd;       // connector path
  std::map<int,int> fMapPsd;            // map of Psd connector
  bool              fCNCTDonePsd;       // check map done?
  void InitializePsd();
  bool ProcessThisEventPsd(short);
  void AppendSignalPsd(const int&,const int&);

private:
  TClonesArray      *fStkLadderSet;     // Stk outdata
  std::string       fCNCTPathStk;       // connector path
  std::map<int,int> fMapStk;            // map of Stk connector
  bool              fCNCTDoneStk;
  void InitializeStk();
  bool ProcessThisEventStk(short);
  void AppendSignalStk(const int&,const int&);

private:
  TClonesArray      *fBgoBarSet;    // Bgo outdata
  std::string       fCNCTPathBgo;   // connector path
  std::map<int,int> fMapBgo;        // map of Bgo connector
  bool              fCNCTDoneBgo;
  void InitializeBgo();
  bool ProcessThisEventBgo(short);
  void AppendSignalBgo(const int&,const int&);

private:
  TClonesArray      *fNudBlockSet;    // Bgo outdata
  std::string       fCNCTPathNud;   // connector path
  std::map<int,int> fMapNud;        // map of Bgo connector
  bool              fCNCTDoneNud;
  void InitializeNud();
  bool ProcessThisEventNud(short);
  void AppendSignalNud(const int&,const int&);

};

#endif

