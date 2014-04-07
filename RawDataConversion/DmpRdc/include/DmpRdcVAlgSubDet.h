/*
 *  $Id: DmpRdcVAlgSubDetSubDet.h, 2014-03-20 23:56:17 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/03/2014
*/

#ifndef DmpRdcVAlgSubDet_H
#define DmpRdcVAlgSubDet_H

#include <map>
#include "DmpVAlgorithm.h"

class TClonesArray;

class DmpRdcVAlgSubDet : public DmpVAlgorithm{
/*
 *  DmpRdcVAlgSubDet
 *
 *
 */
public:
  DmpRdcVAlgSubDet(const std::string&);
  virtual ~DmpRdcVAlgSubDet(){}
  /*
   *  Setup connector fConnector
   *
   *    1. should include "DmpRdcConnectorInterface.h"
   *    2. if (connector path == "default") return true, else: set fRunMe = true, then setup connector
   *
   */
  virtual bool Finialize()  {return true;}
  virtual bool ProcessThisEvent();  // convert one event

protected:
  virtual void AppendThisSignal(const int&,const float&)=0;

protected:
  std::map<int,int> fConnector;     // for all input datas
    /*
     * Connector: FEE channel <--> Detector
     * fConnector[FEEID*1000+ChannelID][LBSD_ID]
     * LBSD_ID = Layer_id*10000+Bar_id*100+Side_id*10+Dy_id
     *
    */
  bool          fRunMe;             // tag to run this subDet
  TClonesArray  *fMSDSet;           // responded bars (update it each event)
};

#endif


