/**
 * @file read_ephem.cc
 * @brief This file contains functions to read/calculate ephemeredis and the attitude calculation.
 * @author Giuseppe Romeo
 * @date Created:  Nov 15, 2005
 * 
 * $Header: /nfs/slac/g/glast/ground/cvs/ScienceTools-scons/orbitSim/src/read_ephem.cxx,v 1.11 2010/12/20 19:30:14 cohen Exp $
 */

#include "../include/read_ephem.h"
#include "../include/functions.h"
#include "../include/atFunctions.h"
#include "../include/GLAST_slew_estimate.h"

#include <vector>

#include <stdexcept>
#include <string>
#include <cstdio>

#include <iostream>
#include <iomanip>
#include <sstream>

#include "../include/Stream.h"
#include "../include/StreamFormatter.h"
#include "../include/st_stream.h"


  /// Stream to control output through verbosity level
st_stream::StreamFormatter osf("read_ephem", "", 2);


EphemData * allocateEphem(int num ) {

  EphemData *eph = new EphemData;

  //MJD(1), X(1), Y(1), Z(1), Lat(1), Long(1), Alt(1), VelRA(1), VelDEC(1)
  eph->MJD.resize(num);
  eph->X.resize(num);
  eph->Y.resize(num);
  eph->Z.resize(num);
  eph->Lat.resize(num);
  eph->Long.resize(num);
  eph->Alt.resize(num);
  eph->VelRA.resize(num);
  eph->VelDEC.resize(num);

  return eph;
}

EphemData * deallocateEphem(EphemData *eph) {


  eph->MJD.clear();
  eph->X.clear();
  eph->Y.clear();
  eph->Z.clear();
  eph->Lat.clear();
  eph->Long.clear();
  eph->Alt.clear();
  eph->VelRA.clear();
  eph->VelDEC.clear();

  delete eph;
  return eph;

}

Attitude * deallocateAttitude (Attitude *att) {


  att->mjd.clear();
  att->SatRA.clear();
  att->SatDEC.clear();
  att->Xra.clear();
  att->Xdec.clear();
  att->Yra.clear();
  att->Ydec.clear();
  att->Zra.clear();
  att->Zdec.clear();
  att->X.clear();
  att->Y.clear();
  att->Z.clear();
  att->Lat.clear();
  att->Lon.clear();
  att->Hei.clear();
  att->in_saa.clear();
  att->in_occ.clear();



  delete att;
  return att;

}





Attitude * allocateAttitude(int num) {

  unsigned int size = num;
  Attitude *att = new Attitude;

  osf.setMethod("allocateAttitude");
  osf.err().precision(15);
  osf.info().precision(15);
  osf.warn().precision(15);
  osf.warn().precision(15);

  osf.info(3) << "Allocating attitude vectors to " << size << " \n";


  att->mjd.resize(size);
  att->X.resize(size);
  att->Y.resize(size);
  att->Z.resize(size);
  att->SatRA.resize(size);
  att->SatDEC.resize(size);
  att->Xra.resize(size);
  att->Xdec.resize(size);
  att->Yra.resize(size);
  att->Ydec.resize(size);
  att->Zra.resize(size);
  att->Zdec.resize(size);
  att->Lat.resize(size);
  att->Lon.resize(size);
  att->Hei.resize(size);
  att->in_saa.resize(size);
  att->in_occ.resize(size);


  return att;

}

Attitude * reallocateAttitude(int num, Attitude *att) {
  att->mjd.resize(num);
  att->X.resize(num);
  att->Y.resize(num);
  att->Z.resize(num);
  att->SatRA.resize(num);
  att->SatDEC.resize(num);
  att->Xra.resize(num);
  att->Xdec.resize(num);
  att->Yra.resize(num);
  att->Ydec.resize(num);
  att->Zra.resize(num);
  att->Zdec.resize(num);
  att->Lat.resize(num);
  att->Lon.resize(num);
  att->Hei.resize(num);
  att->in_saa.resize(num);
  att->in_occ.resize(num);



  return att;

}






EphemData * yyyy_eph(FILE *ifp, double StartTime, double EndTime,
		     double Units, double Resolution) {

  int YYYY, MM, DD, HH, Min, Sec;
  int i, tyear, tmonth, tday, thour, tmin, tsec, it, iret;
  double tx, ty, tz, tlon, tlat, tmjd, latt, height, Timespan;
  //  double do_cal2mjd(int,int,int,int,int,int);
  EphemData * ephemeris = NULL;
  char line[200];
  AtPolarVect gSatP;
  AtVect vSat, gSat;
  int ipts, inum, okay;

  int ckflg = 0;
  double pmjd;
  osf.setMethod("yyyy_eph");
  
  //  StartTime = StartTime - Resolution;
  /* 
   "yyyy_eph" expects an ephemeris file input of this format:
   %d %d %d %d %d %d %lf %lf %lf %lf %lf
   YYYY MM DD HH Min SS Satellite_X_pos Satellite_Y_pos Satellite_Z_pos Lat Long
   X, Y, Z are in decimegamters and get converted to km, and Lat and Long are
   calculated (not used from the file) */



  Timespan = EndTime - StartTime;
  inum = (int)((Timespan+Resolution/2.0)/Resolution);
  inum += 2;   /* Delta plus 1 to get the end point */

  ephemeris = allocateEphem(inum);

  if (ephemeris == NULL) return(EPHNO);

  do_mjd2cal(StartTime,&YYYY,&MM,&DD,&HH,&Min, &Sec);

  i = 0;
  it = 0;

  /* types 1 and 2 have an initial line 
			   with the filename and # pts */
  iret=fscanf(ifp,"%s %d\n",line,&ipts);

  if (ipts < inum) { /* either our resolution or our file size isn't enough */
    osf.warn() << "Warning-- ephemeris does not have enough points to cover time of interest\nfound " << ipts << " points, we will still try to do the best to go on!\n";
  }


  iret=fscanf(ifp,"%d %d %d %d %d %d %lf %lf %lf %lf %lf", 
	      &tyear, &tmonth, &tday, &thour, &tmin, &tsec, &tx,&ty,&tz, &tlon,&tlat);

  tmjd = do_cal2mjd(tyear,tmonth,tday,thour,tmin,tsec);

  if(tmjd > StartTime) {

    std::ostringstream eBufT;
    eBufT << "\n" << __FILE__ << ":" << __LINE__ << ", ERROR: Ephemeredis file does not cover the entire time interval\nEphemeredis file starts at " << tmjd << " while the interval of interest starts at " << StartTime << "\nPlease check. Exiting for now........\n\n" <<std::ends;
    throw std::runtime_error(eBufT.str());

  }

  /* first, read through file until we get to start position */
  okay = 1;
  i = 0;
  while (okay) {

    iret=fscanf(ifp,"%d %d %d %d %d %d %lf %lf %lf %lf %lf", 
		&tyear, &tmonth, &tday, &thour, &tmin, &tsec, &tx,&ty,&tz, &tlon,&tlat);



    if (iret == EOF ) {
      osf.err() << "Error, ephemeris file does not reach start of schedule, exiting\n";
       return(NULL);
    }
    tmjd = do_cal2mjd(tyear,tmonth,tday,thour,tmin,tsec);


    if (tmjd >= StartTime) okay = 0;
    ++i;
  }


 /* next, read in data points, interpolating as needed */

  if (inum+i > ipts) {
    /* either our resolution or our file size isn't enough */
    osf.warn() << "Warning-- ephemeris does not have enough points to cover time of interest\nfound " << ipts << " points, we will still try to do the best to go on\n";
  }

  while (it < inum) { /* keep reading until we get to end of timespan */

    /* do appropriate conversion to make our values */
    tmjd = do_cal2mjd(tyear,tmonth,tday,thour,tmin,tsec);
    vSat[0] = tx * Units;
    vSat[1] = ty * Units;
    vSat[2] = tz * Units;


    atGeodetic(tmjd,vSat,gSat);
    atVectToPol(gSat,&gSatP);
    atEllipsoido(&gSatP,&latt,&height);
    gSatP.lat = latt;


    /* save our values and move on */
    ephemeris->MJD[it] = tmjd;


    ephemeris->X[it] = vSat[0];
    ephemeris->Y[it] = vSat[1];
    ephemeris->Z[it] = vSat[2];
    ephemeris->Lat[it] = gSatP.lat*RAD2DEG;
    ephemeris->Long[it] = gSatP.lon*RAD2DEG;
    ephemeris->Alt[it] = height;

    /* now read through the file until we either run out of points, or
       get the next element of time Resolution away from our current
       reference point */
    iret = fscanf(ifp,"%d %d %d %d %d %d %lf %lf %lf %lf %lf", &tyear, &tmonth,
	   &tday, &thour, &tmin, &tsec, &tx,&ty,&tz, &tlon,&tlat);


    if (iret == EOF) {
      osf.err() <<"Error, ephemeris file does not reach end of schedule, exiting\n";
      return(NULL);
    }

    ++i;

    ++it;
    if(ckflg < 3){
      ckflg++;
    }
    
    // Check the time resolution of the file
    // only after the third row has been read in.
    if(ckflg == 2) {
      double dt = tmjd - pmjd;
      if(fabs(dt-Resolution) > 1.0e-10){
	std::ostringstream eBufT;
	eBufT << "\n" << __FILE__ << ":" << __LINE__ << ", ERROR: The Ephemeris file does not have the requested time resolution.\nPlease, check it! Exiting now........\n\n"<<std::ends;
	throw std::runtime_error(eBufT.str());

      }
    }



    pmjd = tmjd;

  }

  /* ephemeris->Period = Period; */
  ephemeris->SemiMajorAxis = 0;
  ephemeris->Period = 0;
  ephemeris->ent = inum;

  fflush(stdout);
  return(ephemeris);

}




/* CKS: The xyzll_eph routine was written to ingest the STK generated ephemeris for Swift.
   It is similiar to the yyyy_eph routine.  The differences include a comment line as 
   the first line of data from STK and the lattitude and longitude will be used 
   directly from the STK data.  The altitude will be calculated, but is not currently
   planned to be used.

   The time format is also different, Swift will use a UTCJ format: doy/year HH:MM:SS.ss.
   Swift ephem also includes the velocity RA and DEC of the satellite. 
*/ 

EphemData * xyzll_eph(FILE *ifp, double StartTime, double EndTime,
		     double Units, double Resolution) {

  
  int i, tyear, tdoy, thour, tmin, it, iret, isec;
  double tsec, tx, ty, tz, tlon, tlat, mjd, latt, height, Timespan;
  double tvra, tvdec;
  int rez_check;
  double mjd1, rez;
 
  //  double do_utcj2mjd(int,int,int,int,int);
  EphemData * ephemeris = NULL; 
  char *r;
  AtPolarVect gSatP;
  AtVect vSat, gSat;
  int inum, okay;
  const int lnsz = 200;
  char line[lnsz];

  osf.setMethod("xyzll_eph");

  /* 
   "xyzll_eph" expects an ephemeris file input of this format:
   %d/%d %d:%d:%lf %lf %lf %lf %lf %lf %lf %lf
   DOY/YYYY HH:Min:SS.s Satellite_X_pos Satellite_Y_pos Satellite_Z_pos Lat Long veocity_ra velocity_dec
   X, Y, Z are in  km, and Lat and Long (degrees) used, velocity Ra and Dec (degrees) and Altitude is 
   calculated  */


 
  rez_check = 1;
  mjd1 = 0.0;
  
  Timespan = EndTime - StartTime;

  inum = (int)((Timespan+(Resolution/2.))/Resolution);  // round up
  inum+=2;   // include the end point in the count


  /* number of units of resolution we need */
  ephemeris = allocateEphem(inum);



  i = 0;
  it = 0;

  /* The first line in xyzll_eph formatted file is a comment line */
 
			   
  r=fgets(line, lnsz, ifp);  /* read line and ignore */
  if (r == NULL) {
    osf.err() << "xyzll_eph: Error, ephemeris file is empty, exiting\n";
    return EPHNO;
  }
 
  /* first, read through file until we get to start position */
  okay = 1;
  i = 0;
  while (okay) {
    iret = fscanf(ifp,"%d/%d %d:%d:%lf %lf %lf %lf %lf %lf %lf %lf", &tdoy, &tyear,
       &thour, &tmin, &tsec, &tx,&ty,&tz, &tlat, &tlon, &tvra, &tvdec);
    if (iret == EOF) {
      osf.err() << "xyzll_eph: Error, ephemeris file does not reach start of schedule, exiting\n";
      return EPHNO;
    }

    /* round seconds */
    isec = (int) (tsec + 0.5);

    mjd = do_utcj2mjd(tyear,tdoy,thour,tmin, isec);

 
    if (mjd1 == 0) mjd1 = mjd;

    /* Check if StartTime is prior to ephemeris data */

    if  ((i == 0) && (StartTime < (mjd - Resolution))) {
      osf.err() << "xyzll_eph: Error, StartTime (" << StartTime << ") is prior to ephemeris data (" << (mjd-Resolution) << ").  Exiting.\n";
      return (EPHNO);
    }
      
    /* Check that the ephemeris resolution is the same as the TAKO resolution (within 3 seconds */
    if ((rez_check) && (mjd != mjd1)) {
      rez = mjd - mjd1;
      if (fabs(Resolution - rez) < .00003472222222) {
        /* it's good */
 
        rez_check = 0;
      } else {
 
        osf.err() << "xyzll_eph: Error, the ephemeris resolution (" << rez << ") is NOT the same as the Tako Resolution (" << Resolution << "). Exiting.\n" << "The times compared were:  MJD= " << mjd1 << " and MJD1= " << mjd << "\n";
	return (EPHNO);
      }

    }

    if (mjd >= StartTime) okay = 0;
    ++i;
  }

  

 


 /* next, read in data points */

  while (it < inum) { /* keep reading until we get to end of timespan */

    /* do appropriate conversion to make our values */
    double tmjd = do_utcj2mjd(tyear,tdoy,thour,tmin, isec);


    /* Check that the ephemeris resolution is the same as the TAKO resolution (within 3 seconds */
    if ((rez_check) && (tmjd != mjd1)) {
      rez = tmjd - mjd1;
      if (fabs(Resolution - rez) < .00003472222222) {
        /* it's good */
 
        rez_check = 0;
      } else {
 
        osf.err() << "xyzll_eph: Error, the ephemeris resolution (" << rez << ") is NOT the same as the Tako Resolution (" << Resolution << "). Exiting.\n" << "The times compared were:  MJD= " << mjd1 << " and MJD1= " << tmjd << "\n";
	return (EPHNO);
      }
    }



    vSat[0] = tx * Units;
    vSat[1] = ty * Units;
    vSat[2] = tz * Units;

    atGeodetic(tmjd,vSat,gSat); 
    atVectToPol(gSat,&gSatP);
    atEllipsoido(&gSatP,&latt,&height);
    gSatP.lat = latt;

    //if (tlon < 0) tlon = tlon + 360.0;

    ephemeris->MJD[it] = tmjd;
    ephemeris->X[it] = vSat[0];
    ephemeris->Y[it] = vSat[1];
    ephemeris->Z[it] = vSat[2];

    ephemeris->Lat[it] = tlat;
    ephemeris->Long[it] = tlon;
    ephemeris->Alt[it] = height;
    ephemeris->VelRA[it] = tvra;
    ephemeris->VelDEC[it] = tvdec;


    /* now read the next line of data */
      
    iret = fscanf(ifp,"%d/%d %d:%d:%lf %lf %lf %lf %lf %lf %lf %lf", &tdoy, &tyear,
	   &thour, &tmin, &tsec, &tx,&ty,&tz,&tlat, &tlon, &tvra, &tvdec);

    if (iret == EOF) {
      osf.err() << "xyzll_eph: Error, ephemeris file does not reach end of schedule, exiting\n";
      return EPHNO;
    }

    /* round seconds */
    isec = (int) (tsec + 0.5);

    ++i;

    ++it;

  }


  /* ephemeris->Period = Period; */
  ephemeris->SemiMajorAxis = 0;
  ephemeris->Period = 0;
  ephemeris->ent = inum;



  return(ephemeris);

}



EphemData * tlederive(FILE *ifp, double StartTime,
		      double EndTime, double Units, double Resolution, std::string SSatN) {

  EphemData * ephemeris = NULL;

  double Timespan;
  double latt, height;
  AtVect vSat, gSat;
  AtPolarVect gSatP;
  vector pos, vel;

  double temp;
  //  char *SatN  = "DAMPE";  // TLE satellite name is 5 characters
  //char *SatN2 = "DAMPE";  // This is the name used in NORAD file
  char *Sout;
  Sout = new char[SSatN.length() + 1];
  std::strcpy(Sout,SSatN.c_str());
  char *SatN =Sout;
  char *SatN2 = SatN;
  int it, nit;
  double mjd;

  //  const int Nlines = 4000;
  const int Nlines = 3;
  const int bufsiz = 100;
  char ln[Nlines][bufsiz];// = {"\0"};
  char tec[bufsiz];

  int  inum, istatus = 0;

  atElemTle Tle;
  AtTime tz;

  double tsince, tdif;
  int is = 0;
  int il = 0;

  int flgNam = 0;
  int slen;
  double resol;      // resolution in minutes

  // Minutes in one day;


  osf.setMethod("tlederive");




  Timespan = EndTime - StartTime;
  inum = (int)((Timespan+Resolution/2.0)/Resolution); // round up
  inum++;   // include the end point in the count  

  osf.info(2) << "Ephemeris will contain inum=" << inum << " points\n";
  std::cout << "Ephemeris will contain inum=" << inum << " points\n" << std::endl;

  slen = strlen(SatN);

  while (fgets(tec,bufsiz,ifp)) {

    if(strncmp(SatN, tec, slen) ==0){
      strcpy(ln[il++],tec);
      fgets(tec,bufsiz,ifp);
      strcpy(ln[il++],tec);
      fgets(tec,bufsiz,ifp);
      strcpy(ln[il++],tec);
      flgNam = 1;
      break;
    }
    if(strncmp(SatN2, tec, slen) ==0){
      strcpy(ln[il++],tec);
      fgets(tec,bufsiz,ifp);
      strcpy(ln[il++],tec);
      fgets(tec,bufsiz,ifp);
      strcpy(ln[il++],tec);
      flgNam = 1;
      // Make sure SatN contains the name we found.
      SatN=SatN2;
      break;
    }

  }

  if(flgNam == 0){
    osf.err() << "Error: Satellite " << SatN << " or " << SatN2 << " is NOT present in the TLE file\nPlease, check it and try again\n\n";
    std::cout <<"Error: Satellite " << SatN << " or " << SatN2 << " is NOT present in the TLE file\nPlease, check it and try again\n\n" << std::endl;
    return(EPHNO);
  }

  ephemeris = allocateEphem(inum);




  // resol is the time resolution in minutes
  resol = Resolution*minInDay;

  istatus = readTLE(Nlines, SatN, ln, &Tle, StartTime, EndTime, resol); 
     
  //std::cout << "istatus " << istatus << std::endl;

  if (istatus == 1) {

    tdif = (StartTime-Tle.mjd)*minInDay+Tle.isc;

    int itdif = (int)((tdif-(double)((int)tdif))*60.0);
    if(itdif > resol*60.0){
      itdif = (int)(resol*60.0);
    }
/*
    tdif += resol;
    if(tdif > resol)
      tdif -= resol;
*/
    tz.yr = Tle.tm.yr;
    tz.mo = Tle.tm.mo;
    tz.dy = Tle.tm.dy;
    tz.hr = Tle.tm.hr;
    tz.mn = Tle.tm.mn+(int)tdif;
    //    tz.sc = 0;
    tz.sc = itdif;

    temp   = TWO_PI/_xmnpda/_xmnpda;
    Tle.xndt2o = Tle.xndt2o*temp;
    Tle.xndd6o = Tle.xndd6o*temp/_xmnpda;
    Tle.xincl  = Tle.xincl*DEG2RAD;
    Tle.xnodeo = Tle.xnodeo*DEG2RAD;
    Tle.omegao = Tle.omegao*DEG2RAD;
    Tle.xmo    = Tle.xmo*DEG2RAD;   
    Tle.xno    = Tle.xno*temp*_xmnpda;    

    it = 0;

    //    correctTm(&tz);
    //    atMJulian(&tz,&mjd);


    mjd = StartTime;

    while (it < inum) { 
      tsince = tdif+(double)it * resol;
      sgp4(tsince, &pos, &vel, &Tle);
      /* do appropriate conversion to make our values */
      //      mjd = do_cal2mjd(tyear,tmonth,tday,thour,tmin);
      
      /**/
      if(pos.v[0] == 0.0 && pos.v[1] == 0.0 && pos.v[0] == 0.0)
	osf.warn() << "at Sat#=" << is << "X=" << pos.v[0]* xkmper << ", Y=" << pos.v[1]* xkmper << ",Z=" << pos.v[2]* xkmper << ", the position vector is null \n";
      //printf("%4d %02d %02d %02d %02d %05d %f %f %f %f\n",tz.yr, tz.mo, tz.dy, tz.hr, tz.mn, tz.sc, pos.v[0]* xkmper, pos.v[1]* xkmper, pos.v[2]* xkmper, Units); 1

/*
      if(it < 0)
	printf("%4d %02d %02d %02d %02d %05d %f %f %f %f\n",tz.yr, tz.mo, tz.dy, tz.hr, tz.mn, tz.sc, pos.v[0]* xkmper, pos.v[1]* xkmper, pos.v[2]* xkmper, Units);
*/

      //  break;
      
      vSat[0] = pos.v[0] * Units * xkmper;
      vSat[1] = pos.v[1] * Units * xkmper;
      vSat[2] = pos.v[2] * Units * xkmper;
      
      atGeodetic(mjd,vSat,gSat);
      atVectToPol(gSat,&gSatP);
      atEllipsoido(&gSatP,&latt,&height);
      gSatP.lat = latt;

      /* save our values and move on */

      nit = it;

      ephemeris->MJD[it] = mjd;

      ephemeris->X[it] = vSat[0];
      ephemeris->Y[it] = vSat[1];
      ephemeris->Z[it] = vSat[2];
      ephemeris->Lat[it] = gSatP.lat*RAD2DEG;
      ephemeris->Long[it] = gSatP.lon*RAD2DEG;
      ephemeris->Alt[it] = height;

      ++it;

      mjd += resol/minInDay;

      
    }

    /* ephemeris->Period = Period; */
    ephemeris->SemiMajorAxis = 0;
    ephemeris->Period = 0;
    ephemeris->ent = inum;


  }else{

    deallocateEphem(ephemeris);
    return(EPHNO);  /* AMake it clear that there is a problem */

  }

  return(ephemeris);
}







void MakeAtt(double start, double mjde, double mjds, double pra, 
	     double pdec, double offset, double ra, double dec, int mode, 
	     double res, EphemData *ephem, double *lpos, Attitude *OAtt, double TS ) {



//  if the mode is 1, i.e. survey mode, then the final point for
//  slewing must be calculated


  double Timespan = mjde - start;
  int inum = (int)((Timespan+res/2.0)/res);
  inum++;   // Delta plus 1 to get the end point 


  int oas = (int)(((mjde-TS)+res/2.0)/res);
  int flgS = 0;
  Attitude *TOAtt = allocateAttitude(oas);


  double tim = start;

  osf.setMethod("makeAtt");



  if (mode == 1 && start < mjds){
    oas += 2;
    TOAtt = reallocateAttitude(oas, TOAtt);
    double RaDec[2];
    TOAtt->ent = oas;
    osf.info(3) <<"Calling MakeSurvey("<<start-res<<", "<<mjde+res<<", "<<res<<", "<<offset<<"\n";
    MakeSurvey(tim, mjde+res, res, offset, ephem, TOAtt, RaDec, 1, TS);

    int es = (int)(((mjds-TS)+res/2.0)/res);
    ra  = TOAtt->Zra[es];
    dec = TOAtt->Zdec[es];

    osf.info(3) <<"ra="<<ra<<", dec="<<dec<<"\n";

    flgS = 1;

  }


  if(start < mjds) {
    DoSlew(start, mjds, pra, pdec, ra, dec, res, ephem, OAtt, TS);
  }

  //  printf ("2) i=45 ==> mjd=%f, i=46 ==> mjd=%f\n", OAtt->mjd[45], OAtt->mjd[46]);
  if(mode == 1) {
    if(flgS == 0){
      double RaDec[2];// = NULL;
      MakeSurvey(mjds, mjde, res, offset, ephem, OAtt, RaDec, 1, TS);

      int k = (int) (((mjde-TS)+res/2.0)/res);
      lpos[0] = OAtt->Zra[k];
      lpos[1] = OAtt->Zdec[k];
    } else {

      int k = (int) (((mjde-TS)+res/2.0)/res);
      int j = (int) (((mjds-TS)+res/2.0)/res);

      int ii;
      for(ii=j; ii<k; ii++){

	OAtt->mjd[ii]    = TOAtt->mjd[ii];
	OAtt->SatRA[ii]  = TOAtt->SatRA[ii];
	OAtt->SatDEC[ii] = TOAtt->SatDEC[ii];
	OAtt->Xra[ii]    = TOAtt->Xra[ii];
	OAtt->Xdec[ii]   = TOAtt->Xdec[ii];
	OAtt->Yra[ii]    = TOAtt->Yra[ii];
	OAtt->Ydec[ii]   = TOAtt->Ydec[ii];
	OAtt->Zra[ii]    = TOAtt->Zra[ii];
	OAtt->Zdec[ii]   = TOAtt->Zdec[ii];


	osf.info(6) <<"ii="<<ii<<", Zra="<<TOAtt->Zra[ii]<<", Zdec="<<TOAtt->Zdec[ii]<<"\n";	
      }
      lpos[0] = TOAtt->Zra[k-1];
      lpos[1] = TOAtt->Zdec[k-1];
    }
  } else {
    MakePointed(mjds, mjde, res, ra, dec, ephem, OAtt, TS);
    lpos[0] = ra;
    lpos[1] = dec;
  }
  TOAtt = deallocateAttitude(TOAtt);

  osf.info(3) << "\nLeaving MakeAtt with lpos[0]="<<lpos[0]<<", lpos[1]="<<lpos[1]<<"\n\n\n";

//   if(mjds > 54433.2) {
//     exit(0);
//   }
  

  return;
}





/*
void MakeAtt(double start, double mjde, double mjds, double pra, 
	     double pdec, double offset, double ra, double dec, int mode, 
	     double res, EphemData *ephem, double *lpos, Attitude *OAtt, double TS ) {



//  if the mode is 1, i.e. survey mode, then the final point for
//  slewing must be calculated


  double Timespan = mjde - start;
  int inum = (int)((Timespan+res/2.0)/res);
  inum++;   // Delta plus 1 to get the end point 


  int oas = (int)(((mjde-TS)+res/2.0)/res);
  int flgS = 0;
  Attitude *TOAtt = allocateAttitude(oas);
  if (mode == 1 && start < mjds){
    oas += 2;
    TOAtt = reallocateAttitude(oas, TOAtt);
    double RaDec[2];
    TOAtt->ent = oas;
    MakeSurvey(TS, mjde+res, res, offset, ephem, TOAtt, RaDec, 1, TS);

    int es = (int)(((mjds-TS)+res/2.0)/res);
    ra  = TOAtt->Zra[es];
    dec = TOAtt->Zdec[es];

    flgS = 1;

  }

  osf.setMethod("makeAtt");


  if(start < mjds) {
    DoSlew(start, mjds, pra, pdec, ra, dec, res, ephem, OAtt, TS);
  }

  //  printf ("2) i=45 ==> mjd=%f, i=46 ==> mjd=%f\n", OAtt->mjd[45], OAtt->mjd[46]);
  if(mode == 1) {
    if(flgS == 0){
      double RaDec[2];// = NULL;
      MakeSurvey(mjds, mjde, res, offset, ephem, OAtt, RaDec, 1, TS);

      int k = (int) (((mjde-TS)+res/2.0)/res);
      lpos[0] = OAtt->Zra[k];
      lpos[1] = OAtt->Zdec[k];
    } else {

      int k = (int) (((mjde-TS)+res/2.0)/res);
      int j = (int) (((mjds-TS)+res/2.0)/res);
      int ii;

      for(ii=j; ii<k; ii++){

	OAtt->mjd[ii]    = TOAtt->mjd[ii];
	OAtt->SatRA[ii]  = TOAtt->SatRA[ii];
	OAtt->SatDEC[ii] = TOAtt->SatDEC[ii];
	OAtt->Xra[ii]    = TOAtt->Xra[ii];
	OAtt->Xdec[ii]   = TOAtt->Xdec[ii];
	OAtt->Yra[ii]    = TOAtt->Yra[ii];
	OAtt->Ydec[ii]   = TOAtt->Ydec[ii];
	OAtt->Zra[ii]    = TOAtt->Zra[ii];
	OAtt->Zdec[ii]   = TOAtt->Zdec[ii];

	osf.info(3) <<"ii="<<ii<<", Zra="<<TOAtt->Zra[ii]<<", Zdec="<<TOAtt->Zdec[ii]<<"\n";
      }
      lpos[0] = TOAtt->Zra[k-1];
      lpos[1] = TOAtt->Zdec[k-1];
    }
  } else {
    MakePointed(mjds, mjde, res, ra, dec, ephem, OAtt, TS);
    lpos[0] = ra;
    lpos[1] = dec;
  }
  TOAtt = deallocateAttitude(TOAtt);

  osf.info(3) << "\nLeaving MakeAtt with lpos[0]="<<lpos[0]<<", lpos[1]="<<lpos[1]<<"\n\n\n";


  return;
}
*/





void MakeAtt2(double start, double mjde, double pra, double pdec, 
	      double offset, double ra, double dec, int mode, double res, 
	      EphemData *ephem, double *lpos, Attitude *OAtt, double TS ){


/*
  if the mode is 1, i.e. survey mode, then the final point for
  slewing and slew time must be calculated 
*/

  double mjds = start;
  double Timespan = mjde - start;
  int inum = (int)((Timespan+res/2.0)/res);
  inum++;   /* Delta plus 1 to get the end point */

  double slt = 0.0;
  double pslt = 0.0;
  if (mode == 1 ){
    do {
      pslt = slt;
      double RaDec[2];
      MakeSurvey(mjds, (mjds+res), res, offset, ephem, OAtt, RaDec, 0, TS);

      ra = RaDec[0];
      dec = RaDec[1];
      //      printf("pra=%f, ra=%f,   pdec=%f, dec=%f\n", pra, ra, pdec, dec);
      if(pra == ra && pdec == dec){
	mjds = start;
	slt = 0.0;
	pslt = slt;
      } else {
	getslewtime(pra, pdec, ra, dec, res, &slt);
	slt = slt/res;
	slt = (double)((int)(slt+0.5))*res;
      }
      mjds = start+slt;
    } while ((slt - pslt) > res/2.0);
  } else if (mode == 2) {
      if(pra == ra && pdec == dec){
	mjds = start;
	slt = 0.0;
	pslt = slt;
      } else {
	getslewtime(pra, pdec, ra, dec, res, &slt);
	slt = slt/res;
	slt = (double)((int)(slt+0.5))*res;
      }
      mjds = start+slt;
  }


  if(start < mjds) {
    DoSlew(start, mjds, pra, pdec, ra, dec, res, ephem, OAtt, TS);
  }

  if(mode == 1) {
    double RaDec[2];// = NULL; 
    MakeSurvey(mjds, mjde, res, offset, ephem, OAtt, RaDec, 2, TS);
    int k = (int) (((mjde-TS)+res/2.0)/res);
    lpos[0] = OAtt->Zra[k];
    lpos[1] = OAtt->Zdec[k];
  } else {
    MakePointed(mjds, mjde, res, ra, dec, ephem, OAtt, TS);
    lpos[0] = ra;
    lpos[1] = dec;
  }

  return;
}




void MakeSurvey(double start, double end, double res, double offset, 
		EphemData *ephem, Attitude *OAtt, double *rd, int mode, double TS) {


  AtVect vSat, vbSat, vaSat, vVelS;
  AtVect vNSat, vNbSat, vNaSat, vNVelS;
  double mjd, amjd, bmjd;

  double RaDe[11];
  int i, inum, k;
  double sra, sdec, zra, zdec, yra, ydec, xra, xdec, sunx, suny, sunz, suna, sunxy;

  int j = 0;


  int ii, is, jj, ij;
  const int SunAvPts = 10;
  int RemSunPts = 0;
  int SSunPts, TSunPts;
  double TOfs = 18.25*DEG2RAD;
  double IncTOfs;
  double SunSurvOfs = 0.0;
  int flgDir = 0;
  double dk;


  inum = (int) ((end-start+res/2.)/res);
  inum++;

/*
  if(mode != 2){
    int l = 0;
    for(l=0; l<inum-2; l++){
      OAtt->mjd[l] = 0.0;
    }
  }
*/

//offset = -offset*DEG2RAD;
  offset =  offset*DEG2RAD;

  j = 0;
  
  mjd = ephem->MJD[j];

  //  printf ("4) i=45 ==> mjd=%f, i=46 ==> mjd=%f\n", OAtt->mjd[45], OAtt->mjd[46]);

  if(fabs (mjd- start) > 1.0E-6  ) {
    while((mjd < start) && (j < ephem->ent)){
      if(fabs(mjd-start) < 1E-6 ){
	break;
      }
      mjd = ephem->MJD[++j];
    }
  }


  k =(int) (((start-TS)+res/2.0)/res);


  for (i=j;i<inum+j;++i) {
    /* Get the satellite vector in ECI */


    mjd = ephem->MJD[i];    
    vSat[0] = ephem->X[i]; 
    vSat[1] = ephem->Y[i];
    vSat[2] = ephem->Z[i]; 

    if(i+1 >= ephem->ent ) { // Mind the boundaries 
      amjd = mjd + res;
      vaSat[0] = InterPVect(mjd, amjd, vSat[0], vbSat[0], amjd);
      vaSat[1] = InterPVect(mjd, amjd, vSat[1], vbSat[1], amjd);
      vaSat[2] = InterPVect(mjd, amjd, vSat[2], vbSat[2], amjd);
    } else {
      amjd     = ephem->MJD[i+1];
      vaSat[0] = ephem->X[i+1];
      vaSat[1] = ephem->Y[i+1];
      vaSat[2] = ephem->Z[i+1];
    }

    if(i == 0){  // if i-1 < 0
      bmjd     = mjd - res;
      vbSat[0] = InterPVect(mjd, amjd, vSat[0], vaSat[0], bmjd);
      vbSat[1] = InterPVect(mjd, amjd, vSat[1], vaSat[1], bmjd);
      vbSat[2] = InterPVect(mjd, amjd, vSat[2], vaSat[2], bmjd);

    } else {
      bmjd     = ephem->MJD[i-1];
      vbSat[0] = ephem->X[i-1];
      vbSat[1] = ephem->Y[i-1];
      vbSat[2] = ephem->Z[i-1];

    }


    atNormVect(vSat, vNSat);  /* normalize vector vSat */
    atNormVect(vbSat, vNbSat);  /* normalize vector vbSat */
    atNormVect(vaSat, vNaSat);  /* normalize vector vaSat */

    vVelS[0] = (vNaSat[0] - vNbSat[0])/(2.0*res);
    vVelS[1] = (vNaSat[1] - vNbSat[1])/(2.0*res);
    vVelS[2] = (vNaSat[2] - vNbSat[2])/(2.0*res);
    atNormVect(vVelS, vNVelS);  /* normalize vector vaSat */



    GetPos(mjd, vSat, vNVelS, offset, RaDe);


    sra   = RaDe[0];
    sdec  = RaDe[1];
    zra   = RaDe[2];
    zdec  = RaDe[3];
    yra   = RaDe[4];
    ydec  = RaDe[5]; 
    xra   = RaDe[6];
    xdec  = RaDe[7];
    sunx  = RaDe[8]; 
    suny  = RaDe[9]; 
    sunz  = RaDe[10]; 

    if(mode == 0){
      rd[0] = zra;
      rd[1] = zdec;
      return;
    }


    OAtt->mjd[k]    = mjd;
    OAtt->SatRA[k]  = sra;
    OAtt->SatDEC[k] = sdec;
    OAtt->Xra[k]    = xra;
    OAtt->Xdec[k]   = xdec;
    OAtt->Yra[k]    = yra;
    OAtt->Ydec[k]   = ydec;
    OAtt->Zra[k]    = zra;
    OAtt->Zdec[k]   = zdec;



    k++;

    if(k >=inum+j){
      break;
    }



/*******************************************************************************

    Here we check if the sunangle with the Body Z_axis is smaller than
    10 degrees for the next data point; if the case, we start the Sun
    avoidance manuevering, and the resume


*******************************************************************************/

    ii = i+1;

    if (ii >= j+inum || ii >= ephem->ent){
      break;
    }

    // Don't let ii be greater than or equal to  inum
    //  There are only inum points in the array
    //   The index range is (0 to inum-1)

    /* Get the satellite vector in ECI */
    mjd = ephem->MJD[ii];    
    vSat[0] = ephem->X[ii]; 
    vSat[1] = ephem->Y[ii];
    vSat[2] = ephem->Z[ii];  

    bmjd     = ephem->MJD[ii-1];
    vbSat[0] = ephem->X[ii-1];
    vbSat[1] = ephem->Y[ii-1];
    vbSat[2] = ephem->Z[ii-1];

    if(ii+1 >= ephem->ent ) { // Mind the boundaries 
      amjd = mjd + res;
      vaSat[0] = InterPVect(mjd, amjd, vSat[0], vbSat[0], amjd);
      vaSat[1] = InterPVect(mjd, amjd, vSat[1], vbSat[1], amjd);
      vaSat[2] = InterPVect(mjd, amjd, vSat[2], vbSat[2], amjd);
    } else {
      amjd     = ephem->MJD[ii+1];
      vaSat[0] = ephem->X[ii+1];
      vaSat[1] = ephem->Y[ii+1];
      vaSat[2] = ephem->Z[ii+1];
    }



    atNormVect(vSat, vNSat);  /* normalize vector vSat */
    atNormVect(vbSat, vNbSat);  /* normalize vector vbSat */
    atNormVect(vaSat, vNaSat);  /* normalize vector vaSat */

    vVelS[0] = (vNaSat[0] - vNbSat[0])/(2.0*res);
    vVelS[1] = (vNaSat[1] - vNbSat[1])/(2.0*res);
    vVelS[2] = (vNaSat[2] - vNbSat[2])/(2.0*res);
    atNormVect(vVelS, vNVelS);  /* normalize vector vaSat */


    GetPos(mjd, vSat, vNVelS, offset, RaDe);
 

    sra   = RaDe[0];
    sdec  = RaDe[1];
    zra   = RaDe[2];
    zdec  = RaDe[3];
    yra   = RaDe[4];
    ydec  = RaDe[5]; 
    xra   = RaDe[6];
    xdec  = RaDe[7];
    sunx  = RaDe[8]; 
    suny  = RaDe[9]; 
    sunz  = RaDe[10];

    sunxy = sqrt(sunx*sunx+suny*suny);
    suna = atan2(sunxy,sunz);
    suna = suna*RAD2DEG;


    if((fabs(suna) <= 10.0 || fabs(suna) >= 170.0) && (ii+1 < j+inum)){
    //if(fabs(suna) <= 0.0){
      is = 0;
      ii++;
      while((fabs(suna) <= 10.0 || fabs(suna) >= 170.0) && (ii < ephem->ent)){ 
	is++;


	mjd = ephem->MJD[ii];    
	vSat[0] = ephem->X[ii]; 
	vSat[1] = ephem->Y[ii];
	vSat[2] = ephem->Z[ii];
  
	bmjd     = ephem->MJD[ii-1];
	vbSat[0] = ephem->X[ii-1];
	vbSat[1] = ephem->Y[ii-1];
	vbSat[2] = ephem->Z[ii-1];

	if(ii+1 >= ephem->ent ) { // Mind the boundaries 
	  amjd = mjd + res;
	  vaSat[0] = InterPVect(mjd, amjd, vSat[0], vbSat[0], amjd);
	  vaSat[1] = InterPVect(mjd, amjd, vSat[1], vbSat[1], amjd);
	  vaSat[2] = InterPVect(mjd, amjd, vSat[2], vbSat[2], amjd);
	} else {
	  amjd     = ephem->MJD[ii+1];
	  vaSat[0] = ephem->X[ii+1];
	  vaSat[1] = ephem->Y[ii+1];
	  vaSat[2] = ephem->Z[ii+1];
	}



	atNormVect(vSat, vNSat);  /* normalize vector vSat */
	atNormVect(vbSat, vNbSat);  /* normalize vector vbSat */
	atNormVect(vaSat, vNaSat);  /* normalize vector vaSat */

	vVelS[0] = (vNaSat[0] - vNbSat[0])/(2.0*res);
	vVelS[1] = (vNaSat[1] - vNbSat[1])/(2.0*res);
	vVelS[2] = (vNaSat[2] - vNbSat[2])/(2.0*res);
	atNormVect(vVelS, vNVelS);  /* normalize vector vaSat */

	GetPos(mjd, vSat, vNVelS, offset, RaDe);

	sra   = RaDe[0];
	sdec  = RaDe[1];
	zra   = RaDe[2];
	zdec  = RaDe[3];
	yra   = RaDe[4];
	ydec  = RaDe[5]; 
	xra   = RaDe[6];
	xdec  = RaDe[7];
	sunx  = RaDe[8]; 
	suny  = RaDe[9]; 
	sunz  = RaDe[10];

	sunxy = sqrt(sunx*sunx+suny*suny);
	suna = atan2(sunxy,sunz);
	suna = suna*RAD2DEG; 
	ii++;     
      }

      if(is >= SunAvPts){
	SSunPts = i + 1;
	TSunPts = is;
      }else if(is < SunAvPts){
	RemSunPts = SunAvPts - is;
	SSunPts = i + 1 - (int)(((float)RemSunPts/2.0+0.05));
	TSunPts = SunAvPts;
      }

/*******************************************************************************

   We need to decide which way around the Sun we must go, in other words
   we can either subtract or add to the Survey OffSet. We will try both,
   and based on the result, we will decide what to do!

*******************************************************************************/


      ii = i+is/2;

      if(ii <= 0)
	ii = 1;

      mjd = ephem->MJD[ii];    
      vSat[0] = ephem->X[ii]; 
      vSat[1] = ephem->Y[ii];
      vSat[2] = ephem->Z[ii];
  
      bmjd     = ephem->MJD[ii-1];
      vbSat[0] = ephem->X[ii-1];
      vbSat[1] = ephem->Y[ii-1];
      vbSat[2] = ephem->Z[ii-1];

      if(ii+1 >= ephem->ent ) { // Mind the boundaries 
	amjd = mjd + res;
	vaSat[0] = InterPVect(mjd, amjd, vSat[0], vbSat[0], amjd);
	vaSat[1] = InterPVect(mjd, amjd, vSat[1], vbSat[1], amjd);
	vaSat[2] = InterPVect(mjd, amjd, vSat[2], vbSat[2], amjd);
      } else {
	amjd     = ephem->MJD[ii+1];
	vaSat[0] = ephem->X[ii+1];
	vaSat[1] = ephem->Y[ii+1];
	vaSat[2] = ephem->Z[ii+1];
      }




      atNormVect(vSat, vNSat);  /* normalize vector vSat */
      atNormVect(vbSat, vNbSat);  /* normalize vector vbSat */
      atNormVect(vaSat, vNaSat);  /* normalize vector vaSat */

      vVelS[0] = (vNaSat[0] - vNbSat[0])/(2.0*res);
      vVelS[1] = (vNaSat[1] - vNbSat[1])/(2.0*res);
      vVelS[2] = (vNaSat[2] - vNbSat[2])/(2.0*res);
      atNormVect(vVelS, vNVelS);  /* normalize vector vaSat */


      SunSurvOfs = offset+TOfs;
      GetPos(mjd, vSat, vNVelS, SunSurvOfs, RaDe);

      sra   = RaDe[0];
      sdec  = RaDe[1];
      zra   = RaDe[2];
      zdec  = RaDe[3];
      yra   = RaDe[4];
      ydec  = RaDe[5]; 
      xra   = RaDe[6];
      xdec  = RaDe[7];
      sunx  = RaDe[8]; 
      suny  = RaDe[9]; 
      sunz  = RaDe[10];

      sunxy = sqrt(sunx*sunx+suny*suny);
      suna = atan2(sunxy,sunz);
      suna = suna*RAD2DEG;


      if(fabs(suna) <= 90.0){
	flgDir = 0;
      }else{
	flgDir = 1;
      }

      IncTOfs = TOfs / TSunPts;
      dk = .50;
      SunSurvOfs = offset;

      if(SSunPts <= 0){
	SSunPts = 1;
	TSunPts++;
      }
      ij = 0;
      SSunPts--;
      k = SSunPts;

      TOfs = 18.5*DEG2RAD;

      for(jj=SSunPts; jj<SSunPts+TSunPts; jj++){

	if(jj > inum+j ){
	  break;
	}

	IncTOfs = acos(((double)TSunPts/2.0-dk)/((double)TSunPts/2.0));
	IncTOfs = (jj-SSunPts)*180.0*DEG2RAD/TSunPts;

/*
   Now based on Direction above found, we will decide
   wether we need to subtract or add to the Survey
   Offset
*/
	if(flgDir == 1){
	  SunSurvOfs = offset-TOfs*sin(IncTOfs)*sqrt(fabs(sin(IncTOfs)));
	}else{
	  SunSurvOfs = offset+TOfs*sin(IncTOfs)*sqrt(fabs(sin(IncTOfs)));
	}


	mjd = ephem->MJD[jj];    
	vSat[0] = ephem->X[jj]; 
	vSat[1] = ephem->Y[jj];
	vSat[2] = ephem->Z[jj];
  
	bmjd     = ephem->MJD[jj-1];
	vbSat[0] = ephem->X[jj-1];
	vbSat[1] = ephem->Y[jj-1];
	vbSat[2] = ephem->Z[jj-1];

	if(jj+1 >= ephem->ent ) { // Mind the boundaries 
	  amjd = mjd + res;
	  vaSat[0] = InterPVect(mjd, amjd, vSat[0], vbSat[0], amjd);
	  vaSat[1] = InterPVect(mjd, amjd, vSat[1], vbSat[1], amjd);
	  vaSat[2] = InterPVect(mjd, amjd, vSat[2], vbSat[2], amjd);
	} else {
	  amjd     = ephem->MJD[jj+1];
	  vaSat[0] = ephem->X[jj+1];
	  vaSat[1] = ephem->Y[jj+1];
	  vaSat[2] = ephem->Z[jj+1];
	}


	atNormVect(vSat, vNSat); 
	atNormVect(vbSat, vNbSat); 
	atNormVect(vaSat, vNaSat); 

	vVelS[0] = (vNaSat[0] - vNbSat[0])/(2.0*res);
	vVelS[1] = (vNaSat[1] - vNbSat[1])/(2.0*res);
	vVelS[2] = (vNaSat[2] - vNbSat[2])/(2.0*res);
	atNormVect(vVelS, vNVelS); 

	GetPos(mjd, vSat, vNVelS, offset, RaDe);
	//	printf("==>%4d) jj=%d mjd=%f, zdecO=%f, offset=%f, ", k, jj, mjd, RaDe[3], RAD2DEG*offset);
	GetPos(mjd, vSat, vNVelS, SunSurvOfs, RaDe);
	//	printf("zdecS=%f, SunOfst=%f IncTOfs=%f, npts=%d, suna=%f\n", RaDe[3], RAD2DEG*SunSurvOfs, IncTOfs*RAD2DEG, SSunPts+TSunPts, suna);
 
	sra   = RaDe[0];
	sdec  = RaDe[1];
	zra   = RaDe[2];
	zdec  = RaDe[3];
	yra   = RaDe[4];
	ydec  = RaDe[5]; 
	xra   = RaDe[6];
	xdec  = RaDe[7];
	sunx  = RaDe[8]; 
	suny  = RaDe[9]; 
	sunz  = RaDe[10];

	sunxy = sqrt(sunx*sunx+suny*suny);
	suna = atan2(sunxy,sunz);
	suna = suna*RAD2DEG;
	//	printf("%5d) Newly Calculated Sun angle with z-axis = %13.9f\n", jj, suna);


	OAtt->mjd[k]    = mjd;
	OAtt->SatRA[k]  = sra;
	OAtt->SatDEC[k] = sdec;
	OAtt->Xra[k]    = xra;
	OAtt->Xdec[k]   = xdec;
	OAtt->Yra[k]    = yra;
	OAtt->Ydec[k]   = ydec;
	OAtt->Zra[k]    = zra;
	OAtt->Zdec[k]   = zdec;


	k++;
	if(k >=inum+j){
	  break;
	}


	dk += 1.0;
	ij++;

      }
      i += ij+2;
      if(i > ephem->ent){
	i = ephem->ent-1;
      }

      while( OAtt->mjd[i] <= 0.1){
	i--;
// 	if(i > 0 && i < 100){
// 	  printf("%s:%d, %5d) mjd=%f\n", __FILE__, __LINE__, i, OAtt->mjd[i]);
// 	}
      }

	
    } // end if fabs(suna) <= 10.0 || fabs(suna) >= 170.


  }

  osf.info(5) << "Leaving MakeSurvey\n";
  return;
}



void DoSlew(double start, double mjds, double pra, double pdec, double ra, 
	    double dec, double res, EphemData *ephem, Attitude *OAtt, double TS){

  //  double sra, sdec, zra, zdec, yra, ydec, xra, xdec;

  int inum, i, j;
  AtVect xyz, xyz1, xyz2, Nxyz;
  //  AtPolarVect rade1, rade2;
  double consts[2];
  double theta, thetad, theta1, theta2;
  int tm;
  double slewR, reso;
  double incrang, nv, nd, u, nra, ndec;
  double hpi = asin(1.0);
  double fact;

  AtVect vSat, vbSat, vaSat, vVelS;
  AtVect vNSat, vNbSat, vNaSat, vNVelS;
  double mjd, amjd, bmjd;
  double RaDe[11];
  AtVect vSun;
  AtPolarVect gSatP;


  osf.setMethod("DoSlew");

  inum = (int) ((mjds-start+res/2.)/res);


  j = 0;
  
  mjd = ephem->MJD[j];


  if(fabs (mjd- start) > 1.0E-6  ) {
    while((mjd < start) && (j < ephem->ent)){
      if(fabs(mjd-start) < 1E-8 ){
	break;
      }
      mjd = ephem->MJD[++j];
    }
  }


  int k =(int) (((start-TS)+res/2.0)/res);
  //  k++;
  reso = res*minInDay;

  slewR = SLEW_RATE*reso;


  rade2xyz(pra, pdec, xyz1);
  rade2xyz( ra,  dec, xyz2);

  getconsts(xyz1, xyz2, consts);


  angularSep(pra*DEG2RAD, pdec*DEG2RAD, ra*DEG2RAD, dec*DEG2RAD, &theta);


  double dlon =  (ra - pra)*DEG2RAD;
  double dlat = (dec - pdec)*DEG2RAD;
  double a = sin(dlat/2.0)*sin(dlat/2.0) + cos(pdec*DEG2RAD)*cos(dec*DEG2RAD)* sin(dlon/2.0)*sin(dlon/2.0);

  double b = 1.0;
  if(sqrt(a) < b){
    b = sqrt(a);
  }

  double c = 2.0 * asin(b);

  c = c*RAD2DEG;


  thetad = theta*RAD2DEG;


  tm = (int)(thetad/slewR+0.5);


  atSun(mjd, vSun);
  atVectToPol(vSun,&gSatP);
  double raS = gSatP.lon;
  double decS = 90.0*DEG2RAD-gSatP.lat;
  
  double duratS =  GLAST_slew_estimate(raS, decS, pra*DEG2RAD,
				       pdec*DEG2RAD, ra*DEG2RAD, dec*DEG2RAD);

/*
  printf("mjd=%f, raS=%f, decS=%f\n", mjd, raS*RAD2DEG, decS*RAD2DEG);
  exit(0);
*/

  tm = (int)(duratS/(60.0*reso));


  if(tm < inum){
    tm = inum;
  }

  incrang = thetad/(double)tm;


  double resi1 = xyz1[0]*sin(consts[1])+xyz1[1]*cos(consts[1])-
    xyz1[2]*(1.0/(sqrt(1.0/(consts[0]*consts[0])-1.0)));

  double resi2 = xyz2[0]*sin(consts[1])+xyz2[1]*cos(consts[1])-
    xyz2[2]*(1.0/(sqrt(1.0/(consts[0]*consts[0])-1.0)));

  if(fabs(resi1)>0.001 && fabs(resi2)>0.001){
    fact = -1.0;
  } else {
    fact = 1.0;
  }

  if(inum != tm) {
    osf.warn() << "\nFound a discrepancy:\nmjds=" <<mjds << ", start=" << start << ", res=" << res << "\n";
    osf.warn() << "in DoSlew, pra=" << pra << ", pdec=" << pdec << ", ra=" << ra << ", dec=" << dec << ", with inum=" << inum << ", tm=" << tm << ", dt=" << (mjds-start)*1440.0 << ", thetad=" << thetad << ", slewR=" << slewR << ", k=" << k << "\n";
    osf.warn() << "With a slew rate of " << slewR << ", and an angular separation of " << thetad << ", there are " << tm << " points,\nangular increment is " << incrang << "\npra=" << pra << ", pdec=" << pdec << "\nra=" << ra << ", dec=" << dec << "\nresi1=" << resi1 << ",  resi2=" << resi2 << ", fact=" << fact << "\n\n";
  }

  for (i=0; i<tm; i++) {

    theta1 = (double)i*incrang;
    theta2 = thetad - theta1;

    theta1 = cos(theta1*DEG2RAD);
    theta2 = cos(theta2*DEG2RAD);



    getXYZ(xyz1, xyz2, theta1, theta2, consts, xyz, fact);
      
    atNormVect(xyz, Nxyz);  /* normalize vector      */


    nv = acos(Nxyz[2]);

    nd = hpi - nv;

    u = atan2(Nxyz[1], Nxyz[0]);

    nra  = u*RAD2DEG;
    ndec = nd*RAD2DEG;

    if (nra < 0.0) {
      nra += 360.0;
    }

    if(k >= ephem->ent-1) {
      break;
    }

    mjd = ephem->MJD[i+j];    
    vSat[0] = ephem->X[i+j]; 
    vSat[1] = ephem->Y[i+j];
    vSat[2] = ephem->Z[i+j];  
    if(i+1+j >= ephem->ent) { // Mind the boundaries
      amjd = mjd + res;
      vaSat[0] = InterPVect(mjd, amjd, vSat[0], vaSat[0], amjd);
      vaSat[1] = InterPVect(mjd, amjd, vSat[1], vaSat[1], amjd);
      vaSat[2] = InterPVect(mjd, amjd, vSat[2], vaSat[2], amjd);
    } else {
      amjd     = ephem->MJD[i+1+j];
      vaSat[0] = ephem->X[i+1+j];
      vaSat[1] = ephem->Y[i+1+j];
      vaSat[2] = ephem->Z[i+1+j];
    }

    if(i+j-1 == 0){  // if i-1 < 0
      bmjd     = mjd - res;
      vbSat[0] = InterPVect(mjd, amjd, vSat[0], vaSat[0], bmjd);
      vbSat[1] = InterPVect(mjd, amjd, vSat[1], vaSat[1], bmjd);
      vbSat[2] = InterPVect(mjd, amjd, vSat[2], vaSat[2], bmjd);

    } else {
      bmjd     = ephem->MJD[i-1+j];
      vbSat[0] = ephem->X[i-1+j];
      vbSat[1] = ephem->Y[i-1+j];
      vbSat[2] = ephem->Z[i-1+j];

    }


    atNormVect(vSat, vNSat);  /* normalize vector vSat */
    atNormVect(vbSat, vNbSat);  /* normalize vector vbSat */
    atNormVect(vaSat, vNaSat);  /* normalize vector vaSat */

    vVelS[0] = (vNaSat[0] - vNbSat[0])/(2.0*res);
    vVelS[1] = (vNaSat[1] - vNbSat[1])/(2.0*res);
    vVelS[2] = (vNaSat[2] - vNbSat[2])/(2.0*res);
    atNormVect(vVelS, vNVelS);  /* normalize vector vaSat */


    GetPointedPos(mjd, vSat, vNVelS, nra, ndec, RaDe);


    OAtt->mjd[k]    = mjd;


    OAtt->SatRA[k]  = RaDe[0];
    OAtt->SatDEC[k] = RaDe[1];
    OAtt->Xra[k]    = RaDe[6];
    OAtt->Xdec[k]   = RaDe[7];
    OAtt->Yra[k]    = RaDe[4];
    OAtt->Ydec[k]   = RaDe[5];
    OAtt->Zra[k]    = RaDe[2];
    OAtt->Zdec[k]   = RaDe[3];
    OAtt->in_occ[k] = -99999;
    k++;
  }



  return ;
}




void MakePointed(double start, double end, double res, double ra, 
		 double dec, EphemData *ephem, Attitude *OAtt, double TS){


  AtVect vSat, vbSat, vaSat, vVelS;
  AtVect vNSat, vNbSat, vNaSat, vNVelS;
  double mjd, amjd, bmjd;

  double RaDe[11];
  int i, inum, k;
  double sra, sdec, zra, zdec, yra, ydec, xra, xdec, sunx, suny, sunz;

  int j = 0;


  inum = (int) ((end-start+res/2.)/res);
  inum++;


  if(ra<0.0){
    ra = ra+360.0;
  }

  j = 0;
  
  mjd = ephem->MJD[j];


  if(mjd < start) {
    while((mjd < start) && (j < ephem->ent)){
      if(fabs(mjd-start) < 1E-10 ){
	break;
      }
      mjd = ephem->MJD[++j];
    }
  }


  k =(int) (((start-TS)+res/2.0)/res);


  for (i=j;i<inum+j;++i) {
    /* Get the satellite vector in ECI */


    mjd = ephem->MJD[i];    
    vSat[0] = ephem->X[i]; 
    vSat[1] = ephem->Y[i];
    vSat[2] = ephem->Z[i]; 

    if(i+1 > ephem->ent ) { // Mind the boundaries 
      amjd = mjd + res;
      vaSat[0] = InterPVect(mjd, amjd, vSat[0], vbSat[0], amjd);
      vaSat[1] = InterPVect(mjd, amjd, vSat[1], vbSat[1], amjd);
      vaSat[2] = InterPVect(mjd, amjd, vSat[2], vbSat[2], amjd);
    } else {
      amjd     = ephem->MJD[i+1];
      vaSat[0] = ephem->X[i+1];
      vaSat[1] = ephem->Y[i+1];
      vaSat[2] = ephem->Z[i+1];
    }

    if(i == 0){  // if i-1 < 0
      bmjd     = mjd - res;
      vbSat[0] = InterPVect(mjd, amjd, vSat[0], vaSat[0], bmjd);
      vbSat[1] = InterPVect(mjd, amjd, vSat[1], vaSat[1], bmjd);
      vbSat[2] = InterPVect(mjd, amjd, vSat[2], vaSat[2], bmjd);

    } else {
      bmjd     = ephem->MJD[i-1];
      vbSat[0] = ephem->X[i-1];
      vbSat[1] = ephem->Y[i-1];
      vbSat[2] = ephem->Z[i-1];

    }


    atNormVect(vSat, vNSat);  /* normalize vector vSat */
    atNormVect(vbSat, vNbSat);  /* normalize vector vbSat */
    atNormVect(vaSat, vNaSat);  /* normalize vector vaSat */

    vVelS[0] = (vNaSat[0] - vNbSat[0])/(2.0*res);
    vVelS[1] = (vNaSat[1] - vNbSat[1])/(2.0*res);
    vVelS[2] = (vNaSat[2] - vNbSat[2])/(2.0*res);
    atNormVect(vVelS, vNVelS);  /* normalize vector vaSat */



    GetPointedPos(mjd, vSat, vNVelS, ra, dec, RaDe);

    sra   = RaDe[0];
    sdec  = RaDe[1];
    zra   = RaDe[2];
    zdec  = RaDe[3];
    yra   = RaDe[4];
    ydec  = RaDe[5]; 
    xra   = RaDe[6];
    xdec  = RaDe[7];
    sunx  = RaDe[8]; 
    suny  = RaDe[9]; 
    sunz  = RaDe[10]; 


    OAtt->mjd[k]    = mjd;
    OAtt->SatRA[k]  = sra;
    OAtt->SatDEC[k] = sdec;
    OAtt->Xra[k]    = xra;
    OAtt->Xdec[k]   = xdec;
    OAtt->Yra[k]    = yra;
    OAtt->Ydec[k]   = ydec;
    OAtt->Zra[k]    = zra;
    OAtt->Zdec[k]   = zdec;



    k++;
  }



  return;
}





/* CKS: The saa routine was formally called xtesaa. Since this was the method 
   chosen for Swift, I renamed it.
   This routine determines if each ephemeris point is in or out of the SAA polynomial.
   A filename should be passed in which defines SAA polynomial (longitude/latitude pairs).
   In addition to an ephemeris point being in the SAA polynomial, the ephem point 
   prior will also be included as in the SAA polynomial,because somewhere between the 
   two points is when the actual SAA is entered (we're rounding by one resolution).  
   The end of an SAA already rounds to next resolution (the value remains true for full resolution).

   ***** NOTE ****  For this routine to work, the last latitude/longitude pair
   must be the same as the first (index 1)!  This way every side of the polygon
   is accounted for.  (Don't use index 0!)
*/
void saa( EphemData *EphemPtr, const char *filename, double StartTime, 
	  double EndTime, double Resolution, Attitude *att) {

  double lontable[52],lattable[52], lat, lon, pt, nextpt;
  int i, inum, num_saa, num_lat, num_lon, isaa;
  double slopes[52];      /* slopes of SAA polygon sides (deg) */
  double intercepts[52];  /* intercepts of SAA polygon sides (deg) */
  double minLat, minLon, maxLat, maxLon;
  FILE *fptr;
  char jnk[20];
  const int lnsz = 200;
  char  line[lnsz];

  osf.setMethod("saa");

  /* CODE HERE */

  
  num_saa = 0;
  num_lat = 0;
  num_lon = 0;
   
  
  if (strcmp(filename,"NULL")!= 0) {
    /* a filename was passed in, read the longitude and latitude pairs */
   
    if ((fptr = fopen(filename, "r")) == NULL) 
      osf.err() << "saa constraint: could not open file " << filename  << ".\n";
    else {

      
      /* Read file. Ignore comment lines (#), truncate if more than 50 pairs */
      while ((fgets(line,lnsz,fptr) != NULL) && (num_lat < 50) && (num_lon < 50) ) {

	if (line[0] != '#') {
	  if(strncmp(line, "SAAPOLYLAT", 10) == 0){
	    num_lat++;
	    sscanf (line, "%13c%lf", jnk,&lattable[num_lat]); 
	  }else if(strncmp(line, "SAAPOLYLONG", 11) == 0){
	    num_lon++;
	    sscanf (line, "%14c%lf", jnk,&lontable[num_lon]);
	    if (lontable[num_lon] >= 180.0) lontable[num_lon]-=360.0;
	  } else {
	    sscanf (line, "%lf %lf", &lontable[num_saa], &lattable[num_saa]);
	    if (lontable[num_saa] >= 180.0) lontable[num_saa]-=360.0;
	    num_saa++;
	    num_lat++;
	    num_lon++;

	  }


	}

      }
    
      fclose(fptr);


      if(num_lat != num_lon){
	      

	std::ostringstream eBufT;
	eBufT << "\n" << __FILE__ << ":" << __LINE__ << "\n";
	eBufT << "ERROR: while reading SAA LAT and LONG, from file:\n";
	eBufT << "           " << filename << "\n";
	eBufT << "           it appears that the number of lat is " << num_lat << "\n";
	eBufT << "           while the number of long is " << num_lon << "\n";
	eBufT << "Please, correct this problem. Exiting for now.....\n\n"  <<std::ends;
	throw std::runtime_error(eBufT.str());

      } else {
	num_saa = num_lat;
      }




     /*  For the following algorithm to work, the last pair must be the same as the 1st. If the
         file doesn't do this (likely), then add the last pair.                                  */

      if (num_saa > 0)
	if ((lontable[1] != lontable[num_saa]) || (lattable[1] != lattable[num_saa]))
        {
	  num_saa++;
	  lontable[num_saa] = lontable[1];
	  lattable[num_saa] = lattable[1];
        }

    }
  }
 
  if(find_minmax(&lontable[0],&lattable[0],num_saa, &minLon,&maxLon,&minLat,&maxLat) !=0){
    std::ostringstream eBufT;
    eBufT << "\n" << __FILE__ << ":" << __LINE__ << "saa constraint could not find min and max saa (lat,lon)\n\n" <<std::ends;

    throw std::runtime_error(eBufT.str());
  }

  if(calculate_slopes(&lontable[0],&lattable[0],num_saa, &slopes[0],&intercepts[0])!=0){
    std::ostringstream eBufT;
    eBufT << "\n" << __FILE__ << ":" << __LINE__ << "saa constraint could not find saa slopes/intercepts\n\n" <<std::ends;

    throw std::runtime_error(eBufT.str());
  }

  /* determine in number of SAA points needed */
  /* Replaced this:
     inum = (int)((EndTime-StartTime)/Resolution);
     because it caused 10080.0000 to be truncated to 10079
     New calc adds rounding factor to prevent this. */

  inum =  (int)((EndTime-StartTime+Resolution/2.)/Resolution);
  inum++; //GR increased number of data points by one;


  /* now actually generates the SAA points */
 
  /* printf("Checking SAA for %d points.\n",inum); */
  for (i=0;i<inum;++i) {

    lat = EphemPtr->Lat[i]; /* assume it's in degrees? */
    lon = EphemPtr->Long[i];
    if (lon >= 180.) lon-=360.;


    isaa=pt_in_polygon(lat,lon,lattable,lontable,slopes,intercepts,
		       num_saa,minLon,maxLon,minLat,maxLat);

    att->in_saa[i] = 1*isaa;
   
  }

  /* Make sure the constraint encloses the SAA period. For the beginning of the
     SAA period, start the period one resolution (a minute) prior to the first
     point that falls in the saa polygon (basically rounding by one resolution).
     The end of the period is already rounded to the next resolution 
     (the value at the start of the resolution is the value until the next
     resoulution time).
     The resulting SAA constraint period will have up to one resolution (one minute) 
     padding at the beginning and end. */

  pt = (double) att->in_saa[0];
 
  for (i=0;i<inum-1;++i) {
    
    nextpt = (double) att->in_saa[i+1];
    if ((int)nextpt == 1 && (int)pt == 0) {
      /* round up at beginning of SAA period */
      att->in_saa[i] = 1;
    }
 
    pt=nextpt;
  }

  return;

}







void doSurvey(double start, double end, double res, double ira, double idec,
	      double offset, EphemData *ephem, Attitude *OAtt){



  double RaDec[2];
  double Timespan = end - start;
  int inum = (int)((Timespan+res/2.0)/res);
  inum++;   /* Delta plus 1 to get the end point */



  Attitude *OAtt1 = allocateAttitude(inum);
  if ( OAtt1 == (Attitude *)NULL) {
    std::ostringstream eBufT;
    eBufT << "\n" << __FILE__ << ":" << __LINE__ << ", ERROR: Cannot Allocate attitude data structure\nExiting..............\n\n " <<std::ends;

    throw std::runtime_error(eBufT.str());
  }
  OAtt1->ent = inum;


  osf.setMethod("doSurvey");

  Attitude *OAtt2 = allocateAttitude(inum);
  if ( OAtt2 == (Attitude *)NULL) {
    std::ostringstream eBufT;
    eBufT << "\n" << __FILE__ << ":" << __LINE__ << ", ERROR: Cannot Allocate attitude data structure\nExiting..............\n\n " <<std::ends;

    throw std::runtime_error(eBufT.str());
  }
  OAtt2->ent = inum;

  MakeSurvey(start, end, res, offset, ephem, OAtt1, RaDec, 1, start);
  osf.info(4) << __FILE__ << ":" << __LINE__ << ", called MakeSurvey with offset=" << offset << "\n\n";
  MakeSurvey(start, end, res, -offset, ephem, OAtt2, RaDec, 1, start);
  osf.info(4) << __FILE__ << ":" << __LINE__ << ", called MakeSurvey with offset=" << -offset << "\n\n";




  double mjds = start;





  int j =  getEndPoint (start, &mjds, ira, idec, OAtt1, 0, start, res);

  double ra  = OAtt1->Zra[j];
  double dec = OAtt1->Zdec[j];



  if(start < mjds) {
    DoSlew(start, mjds, ira, idec, ra, dec, res, ephem, OAtt, start);
    osf.info(4) << __FILE__ << ":" << __LINE__ << ", called DoSlew with offset=" << offset << "\n\n";
  }




  double Timespan1 = end - mjds;
  int inum1 = (int)((Timespan1+res/2.0)/res);
  inum1++;   /* Delta plus 1 to get the end point */


  int ia = 1;
  int k;
  osf.info(4) << __FILE__ << ":" << __LINE__ << ", the first point after the slew is at k=" << (inum-inum1) << "\n\n";

  for(k = (inum-inum1); k<inum; k++){
    // first of all check if there should be a change in the offset
    
    if(k<inum-2){
      if(ephem->Z[k]<= 0.0 && ephem->Z[k+1] >= 0.0){
	double tmjd = OAtt1->mjd[k]; 
	int yy, dy, hh, mm, ss;
	do_mjd2utc(tmjd, &yy, &dy, &hh, &mm, &ss);

/*
	if(ia == 1){
	  printf ("%4d) Transition taking place at %4d/%03d:%02d:%02d:%02d starting offset=%5.2f ending offset=%5.2f since z0=%f and z1=%f\n", k, yy, dy, hh, mm, ss, offset, -offset, ephem->Z[k], ephem->Z[k+1]);
	  osf.info() << "i=0, OAtt->mjd[0]=" << OAtt->mjd[0] << "\ni=1, OAtt->mjd[1]=" << OAtt->mjd[1] << "\n\n";
	}else {
	  printf ("%4d) Transition taking place at %4d/%03d:%02d:%02d:%02d starting offset=%5.2f ending offset=%5.2f since z0=%f and z1=%f\n", k, yy, dy, hh, mm, ss, -offset, offset, ephem->Z[k], ephem->Z[k+1]); 
	  osf.info() << "i=0, OAtt->mjd[0]=" << OAtt->mjd[0] << "\ni=1, OAtt->mjd[1]=" << OAtt->mjd[1] << "\n\n";
	}
*/


	if(ia == 1){
	  double mjdi = OAtt1->mjd[k];
	  double ira  = OAtt1->Zra[k];
	  double idec = OAtt1->Zdec[k];

	  mjds = mjdi;
	  j =  getEndPoint (mjdi, &mjds, ira, idec, OAtt2, k, start, res);

	  int dn = j-k;

	  if(dn > 0){
	    double dth = 2.0*offset/(double)dn;
	    int jj = k;
	    for(k=jj; k<=j; k++){

	      if(k>= inum)
		break;

	      double noffset = offset-dth*(double)(k-jj);

	      MakeSurvey(OAtt1->mjd[k], OAtt1->mjd[k+1], res, noffset, ephem, OAtt, RaDec, 2, start);
	    }
	    k--;
	  } else {
	    MakeSurvey(OAtt1->mjd[k], OAtt1->mjd[k+1], res, offset, ephem, OAtt, RaDec, 2, start);
	  }
	  ia = 2;
	} else {
	  double mjdi = OAtt2->mjd[k];
	  double ira  = OAtt2->Zra[k];
	  double idec = OAtt2->Zdec[k];


	  mjds = mjdi;
	  j =  getEndPoint (mjdi, &mjds, ira, idec, OAtt1, k, start, res);

	  int dn = j-k;

	  if (dn > 0){
	    double dth = 2.0*offset/(double)dn;
	    int jj = k;
	    for(k=jj; k<=j; k++){

	      if(k>= inum)
		break;

	      double noffset = -offset+dth*(double)(k-jj);
	      MakeSurvey(OAtt2->mjd[k], OAtt2->mjd[k+1], res, noffset, ephem, OAtt, RaDec, 2, start);
	    }
	    k--;
	  } else {
	    MakeSurvey(OAtt1->mjd[k], OAtt1->mjd[k+1], res, offset, ephem, OAtt, RaDec, 2, start);
	  }
	  ia = 1;
	}

      } else {
	if(ia == 1){

	  OAtt->mjd[k]    = OAtt1->mjd[k];
	  OAtt->SatRA[k]  = OAtt1->SatRA[k];
	  OAtt->SatDEC[k] = OAtt1->SatDEC[k];
	  OAtt->Xra[k]    = OAtt1->Xra[k];
	  OAtt->Xdec[k]   = OAtt1->Xdec[k];
	  OAtt->Yra[k]    = OAtt1->Yra[k];
	  OAtt->Ydec[k]   = OAtt1->Ydec[k];
	  OAtt->Zra[k]    = OAtt1->Zra[k];
	  OAtt->Zdec[k]   = OAtt1->Zdec[k];

	} else {

	  OAtt->mjd[k]    = OAtt2->mjd[k];
	  OAtt->SatRA[k]  = OAtt2->SatRA[k];
	  OAtt->SatDEC[k] = OAtt2->SatDEC[k];
	  OAtt->Xra[k]    = OAtt2->Xra[k];
	  OAtt->Xdec[k]   = OAtt2->Xdec[k];
	  OAtt->Yra[k]    = OAtt2->Yra[k];
	  OAtt->Ydec[k]   = OAtt2->Ydec[k];
	  OAtt->Zra[k]    = OAtt2->Zra[k];
	  OAtt->Zdec[k]   = OAtt2->Zdec[k];

	}
	

      }
    } else {

      if(ia == 1){

	OAtt->mjd[k]    = OAtt1->mjd[k];
	OAtt->SatRA[k]  = OAtt1->SatRA[k];
	OAtt->SatDEC[k] = OAtt1->SatDEC[k];
	OAtt->Xra[k]    = OAtt1->Xra[k];
	OAtt->Xdec[k]   = OAtt1->Xdec[k];
	OAtt->Yra[k]    = OAtt1->Yra[k];
	OAtt->Ydec[k]   = OAtt1->Ydec[k];
	OAtt->Zra[k]    = OAtt1->Zra[k];
	OAtt->Zdec[k]   = OAtt1->Zdec[k];

      } else {

	OAtt->mjd[k]    = OAtt2->mjd[k];
	OAtt->SatRA[k]  = OAtt2->SatRA[k];
	OAtt->SatDEC[k] = OAtt2->SatDEC[k];
	OAtt->Xra[k]    = OAtt2->Xra[k];
	OAtt->Xdec[k]   = OAtt2->Xdec[k];
	OAtt->Yra[k]    = OAtt2->Yra[k];
	OAtt->Ydec[k]   = OAtt2->Ydec[k];
	OAtt->Zra[k]    = OAtt2->Zra[k];
	OAtt->Zdec[k]   = OAtt2->Zdec[k];

      }

    }


  }

  osf.info(4) << "i=0, OAtt->mjd[0]=" << OAtt->mjd[0] << "\ni=1, OAtt->mjd[1]=" << OAtt->mjd[1] << "\n";
  return;
}









int getEndPoint (double mjdi, double *mjds, double ira, double idec, 
		 Attitude *LAtt, int idx, double start, double res){

  int ntr = 0;
  double theta = 0.0;
  double ptheta = -999.0;
  const double slewR = SLEW_RATE;

  double fra = LAtt->Zra[idx];
  double fdec = LAtt->Zdec[idx];
  double reso = res*minInDay;
  AtVect vSun;
  AtPolarVect gSatP;



  int j;

  osf.setMethod("getEndPoint");

  while (ntr < 20){

    angularSep(ira*DEG2RAD, idec*DEG2RAD, fra*DEG2RAD, fdec*DEG2RAD, &theta);

    theta = theta*RAD2DEG;

    
    if(theta == ptheta){
      break;
    } else {
      ptheta = theta;
    }
    
    double slewT = theta/slewR;
    slewT = ((double) ((int)(slewT+reso/2.0)))/minInDay;
    *mjds = mjdi+slewT;

    j =(int) (((*mjds-start)+res/2.0)/res);


    atSun(mjdi, vSun);
    atVectToPol(vSun,&gSatP);
    double raS = gSatP.lon;
    double decS = 90.0*DEG2RAD-gSatP.lat;
  
    double duratS =  GLAST_slew_estimate(raS, decS, ira*DEG2RAD,
					 idec*DEG2RAD, fra*DEG2RAD, fdec*DEG2RAD);



    duratS = (double)((int)(duratS/(86400.0*res)));

    duratS = duratS*res;



    *mjds = mjdi+duratS;
    j =(int) (((*mjds-start)+res/2.0)/res);    


    osf.info(4) << "idx="<<idx<<", mjds="<<*mjds<<", start="<<start<<", res="<<res<<", j="<<j<<"\n";

    fra = LAtt->Zra[j];
    fdec = LAtt->Zdec[j];

    ntr++;
    
  }


  return j;

}



void MakeProfiled(double start, double end, double res, double ira, double idec, double epoch, 
		  double *tms, double *ofst, EphemData *ephem, Attitude *OAtt, double begin) {


  double period = tms[16]/secInDay;
  double startT;

  osf.setMethod("MakeProfiled");

  osf.info(4) << "epoch = "<<epoch<<"\n";
  
  if(epoch <= start){
    int np = (int)((start-epoch)/period);
    osf.info(4) << "epoch = "<<epoch<<", np = "<<np<<"\n";
    startT = epoch+period*(double)np;
  }else {
    osf.warn() << "####################################################################################################\n\n";
    osf.warn() << "                                      WARNING\n";
    osf.warn() << "\tEpoch for Profile Survey (" << epoch << ") starting at MJD=" << start << "\n";
    osf.warn() << "\tis larger than the start time. This should not have happened.\n";
    osf.warn() << "\tHowever, orbit simulator will try to interpolate back in time\n\n";
    osf.warn() << "####################################################################################################\n\n";
    int np = (int)((epoch -start)/period)+1;
    startT = epoch - period*(double)np;
  }

  // Rouding up startT to the closest resolution.

  startT = (double)((int)(startT/res+0.5))*res;

  double Timespan = (end-startT);
  int inum = (int)((Timespan+res/2.0)/res);
  inum+=3;

  Attitude *TAtt = allocateAttitude(inum);
  double nend = end+res;
  osf.info(3) << "\nCalling  doProfiled with startT=" << startT << ", while start=" << start << ", begin=" << begin << "\n";

  doProfiled(startT, nend, res, tms, ofst, ephem, TAtt);




  double mjds = start;

  int idx = (int) (((start-startT)+res/2.0)/res);
  int ned = (int) (((end-startT)+res/2.0)/res);

  osf.info(3) << "Calling getEndPoint  with startT=" << startT << ", while start=" << start << ", begin=" << begin << "\n";
  int jj =  getEndPoint (start, &mjds, ira, idec, TAtt, idx, startT, res);
  osf.info(3) << "obtained jj=" << jj << ", mjds=" << mjds << "\n";

  double ra  = TAtt->Zra[jj];
  double dec = TAtt->Zdec[jj];




  //  printf("start=%f, slew=%f, end=%f\n", start, mjds, end);


  if(mjds > end){

    osf.err() << "\n####################################################################################################\n\n";
    osf.err() << "                                           ERROR\n";
    osf.err() << "\tEnd of slew time (" << mjds << ") is greater than the end of this snapshot (" << end << ")\n";
    osf.err() << "\tThis might cause a seg fault. Please check. Exiting for now...........\n\n";
    osf.err() << "####################################################################################################\n\n";

/*
    std::ostringstream eBufT;
    eBufT << "\n####################################################################################################\n\n";
    eBufT << "                                            ERROR\n";
    eBufT << "\tEnd of slew time (" << mjds << ") is greater than the end of this snapshot (" << end << ")\n";
    eBufT << "\tThis might cause a seg fault. Please check. Exiting for now...........\n\n";
    eBufT << "####################################################################################################\n\n" <<std::ends;

    throw std::runtime_error(eBufT.str());
*/

  }

  if(start < mjds) {
    osf.info(3) << "calling DoSlew with start="<<start<<", mjds="<<mjds<<"\n";
    DoSlew(start, mjds, ira, idec, ra, dec, res, ephem, OAtt, begin);
  }

  int k = (int) (((mjds-begin)+res/2.0)/res);

  int j=0;
  for(j=0; j<inum; j++){
    if(fabs(TAtt->mjd[j]-mjds) < res/3.0){
    //    if((TAtt->mjd[j]-mjds) > res/2.0){
    //    if((TAtt->mjd[j]-mjds) >= 0.0 && (TAtt->mjd[j]-mjds) < res/2.0){
      osf.info(4) <<"at j-1="<<j-1<<", mjd="<<TAtt->mjd[j-1]<<", while mjds="<<mjds<<"\n";
      osf.info(4) <<"at j="<<j<<", mjd="<<TAtt->mjd[j]<<", while mjds="<<mjds<<"\n";
      idx = j;
      break;
    }
  }
  //    idx--;


  double tdif = fabs(OAtt->mjd[k-1]-TAtt->mjd[idx-1]);



  int ii = idx;

  if(tdif > 0.0){
    osf.err() << "####################################################################################################\n\n";
    osf.err() << "                                      ERROR\n";
    osf.err() << "In MakeProfiled, while calculating attitude for observation starting at "<<start<<"\n";
    osf.err() << "when merging the calculated attitude for this segment with the overall attitude\n";
    osf.err() << "it was found that at the merging point:\n";
    osf.err() << "the overall attitude would start at "<<OAtt->mjd[k-1]<<"\n";
    osf.err() << "while the newly part would start at "<<TAtt->mjd[idx-1]<<".\n\n";
    osf.err() << "This has the potential to create problems because of gaps.\n";
    osf.err() << "####################################################################################################\n\n";
  }



  for(ii=idx; ii<=ned; ii++){

    OAtt->mjd[k]    = TAtt->mjd[ii];
    OAtt->SatRA[k]  = TAtt->SatRA[ii];
    OAtt->SatDEC[k] = TAtt->SatDEC[ii];
    OAtt->Xra[k]    = TAtt->Xra[ii];
    OAtt->Xdec[k]   = TAtt->Xdec[ii];
    OAtt->Yra[k]    = TAtt->Yra[ii];
    OAtt->Ydec[k]   = TAtt->Ydec[ii];
    OAtt->Zra[k]    = TAtt->Zra[ii];
    OAtt->Zdec[k]   = TAtt->Zdec[ii];
    //printf("k=%d, mjd=%f, ned=%d\n", k,  OAtt->mjd[k], ned);
    k++;
  }

  //  exit(0);


  TAtt = deallocateAttitude(TAtt);

  return;

}


void doProfiled(double start, double end, double res, double *tms, 
		double *ofst, EphemData *ephem, Attitude *OAtt){


  double RaDec[2];
  double mjd = start;
  const int sz = 17;
  int ic, inum, jc, i;
  double offset;
  double angsep, slewr;
  double epoch = start;

  double InterpProfile(double *tms, double *ofst, double res);

  double difincr = InterpProfile(tms, ofst, res);

  double Ltime = tms[16];
  double Lincr = difincr;

  int ncycles = (int)((end-start)*60.0/(tms[sz-1]*res))+1;
  double epoch1, epoch2;
  const double leps = 1.0E-10;


  inum = (int) ((end-start+res/2.)/res);
  inum++;    // and include the end point


  osf.setMethod("doProfiled");

  osf.info(2) << "\n\nProfiled Survey:\n";
  for(i=0; i<sz; i++){
    osf.info(2) << i<<") Time: "<<tms[i]<<", Angle: "<<ofst[i]<<"\n";

  }
  osf.info(2) << "\n\nStart="<<start<<"\nend="<<end<<"\nLast Time tms[sz-1]="<<tms[sz-1]<<"\nResolution="<<res<<"\n";
  osf.info(2) << "Supposed to calculate Profiled Survey from "<<start<<" to "<<end<<"\n";
  osf.info(2) << "The profile contains ncycles=" << ncycles << "\n";

  //printf(" Raw ncycles: %f, end=%f, start=%f, period=%f \n", (end-start)*60.0/(tms[sz-1]*res), end, start, tms[sz-1]);



  int nts = 0;


  for(jc=0; jc<=ncycles+1; jc++){
    if(jc > 0){
      Lincr += difincr*(difincr/(fabs(difincr)));
      if((int)fabs(Lincr) >= (int)(res*secInDay)){
	tms[16] = Ltime+(Lincr/fabs(Lincr))*(double)((int)(res*secInDay));
	Lincr -= (Lincr/fabs(Lincr))*(double)((int)(res*secInDay));
      } else {
	tms[16] = Ltime;
      }
    }

    //  printf("%02d) difincr=%f, Lincr=%f, Ltime=%f ==> tms[16]=%f\n", jc, difincr, Lincr, Ltime, tms[16]);


    osf.info(4) << "Now doing cycle=" << jc << "\n";
    for(ic=0; ic<=sz-1; ic++){
      int ic1 = ic+1;
      int jc1 = jc;
      if(ic == sz-1){
	ic1 = 0;
	jc1 = jc+1;
      }
      epoch1 = epoch+((double)jc*tms[sz-1]+tms[ic])/secInDay;
      epoch2 = epoch+((double)jc1*tms[sz-1]+tms[ic1])/secInDay;


      angsep = ofst[ic1] - ofst[ic];
      if(fabs(epoch2-epoch1)*secInDay <= leps){
	slewr = 0.0;
      }else {
	slewr = angsep*res/(epoch2-epoch1);
      }

      osf.info(4) << "jc="<<jc<<", jc1="<<jc1<<", ic="<<ic<<", ic1="<<ic1<<", epoch1=" << epoch1 << ", epoch2="<< epoch2 << ", diff="<<(epoch2-epoch1)*secInDay<< ", angsep= "<< angsep <<", slewr="<<slewr<<"\n";

      if(fabs(slewr) > SLEW_RATE){
	osf.warn() << "\nWARNING: going from offset " << ofst[ic] << " to " << ofst[ic+1] << ",\nwill make the slew rate (" << slewr << ") greater than the nominal maximum value (" << SLEW_RATE << ")\n\n";
      }

      int ino = (int)((epoch2-epoch1)/res +0.5);
     


      for(i=0; i<ino; i++){

	offset = ofst[ic]+(slewr*(double)i);

	//int k =(int) (((mjd-start)+res/2.0)/res);

	osf.info(4) << "mjd="<<mjd<<", end="<<end<<", jc=" << jc <<", ic="<<ic<<", i="<<i<<", ino="<< ino<<", calling MakeSurvey with offset="<<offset<<"\n";

	MakeSurvey(mjd, mjd, res, offset, ephem, OAtt, RaDec, 2, start);
	nts++;


	mjd = mjd+res;

	if(mjd >= end ){
	  break;
	}
      }

      if(mjd >= end ){
	break;
      }
    }

    if(mjd >= end ){
      break;
    }

  }


  osf.info(4) << "Leaving doProfiled\n";


  return;

}



double InterpProfile(double *tms, double *ofst, double res){



  double Ltms[17], Lofst[17];

  int resS = (int)(res*secInDay+0.5);

  double difincr;

  // Assuming tms[0] = 0
  Ltms[0] = tms[0];
  Lofst[0] = ofst[0];

  int i = 0;
  int drem;

  for(i=1; i<16; i++){
  
    drem = (int)tms[i]%resS;


    if(drem != 0){
      if((double)drem <= (double)resS/2.0){
	Ltms[i] = tms[i]-(double)drem;
      } else {
	Ltms[i] = tms[i]-(double)drem+(double)resS;
      }

      if(Ltms[i] == Ltms[i-1]){
	Ltms[i] += (double)resS;
      }

      Lofst[i] = (ofst[i-1]-ofst[i])*(Ltms[i]-tms[i])/(tms[i-1]-tms[i])+ofst[i];

    } else {
      Ltms[i] = tms[i];
      Lofst[i] = ofst[i];
    }
  
  }


  // Last time is rounded off by defect, the reminder is returned

  Lofst[16] = ofst[16];
  drem = (int)tms[16]%resS;

  if(drem != 0){
    if((double)drem <= (double)resS/2.0){
      Ltms[16] = tms[16]-(double)drem;
      difincr = (double)drem;
    } else {
      Ltms[16] = tms[16]-(double)drem+(double)resS;
      difincr = -(double)drem+(double)resS;
    }

    if(Ltms[16] == Ltms[15]){
      Ltms[16] += (double)resS;
      difincr -= (double)resS;
    }

  } else {
    Ltms[16] = tms[16];
    difincr = 0.0;
  }

  for(i=0; i<17; i++){
    tms[i]  = Ltms[i];
    ofst[i] = Lofst[i];
  }


  return difincr;
}



void occult( EphemData *EphemPtr, double StartTime, double EndTime, 
	     double Resolution, Attitude *att, double EAA,
	     double start_ELT_OFF, double stop_ELT_OFF){

  int i, inum, j, ist;
  // Local variables 
  int eflag;
  double currentTime;
  double elvy;
  double sra, sdec, lat, lon, elv_limit;
  AtVect vSat, vSun, y50, y50t;
  static AtPolarVect y50P={1.,30.,60.};

  double mjdE, mjdS;



  //  elv_limit = 30.0;
  elv_limit = EAA;

  elv_limit *= DEG2RAD; 


  inum =  (int)((EndTime-StartTime+Resolution/2.)/Resolution);
  inum++; //GR increased number of data points by one;



  // now actually generates the Occultation points 
 
  currentTime = StartTime;

 
  //   Aligning Ephem and Survey mjd


  ist = 0;
  mjdE = EphemPtr->MJD[0];
  mjdS = att->mjd[0];



  if(fabs (mjdE- StartTime) > 1.0E-6  ) {
    while((mjdE < StartTime) && (ist < EphemPtr->ent)){
      if(fabs(mjdE-StartTime) < 1E-10 ){
	break;
      }
      mjdE = EphemPtr->MJD[++ist];
    }
  }



  //    printf("In occult, ist=%d\n\n", ist);
 
  j = 0;                 
  for (i=ist;i<inum;++i) {


    sra  = att->Zra[j]*DEG2RAD;
    sdec = att->Zdec[j]*DEG2RAD;


    y50P.lon = sra ;
    y50P.lat = sdec ;

    atPolToVect(&y50P, y50t);  
 
    lat = EphemPtr->Lat[i]; // assume it's in degrees? 
    lon = EphemPtr->Long[i];

    vSat[0] = EphemPtr->X[i];
    vSat[1] = EphemPtr->Y[i];
    vSat[2] = EphemPtr->Z[i];;
    
    atPrecession(MJD_J2000,y50t,currentTime,y50);

    atSun(currentTime, vSun);
    atEarthOccult(vSat, y50, vSun, &eflag, &elvy);   // CKS: changed from atEarthOccult2 
    
    if(att->in_occ[j] < -999){
      att->in_occ[j] = 0;     // This must be coming from slew, hence occultation is not  taken into account
    } else {
      if (eflag == 0) {

	if (elvy < elv_limit){
	  att->in_occ[j] = 1; // occulted 
	}
	else
	  att->in_occ[j] = 0; // not occulted 

      } else {
	att->in_occ[j] = 1; // occulted 
      }
    }

    // User may want to disable the Limb Tracing for a period
    // in this case we will assume that the spacecraft is not occulted
    if(start_ELT_OFF > 0.0 && stop_ELT_OFF > 0.0){
      if(currentTime >= start_ELT_OFF && currentTime <= stop_ELT_OFF){
	  att->in_occ[j] = 0; // not occulted 
      }
    }

    j++;
    currentTime = att->mjd[j];
    
  }


  return;

}

void doLimbTrace(EphemData *EphemPtr, double StartTime, double EndTime, double Resolution, Attitude *att ){

  int i, inum;
  int ns = 0, ne = 0;
  std::vector <int> staocc(1);
  std::vector <int> endocc(1);

  inum =  (int)((EndTime-StartTime+Resolution/2.)/Resolution);
  inum++; //GR increased number of data points by one;

  const int sz = inum/2;
  staocc.resize(sz);
  endocc.resize(sz);

//   int staocc[sz];
//   int endocc[sz];

  osf.setMethod("doLimbTrace");

  for(i=0; i<inum; i++){

    if(i == 0){
      if(att->in_occ[i] == 1){
	staocc[ns] = 0;
	ns++;
      }
    } else {
      if(att->in_occ[i-1] == 0 && att->in_occ[i] == 1){
	staocc[ns] = i;
	ns++;
      } else if(att->in_occ[i] == 0 && att->in_occ[i-1] == 1){ 
	endocc[ne] = i;
	ne++;
      }
    }
  }
  if(ne < ns){
	endocc[ne] = inum-1;
	ne++;
  }


  if(ne == 0){
    osf.warn() << "No target found in occultation\n\n";
  }else {
    for(i=0; i<ns; i++){
      std::cout<<"Target occulted from "<<EphemPtr->MJD[staocc[i]]<<" to "<<EphemPtr->MJD[endocc[i]]<<"\n";
    }
  }

  // Let's find the index difference between Attitude and Ephem


  int ist = 0;
  double mjdE = EphemPtr->MJD[0];



  if(fabs (mjdE- StartTime) > 1.0E-6  ) {
    while((mjdE < StartTime) && (ist < EphemPtr->ent)){
      if(fabs(mjdE-StartTime) < 1E-10 ){
	break;
      }
      mjdE = EphemPtr->MJD[++ist];
    }
  }


  for(i=0; i<ns; i++){

    int js = staocc[i];
    int je = endocc[i];

    if(js > 0 && js < inum){
      js--;
    }

    double phase1, phase2;
    int jep = js + ist;
    getPhase(EphemPtr, Resolution, att, js, jep, &phase1);

    jep = je + ist;
    getPhase(EphemPtr, Resolution, att, je, jep, &phase2);

    double incr = (phase2-phase1)/(double)(je-js);
    incr *= 1.0;

    int k = 0;
    for(k=0; k<=(je-js); k++){
      int ai = js+k;
      jep = js+ist+k;
      doLocation(EphemPtr, Resolution, att, k, ai, jep, phase1, incr);
    }

   

  }

  return;

}


void getPhase(EphemData *EphemPtr, double Resolution, Attitude *att, int js, int jep, double *phase ){


  double mjd = EphemPtr->MJD[jep];
  double amjd, bmjd;
  AtVect vSat;
  AtVect vaSat, vbSat, vNSat, vNbSat, vNaSat, vVelS, vNVelS, vNVelSp;

  AtRotMat UnitM, TRotZ;
  AtRotMat Eci2Sat, TEci2Sat, Sat2Eci;
  double Sra, Sdec, sra, sdec;
  AtPolarVect tpol;
  AtVect ecitar, sattar;
  double satDistance, earthSize;

  vSat[0] = EphemPtr->X[jep];
  vSat[1] = EphemPtr->Y[jep];
  vSat[2] = EphemPtr->Z[jep];


  Sra = att->SatRA[js]*DEG2RAD;
  Sdec = att->SatDEC[js]*DEG2RAD;

  if(jep+1 >= EphemPtr->ent ) { // Mind the boundaries 
    amjd = mjd + Resolution;
    vaSat[0] = InterPVect(mjd, amjd, vSat[0], vbSat[0], amjd);
    vaSat[1] = InterPVect(mjd, amjd, vSat[1], vbSat[1], amjd);
    vaSat[2] = InterPVect(mjd, amjd, vSat[2], vbSat[2], amjd);
  } else {
    amjd     = EphemPtr->MJD[jep+1];
    vaSat[0] = EphemPtr->X[jep+1];
    vaSat[1] = EphemPtr->Y[jep+1];
    vaSat[2] = EphemPtr->Z[jep+1];
  }

  if(jep == 0){  // if i-1 < 0
    bmjd     = mjd - Resolution;
    vbSat[0] = InterPVect(mjd, amjd, vSat[0], vaSat[0], bmjd);
    vbSat[1] = InterPVect(mjd, amjd, vSat[1], vaSat[1], bmjd);
    vbSat[2] = InterPVect(mjd, amjd, vSat[2], vaSat[2], bmjd);

  } else {
    bmjd     = EphemPtr->MJD[jep-1];
    vbSat[0] = EphemPtr->X[jep-1];
    vbSat[1] = EphemPtr->Y[jep-1];
    vbSat[2] = EphemPtr->Z[jep-1];

  }


  atNormVect(vSat, vNSat);  // normalize vector vSat 
  atNormVect(vbSat, vNbSat);  // normalize vector vbSat 
  atNormVect(vaSat, vNaSat);  // normalize vector vaSat 

  vVelS[0] = (vNaSat[0] - vNbSat[0])/(2.0*Resolution);
  vVelS[1] = (vNaSat[1] - vNbSat[1])/(2.0*Resolution);
  vVelS[2] = (vNaSat[2] - vNbSat[2])/(2.0*Resolution);
  atNormVect(vVelS, vNVelS);  // normalize vector vaSat 


  setUnit(UnitM);
  RotateOnZ(Sra, UnitM, TRotZ);

  RotateOnY((90.0*DEG2RAD-Sdec), TRotZ, TEci2Sat);
  atRotVect(TEci2Sat, vNVelS, vNVelSp);
  double psi = atan2(vNVelSp[1], vNVelSp[0]);
  RotateOnZ(psi, TEci2Sat, Eci2Sat);

  TransposeM(Eci2Sat, Sat2Eci);

  satDistance = atNorm(vSat);
  earthSize = EARTH_RADIUS*sin(EARTH_RADIUS / satDistance);

  sra  = att->Zra[js]*DEG2RAD;
  sdec = att->Zdec[js]*DEG2RAD;


  tpol.lon = sra ;
  tpol.lat = sdec ;
  tpol.r   = 1.0;

  AtVect tpos;
  atPolToVect(&tpol, tpos); 
  atPrecession(MJD_J2000, tpos, mjd, ecitar);




  atPolToVect(&tpol, ecitar);
      
  atRotVect(Eci2Sat, ecitar, sattar);

  *phase = atan2(sattar[1], sattar[0]);

    
  return;
 
}

void doLocation(EphemData *EphemPtr, double Resolution, Attitude *att, 
		int k, int js, int jep, double phase, double incr){


  double mjd = EphemPtr->MJD[jep];
  double amjd, bmjd;
  AtVect vSat;
  AtVect vaSat, vbSat, vNSat, vNbSat, vNaSat, vVelS, vNVelS, vNVelSp;

  AtRotMat UnitM, TRotZ;
  AtRotMat Eci2Sat, TEci2Sat, Sat2Eci;
  double Sra, Sdec;
  double satDistance;

  vSat[0] = EphemPtr->X[jep];
  vSat[1] = EphemPtr->Y[jep];
  vSat[2] = EphemPtr->Z[jep];


  Sra = att->SatRA[js]*DEG2RAD;
  Sdec = att->SatDEC[js]*DEG2RAD;

  if(jep+1 >= EphemPtr->ent ) { // Mind the boundaries 
    amjd = mjd + Resolution;
    vaSat[0] = InterPVect(mjd, amjd, vSat[0], vbSat[0], amjd);
    vaSat[1] = InterPVect(mjd, amjd, vSat[1], vbSat[1], amjd);
    vaSat[2] = InterPVect(mjd, amjd, vSat[2], vbSat[2], amjd);
  } else {
    amjd     = EphemPtr->MJD[jep+1];
    vaSat[0] = EphemPtr->X[jep+1];
    vaSat[1] = EphemPtr->Y[jep+1];
    vaSat[2] = EphemPtr->Z[jep+1];
  }

  if(jep == 0){  // if i-1 < 0
    bmjd     = mjd - Resolution;
    vbSat[0] = InterPVect(mjd, amjd, vSat[0], vaSat[0], bmjd);
    vbSat[1] = InterPVect(mjd, amjd, vSat[1], vaSat[1], bmjd);
    vbSat[2] = InterPVect(mjd, amjd, vSat[2], vaSat[2], bmjd);

  } else {
    bmjd     = EphemPtr->MJD[jep-1];
    vbSat[0] = EphemPtr->X[jep-1];
    vbSat[1] = EphemPtr->Y[jep-1];
    vbSat[2] = EphemPtr->Z[jep-1];

  }


  atNormVect(vSat, vNSat);  // normalize vector vSat 
  atNormVect(vbSat, vNbSat);  // normalize vector vbSat 
  atNormVect(vaSat, vNaSat);  // normalize vector vaSat 

  vVelS[0] = (vNaSat[0] - vNbSat[0])/(2.0*Resolution);
  vVelS[1] = (vNaSat[1] - vNbSat[1])/(2.0*Resolution);
  vVelS[2] = (vNaSat[2] - vNbSat[2])/(2.0*Resolution);
  atNormVect(vVelS, vNVelS);  // normalize vector vaSat 


  setUnit(UnitM);
  RotateOnZ(Sra, UnitM, TRotZ);

  RotateOnY((90.0*DEG2RAD-Sdec), TRotZ, TEci2Sat);
  atRotVect(TEci2Sat, vNVelS, vNVelSp);
  double psi = atan2(vNVelSp[1], vNVelSp[0]);
  RotateOnZ(psi, TEci2Sat, Eci2Sat);

  TransposeM(Eci2Sat, Sat2Eci);

  satDistance = atNorm(vSat);
  double beta = phase+((double)k)*incr;

  double theta = 149.99999*DEG2RAD-asin(EARTH_RADIUS/satDistance);

  AtVect Pos;
  Pos[0] = sin(theta)* cos(beta);
  Pos[1] = sin(theta)* sin(beta);
  Pos[2] = cos(theta);

  AtVect Ftar, NFtar;
  atRotVect(Sat2Eci, Pos, Ftar);

  atNormVect(Ftar, NFtar);  // normalize vector vSunsat   
  double sxy = sqrt(NFtar[0]*NFtar[0]+NFtar[1]*NFtar[1]);
  double Tra = atan2(NFtar[1],NFtar[0])*RAD2DEG;

  if(Tra < 0.0){
    Tra = Tra+360.0;
  }
  double Tdec = atan2(sxy, NFtar[2])*RAD2DEG;
  Tdec = 90.0 - Tdec;

  double RaDe[11];	

  GetPointedPos(mjd, vSat, vNVelS, Tra, Tdec, RaDe);


  att->mjd[js]    = mjd;
  att->SatRA[js]  = RaDe[0];
  att->SatDEC[js] = RaDe[1];
  att->Xra[js]    = RaDe[6];
  att->Xdec[js]   = RaDe[7];
  att->Yra[js]    = RaDe[4];
  att->Ydec[js]   = RaDe[5];
  att->Zra[js]    = RaDe[2];
  att->Zdec[js]   = RaDe[3];

  return;
}
