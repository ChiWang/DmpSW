/*=============================================================================
#       FileName :          DmpCalL0Bgo.cc
#       Version  :          0.0.1
#       Author   :          USTC    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-18   15:07:46
#
#------------------------------------------------------------------------------
#       Description  :
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-23   01:10:46
=============================================================================*/

#include <iostream>
#include <fstream>

#include "TFile.h"
#include "TH1F.h"
#include "TPostScript.h"        // save as *.eps
#include "TFitResult.h"

#include "DmpCalL0Manager.hh"
#include "DmpDcdParameterBgo.hh"
#include "DmpEvtBgo.hh"     // include DmpDcdRunMode.hh

using namespace DmpDcdParameter::Bgo;

void DmpCalL0Manager::BookHistBgo(){
  Int_t n=0;
  for (Short_t p=0;p<kPlaneNb;++p) {
    for (Short_t q=0;q<kSideNb*2;++q) {
      for (Short_t b=0;b<kBarNb+kRefBarNb;++b) {
        for (Short_t d=0;d<kDyNb;++d) {
          TString histName = GetHistNameBgo(p,q,b,d);
          fMHistBgo.insert(std::make_pair(histName,new TH1F(histName,histName+";ADC;count",500,-200,1300)));
//std::cout<<fMHistBgo.at(histName)->GetName()<<std::endl;
          ++n;
        }
      }
    }
  }
}

/*
TH1F* DmpCalL0Manager::GetHist(Short_t p,Short_t q,Short_t b,Short_t dy){
  return hist;
}
*/

TString DmpCalL0Manager::GetHistNameBgo(Short_t p,Short_t q,Short_t b ,Short_t dy){
  char name[20];
  sprintf (name,"Bgo-P%d_Q%d_B%d_D%d",p,q,b,dy);
  return (TString)name;
}

void DmpCalL0Manager::FillPedestalBgo(){
  std::vector<int>  *planeID    = fEvtBgo->GetEvent("PlaneID");
  std::vector<int>  *quadrantID = fEvtBgo->GetEvent("QuadrantID");
  std::vector<int>  *barID      = fEvtBgo->GetEvent("BarID");
  std::vector<int>  *dyID       = fEvtBgo->GetEvent("DyID");
  std::vector<double>   *adc    = fEvtBgo->GetEventADC();
/*
  UpdateHitOrder();
*/

  Int_t nHit = fEvtBgo->GetHitNumber();
  for (Int_t n=0;n<nHit;++n) {
    TString histName = GetHistNameBgo(planeID->at(n),quadrantID->at(n),barID->at(n),dyID->at(n));
std::cout<<"2222XXX"<<std::endl;
    //(fMHistBgo.at(histName))->Fill(adc->at(n));
std::cout<<"3333XXX"<<std::endl;
  }
}

void DmpCalL0Manager::UpdateHitOrder(){
  // fHitOrder;
}

void DmpCalL0Manager::SavePedestalBgo(){
  fInRootFile->Close();
  TString dataName = fDataName;
  dataName.ReplaceAll("-rec0.root","-Bgo-ped");
  fOutRootFile = new TFile(fOutDataPath+dataName+".root","RECREATE");
  ofstream outPed(fOutDataPath+dataName+".dat");
  outPed<<"#Format:\tPlane, Quadrant, Bar, Dy: mean, sigma"<<std::endl;

  for (std::map<TString, TH1F*>::iterator i=fMHistBgo.begin();i!=fMHistBgo.end();++i) {
    TH1F    *hist = i->second;
    // reset range, rebin
    Int_t min=0, max=0;
    Int_t nBins = hist->GetXaxis()->GetNbins();
    for (Int_t n=0;n<nBins;++n) {
      if ( hist->GetBinContent(n)>0 ) {
        min = n;
        break;
      }
    }
    for (Int_t n=nBins;n>0;--n) {
      if ( hist->GetBinContent(n)>0 ) {
        max = n;
        if((max+5)>nBins) max = nBins;
        break;
      }
    }
    hist->GetXaxis()->SetRange(min,max);                  // use new range
    while (hist->GetBinContent(hist->GetMaximumBin()) < hist->Integral()/15) {
      hist->Rebin();
    }
    // Fit and check results
    TFitResultPtr r = hist->Fit("gaus","LSQ");       // L: likelihood, Q: quiet mode, S: return fit results to TFitResultPtr
    if (r->Chi2() > 0 ) {
        std::cout<<"Warning:\t"<<hist->GetName()<<"\t\tChi2 = "<<r->Chi2()<<std::endl;
    }
    outPed<<r->Parameter(0)<<" "<<r->Parameter(1)<<"  ";
    

    hist->Write();
    hist->Reset();
  }
  outPed.close();
  ResetRootFile();
}

