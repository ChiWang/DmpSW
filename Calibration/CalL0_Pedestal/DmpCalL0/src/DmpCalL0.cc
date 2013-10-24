/*=============================================================================
#       FileName :          DmpCalL0.cc
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-18   14:50:35
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-23   01:10:37
=============================================================================*/

#include <iostream>
#include <fstream>

#include "TTree.h"

#include "DmpCalL0Manager.hh"

#include "DmpEvtHeader.hh"
#include "DmpEvtBgo.hh"

using namespace std;

int main(int argc, char* argv[]){
  TString inFileName = "DmpCalL0Input.infor";
  if (argc == 2) inFileName = argv[1];

  ifstream* BatchInfor = 0;
  if ( inFileName.Contains(".infor") && inFileName.Contains("DmpCalL0Input") ) {
    BatchInfor = new ifstream (inFileName,ios::in);
  } else {
    cout<<"Usage:\n\t1. dmpCalL0\n\t2. dmpCalL0 /path/DmpCalL0InputXXX.infor"<<endl;
  }

  if (!BatchInfor->good()) {
    cout<<"\n\t---->Error: there's not a file named "<<inFileName<<endl;
    return 0;
  }

  string note, dataName, inDataPath,outDataPath;
  for (Short_t i=0;i<4;++i) {
    getline(*BatchInfor,note);      // reserved 4 lines for note
  }
  getline(*BatchInfor,inDataPath);
  getline(*BatchInfor,note);        // reserved 1 line for note
  getline(*BatchInfor,outDataPath);
  getline(*BatchInfor,note);        // reserved 1 line for note
  *BatchInfor>>dataName;            // get the first dataName

  DmpCalL0Manager* CalL0Man = DmpCalL0Manager::GetInstance();   // Book Hist
  CalL0Man->SetInDataPath(inDataPath);
  CalL0Man->SetOutDataPath(outDataPath);

  while (dataName != "END") {
    CalL0Man->SetDataName(dataName);
    if ( ! CalL0Man->BookTree() ) {
      cout<<"\n\t---->Warning: open "<<CalL0Man->GetInDataPath()+dataName<<" failed"<<endl;
      *BatchInfor>>dataName;
      continue;
    } else {
      cout<<"\n\t---->Reading "<<CalL0Man->GetInDataPath()+dataName<<endl;
    }

    if ( ! CalL0Man->BookBranch() ) {
      *BatchInfor>>dataName;
      continue;
    }

    TTree* tree = CalL0Man->GetTreePointer();
    Long64_t nEvent = tree->GetEntries();
    cout<<"Evt Number = "<<nEvent<<endl;
    //loop of event package. set the order of suv-detector as the order of FEE in InData
    for (Long64_t iEvt=0;iEvt<nEvent;++iEvt) {
      tree->GetEntry(iEvt);
      if (iEvt > 100) break;
      //cout<<"Evt ID = "<<CalL0Man->GetEvent<DmpEvtHeaderRaw>("Header")->GetEventID()<<endl;
      //CalL0Man->GetEvent<DmpEvtBgoRaw>("Bgo")->PrintEvent();
      CalL0Man->FillPedestal("Bgo");

    }
    CalL0Man->SavePedestal("Bgo");
    *BatchInfor>>dataName;
  }
  BatchInfor->close();
  CalL0Man->Clear();
  return 0;
}


