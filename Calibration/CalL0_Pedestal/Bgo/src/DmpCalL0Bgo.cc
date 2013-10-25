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
#include "RooGlobalFunc.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
//#include "TH1F.h"
#include "TPostScript.h"        // save as *.eps
//#include "TFitResult.h"

#include "DmpCalL0Manager.hh"
#include "DmpDcdParameterBgo.hh"
#include "DmpEvtBgo.hh"         // include DmpDcdRunMode.hh

using namespace DmpDcdParameter::Bgo;

void DmpCalL0Manager::ConstructorBgo(){
  fEvtBgo   = new DmpEvtBgoRaw((DmpEvtVHeader*)fEvtHeader);
  fDy2 = new RooRealVar("dy2","dy2",-100,1100);
  fDy5 = new RooRealVar("dy5","dy5",-100,1100);
  fDy8 = new RooRealVar("dy8","dy8",-100,1100);
  BookMapBgo();             // must after fDyX

  fHitOrder = new Short_t*** [kPlaneNb];        // create 4 dimenstion array
  for(Short_t p=0;p<kPlaneNb;++p){
    fHitOrder[p] = new Short_t** [kSideNb*2];
    for(Short_t q=0;q<kSideNb*2;++q){
      fHitOrder[p][q] = new Short_t* [kDyNb];
      for(Short_t d=0;d<kDyNb;++d){
        fHitOrder[p][q][d] = new Short_t [kBarNb+kRefBarNb];
      }
    }
  }
}

void DmpCalL0Manager::DestructorBgo(){
  delete fEvtBgo;
  for (std::map<TString,RooDataSet*>::iterator i=fMapBgo->begin();i!=fMapBgo->end();++i) {
    std::cout<<"deleteing "<<(i->second)->GetName()<<std::endl;
    delete i->second;
  }
  delete fDy2;
  delete fDy5;
  delete fDy8;
  for(Short_t p=0;p<kPlaneNb;++p){
    for(Short_t q=0;q<kSideNb*2;++q){
      for(Short_t d=0;d<kDyNb;++d){
        delete[] fHitOrder[p][q][d];
      }
      delete[] fHitOrder[p][q];
    }
    delete[] fHitOrder[p];
  }
  delete[] fHitOrder;
}

void DmpCalL0Manager::BookMapBgo(){
  for (Short_t p=0;p<kPlaneNb;++p) {
    for (Short_t q=0;q<kSideNb*2;++q) {
      for (Short_t b=0;b<kBarNb+kRefBarNb;++b) {
        TString name = GetMapNameBgo(p,q,b);
        RooDataSet  *dataSet = new RooDataSet(name,name,RooArgSet(*fDy2,*fDy5,*fDy8));
std::cout<<"XXX->   "<<dataSet<<"\t "<<&b<<std::endl;
        //fMapBgo->insert(std::make_pair<TString,RooDataSet*>(name,dataSet));
        fMapBgo->insert(std::make_pair(name,dataSet));
        //(*fMapBgo)[name] = dataSet;
std::cout<<"1111XXX"<<std::endl;
      }
    }
  }
}

TString DmpCalL0Manager::GetMapNameBgo(Short_t p,Short_t q,Short_t b){
  char name[20];
  sprintf (name,"Bgo-P%d_Q%d_B%d",p,q,b);
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

  Int_t nHit = fEvtBgo->GetHitNumber();
  for (Int_t n=0;n<nHit;++n) {
    TString name = GetMapNameBgo(planeID->at(n),quadrantID->at(n),barID->at(n));
  }
*/
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

/*
  for (std::map<TString, TH1F*>::iterator i=fMapBgo->begin();i!=fMapBgo->end();++i) {
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
*/
  outPed.close();
  ResetRootFile();
}

