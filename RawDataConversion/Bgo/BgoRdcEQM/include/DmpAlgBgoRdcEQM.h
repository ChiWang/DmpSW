/*
 *  $Id: DmpAlgBgoRdcEQM.h, 2014-06-17 15:44:38 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 17/06/2014
*/

#ifndef DmpAlgBgoRdcEQM_H
#define DmpAlgBgoRdcEQM_H

#include <fstream>
#include "DmpVAlg.h"

class TClonesArray;
class DmpEvtHeader;

class DmpAlgBgoRdcEQM : public DmpVAlg{
/*
 *  DmpAlgBgoRdcEQM
 *
 *      This class used to read Bgo data, only.
 */
public:
  DmpAlgBgoRdcEQM();
  ~DmpAlgBgoRdcEQM();

  void Set(const std::string&,const std::string&);      // set option
  bool Initialize();        // setup connector, set fCNCTDone = true
  bool ProcessThisEvent();  // include 2 parts, header and Bgo
  bool Finalize();          // clear object in TClonesArray

private:
  bool SetConnector();
  bool ProcessThisEventHeader();
  bool ProcessThisEventBgo();
  void AppendThisSignal(const int&,const int&);

private:
  std::string       fInDataName;        // input data name
  std::ifstream     fInFilePtr;         // in data stream
  DmpEvtHeader   *fEvtHeader;        // event header. out data

private:
  TClonesArray      *fBgoBarSet;        // Bgo output. out data
  std::map<short,int> fCNCTMapBgo;      // map of connector
  std::string       fCNCTPathBgo;       // connector path
  bool              fCNCTDoneBgo;       // connector setted?

};

#endif

