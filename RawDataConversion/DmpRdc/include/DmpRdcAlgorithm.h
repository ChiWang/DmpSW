/*
 *  $Id: DmpRdcAlgorithm.h, 2014-03-09 20:17:53 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpRdcAlgorithm_H
#define DmpRdcAlgorithm_H

#include <map>
#include <vector>
#include <fstream>      // ifstream*

class DmpRdcAlgorithm{
/*
 *  DmpRdcAlgorithm
 *
 *  SetConnectorSub-DetX() and ConversionSub-DetX()    could have many versions correspond to different phase.
 *  Look for the example of Bgo
 *
*/
public:
  static DmpRdcAlgorithm*     GetInstance();
  static void Vanish();
  bool SetConnectorPsd();       // implement in directory of subDet, use DmpRdcDataManager::GetPhase()
  bool SetConnectorStk();
  bool SetConnectorBgo();
  bool SetConnectorNud();

private:
  DmpRdcAlgorithm();
  ~DmpRdcAlgorithm();
  static DmpRdcAlgorithm  *sInstance;
  std::string   fConnectorPath;     // default is prefix/share/Connector
  // Connector: FEE channel <----> Detector
  std::map<int,int>  fConnectorPsd;
  std::map<int,int>  fConnectorStk;
  std::map<int,int>  fConnectorBgo;      // sConnectorBgo[FEEID*1000+ChannelID][LBSD_ID].    LBSD_ID = Layer_id*10000+Bar_id*100+Side_id*10+Dy_id
  std::map<int,int>  fConnectorNud;

public:
  void SetInputData(ifstream *p)    {fInputData = p;}
  bool ConvertEventHeader();
  bool ConvertEventPsd();
  bool ConvertEventStk();
  bool ConvertEventBgo();
  bool ConvertEventNud();
  bool TriggerMatch();

private:
  ifstream      *fInputData;        // pointer of input data
  std::vector<short>    fTrigger;   // size = number of SubDet + 1

};

#endif

