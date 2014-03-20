/*
 *  $Id: DmpRdcAlgBgo.h, 2014-03-19 18:40:49 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#ifndef DmpRdcAlgBgo_H
#define DmpRdcAlgBgo_H

#include <string>
#include <map>
#include <fstream>

class TClonesArray;

class DmpRdcAlgBgo{
public:
  DmpRdcAlgBgo();
  virtual ~DmpRdcAlgBgo();
  virtual bool SetupConnector();
  virtual bool Convert();        // convert one event
  void  SetFileStream(std::ifstream *&p)   {fFile = p;}
  short GetTrigger() const {return fTrigger;}

private:
  bool      fRunMe;        // tag to run this subDet
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
  std::ifstream      *fFile;     // pointer of file stream

private:
  // for one event
  TClonesArray  *fHits;     // responded bars
  short     fTrigger;       // trigger of all FEE

};

#endif


