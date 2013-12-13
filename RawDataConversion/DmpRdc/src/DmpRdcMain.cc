/*=====================================================================
 *   File:   DmpRdcManagerMain.cc
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  13/12/2013   12:30:59
=====================================================================*/

#include <iostream>

#include "DmpRdcManager.hh"

using namespace std;

//------------------------------------------------------------------------------
void Usage();

//------------------------------------------------------------------------------
int main(int argc, char* argv[]){

  DmpRdcManager* RdcMan = DmpRdcManager::GetInstance();
  if ( ! RdcMan->SetConnectorPsd() ) return 1;
  if ( ! RdcMan->SetConnectorStk() ) return 1;
  if ( ! RdcMan->SetConnectorBgo() ) return 1;
  if ( ! RdcMan->SetConnectorNud() ) return 1;

  TString inFileName;
  if (argc > 2) {
    Usage();
    return 1;
  } else if (argc == 2) {
    inFileName = argv[1];
  } else {
    inFileName = "DmpRdcInput.infor";
  }

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
  } else {
    Usage();
    return 1;
  }

  DmpRdcManager::Clear();
  return 0;

}

//------------------------------------------------------------------------------
void Usage(){
  cerr<<"Error: Usage:\tXXX"<<endl;
}
