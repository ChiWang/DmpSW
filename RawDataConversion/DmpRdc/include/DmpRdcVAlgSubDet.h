/*
 *  $Id: DmpRdcVAlgSubDetSubDet.h, 2014-03-20 23:56:17 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/03/2014
*/

#ifndef DmpRdcVAlgSubDet_H
#define DmpRdcVAlgSubDet_H

#include <map>
#include "DmpRdcVAlg.h"

class TClonesArray;

class DmpRdcVAlgSubDet : public DmpRdcVAlg{
public:
  DmpRdcVAlgSubDet();
  virtual ~DmpRdcVAlgSubDet();
  virtual bool SetupConnector();
  virtual bool Convert();           // convert one event

protected:
  std::map<int,int> fConnector;     // for all input datas
    /*
     * Connector: FEE channel <--> Detector
     * fConnector[FEEID*1000+ChannelID][LBSD_ID]
     * LBSD_ID = Layer_id*10000+Bar_id*100+Side_id*10+Dy_id
     *
    */
  bool          fRunMe;             // tag to run this subDet
  TClonesArray  *fHits;             // responded bars (update it each event)

};

#endif


