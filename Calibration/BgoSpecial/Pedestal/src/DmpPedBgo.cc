/*=====================================================================
 *   File:   DmpPedBgo.cc
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    26/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  26/12/2013   17:24:00
=====================================================================*/

#include <iostream>
#include <fstream>

#include "TFile.h"
#include "RooGlobalFunc.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "TPostScript.h"

#include "DmpPedManager.hh"
#include "DmpParameterBgo.hh"
#include "DmpEvtBgoRaw.hh"

using namespace DmpParameter::Bgo;

void DmpPedManager::ConstructorBgo(){
  static Short_t  p=0, q=0, b=0, d=0;

  static TString name ="";
  fADC = new RooRealVar**** [kPlaneNb];
  fMapBgo = new std::map<TString, RooDataSet*>;
  for (p=0;p<kPlaneNb;++p) {            //    BookMapBgo
    fADC[p] = new RooRealVar*** [kSideNb*2];
    for (q=0;q<kSideNb*2;++q) {
      fADC[p][q] = new RooRealVar** [kBarNb+kRefBarNb];
      for (b=0;b<kBarNb+kRefBarNb;++b) {
        fADC[p][q][b] = new RooRealVar* [kDyNb];
        name = GetMapNameBgo(p,q,b);
        fADC[p][q][b][0] = new RooRealVar(name+"-dy2","dy2",-100,1100);
        fADC[p][q][b][1] = new RooRealVar(name+"-dy5","dy5",-100,1100);
        fADC[p][q][b][2] = new RooRealVar(name+"-dy8","dy8",-100,1100);
        fMapBgo->insert(std::make_pair(name,new RooDataSet(name,name,RooArgSet(*fADC[p][q][b][0],*fADC[p][q][b][1],*fADC[p][q][b][2]))));
      }
    }
  }
}

void DmpPedManager::DestructorBgo(){
  delete fEvtBgo;

  static Short_t  p=0, q=0, b=0, d=0;
  for(p=0;p<kPlaneNb;++p){
    for(q=0;q<kSideNb*2;++q){
      for(d=0;d<kDyNb;++d){
        delete[] fHitOrder[p][q][d];
      }
      delete[] fHitOrder[p][q];
    }
    delete[] fHitOrder[p];
  }
  delete[] fHitOrder;

  for(p=0;p<kPlaneNb;++p){
    for(q=0;q<kSideNb*2;++q){
      for(b=0;b<kBarNb+kRefBarNb;++b){
        for(d=0;d<kDyNb;++d){
          delete fADC[p][q][b][d];
        }
        delete[] fADC[p][q][b];
      }
      delete[] fADC[p][q];
    }
    delete[] fADC[p];
  }
  delete[] fADC;

  std::cout<<"\n\tdeleteing map of data set of Bgo"<<std::endl;
  for (std::map<TString,RooDataSet*>::iterator i=fMapBgo->begin();i!=fMapBgo->end();++i) {
    delete i->second;
  }
  delete fMapBgo;
}


TString DmpPedManager::GetMapNameBgo(Short_t p,Short_t q,Short_t b){
  char name[20];
  sprintf (name,"Bgo-P%d_Q%d_B%d",p,q,b);
  return (TString)name;
}

void DmpPedManager::FindPedetsalEeventBgo(){
  static std::vector<int>  *planeID    = fEvtBgo->GetEvent("PlaneID");
  static std::vector<int>  *quadrantID = fEvtBgo->GetEvent("QuadrantID");
  static std::vector<int>  *barID      = fEvtBgo->GetEvent("BarID");
  static std::vector<int>  *dyID       = fEvtBgo->GetEvent("DyID");
  static std::vector<double>   *adc    = fEvtBgo->GetEventADC();
/*
  UpdateHitOrder();
*/

  static Int_t nHit = 0;
  static Short_t n=0, p = 0, q = 0,b = 0;
  nHit = fEvtBgo->GetHitNumber();
std::cout<<"xxx"<<std::endl;
  for (n=0;n<nHit;++n) {
std::cout<<"xxxxxx = "<<dyID->at(n)<<"\t"<<dyID->at(n)/3<<std::endl;
    *(fADC[planeID->at(n)][quadrantID->at(n)][barID->at(n)][dyID->at(n)/3]) = adc->at(n);
  }
std::cout<<"xxx"<<std::endl;

  static TString name ="";
  for (p=0;p<kPlaneNb;++p) {            //    BookMapBgo
    for (q=0;q<kSideNb*2;++q) {
      for (b=0;b<kBarNb+kRefBarNb;++b) {
        name = GetMapNameBgo(p,q,b);
        (*fMapBgo)[name]->add(RooArgSet((*fADC[p][q][b][0]),(*fADC[p][q][b][1]),(*fADC[p][q][b][2])));
      }
    }
  }
}

void DmpPedManager::UpdateHitOrder(){
  // fHitOrder;
}

void DmpPedManager::SavePedestalBgo(){
  fInRootFile->Close();
  TString dataName = fDataName;
  dataName.ReplaceAll("-rec0.root","-Bgo-ped");
  fOutRootFile = new TFile(fOutDataPath+dataName+".root","RECREATE");
  ofstream outPed(fOutDataPath+dataName+".dat");
  outPed<<"#Format:\tPlane, Quadrant, Bar, Dy: mean, sigma"<<std::endl;

  outPed.close();
  ResetRootFile();
}

