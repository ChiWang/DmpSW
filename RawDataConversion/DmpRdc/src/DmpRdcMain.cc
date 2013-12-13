/*=============================================================================
#       FileName :          dmpRdc.cc
#       Version  :          0.0.1
#       Author   :          USTC    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-08-03   08:46:33
#
#------------------------------------------------------------------------------
#       Description  :
#           Refer to ./Reade.md
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-08-16   16:56:51
=============================================================================*/

#include <iostream>

#include "DmpRdc.hh"

using namespace std;

//------------------------------------------------------------------------------
void Usage();

//------------------------------------------------------------------------------
int main(int argc, char* argv[]){

  DmpRdc* RdcMan = DmpRdc::GetInstance();
  if ( ! RdcMan->SetConnectorPsd() ) return 1;
  if ( ! RdcMan->SetConnectorStk() ) return 1;
  if ( ! RdcMan->SetConnectorBgo() ) return 1;
  if ( ! RdcMan->SetConnectorNud() ) return 1;

  TString inFileName = "DmpRdcInput.infor";
  string note;
  if (argc > 2) {
    Usage();
    return 1;
  } else if (argc == 2) {
    inFileName=argv[1];
    if (inFileName.Contains(".dat")) {
      note = argv[1];
      unsigned found = note.find_last_of("/\\");
      string path = note.substr(0,found);
      string name = note.substr(found+1);
//      RdcMan->SetInDataPath(XXX);
//      RdcMan->SetDataName(XXX);
      RdcMan->Core();
    }
  } else {
    if ( inFileName.Contains(".infor") ) {
      ifstream* BatchInfor = new ifstream (inFileName,ios::in);
      if (!BatchInfor->good()) {
        cout<<"\n\t---->Error: there's not a file named "<<inFileName<<endl;
        return 1;
      }
      getline(*BatchInfor,note);    // reserved 1 lines for note
      getline(*BatchInfor,note);
      RdcMan->SetInDataPath(note);
      getline(*BatchInfor,note);    // reserved 1 lines for note
      getline(*BatchInfor,note);
      RdcMan->SetOutDataPath(note);
      getline(*BatchInfor,note);    // reserved 1 lines for note
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
  }

  DmpRdc::Clear();
  return 0;

}

//------------------------------------------------------------------------------
void Usage(){
  cout<<"Usage:\tXXX"<<endl;
}
