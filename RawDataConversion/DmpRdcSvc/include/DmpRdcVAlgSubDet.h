/*
 *  $Id: DmpRdcVAlgSubDet.h, 2014-04-17 00:18:53 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/03/2014
*/

#ifndef DmpRdcVAlgSubDet_H
#define DmpRdcVAlgSubDet_H

#include <ifstream>
#include <map>

#include "DmpVAlg.h"

class TClonesArray;
class DmpEvtHeader;
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
  virtual bool Initialize();
  virtual bool ProcessThisEvent();  // convert one event
  virtual bool Finalize()  {return true;}
  virtual void Set(const std::string &type,const std::string &argv);

protected:
  virtual bool SetupConnector()=0;
  virtual void AppendThisSignal(const int&,const float&)=0;

protected:
  static std::ifstream  *fFile;
  static DmpRdcSvcLog   *fLog;
  static DmpEvtHeader   *fEvtHeader;

protected:
  std::string           fConnectorPath;     // where to read cnct files
  std::map<int,int>     fConnector;         // for all input datas
    /*
     * Connector: FEE channel <--> Detector
     * fConnector[FEEID*1000+ChannelID][LBSD_ID]
     * LBSD_ID = Layer_id*10000+Bar_id*100+Side_id*10+Dy_id
     *
    */
  TClonesArray          *fMSDSet;           // initialize it in concrete class

};

#endif


