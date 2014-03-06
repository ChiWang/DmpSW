/*
 *  $Id: DmpRdcDataManager.h, 2014-03-06 21:47:52 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpRdcDataManager_H
#define DmpRdcDataManager_H

#include <map>
#include <vector>
#include <fstream>      // ifstream*

#include "DmpVDataManager.h"

class TTree;
class DmpRdcDataManager : public DmpVDataManager{
/*
 *  DmpRdcDataManager
 *
 *  SetConnectorSub-DetX() and ConversionSub-DetX()    could have many versions, for cosmic; whole; Beam test 2012..
 *  
 *
*/
public:
  static DmpRdcDataManager*     GetInstance();
  static void Vanish();
  //bool Core();
  void SetHexData(ifstream *p)  {fHexData = p;}

public:
  bool  SetConnectorPsd();
  bool  SetConnectorStk();
  bool  SetConnectorBgo();
  bool  SetConnectorNud();

  bool  ConversionHeader();
  bool  ConversionPsd();
  bool  ConversionStk();
  bool  ConversionBgo();
  bool  ConversionNud();

private:
  DmpRdcDataManager();
  ~DmpRdcDataManager();
  static DmpRdcDataManager  *fInstance;         // singleton
  bool  TriggerMatch();

private:
  bool  SetConnectorBgo_BT2012();
  bool  ConversionBgo_BT2012();
  bool  SetConnectorBgo_CT2013(){return true;}
  bool  ConversionBgo_CT2013(){return true;}
  bool  SetConnectorBgo_Final(){return true;}
  bool  ConversionBgo_Final(){return true;}

private:
  std::string   fConnectorPath;     // connection files of FEE to Detector
  ifstream      *fHexData;          // raw data from detector (fromat hex)
  TTree         *fTree;             // Tree to save output data of RDC
  std::vector<short>    fTrigger;      // size = number of SubDet + 1
  std::map<int, int>    ConnectorPsd;
  std::map<int, int>    ConnectorStk;
  std::map<int, int>    ConnectorBgo;     // FEE 2 Detector
    //ConnectorBgo[FEEID*1000+ChannelID][LBSD_ID]
    //LBSD_ID = Layer_id*10000+Bar_id*100+Side_id*10+Dy_id
  std::map<int, int>    ConnectorNud;
};

#endif

