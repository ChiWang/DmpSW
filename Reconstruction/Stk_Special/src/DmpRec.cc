// $Id: DmpRec.cc,v 1.00 2013-09-05 16:00:00 xin Exp $
//
// 
// ------------------------------------------------------------
//      DAMPE reconstruction main program
//      DPNC U. Geneva Switzerland
//
//
//      ------------ DmpRec main program ------
//           by X.Wu, (5 September 2013)
//  09.09.05 X.Wu: DAMPE reconstruction executable  
//                     
// ************************************************************
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"

#include "EventProcessor.h"

int main(int argc, char **argv)
{
  bool isMC   = true;
  int dumpEvt = -100;

// split by ','
  int nEvtToProcess = -1;
  int iEvtStart = 0;
  if(argc>2) nEvtToProcess = atoi(argv[2]);
  if(argc>3) iEvtStart = atoi(argv[3]);

  std::string argStr = argv[1];
  std::vector<std::string> fileList;
  for (size_t i=0,n; i <= argStr.length(); i=n+1)
    {
      n = argStr.find_first_of(',',i);
      if (n == std::string::npos)
        n = argStr.length();
      std::string tmp = argStr.substr(i,n-i);
      fileList.push_back(tmp);
    }

  // open input files
  TChain fChain("dampe");
  for (unsigned int iFile=0; iFile<fileList.size(); ++iFile)
    {
      std::cout << "open " << fileList[iFile].c_str() << std::endl;
      fChain.Add(fileList[iFile].c_str());
    }
  std::string filename = fileList[0].c_str();
  unsigned pos1 = filename.find("DmpSimu_");
  std::string name = filename.substr (pos1+8);
  unsigned pos2 = name.find("_");
  std::string particleName = name.substr (0,pos2);
  
  std::cout << "input file name indicates type : " << particleName << std::endl;
  std::cout << "number of event to process (-1=all): " << nEvtToProcess << std::endl;
  std::cout << "       starting from event: " << iEvtStart << std::endl;


  // open output histogram
   TFile *hFile = 0;
   std::string outfile = "hist_"+name;
   std::cout << "output histogram file name is " <<  outfile << std::endl;
   hFile = new TFile(outfile.c_str(), "RECREATE");
   
   EventProcessor* m_eventProcessor = new EventProcessor;
   if(particleName=="Photon")        m_eventProcessor->setParticleType(EventProcessor::kPhoton);
   else if(particleName=="Electron") m_eventProcessor->setParticleType(EventProcessor::kElectron);
   else if(particleName=="Proton")   m_eventProcessor->setParticleType(EventProcessor::kProton);
   else                              m_eventProcessor->setParticleType(EventProcessor::kUnkown);
   EventProcessor::flag_isMC	   = isMC;
   EventProcessor::flag_dumpEvt    = dumpEvt; 

   m_eventProcessor->init(hFile);
   fChain.Process(m_eventProcessor,"",nEvtToProcess, iEvtStart);

   m_eventProcessor->finalize(); //close histogram file
   
}
