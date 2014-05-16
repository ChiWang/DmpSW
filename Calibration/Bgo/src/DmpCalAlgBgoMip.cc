/*
 *  $Id: DmpCalAlgBgoMip.cc, 2014-05-16 01:53:38 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 17/10/2013
*/

#include <iostream>

#include "DmpCalManager.h"
#include "DmpCalHeader.h"
#include "DmpCalPsd.h"
#include "DmpCalStk.h"
#include "DmpCalBgo.h"
#include "DmpCalNud.h"

using namespace std;

int main(int argc, char* argv[]){
  TString inFileName = "DmpCalL0SBgoMipInput.infor";
  if (argc == 2) inFileName = argv[1];

  ifstream* BatchInfor = 0;
  if ( inFileName.Contains(".infor") && inFileName.Contains("DmpCalL0SBgoMipInput") ) {
    BatchInfor = new ifstream (inFileName,ios::in);
  } else {
    cout<<"Usage:\n\t1. dmpRdc\n\t2. dmpRdc /path/DmpCalL0SBgoMipInput.infor"<<endl;
  }

  if (!BatchInfor->good()) {
    cout<<"\n\t---->Error: there's not a file named "<<inFileName<<endl;
    return 0;
  }

  string note, dataName, inDataPath,outDataPath;
/*
  DmpCalManager* RdcMan = DmpCalManager::GetInstance();
  if ( !RdcMan->GetPsd()->SetConnector()) return 0;
  if ( !RdcMan->GetStk()->SetConnector()) return 0;
  if ( !RdcMan->GetBgo()->SetConnector()) return 0;
  if ( !RdcMan->GetNud()->SetConnector()) return 0;
*/
  for (Short_t i=0;i<4;++i) {
    getline(*BatchInfor,note);    // reserved 4 lines for note
  }
  getline(*BatchInfor,inDataPath);
  RdcMan->SetInDataPath(inDataPath);
  getline(*BatchInfor,note);      // reserved 1 line for note
  getline(*BatchInfor,outDataPath);
  RdcMan->SetOutDataPath(outDataPath);
  getline(*BatchInfor,note);     // reserved 1 line for note
  *BatchInfor>>dataName;         // get the first dataName

  while (dataName != "END") {
    RdcMan->SetDataName(dataName);
    ifstream* InData = new ifstream((TString)inDataPath+(TString)dataName,ios::in|ios::binary);
    if (!InData->good()) {
      cout<<"\n\t---->Warning: open "<<inDataPath+dataName<<" failed"<<endl;
      *BatchInfor>>dataName;
      continue;
    } else {
      cout<<"\n\t---->Reading "<<inDataPath+dataName<<endl;
    }

    TTree* tree = RdcMan->BookTree("rec-0");
    if ( ! RdcMan->BookBranch(tree) ) {
      *BatchInfor>>dataName;
      continue;
    }

    RdcMan->GetHeader()->Initialize();

    //loop of event package. set the order of suv-detector as the order of FEE in InData
    for (Long64_t nEvt=0;!InData->eof();++nEvt) {
//Long64_t EvtID = RdcMan->GetHeader()->GetPackageID();
//if (EvtID == 20) break;

/*
      if (! RdcMan->GetHeader()->Conversion(InData)) {
        continue;
      }
      if (! RdcMan->GetNud()->Conversion(InData)) {
        continue;
      }
      if (! RdcMan->GetPsd()->Conversion(InData)) {
        continue;
      }
      if (! RdcMan->GetStk()->Conversion(InData)) {
        continue;
      }
*/
      if (! RdcMan->GetBgo()->Conversion(InData)) {
        continue;
      }

      RdcMan->FillAnEvent();
    }

    RdcMan->SaveRootFile();
    InData->close();
    *BatchInfor>>dataName;
  }
  BatchInfor->close();
  RdcMan->Clear();
  cout<<"\n\t---->End of Raw Data Conversion"<<endl;

}


