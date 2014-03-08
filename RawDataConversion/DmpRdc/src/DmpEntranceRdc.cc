/*
 *  $Id: DmpEntranceRdc.cc, 2014-03-08 20:06:58 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

//#include <iostream>

#include "DmpRdcDataManager.h"
#include "DmpEntranceRdc.h"

DmpRdcDataManager *dataManager = 0;

//-------------------------------------------------------------------
bool DmpCore::RdcInitialize(){
  if (not DmpRdcManager::SetConnectorPsd()) return false;
  if (not DmpRdcManager::SetConnectorStk()) return false;
  if (not DmpRdcManager::SetConnectorBgo()) return false;
  if (not DmpRdcManager::SetConnectorNud()) return false;
  dataManager = DmpRdcDataManager::GetInstance();
}

//-------------------------------------------------------------------
void DmpCore::RdcSetInDataPath(std::string p){
  dataManager->SetInDataPath(p);
}

//-------------------------------------------------------------------
void DmpCore::RdcSetOutDataPath(std::string p){
  dataManager->SetOutDataPath(p);
}

//-------------------------------------------------------------------
std::string DmpCore::RdcGetOutDataPath(){
  dataManager->GetOutDataPath();
}

//-------------------------------------------------------------------
void DmpCore::RdcSetOutDataName(std::string n){
  dataManager->SetOutDataName();
}

//-------------------------------------------------------------------
void DmpCore::RdcExecute(std::string dataName){
  if(not dataManager->OpenInputData(dataName))  return;
  dataManager->BookBranch();
  dataManager->CreateOutDataName();
  dataManager->

  string note;
  if (inFileName.Contains(".dat")) {
    note = inFileName;
    unsigned found = note.find_last_of("/\\");
    dataManager->SetInDataPath((TString)note.substr(0,found));
    dataManager->SetDataName((TString)note.substr(found+1));
    dataManager->Core();
  } else if (inFileName.Contains("RdcInput.infor")) {
    ifstream* BatchInfor = new ifstream (inFileName,ios::in);
    if (!BatchInfor->good()) {
      cerr<<"Error: There's not a file named "<<inFileName<<" as batch mode input"<<endl;
      return 1;
    }
    getline(*BatchInfor,note);    // reserved 1 line for note
    getline(*BatchInfor,note);
    dataManager->SetInDataPath(note);
    getline(*BatchInfor,note);    // reserved 1 line for note
    getline(*BatchInfor,note);
    dataManager->SetOutDataPath(note);
    getline(*BatchInfor,note);    // reserved 1 line for note
    while (note != "END") {
      *BatchInfor>>note;
      if (note == "END") break;
      dataManager->SetDataName((TString)note);
      dataManager->Core();
    }
    BatchInfor->close();
    delete BatchInfor;
  }
  dataManager->SaveOutput();
}

//-------------------------------------------------------------------
void DmpCore::RdcClear(){
  DmpRdcDataManager::Vanish();
}

