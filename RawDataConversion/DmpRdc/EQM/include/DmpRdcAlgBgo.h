/*
 *  $Id: DmpRdcAlgBgo.h, 2014-05-26 10:13:30 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#ifndef DmpRdcAlgBgo_H
#define DmpRdcAlgBgo_H

#include <fstream>
#include "DmpVAlg.h"

class TClonesArray;
class DmpEvtRdcHeader;

class DmpRdcAlgBgo : public DmpVAlg{
/*
 *  DmpRdcAlgBgo
 *
 *      This is the default Rdc Alg of Bgo
 *
 *      User could write a new one, and
 *      append it into DmpAlgMgr in JobOpt file. Then,
 *      could run the new Alg.
 *
 */
public:
  DmpRdcAlgBgo();
  ~DmpRdcAlgBgo();
  void Set(const std::string&,const std::string&);
  bool Initialize();
  bool ProcessThisEvent();      // convert one event
  bool Finalize();

private:
  void AppendThisSignal(const int&,const int&);

private:
  std::ifstream         *fFile;             // in data stream, for all Alg. of subDet
  std::string           fConnectorPath;     // where to read cnct files
  std::map<int,int>     fConnector;         // for all input datas
    /*
     * Connector: FEE channel <--> Detector
     * fConnector[FEEID*1000+ChannelID][LBSD_ID]
     * LBSD_ID = Layer_id*10000+Bar_id*100+Side_id*10+Dy_id
     *
    */
  bool                  fConnectorDone;     // mark of Connector

private:
  short     fFEEType;       // FEE type of this subDet
  short     fFEENo;         // number of FEE
  TClonesArray      *fBgoSet;           // a collection of event class of Bgo
  DmpEvtRdcHeader   *fEvtHeader;        // all subDet need it
};

#endif


