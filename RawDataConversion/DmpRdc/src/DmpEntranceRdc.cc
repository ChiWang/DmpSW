/*
 *  $Id: DmpEntranceRdc.cc, 2014-03-07 15:59:55 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#include <iostream>

#include "DmpRdcDataManager.h"
#include "DmpEntranceRdc.h"

using namespace std;

//------------------------------------------------------------------------------
void Usage(){
  cerr<<"Error:\tno input dataName"<<endl;
  return 0;
}

//------------------------------------------------------------------------------
void DmpCore::EntranceRawDataConversion(int argc, char* argv[]){
  if(argc != 2) Usage();
  DmpRdcDataManager *RdcMan = GetInstance();
  if(not RdcMan->OpenInputData(argv[1]))  return -1;

  if ( ! RdcMan->SetConnectorPsd() ) return -2;
  if ( ! RdcMan->SetConnectorStk() ) return -2;
  if ( ! RdcMan->SetConnectorBgo() ) return -2;
  if ( ! RdcMan->SetConnectorNud() ) return -2;

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
      Usage();
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
  } else {
    Usage();
    return 1;
  }

  DmpRdcDataManager::Vanish();
}

//------------------------------------------------------------------------------


