/*
 *  $Id: DmpRdcAlgNud.h, 2014-03-19 18:40:52 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#ifndef DmpRdcAlgNud_H
#define DmpRdcAlgNud_H

#include <string>
#include <map>
#include <fstream>

#include "DmpRunMode.h"

class TClonesArray;
class DmpEvtHeader;

class DmpRdcAlgNud{
public:
  DmpRdcAlgNud();
  virtual ~DmpRdcAlgNud();
  virtual bool SetupConnector();
  virtual bool Convert();        // convert one event
  void  SetFileStream(std::ifstream *p)   {fFile = p;}

private:
  bool      fRunMe;         // tag to run this subDet
  // for all input datas
  std::map<int,int> fConnector;
    /*
     * Connector: FEE channel <--> Detector
     * fConnector[FEEID*1000+ChannelID][LBSD_ID]
     * LBSD_ID = Layer_id*10000+Bar_id*100+Side_id*10+Dy_id
     *
    */

private:
  // for one input data
  std::ifstream *fFile;     // pointer of file stream

private:
  // for one event
  TClonesArray  *fHits;     // responded bars
  DmpEvtHeader  *fHeader;   // to print time, set run mode

};

#endif


