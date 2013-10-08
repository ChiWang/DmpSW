// Description: This class implements the cluster finding 
// algorithm of the Silicon-Tungsten Tracker (STK) of DAMPE
//
// Author(s):
//  - creation by X.Wu, 07/09/2013

#include "StkClusterFinder.h"

#include <map>
#include "TMath.h"
#include <iostream>
#include "SiCluster.h"
#include "StkParamDef.h"

#include "EventProcessor.h"

void StkClusterFinder::init() {
  if (EventProcessor::flag_dumpEvt == -100) std::cout << "In StkClusterFinder::init() " << std::endl;
  m_siClusters_pass1.clear();
  m_siClusters_pass2.clear();
  m_siClusters_layer_pass1.clear();
  m_siClusters_layer_pass2.clear();

  //std::cout << "StkClusterFinder::init called ... " << std::endl;
  m_hNDigitTot  = new TH1F("hNDigitTot","number of digits per event",500,0,500);  
  m_hNDigit3sig = new TH1F("hNDigit3sig","number of digits (3sigma) per event",1000,0,1000);
  m_hNDigit3sigL= new TH1F("hNDigit3sigL","number of digits (3sigma) per event",1000,0,2000);
  m_hSiDigit002 = new TH1F("hSiDigit002","max digit TRB",1000,0,1000);
  m_hSiDigit003 = new TH1F("hSiDigit003","adc",385,0,385);
  m_hSiDigit004 = new TH1F("hSiDigit004","ladder",193,0,193);
  m_hSiDigit005 = new TH1F("hSiDigit005","layer",12,0,12);
  m_hSiDigit006 = new TH1F("hSiDigit006","strip",384,0,1536);
  m_hSiDigit007 = new TH1F("hSiDigit007","trb",8,0,8);
  m_hSiDigit008 = new TH1F("hSiDigit008","block",48,0,48);
  
  m_hSiClus002 = new TH1F("hSiClus002","number of clusters per ladder",100,0,100);
  m_hSiClus003 = new TH1F("hSiClus003","number of clusters per ladder, max>0.02 MeV",100,0,100);

  m_hSiClus005 = new TH1F("hSiClus005","layer",12,0,12);
  m_hSiClus007 = new TH1F("hSiClus007","trb",8,0,8);
  m_hSiClus008 = new TH1F("hSiClus008","Maximum number of clusters per TRB",1000,0,1000);

  m_hSiClus105 = new TH1F("hSiClus105","layer",12,0,12);
  m_hSiClus107 = new TH1F("hSiClus107","trb",8,0,8);
  m_hSiClus108 = new TH1F("hSiClus108","Maximum number of clusters per TRB",1000,0,1000);

  m_hSiClus000 = new TH1F("hSiClus000","number of pass 1 clusters per event",1000,0,1000);
  m_hSiClus300 = new TH1F("hSiClus300","number of pass 2 clusters per event",1000,0,1000);

  m_hSiClusX = new TH2F("hSiClusX","x vs z",1500,70,145, 1300,-35,-9);
  m_hSiClusY = new TH2F("hSiClusY","y vs z",1500,70,145, 1800,90,126);

  int n;
  char hTitle[20];
  
  m_hNCluLayer = new TObjArray(12);
  m_hNClu1Layer= new TObjArray(12);
  for(int m=0; m<12; ++m) { 
    n=sprintf(hTitle,"hNCluSLayer_%02d",m);
    (*m_hNCluLayer)[m] = new TH1F(hTitle,"Number of clusters per layer",50,0,50);
  }

  for(int m=0; m<12; ++m) { 
    n=sprintf(hTitle,"hNClu1Layer_%02d",m);
    (*m_hNClu1Layer)[m] = new TH1F(hTitle,"Number of clusters per layer, max>0.02 MeV",50,0,50);
  }
  
  m_hCluDelX   = new TObjArray(12);
  m_hCluMinDelX= new TObjArray(12);
  for(int m=0; m<12; ++m) { 
    n=sprintf(hTitle,"hCluDelX_%02d",m);
    (*m_hCluDelX)[m]    = new TH1F(hTitle,"delX of cluster of layer",400,-500,500);
  }
  for(int m=0; m<12; ++m) { 
    n=sprintf(hTitle,"hCluMinDelX_%02d",m);
    (*m_hCluMinDelX)[m] = new TH1F(hTitle,"minimum delX of cluster of layer",400,-500,500);
  }

  m_nsigmaWidth  = 9.0;  //road width for finding nearest cluster

  m_3sigma     = 0.008; //9.2% of MPV
  //m_3sigma     = 0.011; //3056e, 3.2sigma 
  m_seedThr    = 0.02;  //cluster seed threshold
  m_seedThrSub = 0.04; //sub cluster seed threshold

   m_ladder0Center[0][0] = (StkParamDef::blockCenterLeft -StkParamDef::BlockSizeXY/2.) + StkParamDef::SiliconGuardRing + StkParamDef::activeTileSize/2;
   m_ladder0Center[1][0] = (StkParamDef::blockCenterRight-StkParamDef::BlockSizeXY/2.) + StkParamDef::SiliconGuardRing + StkParamDef::activeTileSize/2.;
   m_ladder0Center[2][0] = m_ladder0Center[0][0];
   m_ladder0Center[3][0] = m_ladder0Center[1][0];
   //std::cout << " Y ladder 0 center at " << m_ladder0Center[0][0]  << " " << m_ladder0Center[1][0]  
   //     << " " <<  m_ladder0Center[2][0]  << " " <<  m_ladder0Center[3][0]  << std::endl;
   m_ladder0Center[0][1] = (StkParamDef::blockCenterLeft -StkParamDef::BlockSizeXY/2.) + StkParamDef::SiliconGuardRing + StkParamDef::activeTileSize/2;
   m_ladder0Center[1][1] = m_ladder0Center[0][1];
   m_ladder0Center[2][1] = (StkParamDef::blockCenterRight-StkParamDef::BlockSizeXY/2.) + StkParamDef::SiliconGuardRing + StkParamDef::activeTileSize/2.;
   m_ladder0Center[3][1] = m_ladder0Center[2][1];
   //std::cout << " X ladder 0 center at " << m_ladder0Center[0][1]  << " " << m_ladder0Center[1][1]  
   //	     << " " <<  m_ladder0Center[2][1]  << " " <<  m_ladder0Center[3][1]  << std::endl;   
   // Y ladder 0 center at -332.78 47.54 -332.78 47.54
   // X ladder 0 center at -332.78 -332.78 47.54 47.54
   // ladder distance: 95.08

   m_ladderDistance = 2*StkParamDef::SiliconGuardRing + StkParamDef::TilesSeparation + StkParamDef::activeTileSize;
   //std::cout << " ladder distance: " << m_ladderDistance << std::endl;

   m_totalMaxTRB = 0;
   m_nMaxTRB = 0;

   m_totalMaxClusPass1TRB = 0;
   m_nMaxClusPass1TRB = 0;
   m_totalMaxClusPass2TRB = 0;
   m_nMaxClusPass2TRB = 0;

   m_nDigitTot = -1;
  return;
}

void StkClusterFinder::findCluster(std::vector<int>* SiDigit_strip,  std::vector<double>* SiDigit_e, std::vector<unsigned int> * SiDigit_trackID) {

  //clear the cluster list
  m_siClusters_pass1.clear();
  m_siClusters_pass2.clear();
  m_siClusters_layer_pass1.clear();
  m_siClusters_layer_pass2.clear();

  int SiDigit_n = SiDigit_strip->size();
  m_hNDigitTot->Fill(SiDigit_n);

  std::vector<int>    vecint;
  std::vector<double> vecdouble;

  std::vector<std::vector<int> > digimap_layer;
  for(int i= 0; i<12; i++) {
    digimap_layer.push_back(vecint);
    m_layerEnergy[i]        = 0.;
    m_layerEnergyCluster[i] = 0.;
    m_nDigiLayer[i]         = 0;
  }

  for(int i= 0; i<6; i++) {
    m_nDigiPlane[i]         = 0;
  }

  std::vector<std::vector<int> > digimap_ladder;
  std::vector<std::vector<int> > stripmap_ladder;
  for(int i= 0; i<192; i++) {
    digimap_ladder.push_back(vecint);
    stripmap_ladder.push_back(vecint);
  }

  int nDigitBlock[48];
  int nClusBlock[48];
  for(int i= 0; i<48; i++) { 
    nDigitBlock[i]=0; 
    nClusBlock[i]=0;
  }
  
  int nDigitTRB[8];
  int nClusPass1TRB[8];
  int nClusPass2TRB[8];
  for(int i= 0; i<8; i++) { 
    nDigitTRB[i]=0; 
    nClusPass1TRB[i]=0;
    nClusPass2TRB[i]=0;
  }

  //setup the Digit index map per ladder 
  int ndigit_3sigma = 0;
  for(int i= 0; i<SiDigit_n; i++) {
    if( (*SiDigit_e)[i] < m_3sigma) continue; 
    ++ndigit_3sigma;
    int isX = (*SiDigit_strip)[i]/1000000;
    if(isX != 1 && isX != 0) std::cout << " unknown plane type ??? " << isX << std::endl;
    int plane = ((*SiDigit_strip)[i] - isX*1000000)/100000; 
    int iplane = plane*2+isX;
    m_layerEnergy[iplane] += (*SiDigit_e)[i];
    ++m_nDigiLayer[iplane];
    ++m_nDigiPlane[plane];

    digimap_layer[iplane].push_back(i);
    //strip number witin a layer (0-6143)
    //StripNumber += BlockNumber*TileTotal*StripTotal;
    //number of strips in a block 1536
    //strip number within a block (0-1535)
    int block = ((*SiDigit_strip)[i] - isX*1000000 - plane*100000)/1536;
    int strip =  (*SiDigit_strip)[i] - isX*1000000 - plane*100000 - block*1536;
    //int strip_large = (*tt_SiDigit_strip)[i] - isX*1000000 - plane*100000;
    int iblock = iplane*4+block;
    int ladder = strip/384 + block*4 + iplane*16;
    //std::cout << (*SiDigit_strip)[i] << " " << isX << " " << plane << " " << block << " " << ladder << " " << strip_large << std::endl;
    digimap_ladder[ladder].push_back(i);
    int nl = strip/384;
    int stripLadder = strip- nl*384;
    stripmap_ladder[ladder].push_back(stripLadder); //0-383
    int adc    = strip/192 + block*8 + iplane*32;
    //TRB    0   1  2  3  4  5  6  7
    //block  0Y 0X 1Y 1X 2Y 2X 3Y 3X
    int trb = block*2+isX;
    ++nDigitBlock[iblock];
    ++nDigitTRB[trb];
    m_hSiDigit003->Fill(adc);
    m_hSiDigit004->Fill(ladder);
    m_hSiDigit005->Fill(iplane);
    m_hSiDigit006->Fill(strip);
    m_hSiDigit007->Fill(trb);
    m_hSiDigit008->Fill(iblock);
    
  }
  m_nDigitTot = ndigit_3sigma;

  m_hNDigit3sig ->Fill(ndigit_3sigma);
  m_hNDigit3sigL->Fill(ndigit_3sigma);
  bool dmpEvt = false;
  //bool dmpEvt = true;
  if(dmpEvt) { 
    std::cout << " --- Number of digits above 3sigma = " << ndigit_3sigma  << std::endl;
    for(int i= 0; i<12; i++) {
      std::cout << "  layer energy in layer " << i << " = " <<  m_layerEnergy[i] << std::endl;
    }
  }

  int maxTRB = 0;
  for(int j= 0; j<8; j++) {
    if(nDigitTRB[j]>maxTRB) maxTRB = nDigitTRB[j];
  }
  m_hSiDigit002->Fill(maxTRB);
  m_totalMaxTRB += maxTRB;
  ++m_nMaxTRB;

  //first pass cluster finding
  //std::vector<SiCluster>  siClusters_pass1; 

  int nClusEvt = 0;
  int nClus1Evt = 0;
  int maxLadder = 0;
  int nLadderHit = 0;
  int nMaxCluLadder  = 0;
  int nMaxClu1Ladder = 0;
  for(int j= 0; j<192; j++) {
    int iplane = j/16;
    //((TH1F*) hNdigitLadder[j]) -> Fill(nDigitLadder[j]);
    int ndigit = digimap_ladder[j].size();
    if(ndigit>maxLadder) maxLadder = ndigit;
    if(ndigit>0) ++nLadderHit;
    std::vector<int> index1;
    std::vector<int> index2;
    std::vector<int> indexM;
    std::vector<int> clusize;
    int cluSize = 0;
    int ifirst  = -1;
    int ilast   = -1;
    int indFirst  = -1;
    int indLast   = -1;
    int indMax    = -1;
    float cluMax  = 0;
    int ncluster  = 0;
    int ncluster1 = 0;
    for(unsigned int i= 0; i<digimap_ladder[j].size(); i++) {
      bool newCluster = false;
      int strip = stripmap_ladder[j][i];
      int digit = digimap_ladder[j][i];
      if(ifirst == -1) {
	ifirst = strip;
	ilast = ifirst;
	indFirst = i;
	indLast  = indFirst;
	cluSize = 1;
	cluMax = (*SiDigit_e)[digit];
	indMax = i;
      }
      else if( strip == ilast+1)  {
	ilast = strip;
	indLast  = i;
	if((*SiDigit_e)[digit]>cluMax) {
	  cluMax = (*SiDigit_e)[digit];
	  indMax = i;
	}
	++cluSize;
      }
      else {// new cluster
	newCluster = true;
      }
      if(i==digimap_ladder[j].size()-1 || newCluster) {
	//cout << "strip " << ifirst << "  " << ilast << " cluster size "<< cluSize << " max E " << cluMax <<endl;
	//cout << "ind " << indFirst << "  " << indLast <<endl;
	//((TH1F*) hCluSizeLayer[iplane]) -> Fill(cluSize);
	//((TH1F*) hCluMaxELayer[iplane]) -> Fill(cluMax);
	++ncluster;
	//hSiClus006->Fill(cluSize);
	if(cluMax>m_seedThr) { //cluster seed threshold, 0.02 MeV
	  //hSiClus007->Fill(cluSize);
	  ++ncluster1;
	  index1.push_back(indFirst);
	  index2.push_back(indLast);
	  indexM.push_back(indMax);
	  clusize.push_back(cluSize);
	  //cout << cluMax << " " <<  (*tt_SiDigit_e)[digimap_ladder[j][indMax]] << endl;
	  //if(fabs(cluMax-(*tt_SiDigit_e)[digimap_ladder[j][indMax]])>0.001) cout << " max problem! " << endl;
	}
      }
      if(newCluster) {
	ifirst =  strip;
	ilast = ifirst;
	indFirst = i;
	indLast  = indFirst;
	cluSize = 1; 
	cluMax = (*SiDigit_e)[digit];
	indMax = i;
	if(i==digimap_ladder[j].size()-1) {
	  //cout << "strip " << ifirst << "  " << ilast << " cluster size "<< cluSize << " max E " << cluMax <<endl;
	  //cout << "ind " << indFirst << "  " << indLast <<endl;
	  //((TH1F*) hCluSizeLayer[iplane]) -> Fill(cluSize);
	  //((TH1F*) hCluMaxELayer[iplane]) -> Fill(cluMax);
	  ++ncluster;
	  //hSiClus006->Fill(cluSize);
	  if(cluMax>m_seedThr) { //cluster seed threshold, 0.02 MeV
	    //hSiClus007->Fill(cluSize);
	    ++ncluster1;
	    index1.push_back(indFirst);
	    index2.push_back(indLast);
	    indexM.push_back(indMax);
	    clusize.push_back(cluSize);
	    //if(fabs(cluMax-(*tt_SiDigit_e)[digimap_ladder[j][indMax]])>0.001) cout << " max problem! " << endl;
	  }
	}
      }
    }
    if(ncluster>nMaxCluLadder)   nMaxCluLadder = ncluster;
    if(ncluster1>nMaxClu1Ladder) nMaxClu1Ladder = ncluster1;
    for(unsigned int i= 0; i<index1.size(); i++) {
      //if(clusize[i] != index2[i]-index1[i]+1) cout << " size problem! " << endl;
      float maxEstrip = (*SiDigit_e)[digimap_ladder[j][indexM[i]]];
      //hSiClus016->Fill(maxEstrip);
      //if(clusize[i]==1) {
	//int   maxStrip  = stripmap_ladder[j][indexM[i]];
	//int     trackId = SiDigit_trackID[digimap_ladder[j][indexM[i]]];
	//hSiClus009->Fill(maxEstrip);
	//hSiClus010->Fill(maxStrip);
	//hSiClus011->Fill(trackId);	   
      //}
      double esum   = 0.;
      double esumw  = 0.;
      double esumw2 = 0.;
      int nseed = 0;
      for(int s=index1[i]; s<index2[i]+1; s++) {
	float estrip = (*SiDigit_e)[digimap_ladder[j][s]];
	int strip = stripmap_ladder[j][s];
	if(estrip>m_seedThrSub) ++nseed;
	//float strip_c = strip + 0.5;
	float strip_c = strip;
	esum   += (*SiDigit_e)[digimap_ladder[j][s]];
	esumw  += (*SiDigit_e)[digimap_ladder[j][s]]*strip_c;
	esumw2 += (*SiDigit_e)[digimap_ladder[j][s]]*strip_c*strip_c;
      }
      double centroid = esumw/esum;
      //convert strip number to absolute coordinates

      double width2 =  esumw2/esum - centroid*centroid;
      if(clusize[i]==1) {
	width2 = 0;
	if(esum !=  (*SiDigit_e)[digimap_ladder[j][indexM[i]]]) std::cout << " energy: " << esum <<" " <<  (*SiDigit_e)[digimap_ladder[j][indexM[i]]] 
								       << " " << index1[i] << " " << index2[i] << " " << indexM[i] << std::endl;
      }
      double width = sqrt(width2);
      /***
      hSiClus012->Fill(esum);	   
      hSiClus013->Fill(width);	   
      hSiClus014->Fill(esum,clusize[i]);	   
      hSiClus015->Fill(width,clusize[i]);	   
      hSiClus017->Fill(nseed);	   
      hSiClus020->Fill(nseed,clusize[i]);	   
      if(nseed==1)  hSiClus018->Fill(esum);
      ***/	   
      //profile	   
      //int cstrip = (index2[i] - index1[i])/2 + index1[i];
      //bool isOdd = clusize[i]%2;
      float max2 = 0;
      int indmax2 = -1;
      int nminima = 0;
      for(int s=index1[i]; s<index2[i]+1; s++) {
	//int pos = s - cstrip;
	//float efrac = (*SiDigit_e)[digimap_ladder[j][s]]/esum;
	//if(isOdd) hSiClus021->Fill(pos,efrac);
	//else hSiClus022->Fill(pos,efrac);
	if(s!=indexM[i]) {
	  if((*SiDigit_e)[digimap_ladder[j][s]]>max2) {
	    max2 = (*SiDigit_e)[digimap_ladder[j][s]];
	    indmax2 = s;
	  }
	}
	if(s!=index1[i] && s!=index2[i]) {
	  if((*SiDigit_e)[digimap_ladder[j][s]]<(*SiDigit_e)[digimap_ladder[j][s-1]] && 
	     (*SiDigit_e)[digimap_ladder[j][s]]<(*SiDigit_e)[digimap_ladder[j][s+1]] ) {
	    ++nminima;
	    //hSiClus030->Fill((*tt_SiDigit_e)[digimap_ladder[j][s]]);
	  }
	}
      }
      /***
      if(clusize[i]>1)  {
	hSiClus019->Fill(esum);
	hSiClus023->Fill(max2);
	int dmax2 = indmax2 - indexM[i];
	hSiClus024->Fill(dmax2);
	if(abs(dmax2>1)) hSiClus031->Fill(max2);
	if(clusize[i]>2) {
	  hSiClus025->Fill(nminima);
	  hSiClus026->Fill(nminima,clusize[i]);
	  if(nminima==0)  hSiClus027->Fill(esum);
	  else  hSiClus028->Fill(esum);
	}
	else  hSiClus029->Fill(esum);
      }
      else hSiClus029->Fill(esum);
      ***/

      //sub-clusters
      bool isbroken = false;
      if(clusize[i]>2 && nseed > 1) {
	/***
	    std::cout << '\n';
	    std::cout << "nseed = "<<nseed<< std::endl;
	    std::cout <<   " energy: ";
	    for(int s=index1[i]; s<index2[i]+1; s++) {
	      std::cout << ' ' << (*SiDigit_e)[digimap_ladder[j][s]];
	    }
	    std::cout << '\n';
	***/
	std::vector<int> sub_index1;
	std::vector<int> sub_index2;
	int sub_ifirst  = -1;
	int sub_seed    = -1;
	int nsub = 0;
	for(int s=index1[i]; s<index2[i]+1; s++) {
	  float estrip = (*SiDigit_e)[digimap_ladder[j][s]];
	  //int strip = stripmap_ladder[j][s];
	  //seed found
	  if(estrip>m_seedThrSub) {
	    if(sub_ifirst == -1) {//first seed
	      sub_ifirst = index1[i];
	      sub_seed = s;
	    }
	    else {//next seed
	      if(s==sub_seed+1) {//consecutive seed
		sub_seed = s;
	      }
	      else {//non-consecutive seed, break at local minima
		float emin = m_seedThrSub;
		int imin = -1;
		for(int k= sub_seed; k<s; k++) {
		  if((*SiDigit_e)[digimap_ladder[j][k]]<emin) {
		    emin = (*SiDigit_e)[digimap_ladder[j][k]];
		    imin = k;
		  }
		}
		if(imin <0) std::cout << " no local mininal??" << std::endl;
		sub_index1.push_back(sub_ifirst);
		sub_index2.push_back(imin);
		//cout << " sub-cluster index " << sub_ifirst << "  " << imin  << " min E " << emin <<endl;
		++nsub;
		sub_ifirst = imin;
		sub_seed = s;
	      }
	    }
	  }
	  if(s==index2[i] && sub_ifirst != index1[i]) {
	    sub_index1.push_back(sub_ifirst);
	    sub_index2.push_back(s);
	    //cout << " last sub-cluster index " << sub_ifirst << "  " << s <<endl;
	    ++nsub;
	  }
	}
	//hSiClus032->Fill(nsub);
	if(nsub>0) {
	  isbroken = true;
	  for(unsigned int m= 0; m<sub_index1.size(); m++) {
	    //sharing strip
	    int share = 0;
	    if(m==0)                        share = 2; //first sub-cluster, last strip shared 
	    else if(m==sub_index1.size()-1) share = 1; //last sub-cluster, first strip shared 
	    else                            share = 3; //middle sub-cluster, first and last strip shared 		
	    
	    int sub_clusize = sub_index2[m]-sub_index1[m]+1;
	    double sub_esum   = 0.;
	    double sub_esumw  = 0.;
	    double sub_esumw2 = 0.;
	    int sub_stripMax  = -1;
	    float sub_cluMax  = 0;
	    for(int s=sub_index1[m]; s<sub_index2[m]+1; s++) {
	      float estrip = (*SiDigit_e)[digimap_ladder[j][s]];
	      if(s==sub_index1[m] && (share==1 || share==3)) estrip = 0.5*estrip; 
	      else if(s==sub_index2[m] && (share==2 || share==3)) estrip = 0.5*estrip; 
	      int strip = stripmap_ladder[j][s];
	      if(estrip>m_seedThrSub) ++nseed;
	      float strip_c = strip;
	      sub_esum   += estrip;
	      sub_esumw  += estrip*strip_c;
	      sub_esumw2 += estrip*strip_c*strip_c;
	      if(estrip>sub_cluMax) {
		sub_cluMax = estrip;
		sub_stripMax = strip;
	      }
	    }
	    double sub_centroid = sub_esumw/sub_esum;
	    double sub_width2 =  sub_esumw2/sub_esum - sub_centroid*sub_centroid;
	    if(sub_clusize==1) {
	      sub_width2 = 0;
	    }
	    double sub_width = sqrt(sub_width2);
	    //hSiClus101->Fill(sub_clusize);
	    //hSiClus102->Fill(sub_esum);	   
	    //hSiClus103->Fill(sub_width);	   
 	    SiCluster* cl = new SiCluster();
	    cl->setLadder(j);
	    cl->setCentroid(sub_centroid);
	    cl->setWidth(sub_width);
	    cl->setEnergy(sub_esum);
	    cl->setNstrip(sub_clusize);
	    cl->setMaxstrip(sub_stripMax);
	    cl->setIndex1(digimap_ladder[j][sub_index1[m]]);
	    cl->setShared(share);
	    cl->setPass(SiCluster::kPass1);
	    cl->setMaxstripEnergy(sub_cluMax);
	    m_siClusters_pass1.push_back(cl);
	  }
	}
      }

      if(!isbroken) {
	//hSiClus111->Fill(clusize[i]);
	//hSiClus112->Fill(esum);	   
	//hSiClus113->Fill(width);	 
	SiCluster* cl = new SiCluster();
	cl->setLadder(j);
	cl->setCentroid(centroid);
	cl->setWidth(width);
	cl->setEnergy(esum);
	cl->setNstrip(clusize[i]);
	cl->setMaxstrip(stripmap_ladder[j][indexM[i]]);
	cl->setIndex1(digimap_ladder[j][index1[i]]);
	cl->setShared(0);
	cl->setPass(SiCluster::kPass1);
	cl->setMaxstripEnergy(maxEstrip);
	m_siClusters_pass1.push_back(cl);
      }
    }

    int iblock  = j/4;
    int block   = iblock - iplane*4;
    int ip      = iplane/2;
    int isX     = iplane - 2*ip;
    //TRB    0   1  2  3  4  5  6  7
    //block  0Y 0X 1Y 1X 2Y 2X 3Y 3X
    int trb = block*2+isX;
    nClusBlock[iblock] +=ncluster1;
    nClusPass1TRB[trb] +=ncluster1;
    nClusEvt  += ncluster;
    nClus1Evt += ncluster1;

    ((TH1F*) (*m_hNCluLayer) [iplane]) -> Fill(ncluster);
    ((TH1F*) (*m_hNClu1Layer)[iplane]) -> Fill(ncluster1);
    m_hSiClus002->Fill(ncluster);
    m_hSiClus003->Fill(ncluster1);
  }

  m_hSiClus000->Fill(nClus1Evt);

  int maxClusPass1TRB = 0;
  for(int j= 0; j<8; j++) {
    if(nClusPass1TRB[j]>maxClusPass1TRB) maxClusPass1TRB = nClusPass1TRB[j];
  }
  m_hSiClus008->Fill(maxClusPass1TRB);
  m_totalMaxClusPass1TRB += maxClusPass1TRB;
  ++m_nMaxClusPass1TRB;

  if(dmpEvt) { 
    std::cout << " --- Number of pass1 cluster = " << m_siClusters_pass1.size()  << std::endl;
    std::cout << " clus  isX   plane    ladder    centroid    localX  nstrp   maxE"  << std::endl;
  }

  //set centroid on local coordinate to pass1 clusters
  for(unsigned int i= 0; i<m_siClusters_pass1.size(); i++) {
    int lad = m_siClusters_pass1[i]->getLadder();
    int plane = lad/16;
    m_layerEnergyCluster[plane] +=  m_siClusters_pass1[i]->getEnergy();
    int isX   = plane%2;
    int block = lad - plane*16;
    block = block/4;
    int ladder= lad - plane*16 - block*4;
    //double localX_onLadder = activeEdge + 0.5*pitch + finalCluster_centroid[i]*ROpitch;
    double localX_onLadder = (StkParamDef::activeEdge) + 0.5*(StkParamDef::pitch) + m_siClusters_pass1[i]->getCentroid()*(StkParamDef::ROpitch);
    double ladderCenter = m_ladder0Center[block][isX] + ladder*m_ladderDistance;
    double localX_onPlane  = localX_onLadder + ladderCenter;
    m_siClusters_pass1[i]->setXcentroid(localX_onPlane);
    if(dmpEvt) { 
      std::cout << "    " << i << "   " << isX << "      " << plane << "          " << lad 
		<< "       " <<  m_siClusters_pass1[i]->getCentroid() << "      " << localX_onPlane 
		<< "       " <<  m_siClusters_pass1[i]->getNstrip()
		<< "       " <<  m_siClusters_pass1[i]->getMaxstripEnergy() << std::endl;
    }
    m_hSiClus005->Fill(plane);
    m_hSiClus007->Fill(m_siClusters_pass1[i]->getTRB());
  }

  //futher split long clusters (Pass2)
  //std::vector<SiCluster>  siClusters_pass2; 
  int nfineCluster = 0;
  for(unsigned int i= 0; i<m_siClusters_pass1.size(); i++) {
    int cluSize = 0;
    int indFirst  = -1;
    int indLast   = -1;
    int indMax    = -1;
    float cluMax  = 0;
    int nsub_cluster  = 0;
    for(int j= 0; j<m_siClusters_pass1[i]->getNstrip(); j++) {
      int k = m_siClusters_pass1[i]->getIndex1()+j;
      bool endCluster = false;
      if(indFirst == -1) {
	indFirst = k;
	indLast  = indFirst;
	cluSize = 1;
	cluMax = (*SiDigit_e)[k];
	indMax = k;
	if(j==m_siClusters_pass1[i]->getNstrip()-1) endCluster = true;
      }
      else {
	indLast  = k;
	if((*SiDigit_e)[k]>cluMax) {
	  cluMax = (*SiDigit_e)[k];
	  indMax = k;
	}
	++cluSize;
	if(j<m_siClusters_pass1[i]->getNstrip()-1) { //not the last strip, find local minima
	  if((*SiDigit_e)[k]<(*SiDigit_e)[k-1] && (*SiDigit_e)[k]<(*SiDigit_e)[k+1]) endCluster = true;
	}
	else {//last strip
	  endCluster = true;
	}
      }
      if(endCluster) {	    
	++nsub_cluster;
	SiCluster* cl = new SiCluster();
	cl->setNstrip(cluSize);
	cl->setMaxstrip(indMax);
	cl->setIndex1(indFirst);
	cl->setPass(SiCluster::kPass2);

	//cl->setLadder(j);
	//cl->setCentroid(centroid);
	//cl->setWidth(width);
	//cl->setEnergy(esum);
	//cl->setShared(0);

	if(nsub_cluster==1) {
	  if(cluSize < m_siClusters_pass1[i]->getNstrip())       {
	    cl->setShared( 2|m_siClusters_pass1[i]->getShared() );
	  }
	  else cl->setShared( m_siClusters_pass1[i]->getShared() );
	  if(cluSize > m_siClusters_pass1[i]->getNstrip()) std::cout << " wrong subcluster size! " << std::endl;
	}
	else if (j==m_siClusters_pass1[i]->getNstrip()-1) {
	  if(cluSize < m_siClusters_pass1[i]->getNstrip())       cl->setShared( 1|m_siClusters_pass1[i]->getShared() );
	  else std::cout << " wrong subcluster size! " << std::endl;
	}
	else {
	  cl->setShared(3);
	}
	m_siClusters_pass2.push_back(cl);

	indFirst = k;
	indLast  = indFirst;
	cluSize = 1;
	cluMax = (*SiDigit_e)[k];
	indMax = k;
      }
    }

    int ind_begin = nfineCluster;
    if(nsub_cluster == 1) {//cluster not broken, copy from original cluster 
      m_siClusters_pass2[ind_begin]->setLadder   ( m_siClusters_pass1[i]->getLadder()    );
      m_siClusters_pass2[ind_begin]->setCentroid ( m_siClusters_pass1[i]->getCentroid()  );
      m_siClusters_pass2[ind_begin]->setXcentroid( m_siClusters_pass1[i]->getXcentroid() );
      m_siClusters_pass2[ind_begin]->setWidth    ( m_siClusters_pass1[i]->getWidth()     );
      m_siClusters_pass2[ind_begin]->setEnergy   ( m_siClusters_pass1[i]->getEnergy()    );
      m_siClusters_pass2[ind_begin]->setMaxstripEnergy   ( m_siClusters_pass1[i]->getMaxstripEnergy()    );
      //hSiClus211->Fill(finalCluster_nstrip[i]);
      //hSiClus212->Fill(finalCluster_energy[i]);	   
      //hSiClus213->Fill(finalCluster_width[i]);	   
    }
    else {//recalculate cluster information	
      for(int j= 0; j<nsub_cluster; j++) {
	m_siClusters_pass2[ind_begin+j]->setLadder( m_siClusters_pass1[i]->getLadder() );//still same ladder
	int lad = m_siClusters_pass1[i]->getLadder();
	int plane = lad/16;
	int isX   = plane%2;
	int block = lad - plane*16;
	block = block/4;
	int ladder= lad - plane*16 - block*4;

	double sub_esum   = 0.;
	double sub_esumw  = 0.;
	double sub_esumw2 = 0.;
	double sub_emax = 0.;
	int share  = m_siClusters_pass2[ind_begin+j]->getShared();
	int fstrip = m_siClusters_pass2[ind_begin+j]->getIndex1();
	int lstrip = m_siClusters_pass2[ind_begin+j]->getIndex1()+m_siClusters_pass2[ind_begin+j]->getNstrip()-1;
	for(int s=fstrip; s<=lstrip; s++) {
	  float estrip = (*SiDigit_e)[s];
	  if(s==fstrip && (share==1 || share==3)) estrip = 0.5*estrip; 
	  else if(s==lstrip && (share==2 || share==3)) estrip = 0.5*estrip; 
	  int iplane = plane/2;
	  int strip = (*SiDigit_strip)[s] - isX*1000000 - iplane*100000 - block*1536;
	  int nl = strip/384;
	  int stripLadder = strip- nl*384;	  
	  sub_esum   += estrip;
	  sub_esumw  += estrip*stripLadder;
	  sub_esumw2 += estrip*stripLadder*stripLadder;
	  if(estrip > sub_emax) sub_emax = estrip;
	  //cout << " new strip " << s << " " << " strip " << stripLadder << " energy " << estrip << endl;
	}
	double sub_centroid = sub_esumw/sub_esum;
	double sub_width2 =  sub_esumw2/sub_esum - sub_centroid*sub_centroid;
	if(m_siClusters_pass2[ind_begin+j]->getNstrip()==1) {
	  sub_width2 = 0;
	}
	double sub_width = sqrt(sub_width2);

	double localX_onLadder = StkParamDef::activeEdge + 0.5*StkParamDef::pitch + sub_centroid*StkParamDef::ROpitch;
	double ladderCenter = m_ladder0Center[block][isX] + ladder*m_ladderDistance;
	double localX_onPlane  = localX_onLadder + ladderCenter;

	//cout << " new centroid " << sub_centroid << " energy " << sub_esum << " width " << sub_width << " x " << localX_onPlane << endl;
	m_siClusters_pass2[ind_begin+j]->setCentroid(sub_centroid);
	m_siClusters_pass2[ind_begin+j]->setWidth(sub_width);
	m_siClusters_pass2[ind_begin+j]->setEnergy(sub_esum);
	m_siClusters_pass2[ind_begin+j]->setXcentroid(localX_onPlane);
	m_siClusters_pass2[ind_begin+j]->setMaxstripEnergy(sub_emax);
	//hSiClus201->Fill(fineCluster_nstrip[nfineCluster+j]);
	//hSiClus202->Fill(sub_esum);	   
	//hSiClus203->Fill(sub_width);	   
	
      }
    }
    nfineCluster += nsub_cluster;
  }
  //std::cout << " StkClusterFinder: number of pass2 cluster found = " << nfineCluster << " " << m_siClusters_pass2.size() << std::endl;

  m_hSiClus300->Fill(nfineCluster);	   

  //sort clusters into 12 tracking layers
  std::vector<SiCluster*> vecCl;
  //std::vector<std::vector<SiCluster*> > m_siCluster_layer_pass2;
  for(int i= 0; i<12; i++) {
    m_siClusters_layer_pass2.push_back(vecCl);
  }

  if(dmpEvt) { 
    std::cout << " --- Number of pass2 cluster = " << m_siClusters_pass2.size()  << std::endl;
    std::cout << " clus  isX   plane   ladder    centroid    localX      layer Z      energy    nstrp   maxE"  << std::endl;
  }
  for(unsigned int i= 0; i<m_siClusters_pass2.size(); i++) {
    //siClusters[i]->Print();
    int plane = m_siClusters_pass2[i]->getPlane();
    int isX   = m_siClusters_pass2[i]->getView();
    int layer = plane*2 + isX;
    if(dmpEvt) { 
      std::cout << "    " << i << "   " << isX << "      " << plane << "          " << m_siClusters_pass2[i]->getLadder()
		<< "       " <<  m_siClusters_pass2[i]->getCentroid() << "      " << m_siClusters_pass2[i]->getXcentroid()  
		<< "       " <<  m_siClusters_pass2[i]->getLayerZ() << "      " << m_siClusters_pass2[i]->getEnergy() 
		<< "       " <<  m_siClusters_pass2[i]->getNstrip()
		<< "       " <<  m_siClusters_pass2[i]->getMaxstripEnergy() << std::endl;
      if(isX) m_hSiClusX->Fill(m_siClusters_pass2[i]->getLayerZ(),m_siClusters_pass2[i]->getXcentroid());
      else    m_hSiClusY->Fill(m_siClusters_pass2[i]->getLayerZ(),m_siClusters_pass2[i]->getXcentroid());
    }

    m_siClusters_layer_pass2[layer].push_back(m_siClusters_pass2[i]);
    //TRB    0   1  2  3  4  5  6  7
    //block  0Y 0X 1Y 1X 2Y 2X 3Y 3X
    int trb = m_siClusters_pass2[i]->getTRB();
    ++nClusPass2TRB[trb];
    m_hSiClus105->Fill(layer);
    m_hSiClus107->Fill(trb);
  }

  int maxClusPass2TRB = 0;
  for(int j= 0; j<8; j++) {
    if(nClusPass2TRB[j]>maxClusPass2TRB) maxClusPass2TRB = nClusPass2TRB[j];
  }
  m_hSiClus108->Fill(maxClusPass2TRB);
  m_totalMaxClusPass2TRB += maxClusPass2TRB;
  ++m_nMaxClusPass2TRB;

  return;
}

std::vector<SiCluster*>& StkClusterFinder::getClusters(SiCluster::ClusterType type) {
  if(type==SiCluster::kPass1) return m_siClusters_pass1;
  if(type==SiCluster::kPass2) return m_siClusters_pass2;
  return m_siClusters_pass2;
}

std::vector<std::vector<SiCluster*> >& StkClusterFinder::getClusters_layer(SiCluster::ClusterType type) {
  if(type==SiCluster::kPass1) return m_siClusters_layer_pass1;
  if(type==SiCluster::kPass2) return m_siClusters_layer_pass2;
  return m_siClusters_layer_pass2;
}

void StkClusterFinder::plotDelX(TVector3 pos, TVector3 dir, SiCluster::ClusterType type) {
  std::vector<std::vector<SiCluster*> > siCluster_layer;
  if(type==SiCluster::kPass1) siCluster_layer = m_siClusters_layer_pass1;
  if(type==SiCluster::kPass2) siCluster_layer = m_siClusters_layer_pass2;
  else siCluster_layer = m_siClusters_layer_pass2;

  for(int i= 5; i>=0; --i) {
    int layer = i*2;
    //std::cout << " number of clusters in x layer of plane "<< i <<" = "<< siCluster_layer[layer+1].size() << std::endl;	
    //std::cout << " number of clusters in y layer of plane "<< i <<" = "<< siCluster_layer[layer].size() << std::endl;	
    if(siCluster_layer[layer+1].size() == 0) continue; //no x cluster in this layer
    if(siCluster_layer[layer].size()   == 0) continue; //no y cluster in this layer
    //project the initial direction into the x-layer

    double lengthX  = (siCluster_layer[layer+1][0]->getLayerZ() - pos.Z())/dir.Z();
    double lengthY  = (siCluster_layer[layer][0]  ->getLayerZ() - pos.Z())/dir.Z();
    double predX = (pos+lengthX*dir).X();
    double predY = (pos+lengthY*dir).Y();
    double minDx = 9999.;
    double minDy = 9999.;
    for(unsigned int j= 0; j<siCluster_layer[layer+1].size(); ++j) {
      double x = siCluster_layer[layer+1][j]->getXcentroid();
      double dX = x - predX;
      ((TH1F*) (*m_hCluDelX)[layer+1]) -> Fill(dX);
      if( fabs(minDx)>fabs(dX) ) minDx = dX;
    }
    for(unsigned int j= 0; j<siCluster_layer[layer].size(); ++j) {
      double y = siCluster_layer[layer][j]->getXcentroid();
      double dY = y - predY;
      ((TH1F*) (*m_hCluDelX)[layer]) -> Fill(dY);
      if( fabs(minDy)>fabs(dY) ) minDy = dY;
    }
    ((TH1F*) (*m_hCluMinDelX)[layer+1]) -> Fill(minDx);
    ((TH1F*) (*m_hCluMinDelX)[layer]  ) -> Fill(minDy);
  }
  return;
}

void StkClusterFinder::findSpacePointInFullPlane(int plane, SiCluster::ClusterType type, std::vector<SpacePoint>& spacePoints, int view) {
  std::vector<std::vector<SiCluster*> > siCluster_layer;
  if(type==SiCluster::kPass1) siCluster_layer = m_siClusters_layer_pass1;
  if(type==SiCluster::kPass2) siCluster_layer = m_siClusters_layer_pass2;
  else siCluster_layer = m_siClusters_layer_pass2;

  int layer = plane*2;

  int searchLayer = -1;
  if(view == StkParamDef::kXview) searchLayer = plane*2 + 1;
  if(view == StkParamDef::kYview) {
    searchLayer = plane*2;
    layer = plane*2 + 1;
  }

  //std::cout << "  number of x/y clusters in plane " << plane << " = " << siCluster_layer[layer+1].size() << "/" << siCluster_layer[layer].size() << std::endl;
  if(siCluster_layer[searchLayer].size() == 0) return; //no cluster in this layer
  if(siCluster_layer[layer].size()   == 0) return; //no cluster in the other view

  for(unsigned int j= 0; j<siCluster_layer[searchLayer].size(); ++j) {
    double x       = siCluster_layer[searchLayer][j]->getXcentroid();
    int blockX     = siCluster_layer[searchLayer][j]->getBlock();
    double energyX = siCluster_layer[searchLayer][j]->getEnergy();
    //search for a hit in the otherview
    bool isSp =false;
    for(unsigned int k= 0; k<siCluster_layer[layer].size(); ++k) {
      //has to be the same block
      if(blockX != siCluster_layer[layer][k]->getBlock()) continue;
      //find one pair, make a space point
      isSp =true;
    }
    if(isSp) {
      if(view == StkParamDef::kXview) {
	SpacePoint sp = SpacePoint(plane,blockX,x,-999999.0,energyX,0.0, siCluster_layer[searchLayer][j], 0);
	spacePoints.push_back(sp);
      }
      else {
	SpacePoint sp = SpacePoint(plane,blockX,-999999.0,x,0.0,energyX, 0, siCluster_layer[searchLayer][j]);
	spacePoints.push_back(sp);
      }
    }
  }

  return;
}

void StkClusterFinder::findSpacePointInFullPlane(int plane, SiCluster::ClusterType type, std::vector<SpacePoint>& spacePoints) {
  std::vector<std::vector<SiCluster*> > siCluster_layer;
  if(type==SiCluster::kPass1) siCluster_layer = m_siClusters_layer_pass1;
  if(type==SiCluster::kPass2) siCluster_layer = m_siClusters_layer_pass2;
  else siCluster_layer = m_siClusters_layer_pass2;

  int layer = plane*2;

  //std::cout << "  number of x/y clusters in plane " << plane << " = " << siCluster_layer[layer+1].size() << "/" << siCluster_layer[layer].size() << std::endl;
  if(siCluster_layer[layer+1].size() == 0) return; //no x cluster in this layer
  if(siCluster_layer[layer].size()   == 0) return; //no y cluster in this layer

  for(unsigned int j= 0; j<siCluster_layer[layer+1].size(); ++j) {
    double x       = siCluster_layer[layer+1][j]->getXcentroid();
    int blockX     = siCluster_layer[layer+1][j]->getBlock();
    double energyX = siCluster_layer[layer+1][j]->getEnergy();
    //search for a y hit
    for(unsigned int k= 0; k<siCluster_layer[layer].size(); ++k) {
      double y = siCluster_layer[layer][k]->getXcentroid();
      //has to be the same block
      if(blockX != siCluster_layer[layer][k]->getBlock()) continue;
      //find one pair, make a space point
      double energyY = siCluster_layer[layer][k]->getEnergy();
      SpacePoint sp = SpacePoint(plane,blockX,x,y,energyX,energyY,siCluster_layer[layer+1][j],siCluster_layer[layer][k]);
      spacePoints.push_back(sp);
      //sp.Print();
    }
  }

  return;

}

void StkClusterFinder::findSpacePointInPlane(int plane, TVector3 pos, TVector3 dir, double radius, SiCluster::ClusterType type, std::vector<SpacePoint>& spacePoints) {

  std::vector<std::vector<SiCluster*> > siCluster_layer;
  if(type==SiCluster::kPass1) siCluster_layer = m_siClusters_layer_pass1;
  if(type==SiCluster::kPass2) siCluster_layer = m_siClusters_layer_pass2;
  else siCluster_layer = m_siClusters_layer_pass2;

  int layer = plane*2;

  //std::cout << "  number of x/y clusters in plane " << plane << " = " << siCluster_layer[layer+1].size() << "/" << siCluster_layer[layer].size() << std::endl;
  if(siCluster_layer[layer+1].size() == 0) return; //no x cluster in this layer
  if(siCluster_layer[layer].size()   == 0) return; //no y cluster in this layer

  std::multimap<double, SpacePoint> sortMap;
  //project the initial direction into the x-layer
  double lengthX  = (siCluster_layer[layer+1][0]->getLayerZ() - pos.Z())/dir.Z();
  double lengthY  = (siCluster_layer[layer][0]  ->getLayerZ() - pos.Z())/dir.Z();
  double predX = (pos+lengthX*dir).X();
  double predY = (pos+lengthY*dir).Y();
  for(unsigned int j= 0; j<siCluster_layer[layer+1].size(); ++j) {
    double x = siCluster_layer[layer+1][j]->getXcentroid();
    double dX = x - predX;
    //search for hit in +-10cm from the predicted position
    if( fabs(dX)>radius ) continue;
    double energyX = siCluster_layer[layer+1][j]->getEnergy();
    int blockX = siCluster_layer[layer+1][j]->getBlock();
    //search for a y hit
    for(unsigned int k= 0; k<siCluster_layer[layer].size(); ++k) {
      double y = siCluster_layer[layer][k]->getXcentroid();
      double dY = y - predY;
      if( fabs(dY)>radius ) continue;
      //check radius
      double dr2 = dX*dX+dY*dY;
      if( dr2 > radius*radius ) continue; 
      //has to be the same block
      if(blockX != siCluster_layer[layer][k]->getBlock()) continue;
      double energyY = siCluster_layer[layer][k]->getEnergy();
      //find one pair, make a space point
      SpacePoint sp = SpacePoint(plane,blockX,x,y,energyX,energyY,siCluster_layer[layer+1][j],siCluster_layer[layer][k]);
      std::pair<double, SpacePoint> sortSp(dr2,sp);
      //std::pair<double, SpacePoint> sortSp(dX,sp);
      // std::pair<double, SpacePoint> sortSp(fabs(dX)+fabs(dY),sp);
      sortMap.insert(sortSp);
      //std::cout << "one sp with dr= " << sqrt(dr2) << std::endl;
      //sp.Print();
    }
  }
  //std::cout << " number of sp found " << sortMap.size() << std::endl;
	
  if(sortMap.size()>0) {
    typedef std::multimap<double, SpacePoint>::const_iterator mapIter;
    mapIter iter = sortMap.begin();
    for(iter=sortMap.begin(); iter!=sortMap.end();++iter) {
      spacePoints.push_back((*iter).second);
    }
  }

  return;
}

//bool StkClusterFinder::findNearestCluInLayer(int layer, double coord, double sigma, SiCluster::ClusterType type, SiCluster& nearClu) {
SiCluster* StkClusterFinder::findNearestCluInLayer(int layer, double coord, double sigma, SiCluster::ClusterType type) {
  SiCluster* nearClu = 0;
  std::vector<std::vector<SiCluster*> > siCluster_layer;
  if(type==SiCluster::kPass1) siCluster_layer = m_siClusters_layer_pass1;
  if(type==SiCluster::kPass2) siCluster_layer = m_siClusters_layer_pass2;
  else siCluster_layer = m_siClusters_layer_pass2;

  // std::cout << "StkClusterFinder::findNearestCluInLayer:  number of clusters in layer " << layer << " = " << siCluster_layer[layer].size() << std::endl;
  //std::cout << "StkClusterFinder::findNearestCluInLayer:  coord = " << coord << " sigma = " << sigma << std::endl;
  if(siCluster_layer[layer].size()   == 0) return nearClu; //no cluster in this layer
  //if(siCluster_layer[layer].size()   == 0) return false; //no cluster in this layer
  
  double minDx = 9999.;
  int imin = -1;
  for(unsigned int j= 0; j<siCluster_layer[layer].size(); ++j) {
    //siCluster_layer[layer][j]->Print();
    double x = siCluster_layer[layer][j]->getXcentroid();
    double dX = x - coord;
    if( fabs(minDx)>fabs(dX) ) {
      minDx = dX;
      imin = j;
    }
  }
  //std::cout << "StkClusterFinder::findNearestCluInLayer:   mindx = " << minDx << std::endl;
  if(minDx < m_nsigmaWidth * sigma) {
    nearClu = (SiCluster*) siCluster_layer[layer][imin];
  }
  //std::cout << "StkClusterFinder::findNearestCluInLayer: no cluster found!!! " << std::endl;
  return nearClu;

}

int StkClusterFinder::getNclusterInLayer(int layer, SiCluster::ClusterType type) {
  std::vector<std::vector<SiCluster*> > siCluster_layer;
  if(type==SiCluster::kPass1) siCluster_layer = m_siClusters_layer_pass1;
  if(type==SiCluster::kPass2) siCluster_layer = m_siClusters_layer_pass2;
  else siCluster_layer = m_siClusters_layer_pass2;

  return siCluster_layer[layer].size();
}

int StkClusterFinder::getNclusterInPlane(int plane, SiCluster::ClusterType type) {
  std::vector<std::vector<SiCluster*> > siCluster_layer;
  if(type==SiCluster::kPass1) siCluster_layer = m_siClusters_layer_pass1;
  if(type==SiCluster::kPass2) siCluster_layer = m_siClusters_layer_pass2;
  else siCluster_layer = m_siClusters_layer_pass2;

  return siCluster_layer[plane*2].size()+siCluster_layer[plane*2+1].size();
}

void StkClusterFinder::clearCluster() {
    for (unsigned int i = 0; i < m_siClusters_pass1.size(); ++i) {
      delete m_siClusters_pass1[i]; 
    }
    m_siClusters_pass1.clear();
    for (unsigned int i = 0; i < m_siClusters_pass2.size(); ++i) {
      delete m_siClusters_pass2[i]; 
    }
    m_siClusters_pass2.clear();

    m_siClusters_layer_pass1.clear();
    m_siClusters_layer_pass2.clear();
}

