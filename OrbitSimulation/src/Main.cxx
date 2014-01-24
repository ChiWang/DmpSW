// Main program for OrbSim

//#include "include/Functions.h"

#include <iostream>
#include <TFile.h>
#include <TTree.h>


//using namespace std;
#include "../include/functions.h"
#include "../include/atFunctions.h"
#include "../include/read_ephem.h"
#include "../include/OrbSim.h"



#include "../include/IniReader.h"

//#include "../include/jpleph.h"

#include "../include/IGRField.h"
using namespace astro;



///////////////////////////////////////////////////////////////
// interface to ppfrag fortran routines in igrf_sub.f
//extern "C" void   INITIZE_();
///////////////////////////////////////////////////////////////


int main(int argc, char** argv)
{

  
  // READ INIT FILE

  char * Ini_Filename = argv[1];// = "/lustrehome/gargano/DAMPE/DAMPESW/DmpSoftware/branches/I_0.0_OrbitSimulation/test/DAMPE.ini";
  std::cout << "Reading Ini_FileName : " <<  Ini_Filename<< std::endl;
 
  char * EphemFileName;
  EphemFileName = IniReadString(Ini_Filename, "EphemName", "../data/DAMPE.tle");
  //std::cout << "Ephem File : " << EphemFileName << std::endl;
  
  double start_MJD = IniReadDouble(Ini_Filename, "Start_MJD", 57388); 
  double stop_MJD = IniReadDouble(Ini_Filename, "Stop_MJD",57389);

  double Ira = IniReadDouble(Ini_Filename, "Ira",0.);
  double Idec = IniReadDouble(Ini_Filename, "Idec",0.);
  double Units = IniReadDouble(Ini_Filename, "Units",1.);
  double Resolution = IniReadDouble(Ini_Filename, "Resolution",1.);
  char * TLname;
  TLname = IniReadString(Ini_Filename, "TimelnCmd", "|SURVEY|+0.1|");
  char * saafile;
  saafile = IniReadString(Ini_Filename, "saafile", "../data/L_SAA_2008198.03");
  char * RootFileName;
  RootFileName = IniReadString(Ini_Filename, "RootFileName", "../test/output.root");
  char * IGRFDataPath;
  IGRFDataPath = IniReadString(Ini_Filename, "IGRFDataPath", "/lustrehome/gargano/DAMPE/DAMPESW/DmpSoftware/branches/I_0.0_OrbitSimulation/data/");

  bool BuildMap = IniReadBool(Ini_Filename, "BuildMap", false);

  int latSteps = IniReadInt(Ini_Filename, "LatMapNStep",180);
  int lonSteps = IniReadInt(Ini_Filename, "LonMapNStep",360);
  double RMap = IniReadDouble(Ini_Filename, "RMap",500);
  char * SATname;
  SATname = IniReadString(Ini_Filename, "SATname", "DAMPE");
  std::cout << "SATname " << SATname << std::endl; 


  AtVect vSun;
  AtPolarVect pSun;

  AtVect vSat;
  AtPolarVect pSat;

  AtVect vSatX;
  AtPolarVect pSatX;
  AtVect vSatRX;

  AtVect vSatY;
  AtPolarVect pSatY;  
  AtVect vSatRY;

  AtVect vSatZ;
  AtVect vSatZInv;

  AtPolarVect pSatZ;  
  AtVect vSatRZ;

  AtVect vSatZenith;
  AtPolarVect pSatZenith;  
  


  InitI initf;
  /// starting time in MJD
  initf.start_MJD =start_MJD;
  /// stopping time in MJD
  initf.stop_MJD =stop_MJD;
  /// SATname Satellite Name as is reported in tle file
  initf.SATname = SATname; 
  /// Ephemeris file name, path included  
  initf.EPHname = EphemFileName;
  /// function name to read/propagate ephemeris   
  initf.EPHfunc = "tlederive"; // fixed since is the only implemented way to pass DAMPE Ephemeris
  /// Timeline type (TAKO, ASFLOWN, or SINGLE)
  initf.TLtype = "SURVAY"; // fixed since is the only way implemented to simulate DAMPE Attitude
  /// Initial RA                    
  initf.Ira = Ira;   
  /// Initial DEC      
  initf.Idec =Idec; 
  /// conversion factor to convert in Km    
  initf.Units = Units;  
  /// Ephemeris resolution, and therefore   
  /// orbit simulator resolution in minutes
  initf.Resolution = Resolution;
  /// Timeline file name, path included
  initf.TLname = TLname;
  /// SAA file definition    
  initf.saafile = saafile ;
  std::cout <<  "saafile: " << saafile << std::endl;
  int yy, MM, dd, hh, mm, ss;
  do_mjd2cal(initf.start_MJD, &yy, &MM, &dd, &hh, &mm, &ss);
  printf("\n Start Date: %4d-%02d-%02dT%02d:%02d:%02d \n", yy, MM, dd, hh, mm, ss);
  do_mjd2cal(initf.stop_MJD, &yy, &MM, &dd, &hh, &mm, &ss);
  printf("\n Stop Date: %4d-%02d-%02dT%02d:%02d:%02d \n", yy, MM, dd, hh, mm, ss);


  // Add a little buffer to the end time so we calculate enough ephem
  // and attitude point to get positions up to the end of the desired time.
  double stop_buffer = 0.1;
  initf.stop_MJD=initf.stop_MJD+stop_buffer;

  // Fixing the start time according to the resolution
  double stmjd = initf.start_MJD;
  double fday = (stmjd - (double)((int)stmjd))*minInDay;
  fday = (double)((int)(fday/initf.Resolution)-1)*initf.Resolution;
  stmjd = (double)((int)stmjd)+fday/minInDay;

  if((initf.start_MJD - stmjd)- initf.Resolution > 1.0E-6){
    std::cout <<"Initial start time=" << initf.start_MJD << ", corrected time=" << stmjd  << std::endl;
    initf.start_MJD = stmjd; 
  }
  
  // Also fix the stop time based on resolution.
  double enmjd = initf.stop_MJD;
  fday = (enmjd - (double)((int)enmjd))*minInDay;
  fday = (double)((int)(fday/initf.Resolution)+1)*initf.Resolution;
  enmjd = (double)((int)enmjd)+fday/minInDay;

  if((initf.stop_MJD - enmjd)- initf.Resolution > 1.0E-6){
    std::cout  <<"Initial stop time=" << initf.stop_MJD << ", corrected time=" << enmjd  << std::endl;
    initf.stop_MJD = enmjd;
  }
  

  initf.Resolution = initf.Resolution/minInDay; // conversion of resolution in fraction of day
  

  // EPHEM DEFINTION FROM TLE
  EphemData * ephemeris = NULL;  
  FILE * ephF = NULL;
  if ((ephF=fopen(initf.EPHname.c_str(),"r")) == NULL){
    std::cout <<"Cound not open Ephemeredis file" << std::endl;
    return -1;
  }
  ephemeris = tlederive(ephF, initf.start_MJD,initf.stop_MJD , initf.Units, initf.Resolution,initf.SATname );   
  fclose(ephF);
  if (ephemeris == NULL){
    std::cout << "\nPossibly something went wrong while reading/generating ephemeris.\nThe Ephemeris structure is still \"NULL\"\n\n" << std::endl;
    return -1;
  }
  // just for test
  std::cout << "From Ephem file, start mjd = " << ephemeris->MJD[0] <<  std::endl;

  // ATTITUDE DEFINITION
 
  //Make an empty Attitude structure Oat. 
  Attitude *Oat = NULL;

  Oat = doCmd(&initf, ephemeris);

  // Restore stop_MJD to its correct, but smaller value
  initf.stop_MJD=initf.stop_MJD-stop_buffer;

  if(Oat == NULL){
    std::cout << "\nPossibly something went wrong while calculating the spacecraft attitude.\nThe Attitude structure is still \"NULL\"\n\n" << std::endl;
    return -1;
  }  



  
 

  // Output root file

  TFile fout(RootFileName,"recreate");
  std::cout << "Opening Root File " << RootFileName << std::endl; 

  
  TTree OrbitTree("OrbitTree","Tree with orbit parameters");
  // create the branches and assign the fill-variables to them
  Int_t ev;
  Double_t lat_geo, lon_geo, rad_geo, ra_zenith, dec_zenith, ra_scz, dec_scz, ra_scx, dec_scx, ra_scy, dec_scy, livetime;
  Double_t pos[3];
  Bool_t in_saa;
  UInt_t stop,start;
  Double_t dipoleMoment, L, B, bEast, bNorth, bDown, bAbs, bEquator, R, verticalRigidityCutoff, invariantLatitude; 
  Double_t BVect[3];
  Double_t SunLat, SunLon;


  OrbitTree.Branch("ev",&ev,"ev/I");
  OrbitTree.Branch("start", &start, "start/i");
  OrbitTree.Branch("stop", &stop, "stop/i");
  OrbitTree.Branch("lat_geo", &lat_geo, "lat_geo/D");
  OrbitTree.Branch("lon_geo", &lon_geo, "lon_geo/D");
  OrbitTree.Branch("rad_geo", &rad_geo, "rad_geo/D");
  OrbitTree.Branch("pos", &pos, "pos[3]/D");

  OrbitTree.Branch("ra_zenith", &ra_zenith, "ra_zenith/D");
  OrbitTree.Branch("dec_zenith", &dec_zenith, "dec_zenith/D");

  OrbitTree.Branch("ra_scz", &ra_scz, "ra_scz/D");
  OrbitTree.Branch("dec_scz", &dec_scz, "dec_scz/D");
  OrbitTree.Branch("ra_scx", &ra_scx, "ra_scx/D");
  OrbitTree.Branch("dec_scx", &dec_scx, "dec_scx/D");
  OrbitTree.Branch("ra_scy", &ra_scy, "ra_scy/D");
  OrbitTree.Branch("dec_scy", &dec_scy, "dec_scx/D");

  //OrbitTree.Branch("livetime", &livetime, "livetime/D");
  OrbitTree.Branch("in_saa", &in_saa, "in_saa/O");


  // Geomagnetic Section 
  OrbitTree.Branch("dipoleMoment", &dipoleMoment, "dipoleMoment/D");
  OrbitTree.Branch("L", &L, "L/D");
  //OrbitTree.Branch("B", &B, "B/D");
  OrbitTree.Branch("bEast", &bEast, "bEast/D");
  OrbitTree.Branch("bNorth", &bNorth, "bNorth/D");
  OrbitTree.Branch("bDown", &bDown, "bNorth/D");
  OrbitTree.Branch("BVect", &BVect, "BVect[3]/D");
  //  OrbitTree.Branch("bX", &bX, "bX/D");
  //OrbitTree.Branch("bY", &bY, "bY/D");
  //OrbitTree.Branch("bZ", &bZ, "bZ/D");
  OrbitTree.Branch("bAbs", &bAbs, "bNorth/D");
  //OrbitTree.Branch("bEquator", &bEquator, "bEquator/D");
  //OrbitTree.Branch("R", &R, "R/D");
  OrbitTree.Branch("verticalRigidityCutoff", &verticalRigidityCutoff, "verticalRigidityCutoff/D");
  OrbitTree.Branch("invariantLatitude", &invariantLatitude, "invariantLatitude/D");


  // Sun Position

  OrbitTree.Branch("SunLat", &SunLat, "SunLat/D");
  OrbitTree.Branch("SunLon", &SunLon, "SunLon/D");
 
  //fill the tree
  for (Int_t i=0; i<Oat->ent; i++) {

    stop = (UInt_t)((Oat->mjd[i]-MJDREF)*secInDay+0.5);
    start = stop - (UInt_t)(initf.Resolution*secInDay);


    


    

    ev = i;
    lat_geo = Oat->Lat[i];
    lon_geo = Oat->Lon[i];
    rad_geo = Oat->Hei[i]*1000.0;

    pSat.lat = lat_geo;
    pSat.lon = lon_geo;
    pSat.r = rad_geo;
 



    pos[0]=Oat->X[i]*1000.0;
    pos[1]=Oat->Y[i]*1000.0;
    pos[2]=Oat->Z[i]*1000.0;
    ra_zenith = Oat->SatRA[i];
    dec_zenith = Oat->SatDEC[i];
    pSatZenith.lon = Oat->SatRA[i]*DEG2RAD;
    pSatZenith.lat =  Oat->SatDEC[i]*DEG2RAD;
    pSatZenith.r = 1; // fake only for direction purposes
    atPolToVect(&pSatZenith,vSatZenith);
   

  
    pSatZ.lon = Oat->Zra[i]*DEG2RAD;
    pSatZ.lat =  Oat->Zdec[i]*DEG2RAD;
    pSatZ.r = 1; // fake only for direction purposes
    atPolToVect(&pSatZ,vSatZ);
   
    pSatX.lon = Oat->Xra[i]*DEG2RAD;
    pSatX.lat =  Oat->Xdec[i]*DEG2RAD;
    pSatX.r = 1; // fake only for direction purposes
    atPolToVect(&pSatX,vSatX);
  
    pSatY.lon = Oat->Yra[i]*DEG2RAD;
    pSatY.lat =  Oat->Ydec[i]*DEG2RAD;
    pSatY.r = 1; // fake only for direction purposes
    atPolToVect(&pSatY,vSatY);



    ra_scz = pSatZ.lon*RAD2DEG;
    dec_scz = pSatZ.lat*RAD2DEG;

    
    ra_scx = pSatX.lon*RAD2DEG;
    dec_scx = pSatX.lat*RAD2DEG;
    
          
    ra_scy = pSatY.lon*RAD2DEG;
    dec_scy = pSatY.lat*RAD2DEG;



    //double theta;
    //angularSep(ra_scz*DEG2RAD, dec_scz*DEG2RAD, ra_zenith*DEG2RAD, dec_zenith*DEG2RAD, &theta);
    //std::cout << "Angular sep between Z and Zenith " << theta*RAD2DEG << std::endl; 


    // To check if it is useful at this stage
    /*
    in_saa = Oat->in_saa[i];
    if (Oat->in_saa[i] == 1)
      {
	livetime = 0.0;
      } else 
      {
	livetime = initf.Resolution*secInDay*0.93; // check 0.93 ???    
      }
    */  
    
    // Geomagnetic  section
   // the year is fixed at 2015 since is the last valid yesr for IGRF at the moment
    IGRField::Model().compute(lat_geo, lon_geo, rad_geo, 2015, IGRFDataPath);
   
    dipoleMoment = IGRField::Model().dipoleMoment(); // Get dipole moment    
    L = IGRField::Model().L(); // Get McIlwain L
    //B = IGRField::Model().B(); // Get B/B0 bAbs/bEquator
    /*BNORTH, BEAST, BDOWN   COMPONENTS OF THE FIELD WITH RESPECT */
    /*                 TO THE LOCAL GEODETIC COORDINATE SYSTEM, WITH AXIS */
    /*                 POINTING IN THE TANGENTIAL PLANE TO THE NORTH, EAST */
    /*                 AND DOWNWARD. */
    bEast = IGRField::Model().bEast();// Get B_East in G
    bNorth = IGRField::Model().bNorth();// Get B_North in G 
    bDown = IGRField::Model().bDown();// Get B_Down in G 
    BVect[0] = IGRField::Model().bX();// Get B_X in G
    BVect[1] = IGRField::Model().bY();// Get B_Y in G 
    BVect[2] = IGRField::Model().bZ();// Get B_Z in G 


    /* BABS  MAGNETIC FIELD STRENGTH IN GAUSS  */
    bAbs = IGRField::Model().bAbs();// Get absolute value of B
    //bEquator = IGRField::Model().bEquator();// Get absolute value of B at the equator
    // R = IGRField::Model().R();// Get R alternative from http://www.spenvis.oma.be/spenvis/help/background/magfield/rlambda.html
    verticalRigidityCutoff  = IGRField::Model().verticalRigidityCutoff();// Get vertical rigidity cutoff
    invariantLatitude = IGRField::Model().invariantLatitude();// Get invariant latitude


    
    // Solar position section
    // evaluate sun position in cartesina
    atSun(Oat->mjd[i],vSun);   
    //    std::cout << "Sun x " << vSun[0] << "Sun y " << vSun[1] << " Sun z " << vSun[2] <<std::endl;
    // transform in polar
    atVectToPol( vSun, &pSun);
    //std::cout << "Sun lon " << pSun.lon*180/3.14 << "Sun lat " << pSun.lat*180/3.14 << " Sun R " << pSun.r <<std::endl;

    SunLon = pSun.lon*RAD2DEG;
    SunLat = pSun.lat *RAD2DEG;


    OrbitTree.Fill();
  }

  if(BuildMap){

    Int_t LatSteps,LonSteps;

    TTree MapTree("MapTree","Tree with parameters to build geomagnetic maps");
    MapTree.Branch("lat_geo", &lat_geo, "lat_geo/D");
    MapTree.Branch("lon_geo", &lon_geo, "lon_geo/D");
    MapTree.Branch("rad_geo", &rad_geo, "rad_geo/D");
    // Geomagnetic Section 
    MapTree.Branch("dipoleMoment", &dipoleMoment, "dipoleMoment/D");
    MapTree.Branch("L", &L, "L/D");
    //MapTree.Branch("B", &B, "B/D");
    MapTree.Branch("bEast", &bEast, "bEast/D");
    MapTree.Branch("bNorth", &bNorth, "bNorth/D");
    MapTree.Branch("bDown", &bDown, "bNorth/D");
    MapTree.Branch("bAbs", &bAbs, "bNorth/D");
    OrbitTree.Branch("BVect", &BVect, "BVect[3]/D");
    //MapTree.Branch("bEquator", &bEquator, "bEquator/D");

    MapTree.Branch("verticalRigidityCutoff", &verticalRigidityCutoff, "verticalRigidityCutoff/D");
    MapTree.Branch("invariantLatitude", &invariantLatitude, "invariantLatitude/D");
    MapTree.Branch("LatSteps", &LatSteps,"LatSteps/I" );
    MapTree.Branch("LonSteps", &LonSteps,"LonSteps/I" );

   
      
    for (Int_t lat=0; lat<=latSteps; lat++) {
      for (Int_t lon=0; lon<=lonSteps; lon++) {
	
	LatSteps = latSteps;
	LonSteps = lonSteps;
	lat_geo = lat*180./latSteps - 90;
	lon_geo = lon*360./lonSteps;
	rad_geo = RMap;
	//std::cout << "lat " << lat_geo << " lon " << lon_geo << std::endl;  
	// Geomagnetic  section
	// the year is fixed at 2015 since is the last valid yesr for IGRF at the moment
	IGRField::Model().compute(lat_geo, lon_geo, rad_geo, 2015, IGRFDataPath);
	
	dipoleMoment = IGRField::Model().dipoleMoment(); // Get dipole moment    
	L = IGRField::Model().L(); // Get McIlwain L
	B = IGRField::Model().B(); // Get B/B0 bAbs/bEquator
	/*BNORTH, BEAST, BDOWN   COMPONENTS OF THE FIELD WITH RESPECT */
	/*                 TO THE LOCAL GEODETIC COORDINATE SYSTEM, WITH AXIS */
	/*                 POINTING IN THE TANGENTIAL PLANE TO THE NORTH, EAST */
	/*                 AND DOWNWARD. */
	bEast = IGRField::Model().bEast();// Get B_East
	bNorth = IGRField::Model().bNorth();// Get B_North
	bDown = IGRField::Model().bDown();// Get B_Down
	BVect[0] = IGRField::Model().bX();// Get B_X in G
	BVect[1] = IGRField::Model().bY();// Get B_Y in G 
	BVect[2] = IGRField::Model().bZ();// Get B_Z in G 
	/* BABS  MAGNETIC FIELD STRENGTH IN GAUSS  */
	bAbs = IGRField::Model().bAbs();// Get absolute value of B
	//bEquator = IGRField::Model().bEquator();// Get absolute value of B at the equator
	// R = IGRField::Model().R();// Get R alternative from http://www.spenvis.oma.be/spenvis/help/background/magfield/rlambda.html
	verticalRigidityCutoff  = IGRField::Model().verticalRigidityCutoff();// Get vertical rigidity cutoff
	invariantLatitude = IGRField::Model().invariantLatitude();// Get invariant latitude
	MapTree.Fill();
	
      }
    }
    MapTree.Write();
  }
  
  OrbitTree.Write();
  fout.Close();
  std::cout << "Closing Root File " << RootFileName << std::endl; 
 

  return 0;

}
