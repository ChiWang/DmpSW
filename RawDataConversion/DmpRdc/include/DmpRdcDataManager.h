/*
 *  $Id: DmpRdcDataManager.h, 2014-03-07 09:43:19 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpRdcDataManager_H
#define DmpRdcDataManager_H

#include <map>
#include <vector>
#include <fstream>      // ifstream*

#include "DmpVDataManager.h"

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
  void BookBranch();
  void SetOutDataName(std::string name = "default");

private:
  DmpRdcDataManager();
  ~DmpRdcDataManager();
  static DmpRdcDataManager  *fInstance;         // singleton

public:
  bool  OpenInputData(std::string);
  bool  SetConnectorPsd();
  bool  SetConnectorStk();
  bool  SetConnectorBgo();
  bool  SetConnectorNud();
  bool  Execute();

private:
  bool  ConversionHeader();
  bool  ConversionPsd();
  bool  ConversionStk();
  bool  ConversionBgo();
  bool  ConversionNud();

private:
  bool  TriggerMatch();
  bool  SetConnectorBgo_BT2012();
  bool  ConversionBgo_BT2012();
  bool  SetConnectorBgo_CT2013(){return true;}
  bool  ConversionBgo_CT2013(){return true;}
  bool  SetConnectorBgo_Final(){return true;}
  bool  ConversionBgo_Final(){return true;}

private:
  static std::string   fConnectorPath;     // connection files of FEE to Detector. Top path, include all directories of subDet
  std::string   fInDataName;        // input raw data from detector(format binary)
  ifstream      *fHexData;          // pointer of input data
  std::vector<short>    fTrigger;      // size = number of SubDet + 1
  std::map<int, int>    ConnectorPsd;
  std::map<int, int>    ConnectorStk;
  std::map<int, int>    ConnectorBgo;     // FEE 2 Detector
    //ConnectorBgo[FEEID*1000+ChannelID][LBSD_ID]
    //LBSD_ID = Layer_id*10000+Bar_id*100+Side_id*10+Dy_id
  std::map<int, int>    ConnectorNud;
};

#endif

