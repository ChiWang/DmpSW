/*
 *  $Id: DmpRdcVAlgSubDet.h, 2014-04-17 00:18:53 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/03/2014
*/

#ifndef DmpRdcVAlgSubDet_H
#define DmpRdcVAlgSubDet_H

#include <fstream>
#include <map>

#include "DmpVAlg.h"

class TClonesArray;
class DmpEvtRdcHeader;
class DmpRdcSvcLog;

class DmpRdcVAlgSubDet : public DmpVAlg{
/*
 *  DmpRdcVAlgSubDet
 *
 *      if you want to create a new RdcAlg for your subDet, derive from this class
 *
 */
public:
  DmpRdcVAlgSubDet(const std::string&);
  virtual ~DmpRdcVAlgSubDet(){}
  virtual void Set(const std::string &type,const std::string &argv);
  bool Initialize();
  bool Finalize()  {return true;}

protected:
  virtual bool InitializeSubDet()=0;        // setup connector, and so on
  virtual void AppendThisSignal(const int&,const float&)=0;

protected:
  std::ifstream         *fFile;             // in data stream, for all Alg. of subDet
  DmpRdcSvcLog          *fLog;              // log status, for all Alg. of subDet
  DmpEvtRdcHeader          *fEvtHeader;        // all subDet need it
  std::string           fConnectorPath;     // where to read cnct files
  std::map<int,int>     fConnector;         // for all input datas
    /*
     * Connector: FEE channel <--> Detector
     * fConnector[FEEID*1000+ChannelID][LBSD_ID]
     * LBSD_ID = Layer_id*10000+Bar_id*100+Side_id*10+Dy_id
     *
    */
  bool                  fConnectorDone;     // mark of Connector

protected:
  TClonesArray          *fMSDSet;           // initialize it in InitializeSubDet

};

#endif


