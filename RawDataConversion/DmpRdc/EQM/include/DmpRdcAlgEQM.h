/*
 *  $Id: DmpRdcAlgEQM.h, 2014-08-01 10:58:20 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 01/08/2014
*/

#ifndef DmpRdcAlgEQM_H
#define DmpRdcAlgEQM_H

#include <fstream>
#include <vector>

class TClonesArray;
class DmpEvtHeader;

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
typedef std::map<short, std::vector>  DmpRdcFeeDataBuffer;
/*
 *  DmpRdcFeeDataBuffer
 * key:     Fee id
 * value:   Fee data, size is data length
 */
  std::string       fInDataName;    // input data name
  std::ifstream     fFile;          // in data stream
  std::map<short,DmpRdcFeeDataBuffer>  fHeaderBuffer;       // data buffer for event header
  std::map<short,DmpRdcFeeDataBuffer>  fBgoBuffer;          // data buffer for Bgo
  /*
   * key:
   *    event id
   * value:
   *    a vector of DmpRdcFeeDataBuffer
   */
  std::map<short,DmpRdcFeeDataBuffer>  fPsdBuffer;          // data buffer for Psd
  std::map<short,DmpRdcFeeDataBuffer>  fStkBuffer;          // data buffer for Stk
  std::map<short,DmpRdcFeeDataBuffer>  fNudBuffer;          // data buffer for Nud

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

