/*=====================================================================
 *   File:   DmpPedMain.cc
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  26/12/2013   18:52:11
=====================================================================*/

#include <iostream>

#include "DmpBgoPedManager.hh"

using namespace std;

//------------------------------------------------------------------------------
void Usage();

//------------------------------------------------------------------------------
int main(int argc, char* argv[]){

  TString inFileName;
  if (argc == 2) {
    inFileName = argv[1];
    if ( ! inFileName.Contains("_raw.root") ) {
      Usage();
      return 1;
    }
  } else {
    Usage();
    return 1;
  }

  DmpBgoPedManager* PedMan = DmpBgoPedManager::GetInstance();

  string note = inFileName;
  unsigned found = note.find_last_of("/\\");
  PedMan->SetInDataPath((TString)note.substr(0,found));
  PedMan->SetDataName((TString)note.substr(found+1));
  PedMan->Core();

  DmpBgoPedManager::Clear();
  return 0;

}

//------------------------------------------------------------------------------
void Usage(){
  cerr<<"Usage:"<<endl;
  cerr<<"\t./dmpBgoPed  XXXX_raw.root\t\t single mode, just convert one data, and save the result and ./"<<endl;
}


