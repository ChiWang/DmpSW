/*
 *  $Id: DmpRdcVAlgSubDet.h, 2014-04-09 19:58:09 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 20/03/2014
*/

#ifndef DmpRdcVAlgSubDet_H
#define DmpRdcVAlgSubDet_H

#include <map>
#include "DmpVAlg.h"

class TClonesArray;

class DmpRdcVAlgSubDet : public DmpVAlg{
/*
 *  DmpRdcVAlgSubDet
 *
 *
 */
public:
  DmpRdcVAlgSubDet(const std::string&);
  virtual ~DmpRdcVAlgSubDet(){}
  virtual bool ProcessThisEvent();  // convert one event
  virtual bool Finalize()  {return true;}

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


