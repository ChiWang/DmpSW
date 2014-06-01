/*
 *  $Id: DataCheckMain.cc, 2014-05-10 21:29:47 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 10/05/2014
*/

#include <iostream>
#include <algorithm>

#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TCanvas.h"
#include "TH2F.h"

//#include "DmpEvtMCPrimaryParticle.h"
//#include "DmpEvtMCStkMSD.h"
//#include "DmpEvtMCPsdMSD.h"
//#include "DmpEvtMCBgoMSD.h"
#include "DmpEvtMCNudMSD.h"

int main(int argc, char* argv[]){
  std::cout<<"==> Reading file "<<argv[1]<<std::endl;
  if(argc == 3){
    std::cout<<"event max = "<<argv[2]<<std::endl;
  }

  TFile *aFile = new TFile(argv[1]);
  TTree *aTree = dynamic_cast<TTree*>(aFile->Get("DAMPE_MCTruth"));
  TClonesArray *nud_Set = new TClonesArray("DmpEvtMCNudMSD",5);
  DmpEvtMCNudMSD  *aMSD = 0;
  aTree->SetBranchAddress("Nud",&nud_Set);
  short timeGap = DmpEvtMCNudMSD::GetDeltaTime();
  long N = aTree->GetEntries();
  for(long i=0;i<N;++i){
    aTree->GetEntry(i);
    short nBlocks = nud_Set->GetEntriesFast();
    std::cout<<"\n\nEvent ID = "<<i<<"(nBlocks "<<nBlocks<<")"<<std::endl;
    for(short id = 0;id<nBlocks;++id){
      aMSD = (DmpEvtMCNudMSD*)nud_Set->At(id);
      double startT = aMSD->GetStartTime();
      double stopT = aMSD->GetStopTime();
      std::cout<<"\nblock ID = "<<aMSD->GetSDID()<<"\ttime("<<startT<<" ~ "<<stopT<<")"<<std::endl;
      std::vector<double> eVec = aMSD->GetEnergy();
      double minE = *std::min_element(eVec.begin(),eVec.end());
      double maxE = *std::max_element(eVec.begin(),eVec.end());
      char name[100];
      int eSize = eVec.size();
      snprintf(name,100,"Event-%d_Block-%d",i,id);
      TH2F *aHist = new TH2F(name,name,eSize+2,startT-timeGap,stopT+timeGap,(maxE-minE)+1,minE,maxE); 
      for(int index=0;index<eSize;++index){
        aHist->Fill(startT+timeGap*index,eVec[index]);
        std::cout<<" e "<<eVec[index];
      }
      std::cout<<std::endl;
    }
  }
  return 0;
}


