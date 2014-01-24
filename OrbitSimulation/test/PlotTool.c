void PlotTool(){}

void MapsPlot(TString filename){

  // Tool to make some maps plots
  cout << "Opening ROOT file: " << filename <<endl;

  gROOT->Reset();
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);
  //gStyle->SetCanvasColor(33);
  //gStyle->SetFrameFillColor(18);


  TFile *f = TFile::Open(filename);
  f->ls();



  TTree *MapTree = (TTree*)f->Get("MapTree");
  Int_t ev;
  Double_t lat_geo, lon_geo, rad_geo;
  Double_t dipoleMoment, L, B, bEast, bNorth, bDown, bAbs, bEquator, R, verticalRigidityCutoff, invariantLatitude; 
  Double_t BVect[3];
  Int_t LatSteps,LonSteps;


  
  MapTree->SetBranchAddress("lat_geo", &lat_geo);
  MapTree->SetBranchAddress("lon_geo", &lon_geo);
  MapTree->SetBranchAddress("rad_geo", &rad_geo);
  // Geomagnetic Section 
  MapTree->SetBranchAddress("dipoleMoment", &dipoleMoment);
  MapTree->SetBranchAddress("L", &L);

  MapTree->SetBranchAddress("bEast", &bEast);
  MapTree->SetBranchAddress("bNorth", &bNorth);
  MapTree->SetBranchAddress("bDown", &bDown);
  MapTree->SetBranchAddress("bAbs", &bAbs);
  OrbitTree->SetBranchAddress("BVect", &BVect);

  
  MapTree->SetBranchAddress("verticalRigidityCutoff", &verticalRigidityCutoff);
  MapTree->SetBranchAddress("invariantLatitude", &invariantLatitude);
  MapTree->SetBranchAddress("LatSteps", &LatSteps);
  MapTree->SetBranchAddress("LonSteps", &LonSteps);

  MapTree->GetEntry(1);
  Int_t iLatSteps = LatSteps;
  Int_t iLonSteps = LonSteps;
 

  TH2D *h_BAbs_Map = new TH2D("h_BAbs_Map", "Map of Magnetic field in Gauss", iLonSteps,0., +360.,iLatSteps, -90., 90. );
  TH2D *h_VRC_Map = new TH2D("h_VRC_Map", "Map of Vertical Rigidity Cutoff", iLonSteps,0., +360.,iLatSteps, -90., 90. );
 
  


  Int_t nentries = (Int_t)MapTree->GetEntries();
  for (Int_t i=0; i<nentries; i++) {
    MapTree->GetEntry(i);
    //cout << "lat_geo: " << lat_geo << " lon_geo "<<lon_geo << endl;
    h_BAbs_Map->Fill(lon_geo, lat_geo, bAbs);
    h_VRC_Map->Fill(lon_geo, lat_geo,verticalRigidityCutoff ); 
  }


  TCanvas *c1 = new TCanvas("c1", "c1", 600, 600);
  c1->Divide(1,2);
  c1->cd(1);
  h_BAbs_Map->DrawCopy("COLZ");
  c1->cd(2);
  h_VRC_Map->DrawCopy("COLZ");

  f->Close();

}
void OrbitPlot(TString filename){

  // Tool to make some maps plots
  cout << "Opening ROOT file: " << filename <<endl;

  gROOT->Reset();
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);
  //gStyle->SetCanvasColor(33);
  //gStyle->SetFrameFillColor(18);


  TFile *f = TFile::Open(filename);
  f->ls();



  TTree *MapTree = (TTree*)f->Get("OrbitTree");
 
  Int_t ev;
  Double_t lat_geo, lon_geo, rad_geo, ra_zenith, dec_zenith, ra_scz, dec_scz, ra_scx, dec_scx, ra_scy, dec_scy, livetime;
  Double_t pos[3];
  Bool_t in_saa;
  UInt_t stop,start;
  Double_t dipoleMoment, L, B, bEast, bNorth, bDown, bAbs, bEquator, R, verticalRigidityCutoff, invariantLatitude; 
  Double_t BVect[3];
  Double_t SunLat, SunLon;
  
 
 
  
  OrbitTree->SetBranchAddress("ev",&ev);
  OrbitTree->SetBranchAddress("start", &start);
  OrbitTree->SetBranchAddress("stop", &stop);
  OrbitTree->SetBranchAddress("lat_geo", &lat_geo);
  OrbitTree->SetBranchAddress("lon_geo", &lon_geo);
  OrbitTree->SetBranchAddress("rad_geo", &rad_geo);
  OrbitTree->SetBranchAddress("pos", &pos);

  OrbitTree->SetBranchAddress("ra_zenith", &ra_zenith);
  OrbitTree->SetBranchAddress("dec_zenith", &dec_zenith);

  OrbitTree->SetBranchAddress("ra_scz", &ra_scz);
  OrbitTree->SetBranchAddress("dec_scz", &dec_scz);
  OrbitTree->SetBranchAddress("ra_scx", &ra_scx);
  OrbitTree->SetBranchAddress("dec_scx", &dec_scx);
  OrbitTree->SetBranchAddress("ra_scy", &ra_scy);
  OrbitTree->SetBranchAddress("dec_scy", &dec_scy);

 
  OrbitTree->SetBranchAddress("in_saa", &in_saa);


  // Geomagnetic Section 
  OrbitTree->SetBranchAddress("dipoleMoment", &dipoleMoment);
  OrbitTree->SetBranchAddress("L", &L);
  OrbitTree->SetBranchAddress("bEast", &bEast);
  OrbitTree->SetBranchAddress("bNorth", &bNorth);
  OrbitTree->SetBranchAddress("bDown", &bDown);
  OrbitTree->SetBranchAddress("BVect", &BVect);  
  OrbitTree->SetBranchAddress("bAbs", &bAbs);
  OrbitTree->SetBranchAddress("verticalRigidityCutoff", &verticalRigidityCutoff);
  OrbitTree->SetBranchAddress("invariantLatitude", &invariantLatitude);


   // Sun Position

  OrbitTree->SetBranchAddress("SunLat", &SunLat);
  OrbitTree->SetBranchAddress("SunLon", &SunLon);

  TH2D *h_scz_dir = new TH2D("h_scz_dir", "Z Axis", 360,0., +360.,90, -90., 90. );
  TH2D *h_scy_dir = new TH2D("h_scy_dir", "Y Axis", 360,0., +360.,90, -90., 90. );
  TH2D *h_scx_dir = new TH2D("h_scy_dir", "X Axis", 360,0., +360.,90, -90., 90. );
  TH2D *h_zenith_dir = new TH2D("h_zenith_dir", "X Axis", 360,0., +360.,90, -90., 90. );
  TH2D *h_sun_dir = new TH2D("h_sun_sir", "Sun", 360,0., +360.,90, -90., 90. );

  TH2D *h_sat_pos = new TH2D("h_sat_pos", "Satellite position", 360,0., +360.,90, -90., 90. );
  TH2D *h_sat_pos_B = new TH2D("h_sat_pos_B", "B(G) @ Satellite position", 360,0., +360.,90, -90., 90. );
 

  


  Int_t nentries = (Int_t)OrbitTree->GetEntries();
  for (Int_t i=0; i<nentries; i++) {
    OrbitTree->GetEntry(i);
    h_scz_dir->Fill(ra_scz,dec_scz);
    h_scy_dir->Fill(ra_scy,dec_scy);

    h_scx_dir->Fill(ra_scx,dec_scx);
   

    h_sun_dir->Fill(SunLon,SunLat);
    h_zenith_dir->Fill(ra_zenith,dec_zenith);

    h_sat_pos->Fill(lon_geo,lat_geo);
    h_sat_pos_B->Fill(lon_geo,lat_geo,bAbs);

    //cout << rad_geo/1000. << endl;

  }


  TCanvas *c1 = new TCanvas("c1", "c1", 600, 600);
  c1->Divide(1,1);
  c1->cd(1);
  h_scz_dir->DrawCopy();

  h_scy_dir->SetMarkerColor(kRed);
  h_scy_dir->DrawCopy("SAME");

  h_scx_dir->SetMarkerColor(kBlue);    
  h_scx_dir->DrawCopy("SAME");

  h_sun_dir->SetMarkerColor(kYellow);  
  h_sun_dir->DrawCopy("SAME");

  TCanvas *c2 = new TCanvas("c2", "c2", 600, 600);
  c2->Divide(1,2);
  c2->cd(1);
  h_sat_pos->DrawCopy("");
  c2->cd(2);
  h_sat_pos_B->DrawCopy("COLZ");
  
  
  f->Close();

}
