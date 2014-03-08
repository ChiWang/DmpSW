/*
 *  $Id: DmpEntranceRdc.cc, 2014-03-08 20:06:58 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

//#include <iostream>

#include "DmpRdcDataManager.h"
#include "DmpEntranceRdc.h"

//-------------------------------------------------------------------
void DmpCore::RdcSetInDataPath(std::string p){
  DmpRdcDataManager::GetInstance()->SetInDataPath(p);
}

//-------------------------------------------------------------------
void DmpCore::RdcSetOutDataPath(std::string p){
  DmpRdcDataManager::GetInstance()->SetOutDataPath(p);
}

//-------------------------------------------------------------------
std::string DmpCore::RdcGetOutDataPath(){
  DmpRdcDataManager::GetInstance()->GetOutDataPath();
}

//-------------------------------------------------------------------
void DmpCore::RdcSetOutDataName(std::string n){
  DmpRdcDataManager::GetInstance()->SetOutDataName();
}

//-------------------------------------------------------------------
void DmpCore::RdcInitialize(){
  RdcMan = DmpRdcDataManager::GetInstance();

  if ( ! RdcMan->SetConnectorPsd() ) return -2;
  if ( ! RdcMan->SetConnectorStk() ) return -2;
  if ( ! RdcMan->SetConnectorBgo() ) return -2;
  if ( ! RdcMan->SetConnectorNud() ) return -2;
}

//-------------------------------------------------------------------
void DmpCore::RdcExecute(std::string dataName){
  if(not RdcMan->OpenInputData(dataName))  return;
  RdcMan->BookBranch();
  RdcMan->CreateOutDataName();
  RdcMan->

  string note;
  if (inFileName.Contains(".dat")) {
    note = inFileName;
    unsigned found = note.find_last_of("/\\");
    RdcMan->SetInDataPath((TString)note.substr(0,found));
    RdcMan->SetDataName((TString)note.substr(found+1));
    RdcMan->Core();
  } else if (inFileName.Contains("RdcInput.infor")) {
    ifstream* BatchInfor = new ifstream (inFileName,ios::in);
    if (!BatchInfor->good()) {
      cerr<<"Error: There's not a file named "<<inFileName<<" as batch mode input"<<endl;
      return 1;
    }
    getline(*BatchInfor,note);    // reserved 1 line for note
    getline(*BatchInfor,note);
    RdcMan->SetInDataPath(note);
    getline(*BatchInfor,note);    // reserved 1 line for note
    getline(*BatchInfor,note);
    RdcMan->SetOutDataPath(note);
    getline(*BatchInfor,note);    // reserved 1 line for note
    while (note != "END") {
      *BatchInfor>>note;
      if (note == "END") break;
      RdcMan->SetDataName((TString)note);
      RdcMan->Core();
    }
    BatchInfor->close();
    delete BatchInfor;
  }
  RdcMan->SaveOutput();
}

//-------------------------------------------------------------------
void DmpCore::RdcClear(){
  DmpRdcDataManager::Vanish();
}

