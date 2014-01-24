/**
 * @file functUtil.cc
 * @brief This file contains functions miscellaneous utility functions
 * @author Giuseppe Romeo
 * @date Created:  Nov 15, 2005
 * 
 * $Header: /nfs/slac/g/glast/ground/cvs/ScienceTools-scons/orbitSim/src/functUtil.cxx,v 1.9 2010/12/20 19:30:14 cohen Exp $
 */
#include "../include/functions.h"
#include "../include/atFunctions.h"
#include "../include/OrbSim.h"

#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string>

#include <iostream>
#include <iomanip>
#include <sstream>

#include "../include/Stream.h"
#include "../include/StreamFormatter.h"
#include "../include/st_stream.h"

#include <algorithm>    // std::max
  /// Stream to control output through verbosity level
st_stream::StreamFormatter fosf("functUtil", "", 2);

/*  This is a julian date routine, converting any calender date to
    Modified Julian Date.  It is adapted from numerical recipes */

double do_cal2mjd(int iyyy, int mm, int id, int hour, int min, int sec)
{
  long jul;
  int ja, jy, jm;
  double MJD, UT;
  const double hourInDay = 24.0;

  fosf.setMethod("do_cal2mjd");

  jy = iyyy;

  /*  Convert time to fraction of a day */
  UT = hour/hourInDay +  min/minInDay + sec/secInDay;

  if (jy == 0)
    {
      fosf.err() << "ERROR-- there is no year zero, adjusting to year 1\n";
      jy = 1;
    }
  if (jy < 0) ++jy;
  if (mm > 2)
    jm = mm + 1;
  else
    {
      --jy;
      jm=mm+13;
    }
  jul = (long) (floor(365.25*jy)+floor(30.6001*jm)+id+1720995);
  /* gregorian reference number based on (15+31L*(10+12L*1582)) */
  if (id+31L*(mm+12L*iyyy) >= 588829)
    {
      ja = (int)(0.01*jy);
      jul += 2-ja+(int) (0.25*ja);
    }
  
  MJD = (double)jul - 0.5 +  UT - 2400000.5; /* converts to MJD */
  
  return(MJD);
  
}


void do_mjd2cal(double MJD, int *iyyy, int *mm, int *id, int *hour, int *min, int *sec)
{
  long jdate;
  long ja,jalpha,jb,jc,jd,je;
  double utcalc, UT;

  fosf.setMethod("do_mjd2cal");

  MJD = MJD + 2400000.5; /* convert from MJD to JD for internal use */

  utcalc = (double) (MJD+0.5 - (int)(MJD+0.5));
  UT = utcalc; /* keep as decimal days */
  MJD = MJD - UT;
 
  jdate = (long) (MJD+0.5); /* ignore UT effect right now */
 
  if (jdate >=  2299161)

    {
      jalpha = (long)(((double) (jdate-1867216)-0.25)/36524.25);
      ja = jdate + 1 + jalpha - (long) (0.25*jalpha);
    }
  else
    ja = jdate;
  jb = ja+1524;
  jc = (long)(6680.0+((double) (jb-2439870)-122.1)/365.25);
  jd = (long)(365*jc+(0.25*jc));
  je = (long)((jb-jd)/30.6001);

  *id = jb-jd-(long) (30.6001*je);
  *mm=je-1;
  if (*mm > 12) *mm-=12;
  *iyyy=jc-4715;
  if (*mm > 2) --(*iyyy);
  if (*iyyy <= 0)--(*iyyy);

  *hour = (int)(UT*24);
  *min = (int)( 0.5+ (UT*24.0-*hour)*60.0 ); /* the 0.5 helps round properly
						 to the nearest minute! */

  if (*min == 60 || *hour == 24) {
    if (*hour != 24 && *min == 60) { /* somewhat common round-off fix event */
      ++*hour;
      *min = 0;
    }
    if (*hour == 24) {
      fosf.warn() << "Warning: time reads " << *hour << ":" << *min << "\n";
    }
  }

  *sec = (int) (0.5+(((UT*24.0-*hour)*60.0)-*min)*60.0);

}


void do_mjd2utc(double mjd, int *yyy, int *doy, int *hh, int *mm, int *ss){

  int month, dom, leapday;

  int DaysMonth[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};


  do_mjd2cal(mjd, yyy, &month, &dom, hh, mm, ss);


  leapday = 0;
  if (*yyy % 4 == 0)
    leapday = 1;

  *doy = DaysMonth[month-1];
  

  *doy = *doy+leapday+dom;

  return;
  


}


double do_utcj2mjd (int iyyy, int doy, int hour, int min, int sec)
{
  /* The following array contains the last day of year
     in that month (index 3 is March and day of year 90 is Mar 31), adjust for 
     leap year in code.
                       NA  J  F   M   A    M    J    J    A    S    O    N     D    */
  int DaysMonth[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

  int i, month, dom, leapday;
  double mjd;

  fosf.setMethod("do_utcj2mjd");
  dom=0;
  leapday = 0;
  if (iyyy % 4 == 0)
    leapday = 1;

  if (doy < 1 || doy > 365 + leapday){
    fosf.err() << "Wrong day of year: " << doy << "\n";
    return (0.0);
  }

  month=0;
  i= 1;
  while (month == 0)
  {
    if (i > 1 && leapday)
    {
      if (doy <= (DaysMonth[i]+ leapday))
      {
	  month = i;
	  dom = doy - DaysMonth[i - 1];
	  if (i > 2)       /* exclude Feb here */
	    dom--;
      }
    }
    else
      if (doy <= DaysMonth[i])
      {
	month = i;
        dom = doy - DaysMonth[i - 1];
      }

    i++;
  }


  mjd = do_cal2mjd (iyyy, month, dom, hour, min, sec);



  return (mjd);

}

double do_met2mjd(double met) {

  double mjd = met/secInDay + MJDREF;

  return mjd;

}

double do_mjd2met(double mjd) {

  double met = (mjd - MJDREF)*secInDay;

  return met;

}

double getMJD(char *ln){

  // Removing initial backslashes and space
  char *jnk = ln;
  ++jnk; ++jnk; ++jnk;
  char *TL;
  TL = strtok(jnk, " ");
  int yyy, doy, hh, mm, ss;

  sscanf(TL, "%d/%d:%d:%d:%d", &yyy, &doy, &hh, &mm, &ss);

  double mjdt = do_utcj2mjd (yyy, doy, hh, mm, ss);

  return mjdt;


}

/*
 * Match string against the extended regular expression in
 * pattern, treating errors as no match.
 *
 * return 1 for match, 0 for no match
 */




int match_str(const char *string, const char *pattern) {

  const int len = strlen(pattern);
  const int slen = strlen(string);

  char *UpStr = capitalize_str(string, slen);

  char *PAT = capitalize_str(pattern, len);

  int match = 0;

  fosf.setMethod("match_str");

  fosf.info(3) << "string="<< UpStr <<" ===> pattern="<< PAT <<"\n";

  int i, j;
  char c;
  char *STR;

  char s;


  char *NPAT;
  NPAT = (char *) malloc((len-1) * sizeof(char));

  s = PAT[len-1];

  STR = (char *) malloc((len+1) * sizeof(char));

  if(strncmp(PAT, "^", 1) == 0 && s == '$'){
    int nlen = len - 1;

    c = UpStr[0];
    sprintf(STR, "%c", c);
    sprintf(NPAT, "%c", PAT[1]);

    for(j=1; j<nlen-1; j++){
      c=UpStr[j];
      sprintf(STR, "%s%c", STR, c);

      if(j<len-1)
	sprintf(NPAT, "%s%c", NPAT, PAT[j+1]);
    }

    if(strcmp(STR, NPAT) == 0 && slen == len-2){
      fosf.info(4) << "EXACT match: STR="<<STR<<" ===> NPAT="<<NPAT<<", MATCH FOUND\n";
      match = 1;
    }

  
    //  }else if(strncmp(PAT, "^", 1) == 0 && strcmp(s, "$") != 0){
  }else if(strncmp(PAT, "^", 1) == 0 && s != '$'){
    c = UpStr[0];
    sprintf(STR, "%c", c);
    sprintf(NPAT, "%c", PAT[1]);

    for(j=1; j<len-1; j++){
      c=UpStr[j];
      sprintf(STR, "%s%c", STR, c);

      if(j<len-1)
	sprintf(NPAT, "%s%c", NPAT, PAT[j+1]);
    }

    if(strcmp(STR, NPAT) == 0){
      fosf.info(4) << "BEGIN match: STR="<<STR<<" ===> NPAT="<<NPAT<<", MATCH FOUND\n";
      match = 1;
    }


  } else if (s == '$' && strncmp(PAT, "^", 1) != 0){
    int nlen = len - 1;
    c = UpStr[slen-nlen];
    sprintf(STR, "%c", c);
    sprintf(NPAT, "%c", PAT[0]);

    for(j=slen-nlen+1; j<slen; j++){
      c=UpStr[j];
      sprintf(STR, "%s%c", STR, c);

      sprintf(NPAT, "%s%c", NPAT, PAT[j-slen+nlen]);
    }

    if(strcmp(STR, NPAT) == 0){
      fosf.info(4) << "END match: STR="<<STR<<" ===> NPAT="<<NPAT<<", MATCH FOUND\n";
      match = 1;
    }

      
  } else {

    for(i=0; i<slen-len+1; i++){
      c = UpStr[i];
      sprintf(STR, "%c", c);

      for(j=i+1; j<len+i; j++){
	c=UpStr[j];
	sprintf(STR, "%s%c", STR, c);
      }

      if(strcmp(STR, PAT) == 0){
	match = 1;
	fosf.info(4) << "ANY match: STR="<<STR<<" ===> PAT="<<PAT<<", MATCH FOUND\n";
	break;
      }
    }

  }


  free(NPAT);
  free(STR);

  fosf.info(3) << "Returning with match="<<match<<"\n";
  return match;
}




char * capitalize_str(const char *str, const int len) {

  int i=1;
  char c;
  char *STR;
  STR = (char *) malloc((len+1) * sizeof(char));
  c = str[0];
  sprintf(STR, "%c", toupper(c));
  while (str[i]){
   
    c=str[i];
    sprintf(STR, "%s%c", STR, toupper(c));
    i++;
  }

  return STR;
}


int match2str(const char *string, const char *pattern1, const char *pattern2) {

  const int len = strlen(string);

  const int patlen1 = strlen(pattern1);

  const int patlen2 = strlen(pattern2);

  if(len < (patlen1+patlen2)){
    return 0;
  }

  char *ln;
  ln = (char *) malloc((len+1) * sizeof(char));

  strcpy(ln, string);

  if(match_str(ln, pattern1) != 1){
    return 0;
  }


  int i = 0;
  if(pattern1[0] != '^'){
    
    //    char pat1[patlen1+1];
    char *pat1;
    pat1 = (char *) malloc((patlen1+1) * sizeof(char));

    strcpy(pat1, "^");
    strcat(pat1, pattern1);

    while(match_str(ln, pat1) != 1){
      ++ln;
    }

    for(i=0; i<patlen1+1; i++){
      ++ln;
    }

    free(pat1);
  } else {

    while(match_str(ln, pattern1) != 1){
      ++ln;
    }

    for(i=0; i<patlen1; i++){
      ++ln;
    }

  }

  
  while(ln[0] == ' '){
    ++ln;
  }

  if(match_str(ln, pattern2) != 1){
    free(ln);
    return 0;
  }

  free(ln);
  return 1;
}



//  This function is a replacement for:
//(match((const char*) ln, "^[0-9]{4}-[0-9]{3}-[0-9]{2}:[0-9]{2}:[0-9]{2}.[0-9]{6}[ ]*[|][ ]*[A-Za-z]+[ ]*[|][ ]*Maneuver[ ]*[|]") == 1)
//since regular expressions cannot be used in Win32


int checkManeuver(const char *str){

  const int len = strlen(str);

  char *ln;
  ln = (char *) malloc((len+1) * sizeof(char));

  strcpy(ln, str);
  strcat(ln, "\0");


  if(checkDate(ln) != 1){
    return 0;
  }

  char *str1 = processline(ln, '|');
  char *str2 = processline(str1, '|');

  
  while(str2[0] == ' '){
    ++str2;
  }

  if(match_str(str2, "^Maneuver") != 1){
    free(ln);
    return 0;
  }

  free(ln);
  return 1;
}


//match((const char*) ln, "^[0-9]{4}-[0-9]{3}-[0-9]{2}:[0-9]{2}:[0-9]{2}.[0-9]{6}[ ]*[|][ ]*Maneuver[ ]*[|][ ]*Zenith[ ]*Point[ ]*[|]")

int checkManZenith(const char *str){


  const int len = strlen(str);

  char *ln;
  ln = (char *) malloc((len+1) * sizeof(char));

  strcpy(ln, str);
  strcat(ln, "\0");

  if(checkDate(ln) != 1){
    free(ln);
    return 0;
  }

  char *str1 = processline(ln, '|');

  while(str1[0] == ' '){
    ++str1;
  }

  if(match_str(str1, "^Maneuver") != 1){
    return 0;
  }
  
  char *str2 = processline(ln, '|');

  while(str2[0] == ' '){
    ++str2;
  }

  if(match_str(str2, "^Zenith") != 1){
    free(ln);
    return 0;
  }

  int i = 0;
  for(i=0; i<6; i++){
    ++str2;
  }

  while(str2[0] == ' '){
    ++str2;
  }

  if(match_str(str2, "^Point") != 1){
    free(ln);
    return 0;
  }


  free(ln);
  return 1;
}


int checkDate(char *ln){


  int datelen = 27;

  int lenstr = strlen(ln);

  if(datelen > lenstr){
    return 0;
  } 

  
  int i = 0;
  char s;

  // 2 0 0 7 - 1 9 3 - 0  0  :  0  0  :  0  0  :  0  0  .  0  0  0  0  0  0
  // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
  for(i=0; i<datelen; i++){
    s = ln[i];

    if(i<4 || (i>4 && i<8) || (i>8 && i<11) || 
       (i>11 && i<14) || (i>14 && i<17) || (i>17 && i<20) || i>20) {
       if (isdigit(ln[i]) == 0){
	 return 0;
       }

    } else if(i==4 || i==8){
      if(s != '-'){
	return 0;
      }
    } else if(i==11 || i==14 || i==17){
      if(s != ':'){
	return 0;
      }

    } else if(i==20){
      if(s != '.'){
	return 0;
      }

    }

  }

  return 1;
}



int chkStr (char *str) {

  const int len = strlen(str);
  int i = 0;

  // Removing initial spaces

  while (i<len && str[0] == ' '){
    ++str;
  }

  char *str1 = str;

  const int len1 = strlen(str1);
  while(i<len1){
    
    if(str1[0] == '\0' || str1[0] == ' ')
      break;


    if(str1[0] == '.' || 
       (str1[0] == '-') || 
       (str1[0] == '+')){

    } else if (isdigit((const char)str1[0])){

    } else {
      return 0;
    }



    ++str1;
    i++;
  }


  return 1;
}




double InterPVect(double y1, double y2, double x1, double x2, double x0) {

  double a, b, y0;

  a = (y1-y2)/(x1-x2);

  b = y1 - a*x1;


  y0 = a*x0+b;

  return y0;
}


void GetPos(double mjd, AtVect vSat, AtVect vNVel, double SurvOfs, double *RVal){

/*
 * Subroutine: GetPos
 *
 * Purpose: compute the pointing info
 *
 * Parameters:
 *   i - index into the ephemeris array (used in debug prints)
 *   mjd - time
 *   vSat -  spacecraft position vector (X,Y,X)
 *   vNVel - normalized spacecraft velocity vector 
 *   SurvOfs - radians, desired offset of boresight from zenith
 *             negative is toward the north, positive is toward the south (MJM)
 *   RVal - pointer to array in which to return the pointing info
 *            RVal[0] = degrees, spacecraft right ascension
 *            RVal[1] = degrees, spacecraft declination
 *            RVal[2] = degrees, spacecraft pointing right ascension ;
 *            RVal[3] = degrees, spacecraft pointing declination
 *            RVal[4] = degrees, RA where the spacecraft y-axis is pointing
 *            RVal[5] = degrees, Declination where the spacecraft y-axis is pointing
 *            RVal[6] = Sun vector, x
 *            RVal[7] = Sun vector, y
 *            RVal[8] = Sun vector, z
 *            RVal[9] = degrees, right ascension of the sun;
 *            RVal[10] = degrees, declination of the sun
 *
 */

/*
  sra, sdec are the spacecraft right Ascension and declination
  pra, pdec is where the spacecraft is pointing
  rra, rdec is where the spacecraft x-axis is pointing
  apra, apdec is where the spacecraft y-axis is pointing
*/
  double sxy, sra, sdec, psi, rra, rdec, rsxy, Sra, Sdec;  
  double apra, apdec, apxy, pra, pdec, pxy;
  AtRotMat UnitM, TRotZ;
  AtRotMat TEci2Sat, Eci2Sat, TSat2Eci, Sat2Eci;
  AtRotMat TBody2Eci, Body2Eci, TEci2Body, Eci2Body;
  AtVect vFT, vFTECI, vNFTECI;
  AtVect vNVelSp, vNSat;
  AtVect vSun, vSunsat, vNSun, vNEciSun;
  double BSunAngle;
  double kmconv;

  fosf.setMethod("GetPos");
//  AtVect Temp1, NTemp1;
//  double angleB;

  atNormVect(vSat, vNSat);  /* normalize vector vSunsat */  
  sxy = sqrt(vNSat[0]*vNSat[0]+vNSat[1]*vNSat[1]);
  sra = atan2(vNSat[1],vNSat[0]);
  sdec = atan2(sxy, vNSat[2]);
  if(sra < 0.0){
    sra = sra+(360.0*DEG2RAD);
  }


  if (mjd > 1000000.0){

    fosf.err() << "GetPos: bad data input. returning 0 vector\n";
    int j=0;
    for( ; j<10; j++) RVal[j] = 0.0;
  }

  setUnit(UnitM);
  RotateOnZ(sra, UnitM, TRotZ);
  RotateOnY(sdec, TRotZ, TEci2Sat);

  /*
    Calculating the velocity vector in the primed system of reference
  */    
  TransposeM(TEci2Sat, TSat2Eci);
  vFT[0] = 0.0;
  vFT[1] = 0.0;
  vFT[2] = 1.0;
  atRotVect(TSat2Eci, vFT, vFTECI);



  atRotVect(TEci2Sat, vNVel, vNVelSp);
  psi = atan2(vNVelSp[1], vNVelSp[0]);
  RotateOnZ(psi, TEci2Sat, Eci2Sat);
  TransposeM(Eci2Sat, Sat2Eci);


  vFT[0] = 0.0;
  vFT[1] = 0.0;
  vFT[2] = 1.0;
  atRotVect(Sat2Eci, vFT, vFTECI);


  atNormVect(vFTECI, vNFTECI);  /* normalize vector vSunsat */  
  rsxy = sqrt(vNFTECI[0]*vNFTECI[0]+vNFTECI[1]*vNFTECI[1]);
  rra = atan2(vNFTECI[1], vNFTECI[0]);
  rdec = atan2( vNFTECI[2], rsxy);

  if(rra < 0.0){
    rra = rra+360.0*DEG2RAD;
  }
  rdec = (90.0*DEG2RAD - rdec);

  if(fabs(sra-rra) > 1.0e-10 || fabs (sdec-rdec) > 1.0e-10) {
    AtVect xyz2;
    rade2xyz( sra*RAD2DEG,  sdec*RAD2DEG, xyz2);
    fosf.info().precision(15);
    fosf.info() << "1) sra=" << sra << "   sdec=" << sdec << "\n3) rra=" << rra << "   rdec=" << rdec << "\n";
    fosf.info() << "vNFTECI[0]=" << vNFTECI[0] << ", vNFTECI[1]=" << vNFTECI[1] << ", vNFTECI[2]=" << vNFTECI[2] << "\n";
    fosf.info() << "   xyz2[0]=" << xyz2[0] << ",    xyz2[1]=" << xyz2[1] << ",    xyz2[2]=" << xyz2[2] << "\n";
    fosf.info() << "  vNSat[0]=" << vNSat[0] << ",   vNSat[1]=" << vNSat[1] << ",   vNSat[2]=" << vNSat[2] << "\n";
  }



  /* Test to determine velcity vector direction */
  /*
  double r;
  AtVect vNVelSat;
  atRotVect(Eci2Sat, vNVel, vNVelSat);

  vFT[0] = 0.0;
  vFT[1] = 0.0;
  vFT[2] = 1.0;
  atAngDistance(vNVelSat,vFT,&r);
  std::cout << "Angular distance between velocity Vector and Z axis in satellatie frame" << r*RAD2DEG << std::endl;
  vFT[0] = 1.0;
  vFT[1] = 0.0;
  vFT[2] = 0.0;  
  atAngDistance(vNVelSat,vFT,&r);
  std::cout << "Angular distance between velocity Vector and X axis in satellatie frame" << r*RAD2DEG << std::endl;
  vFT[0] = 0.0;
  vFT[1] = 1.0;
  vFT[2] = 0.0;
  atAngDistance(vNVelSat,vFT,&r);
  std::cout << "Angular distance between velocity Vector and Y axis in satellatie frame" << r*RAD2DEG << std::endl;
  */
   

  /*******************************************************************************

  This is the final transformation. In order to do that, we define the 
  satellite body frame as follows:
  a) z-axis along the previoulsy defined axis, or in other words along the
     detector axis
  b) y-axis along the solar panels
  c) x-axis along the satellite radiators

  Three constraints must be satisfied during survey:
  1) the z-axis will be pointing with a rocking angle of +/- a given offset
     therefore, we make a clockwise rotation along the x'-axis

  2) the solar panels must always be normal to the local sun vector, so 
     the projection of the local sun vector on the local x-y plane must 
     be parallel or anti-parallel to the local x-axis (see below)

  3) if the local sun vector makes angle smaller than 10 degrees with the 
     local x-axis, a "yaw-flip" maneuvering (TBD) must take place making sure
     that the radiators are not facing the sun.

  *******************************************************************************/

  /*
    first rotate clockwise along the x'-axis of SurvOfs
  */
  //Giuseppe fixed this somewhere in read_ephem, but there really should
  //be a minus sign here.
  //RotateOnX(-SurvOfs, Eci2Sat, TEci2Body);
  RotateOnX(SurvOfs, Eci2Sat, TEci2Body);
    
  TransposeM(TEci2Body, TBody2Eci);

  /* 
     Calculating the alterante pointing place in case of
     a change in the rocking angle
  */
  vFT[0] = 0.0;
  vFT[1] = sin(-SurvOfs*2.0);
  vFT[2] = cos(SurvOfs*2.0);
  atRotVect(TBody2Eci, vFT, vFTECI);

  atNormVect(vFTECI, vNFTECI);

  




  /* Get current sun vector in ECI */

  if (mjd > 1000000.0) {
    fosf.warn() << "WARNING: Not calling atSun, mjd= " << mjd << "\n";
    vSun[0] = 0.0;
    vSun[1] = 0.0;
    vSun[2] = 0.0;
  } else {
    atSun(mjd, vSun);
  }

  /* convert to km */
  kmconv = 149600000.0/60.0;   /* atSun returns a vector using distance 60(?) */
  vSun[0] = kmconv * vSun[0];
  vSun[1] = kmconv * vSun[1];
  vSun[2] = kmconv * vSun[2];
  /* Get the sun vector in ECI referenced to the spacecraft (this is why we converted to km)*/
  vSun[0] = vSun[0] - vSat[0];
  vSun[1] = vSun[1] - vSat[1];
  vSun[2] = vSun[2] - vSat[2];
 
  /* Rotate the Sun vector into spacecraft frame */
  atRotVect(TEci2Body, vSun, vSunsat);
  atNormVect(vSunsat, vNSun);  /* normalize vector vSunsat */


  atNormVect(vSun, vNEciSun);  /* normalize vector vSunsat */  
  rsxy = sqrt(vNEciSun[0]*vNEciSun[0]+vNEciSun[1]*vNEciSun[1]);
  rra = atan2(vNEciSun[1],vNEciSun[0]);
  rdec = atan2(rsxy, vNEciSun[2]);

  rsxy = sqrt(vSun[0]*vSun[0]+vSun[1]*vSun[1]);
  Sra = atan2(vSun[1],vSun[0]);
  Sdec = atan2(rsxy, vSun[2]);



  /*
    Calculating the angle between x-axis of the body frame, and the 
    local sun vector:
  */

  BSunAngle = atan2(vNSun[1], vNSun[0]);

  /*******************************************************************************

    Finally, rotate counter-clockwise around the local Z-axis of angle
    BSunAngle

  *******************************************************************************/
  RotateOnZ(BSunAngle, TEci2Body, Eci2Body);
  TransposeM(Eci2Body, Body2Eci);

  /*
    yaw flip TBD......
  */

    

  /*******************************************************************************

    Finally, let's get ra and dec of the observing point during survey

  *********************************************************************************/

    

  sra  = sra*RAD2DEG;
  sdec = sdec*RAD2DEG;
  /*
  we define the DAMPE satellite body frame as follows:
  a) z-axis pointing into the Eart (-Zenith )
  b) y-axis defined using right hand rule (solar panel) 
  c) x-axis along the satellite motion direction
  */
  /*
  we define the FERMI satellite body frame as follows:
  a) z-axis pointing outside from the Eart (zenith plus an offset)
  b) y-axis along the solar panel
  c) x-axis along the satellite radiators
  */



  // Make modification to move from FERMI ref to DAMPE ref Inversion in Z axis direction
  /*
  vFT[0] = 0.0;
  vFT[1] = 0.0;
  vFT[2] = 1.0;
  */

  vFT[0] = 0.0;
  vFT[1] = 0.0;
  vFT[2] = -1.0;
  atRotVect(Body2Eci, vFT, vFTECI);
  pxy = sqrt(vFTECI[0]*vFTECI[0]+vFTECI[1]*vFTECI[1]);
  pra = atan2(vFTECI[1],vFTECI[0]);
  pdec = atan2(pxy, vFTECI[2]);
  pra  = pra*RAD2DEG;
  pdec = pdec*RAD2DEG;


  vFT[0] = 0.0;
  vFT[1] = 1.0;
  vFT[2] = 0.0;
  atRotVect(Body2Eci, vFT, vFTECI);
  apxy = sqrt(vFTECI[0]*vFTECI[0]+vFTECI[1]*vFTECI[1]);
  apra = atan2(vFTECI[1],vFTECI[0])*RAD2DEG;
  apdec = atan2(apxy, vFTECI[2])*RAD2DEG;





  vFT[0] = 1.0;
  vFT[1] = 0.0;
  vFT[2] = 0.0; 
  atRotVect(Body2Eci, vFT, vFTECI);
  apxy = sqrt(vFTECI[0]*vFTECI[0]+vFTECI[1]*vFTECI[1]);
  rra = atan2(vFTECI[1],vFTECI[0])*RAD2DEG;
  rdec = atan2(apxy, vFTECI[2])*RAD2DEG;

  if(sra < 0.0){
    sra += 360.0;
  }
  sdec = 90.0-sdec;


  if(pra < 0.0){
    pra += 360.0;
  }
  pdec = 90.0-pdec;

  if(apra < 0.0){
    apra += 360.0;
  }
  apdec = 90.0-apdec;

  if(rra < 0.0){
    rra += 360.0;
  }
  rdec = 90.0-rdec;

  if(Sra < 0.0){
    Sra += 360.0;
  }
  Sdec = 90.0-Sdec;


  RVal[0]  = sra;
  RVal[1]  = sdec;
  RVal[2]  = pra;
  RVal[3]  = pdec;
  RVal[4]  = apra;
  RVal[5]  = apdec;
  RVal[6]  = rra;
  RVal[7]  = rdec;
  RVal[8]  = vNSun[0];
  RVal[9]  = vNSun[1];
  RVal[10] = vNSun[2];
  

  return;

} /* end GetPos */




void TransposeM (AtRotMat rm, AtRotMat Trm){

  int i, j;
  for(i=0; i<3; i++){
    for(j=0; j<3; j++){
      Trm[i][j] = rm[j][i];
    }
  }

  return;
} 


void setUnit(AtRotMat rm){

  int i,j;

  for(i=0; i<3; i++){
    for(j=0; j<3; j++){
      if(i==j){
	rm[i][j] = 1.0;
      }else{
	rm[i][j] = 0.0;
      }
    }
  }

  return;

}

void RotateOnX(double a, AtRotMat rm, AtRotMat Rmat){

/*
  Rotate counter-clockwise along the x'-axis of an angle a
*/
  double c, s;
  if(a<1e-5){
    a=0;
  }
  //std::cout << " a value " << a << std::endl;
  c = cos(a);
  s = sin(a);

  Rmat[0][0] = rm[0][0];
  Rmat[0][1] = rm[0][1];
  Rmat[0][2] = rm[0][2];

  Rmat[1][0] = rm[1][0]*c+rm[2][0]*s;
  Rmat[1][1] = rm[1][1]*c+rm[2][1]*s;
  Rmat[1][2] = rm[1][2]*c+rm[2][2]*s;


  Rmat[2][0] = -rm[1][0]*s+rm[2][0]*c; 
  Rmat[2][1] = -rm[1][1]*s+rm[2][1]*c;
  Rmat[2][2] = -rm[1][2]*s+rm[2][2]*c;  


  return;
}

void RotateOnY(double a, AtRotMat rm, AtRotMat Rmat){

/*
  Rotate counter-clockwise along the y'-axis of an angle a
*/
  double c, s;
  
  c = cos(a);
  s = sin(a);

  Rmat[0][0] = rm[0][0]*c-rm[2][0]*s;
  Rmat[0][1] = rm[0][1]*c-rm[2][1]*s;
  Rmat[0][2] = rm[0][2]*c-rm[2][2]*s;

  Rmat[1][0] = rm[1][0];
  Rmat[1][1] = rm[1][1];
  Rmat[1][2] = rm[1][2];

  Rmat[2][0] = rm[0][0]*s+rm[2][0]*c; 
  Rmat[2][1] = rm[0][1]*s+rm[2][1]*c;
  Rmat[2][2] = rm[0][2]*s+rm[2][2]*c;

  return; 

}
void RotateOnZ(double a, AtRotMat rm, AtRotMat Rmat){
/*
 Rotate counter-clockwise around the local Z-axis of angle a
*/
    
  double c, s;
  
  c = cos(a);
  s = sin(a);

  Rmat[0][0] = rm[0][0]*c+rm[1][0]*s;
  Rmat[0][1] = rm[0][1]*c+rm[1][1]*s;
  Rmat[0][2] = rm[0][2]*c+rm[1][2]*s; 

  Rmat[1][0] = -rm[0][0]*s+rm[1][0]*c;
  Rmat[1][1] = -rm[0][1]*s+rm[1][1]*c;
  Rmat[1][2] = -rm[0][2]*s+rm[1][2]*c; 

  Rmat[2][0] = rm[2][0];
  Rmat[2][1] = rm[2][1];
  Rmat[2][2] = rm[2][2];




  return;
}


/*
  Calculates the two constats for the great circle passing through
  position1, and position2.
*/
void getconsts( AtVect pos1,   AtVect pos2, double *consts){


  double tmp;

  if((pos2[2]*pos1[0]-pos1[2]*pos2[0]) != 0.0){
         consts[1] = atan ((pos1[2]*pos2[1] - pos2[2]*pos1[1])/
 		      (pos2[2]*pos1[0]-pos1[2]*pos2[0]));
    //    consts[1] = atan2 ((pos1[2]*pos2[1] - pos2[2]*pos1[1]),
    //		       (pos2[2]*pos1[0]-pos1[2]*pos2[0]));
  } else {
    if((pos1[2]*pos2[1] - pos2[2]*pos1[1]) < 0){
      consts[1] = RAD2DEG*270.0;
    }else {
      consts[1] = RAD2DEG*90.0;
    }
  }

  tmp = pos1[2]/(pos1[0]*sin(consts[1])+pos1[1]*cos(consts[1]));
  tmp = pos2[2]/(pos2[0]*sin(consts[1])+pos2[1]*cos(consts[1]));


  consts[0] = -sqrt(1.0/(tmp*tmp+1.0));


  return;
}


void getXYZ(AtVect r1, AtVect r2, double t1, double t2, double *consts, AtVect xyz, double fact){

  AtVect a, b, c;
  double delta, numx, numy, numz;




  a[0] = r1[0];
  a[1] = r1[1];
  a[2] = r1[2];

  b[0] = r2[0];
  b[1] = r2[1];
  b[2] = r2[2];

  c[0] = sin(consts[1]);
  c[1] = cos(consts[1]);
  c[2] = -1.0/sqrt((1.0/(consts[0]*consts[0])-1.0))*fact;

  delta = getDet(a, b, c);

  if(delta == 0.0){
    delta = 0.000001;
  }

  a[0] = t1;
  a[1] = r1[1];
  a[2] = r1[2];

  b[0] = t2;
  b[1] = r2[1];
  b[2] = r2[2];

  c[0] = 0;
  c[1] = cos(consts[1]);
  c[2] = -1.0/sqrt((1.0/(consts[0]*consts[0])-1.0))*fact;


  numx = getDet(a, b, c);
  xyz[0] = numx/delta;

  a[0] = r1[0];
  a[1] = t1;
  a[2] = r1[2];

  b[0] = r2[0];
  b[1] = t2;
  b[2] = r2[2];

  c[0] = sin(consts[1]);
  c[1] = 0.0;
  c[2] = -1.0/sqrt((1.0/(consts[0]*consts[0])-1.0))*fact;


  numy = getDet(a, b, c);
  xyz[1] = numy/delta;


  a[0] = r1[0];
  a[1] = r1[1];
  a[2] = t1;

  b[0] = r2[0];
  b[1] = r2[1];
  b[2] = t2;

  c[0] = sin(consts[1]);
  c[1] = cos(consts[1]);
  c[2] = 0.0;



  numz = getDet(a, b, c);
  xyz[2] = numz/delta;


  return;
}




double getDet(AtVect ra, AtVect rb, AtVect rc) {

  double det;

  det = ra[0]*rb[1]*rc[2] - ra[0]*rb[2]*rc[1] +
        ra[1]*rb[2]*rc[0] - ra[1]*rb[0]*rc[2] +
        ra[2]*rb[0]*rc[1] - ra[2]*rb[1]*rc[0];

  return det;

}




void rade2xyz( double ra,  double dec, AtVect xyz){


  double hpi = asin(1.0);

  double v = hpi-dec*DEG2RAD;
  double u = ra*DEG2RAD;

  xyz[0] = cos(u)*sin(v);
  xyz[1] = sin(u)*sin(v);
  xyz[2] = cos(v);

  return;
}


void angularSep(double pra, double pdec, double ra, double dec, double *theta){

  *theta = acos(std::min(std::max(cos(pdec)*cos(dec)*cos(pra-ra)+sin(pdec)*sin(dec),-1.0),1.0));
 
  return;
}


void getslewtime(double pra, double pdec, double ra, double dec, double res, double *slewt){

  double reso = res*minInDay;
  double slewR = SLEW_RATE/reso;
  double theta;

  angularSep(pra*DEG2RAD, pdec*DEG2RAD, ra*DEG2RAD, dec*DEG2RAD, &theta);
  *slewt = theta*RAD2DEG/slewR;
  
  *slewt = *slewt/minInDay;
  return;
}

void GetPointedPos(double mjd, AtVect vSat, AtVect vNVel, 
		   double ra, double dec, double *RVal){



/*
  sra, sdec are the spacecraft right Ascension and declination
  pra, pdec is where the spacecraft is pointing
  rra, rdec is where the spacecraft x-axis is pointing
  apra, apdec is where the spacecraft y-axis is pointing
*/
  double sxy, sra, sdec, psi, rra, rdec, rsxy, Sra, Sdec;  
  double apra, apdec, apxy, pra, pdec, pxy;
  AtRotMat UnitM, TRotZ;
  AtRotMat TEci2Sat, Eci2Sat, TSat2Eci, Sat2Eci;
  AtRotMat Body2Eci, Eci2Body;
  AtVect vFT, vFTECI, vNFTECI;
  AtVect vNVelSp, vNSat;
  AtVect vSun, vSunsat, vNSun, vNEciSun;
  double BSunAngle;
  double kmconv;

  fosf.setMethod("GetPointedPos");

  ra = ra*DEG2RAD;
  dec = dec*DEG2RAD;  

  atNormVect(vSat, vNSat);  /* normalize vector vSunsat */  
  sxy = sqrt(vNSat[0]*vNSat[0]+vNSat[1]*vNSat[1]);
  sra = atan2(vNSat[1],vNSat[0]);

  if(sra < 0.0){
    sra = sra+360.0*DEG2RAD;
  }
  sdec = atan2(sxy, vNSat[2]);


  if (mjd > 1000000.0)
    {
      fosf.warn() << __FILE__ << ":" << __LINE__ << ", WARNING: bad data input. returning 0 vector\n";
      int j=0;
      for( ; j<10; j++) RVal[j] = 0.0;
    }
  setUnit(UnitM);
  RotateOnZ(ra, UnitM, TRotZ);
  RotateOnY((90.0*DEG2RAD-dec), TRotZ, TEci2Sat);

  /*
    Calculating the velocity vector in the primed system of reference
  */    
  TransposeM(TEci2Sat, TSat2Eci);
  vFT[0] = 0.0;
  vFT[1] = 0.0;
  vFT[2] = 1.0;
  atRotVect(TSat2Eci, vFT, vFTECI);



  atRotVect(TEci2Sat, vNVel, vNVelSp);
  psi = atan2(vNVelSp[1], vNVelSp[0]);
  RotateOnZ(psi, TEci2Sat, Eci2Sat);
  TransposeM(Eci2Sat, Sat2Eci);
  

  vFT[0] = 0.0;
  vFT[1] = 0.0;
  vFT[2] = 1.0;
  atRotVect(Sat2Eci, vFT, vFTECI);





  atNormVect(vFTECI, vNFTECI);  /* normalize vector vSunsat */  
  rsxy = sqrt(vNFTECI[0]*vNFTECI[0]+vNFTECI[1]*vNFTECI[1]);
  rra = atan2(vNFTECI[1], vNFTECI[0]);
  rdec = atan2( vNFTECI[2], rsxy);

  if(rra < 0.0){
    rra = rra+360.0*DEG2RAD;
  }

  if(fabs(ra-rra) > 1.0e-10 || fabs (dec-rdec) > 1.0e-10) {
    AtVect xyz2;
    rade2xyz( ra*RAD2DEG,  dec*RAD2DEG, xyz2);


    fosf.info() << "1) sra=" << sra << "   sdec=" << sdec << "\n2)  ra=" << ra << "    dec=" << dec << "\n3) rra=" << rra << "   rdec=" << rdec << "\n";
    fosf.info() << "vNFTECI[0]=" << vNFTECI[0] << ", vNFTECI[1]=" << vNFTECI[1] << ", vNFTECI[2]=" << vNFTECI[2] << "\n";
    fosf.info() << "   xyz2[0]=" << xyz2[0] << ",    xyz2[1]=" << xyz2[1] << ",    xyz2[2]=" << xyz2[2] << "\n";
    fosf.info() << "  vNSat[0]=" << vNSat[0] << ",   vNSat[1]=" << vNSat[1] << ",   vNSat[2]=" << vNSat[2] << "\n";

  }

  /* Get current sun vector in ECI */

  if (mjd > 1000000.0) {
    fosf.warn() << "WARNING: Not calling atSun, mjd=" << mjd << "\n";
    vSun[0] = 0.0;
    vSun[1] = 0.0;
    vSun[2] = 0.0;
  } else {
    atSun(mjd, vSun);
  }

  /* convert to km */
  kmconv = 149600000.0/60.0;   /* atSun returns a vector using distance 60(?) */
  vSun[0] = kmconv * vSun[0];
  vSun[1] = kmconv * vSun[1];
  vSun[2] = kmconv * vSun[2];
  /* Get the sun vector in ECI referenced to the spacecraft (this is why we converted to km)*/
  vSun[0] = vSun[0] - vSat[0];
  vSun[1] = vSun[1] - vSat[1];
  vSun[2] = vSun[2] - vSat[2];
 
  /* Rotate the Sun vector into spacecraft frame */
  atRotVect(Eci2Sat, vSun, vSunsat);
  atNormVect(vSunsat, vNSun);  /* normalize vector vSunsat */


  atNormVect(vSun, vNEciSun);  /* normalize vector vSunsat */  
  rsxy = sqrt(vNEciSun[0]*vNEciSun[0]+vNEciSun[1]*vNEciSun[1]);
  rra = atan2(vNEciSun[1],vNEciSun[0]);
  rdec = atan2(rsxy, vNEciSun[2]);

  rsxy = sqrt(vSun[0]*vSun[0]+vSun[1]*vSun[1]);
  Sra = atan2(vSun[1],vSun[0]);
  Sdec = atan2(rsxy, vSun[2]);



  /*
    Calculating the angle between x-axis of the body frame, and the 
    local sun vector:
  */

  BSunAngle = atan2(vNSun[1], vNSun[0]);

  /*******************************************************************************

    Finally, rotate counter-clockwise around the local Z-axis of angle
    BSunAngle

  *******************************************************************************/
  RotateOnZ(BSunAngle, Eci2Sat, Eci2Body);
  TransposeM(Eci2Body, Body2Eci);

    

  /*******************************************************************************

    Finally, let's get ra and dec of the observing point during survey

  *********************************************************************************/

    

  sra  = sra*RAD2DEG;
  sdec = sdec*RAD2DEG;

  vFT[0] = 0.0;
  vFT[1] = 0.0;
  vFT[2] = 1.0;
  atRotVect(Body2Eci, vFT, vFTECI);
  pxy = sqrt(vFTECI[0]*vFTECI[0]+vFTECI[1]*vFTECI[1]);
  pra = atan2(vFTECI[1],vFTECI[0]);
  pdec = atan2(pxy, vFTECI[2]);
  pra  = pra*RAD2DEG;
  pdec = pdec*RAD2DEG;


  vFT[0] = 0.0;
  vFT[1] = 1.0;
  vFT[2] = 0.0;
  atRotVect(Body2Eci, vFT, vFTECI);
  apxy = sqrt(vFTECI[0]*vFTECI[0]+vFTECI[1]*vFTECI[1]);
  apra = atan2(vFTECI[1],vFTECI[0])*RAD2DEG;
  apdec = atan2(apxy, vFTECI[2])*RAD2DEG;





  vFT[0] = 1.0;
  vFT[1] = 0.0;
  vFT[2] = 0.0;
  atRotVect(Body2Eci, vFT, vFTECI);
  apxy = sqrt(vFTECI[0]*vFTECI[0]+vFTECI[1]*vFTECI[1]);
  rra = atan2(vFTECI[1],vFTECI[0])*RAD2DEG;
  rdec = atan2(apxy, vFTECI[2])*RAD2DEG;

  if(sra < 0.0){
    sra += 360.0;
  }
  sdec = 90.0-sdec;


  if(pra < 0.0){
    pra += 360.0;
  }
  pdec = 90.0-pdec;

  if(apra < 0.0){
    apra += 360.0;
  }
  apdec = 90.0-apdec;

  if(rra < 0.0){
    rra += 360.0;
  }
  rdec = 90.0-rdec;

  if(Sra < 0.0){
    Sra += 360.0;
  }
  Sdec = 90.0-Sdec;



  RVal[0]  = sra;
  RVal[1]  = sdec;
  RVal[2]  = pra;
  RVal[3]  = pdec;
  RVal[4]  = apra;
  RVal[5]  = apdec;
  RVal[6]  = rra;
  RVal[7]  = rdec;
  RVal[8]  = vNSun[0];
  RVal[9]  = vNSun[1];
  RVal[10] = vNSun[2];

  return;
} 


/* CKS:  find_minmax determines the minimum and maximum latitude and longitude 
   values for the saa polygon.  These values are used later to quickly eliminate 
   points as being potential points in the saa polygon.
*/ 

int find_minmax(double *lon, double *lat, int num_saa, double *minLon, double *maxLon, double *minLat, double *maxLat){ 
  int i=0;

  fosf.setMethod("find_minmax");
  /* initial values which are sure to be replaced by real data. */
  *maxLat = -100.0; 
  *minLat =  100.0;
  *maxLon = -400.0;
  *minLon =  400.0;
  
  if (!num_saa) {
    fosf.err() << "No saa latitudes and longitudes - can't find min or max\n";
    return -1;
  }

  for (i=1; i <= num_saa; i++) {
    if (lat[i] > *maxLat) { *maxLat = lat[i]; }
    if (lat[i] < *minLat) { *minLat = lat[i]; }
    if (lon[i] > *maxLon) { *maxLon = lon[i]; }
    if (lon[i] < *minLon) { *minLon = lon[i]; }
  }

  return 0;
}


/* CKS:  calculate_slopes determines the slope and intercept for every line which
   makes up the saa polynomial. (Note: longitude is y axis, latitude the x axis)
*/
int calculate_slopes(double *lon, double *lat, int num_saa, double *slopes,
		     double *intercepts) {
  int i;
  fosf.setMethod("find_minmax");
  if (num_saa < 3) { 
    fosf.err() << "Error:  calculate_slopes needs more than 2 polygon pts"; 
    return -1; /* error */ 
  }


  for (i=1;i<num_saa;++i) {
    if(lat[i+1] != lat[i]) {
       slopes[i] = ( lon[i+1] - lon[i])/(lat[i+1] - lat[i]);
    } else {
       slopes[i] = 1.0e+9;
       if( (lon[i+1] - lon[i]) < 0) { slopes[i] *= -1.0; }
    }
    intercepts[i] = lon[i] - slopes[i] * lat[i];
  }

 
  return 0;
}



int pt_in_polygon(double dlat, double dlon,
		  double lattable[], double lontable[],
		  double slopes[], double intercepts[], int num_saa,
		  double minLon, double maxLon, double minLat, double maxLat) {
  int i, numBoundaries=0;
  if ( dlon < minLon || dlon > maxLon) { return 0; }
  else if (dlat < minLat || dlat > maxLat) { return 0; }
  else {
    /* Now we project a straight latitude line to the edge of our world graph
       If an odd number of boundaries are pierced, then we are inside
       You may have to think about this algorithm for a bit to understand
       why it is true, but this is the most efficient algorithm */ 
    for (i =1; i < (num_saa); i++) {
      /* check to see if this line segment is to the right or left of us */
      if( (dlat > lattable[i] && dlat > lattable[i+1]) ||
	  (dlat < lattable[i] && dlat < lattable[i+1] ) ) {
	/* not a potential boundary */
      } else {
	if( dlon < lontable[i] && dlon < lontable[i+1]) { 
	  /* line is "above" our point - flag it */
	  numBoundaries++;
	} else if (dlon > lontable[i] && dlon > lontable[i+1]) {
	  /* line is below our point, dont flag it */
	} else {
	  if( slopes[i] > 1.e8 || slopes[i] < -1.e8 ) { /* vertical line */ 
	    numBoundaries++; /* must be exactly on line segment to get here*/ 
	  } else {
	    if (dlon < (slopes[i]*dlat + intercepts[i])) {
	      numBoundaries++;
	    }
	  }
	}
      }
    }
    

    // odd number of boundaries implies that we are inside the polygon
    if((numBoundaries%2) == 1) { return 1;}
    return 0;
  }
}







/*
 * readTLE = Get the two-line element set for a satellite name
 * 
 * Arguments:
 * Nl - Number of lines in ln
 * CheckSatName - Satellite name used by NORAD (TLE producer)
 * ln - lines from TLE file
 * tle - output, TLE data parses from ln
 * sta - start time of schedule window, MJD
 * sto - end time of schedule window, MJD
 *
 * Returns:
 *   1 = TLE found, returned in atElemTle *tle
 *   0 = Error generating ephemeris
 */
int readTLE(const int Nl, char* CheckSatName, char ln[][100], 
	    atElemTle *tle, double sta, double sto, double resol){

  /*  Function prototypes */

  /* Local variables*/
  int status = 1;
  int slen;
  int LineNum;
  int iflgS = 0;
  char SName[100],line1[100],line2[100];
  char Sat[15]="\0";  


  int dom[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  double EpochYear, EpochDay;
  int iyr,iday, ihr, imn, isec;
  double fday, mn;
  int diff;
  int m;
  int il = 0;
  int factor;


  fosf.setMethod("readTLE");

  slen = strlen(CheckSatName);
  while ((il<Nl) && (iflgS==0)) {
    strcpy(SName,ln[il++]);
    strcpy(line1,ln[il++]);
    strcpy(line2,ln[il++]);

    
    strncpy(Sat,SName,slen);
    strcat(Sat,"\0\0\0");

    if (strcmp(CheckSatName,Sat) == 0){
      iflgS = 1;
      break;
    }
  }

  if(iflgS == 0){
    fosf.err() << __FILE__ << ":" << __LINE__ << "readtle - The Satellite " << CheckSatName << " is not present in TLE file\n";
    return 0;
  }
  sscanf(line1,"%1d",&LineNum);
  if (LineNum != 1)
    {
      std::ostringstream eBufT;
      eBufT << "\n" << __FILE__ << ":" << __LINE__ << ", ERROR: Line 1 not present for satellite " << Sat << " in TLE file\n\n" << std::ends;
;
      throw std::runtime_error(eBufT.str());
    }
  sscanf(line2,"%1d",&LineNum);
  if (LineNum != 2)
    {
      std::ostringstream eBufT;
      eBufT << "\n" << __FILE__ << ":" << __LINE__ << ", ERROR: Line 2 not present for satellite " << Sat << " in TLE file\n\n" << std::ends;

      throw std::runtime_error(eBufT.str());
    }


  sscanf(line1,"%*2c%5d%*10c%2lf%12lf%10lf%*2c%5lf%2d%*2c%5lf%2d",
	 &tle->SatNum,&EpochYear,&EpochDay,&tle->xndt2o,&tle->xndd6o,&tle->iexp,&tle->bstar, &tle->ibexp);

  if(EpochYear > 50){
    iyr = (int)(EpochYear+1900.0);
  }else{
    iyr = (int)(EpochYear+2000.0);
  }
  if((iyr%4)==0){
    dom[1] = 29;
  }
  fosf.info(3) << "EpochYear=" << EpochYear << ", EpochDay=" << EpochDay << "\n";
  iday = (int)(EpochDay);
  fday = EpochDay-iday; /* fraction of day */

  /* Compute month/day from day of year */
  m = 0;
  diff = iday;
  while(diff > 0){
    diff = diff - dom[m];
    m++;
  }
  iday = diff+dom[m-1];

  /* Get hour, minute, and seconds from fraction of day */
  ihr = (int)(fday*24.0);
  mn = (fday*24.0 - ihr)*60.0;
  imn = (int)mn;
  tle->isc = 1.0-(mn-(double)imn);

  isec = (int)((mn-(double)imn) *60.0);

  tle->tm.yr = iyr;
  tle->tm.mo = m;
  tle->tm.dy = iday;
  tle->tm.hr = ihr;

/*
   If resolution is greater than 1 minutes, round off to the closest minute
   otherwise, to the closest 1/2 minutes.
*/


  if(resol >= 1.0){
    tle->tm.mn = imn+1; /* MJM why +1 */
    tle->tm.sc = 0;     /* MJM why zero? */
  } else {
    if( (mn-(double)imn)<= resol){
      tle->tm.sc = (int)(resol*60.0);
      tle->tm.mn = imn;
      tle->isc = resol-(mn-(double)imn);
    } else {
      factor = ((int)((mn-(double)imn)/resol)+1);
      tle->tm.sc =(int) ((double) factor*resol*60.0+0.5);
      tle->tm.mn = imn;
      tle->isc = (double)tle->tm.sc/60.0-(mn-(double)imn);
    }
  }

  correctTm(&tle->tm);

  tle->mjd = do_cal2mjd(tle->tm.yr,tle->tm.mo,tle->tm.dy,tle->tm.hr,tle->tm.mn, tle->tm.sc);

  if(tle->mjd > sta){
    fosf.err() << __FILE__ << ":" << __LINE__ << ", TLE file is too new since schedule start time " << sta << " is before the TLE epoch time " << tle->mjd << "\n";
    std::cout << "TLE file is too new since schedule start time " << sta << " is before the TLE epoch time " << tle->mjd << "\n" << std::endl;
    return 0;

  }else if((sto-tle->mjd) > 30.0){
    fosf.warn() << "TLE file is too old since schedule stop time " << sto << " is more than 30 days after than TLE TLE epoch time " << tle->mjd << "\n";
  }


  sscanf(line2,"%*8c%8lf%8lf%7lf%8lf%8lf%11lf%5d",
	 &tle->xincl,&tle->xnodeo,&tle->eo,&tle->omegao,&tle->xmo, &tle->xno,&tle->EpochRev);
  

  if(tle->xno <= 0.0){
    std::ostringstream eBufT;
    eBufT << "\n" << __FILE__ << ":" << __LINE__ << ", ERROR: From TLE file it appears that Mean Motin is <= 0\nCannot continue.........exiting now\n\n " <<std::ends;

    throw std::runtime_error(eBufT.str());
  }
  if(tle->eo > 0){
    tle->eo = tle->eo*1.0E-7;
  }
  while(tle->xndd6o > 1.0){
    tle->xndd6o = tle->xndd6o/10.0;
  }
  while(tle->bstar > 1.0){
    tle->bstar = tle->bstar/10.0;
  }
  tle->xndd6o = tle->xndd6o*pow(10.0,tle->iexp);
  tle->bstar = tle->bstar*pow(10.0,tle->ibexp);

  status = 1;

  return status;
}


void correctTm(AtTime *tz){
  int is = 0;
  int im = 0;
  int ih = 0;
  int in = 0;
  int iy = 0;

  int dom[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};



  if((tz->yr%4)==0){
    dom[1] = 29;
  }


  while(tz->sc >= 60){
    tz->sc -= 60;
    is++;
  }
  tz->mn += is;

  while(tz->mn >= 60){
    tz->mn -= 60;
    im++;
  }
  tz->hr += im;

  while(tz->hr >= 24){
    tz->hr -= 24;
    ih++;
  }
  tz->dy += ih;

  while(tz->dy > dom[tz->mo-1]){
    tz->dy -= dom[tz->mo-1];
    tz->mo++;
    if(tz->mo > 12){
      tz->mo = tz->mo%12;
      iy++;
    }
    in++;
  }

  if(tz->dy == 0){
    tz->mo--;
    tz->dy = dom[tz->mo-1];
  }
  //  tz->mon += in;
  while(tz->mo > 12){
    tz->mo -= 12;
    iy++;
  }
  tz->yr += iy;

}


double cube(double x)
{
	x = pow(x , 3.0);
	return x;
}


double sqr(double x)
{
	x *= x;
	return x;
}


double fmod2p (double x)
{
	x = modulus (x, 2.0 * _pi );
	return x;
}

double modulus (double arg1, double arg2)
{
	double modu;
	modu = arg1 - floor(arg1/arg2) * arg2;
	if (modu >= 0)
		return modu;
	else
	{
		modu += arg2;
		return modu;
	}
	return -1; /* shouldn't happen */
}



void sgp4 (double tsince, struct vector *pos, struct vector *vel, atElemTle *satdata)
{
	struct vector MV, NV, UV, VV;
	double a1=0, a3ovk2=0, ao=0, aodp=0, aycof=0;
        double betao=0, betao2=0, c1=0, c1sq=0;
	double c2=0, c3=0, c4=0, c5=0, coef=0, coef1=0;
	double cosio=0, d2=0, d3=0, d4=0, del1=0, delmo=0;
	double delo=0, eeta=0, eosq=0, eta=0, etasq=0, qoms24=0;
	double omgcof=0, omgdot=0, perige=0, pinvsq=0, psisq=0;
	double s4=0, sinio=0, sinmo=0, t2cof=0, t3cof=0, t4cof=0;
	double t5cof=0, temp=0, temp1=0, temp2=0, temp3=0, theta2=0;
	double theta4=0, tsi=0, x1m5th=0, x1mth2=0, x3thm1=0, x7thm1=0;
	double xhdot1=0, xlcof=0, xmcof=0, xmdot=0, xnodcf=0, xnodot=0;
	double xnodp=0;
	int isimp=0, i=0;
	double rfdotk;
	double rdotk,xinck,xnodek,uk,rk;
	double cos2u,sin2u,u,sinu,cosu,betal,rfdot,rdot,r,pl,elsq;
	double esine,ecose,epw,temp6,temp5,temp4,cosepw,sinepw;
	double capu,ayn,xlt,aynl,xll,axn,xn,beta,xl,e,a,tfour;
	double tcube,delm,delomg,templ,tempe,tempa,xnode,tsq,xmp;
	double omega,xnoddf,omgadf,xmdf;
	double xke=0, s=0, qo=0, qoms2t=0, temp7=0;
        /* Constants */
	s = _ae + 78 / xkmper;
	qo = _ae + 120 / xkmper;
	xke = sqrt((3600.0 * ge) / cube(xkmper));
	qoms2t = sqr ( sqr (qo - s));
	temp2 = xke / (satdata->xno);
	a1 = pow (temp2 , _tothrd);
	cosio = cos (satdata->xincl);

	theta2 = sqr(cosio);
	x3thm1 = 3.0 * theta2 - 1.0;
	eosq = sqr (satdata->eo);
	betao2 = 1.0 - eosq;
	betao = sqrt (betao2);
	del1 = 1.5 * CK2 * x3thm1 / (sqr(a1) * betao * betao2);
	ao = a1 * ( 1.0 - del1*((1.0/3.0) + del1 * (1.0 + (134.0/81.0) * del1)));
	delo = 1.5 * CK2 * x3thm1 / (sqr(ao) * betao * betao2);
	xnodp = (satdata->xno)/(1.0 + delo);
	aodp = ao/(1.0 - delo);
        /* Initialization */
	/* For perigee less than 220 kilometers, the isimp flag is set and
	   the equations are truncated to linear variation in sqrt a and
	   quadratic variation in mean anomaly.  Also, the c3 term, the
	   delta omega term, and the delta m term are dropped. */
	isimp = 0;
	if ((aodp * (1.0 - satdata->eo)/ _ae) < (220.0/xkmper + _ae))
	    isimp = 1;
	/* For perigee below 156 km, the values of s and qoms2t are altered.*/
	s4 = s;
	qoms24 = qoms2t;
	perige = (aodp * (1.0 - satdata->eo) - _ae) * xkmper;
	if (perige < 156)
	{
	    s4 = perige - 78.0;
	    if (perige <= 98)
		s4 = 20.0;
	    qoms24 = pow (((120.0 - s4) * _ae / xkmper), 4.0);
	    s4 = s4 / xkmper + _ae;
	}
	pinvsq = 1.0 / ( sqr(aodp) * sqr(betao2) );
	tsi = 1.0 / (aodp - s4);
	eta = aodp * (satdata->eo) * tsi;
	etasq = sqr (eta);
	eeta = (satdata->eo) * eta;
	psisq = fabs( 1.0 - etasq);
	coef = qoms24 * pow( tsi, 4.0);
	coef1 = coef / pow ( psisq, 3.5);
	c2 = coef1 * xnodp * (aodp * (1.0 + 1.5 * etasq + eeta * (4.0 + etasq)) + 0.75 * CK2 * tsi / psisq * x3thm1 * (8.0 + 3.0 * etasq * (8.0 + etasq)));
	c1 = (satdata->bstar) * c2;
	sinio = sin(satdata->xincl);
	a3ovk2 = -XJ3 / CK2 * pow( _ae , 3.0);
	c3 = coef * tsi * a3ovk2 * xnodp * _ae * sinio / (satdata->eo);
	x1mth2 = 1.0 - theta2;
	c4 = 2.0 * xnodp * coef1 * aodp * betao2 * ( eta * (2.0 + 0.5 * etasq) + (satdata->eo) * (0.5 + 2.0 * etasq) - 2.0 * CK2 * tsi / (aodp * psisq) * ( -3.0 * x3thm1 * ( 1.0 - 2.0 * eeta + etasq * (1.5 - 0.5*eeta)) + 0.75 * x1mth2 * (2.0 * etasq - eeta * (1.0 + etasq)) * cos(2.0 * (satdata->omegao))));
	c5 = 2.0 * coef1 * aodp * betao2 * (1.0 + 2.75 * (etasq + eeta) + eeta * etasq);
	theta4 = sqr(theta2);
	temp1 = 3.0 * CK2 * pinvsq * xnodp;
	temp2 = temp1 * CK2 * pinvsq;
	temp3 = 1.25 * CK4 * pinvsq * pinvsq * xnodp;
	xmdot = xnodp + 0.5 * temp1 * betao * x3thm1 + 0.0625 * temp2 * betao * (13.0 - 78.0 * theta2 + 137.0 * theta4);
	x1m5th = 1.0 - 5.0 * theta2;
	omgdot = -0.5 * temp1 * x1m5th + 0.0625 * temp2 * (7.0 - 114.0 * theta2 + 395.0 * theta4) + temp3 * (3.0 - 36.0 * theta2 + 49.0 * theta4);
	xhdot1 = -temp1 * cosio;
	xnodot = xhdot1 + (0.5 * temp2 * (4.0 - 19.0 * theta2) + 2.0 * temp3 * (3.0 - 7.0 * theta2)) * cosio;
	omgcof = (satdata->bstar) * c3 * cos(satdata->omegao);
	xmcof = -(2.0/3.0) * coef * (satdata->bstar) * _ae / eeta;
	xnodcf = 3.5 * betao2 * xhdot1 * c1;
	t2cof = 1.5 * c1;
	xlcof = 0.125 * a3ovk2 * sinio * (3.0 + 5.0 * cosio) / (1.0 + cosio);
	aycof = 0.25 * a3ovk2 * sinio;
	delmo = pow ((1.0 + eta * cos(satdata->xmo)), 3);
	sinmo = sin(satdata->xmo);
	x7thm1 = 7.0 * theta2 - 1.0;
	if (isimp==0)
	{
	    c1sq = sqr(c1);
	    d2 = 4.0 * aodp * tsi * c1sq;
	    temp = d2 * tsi * c1 / 3.0;
	    d3 = (17.0 * aodp + s4)*temp;
	    d4 = 0.5 * temp * aodp * tsi * (221.0 * aodp + 31.0 * s4) * c1;
	    t3cof = d2 + 2.0*c1sq;
	    t4cof = 0.25 * (3.0 * d3 + c1 * (12.0 * d2 + 10.0 * c1sq));
	    t5cof = 0.2 * (3.0 * d4 + 12.0 * c1 * d3 + 6.0 * d2 * d2 + 15.0 * c1sq * (2.0 * d2 + c1sq));
	}
	/* Update for secular gravity and atmospheric drag. */
	xmdf = satdata->xmo + xmdot * tsince;
	omgadf = satdata->omegao + omgdot * tsince;
	xnoddf = satdata->xnodeo + xnodot * tsince;
	omega = omgadf;
	xmp = xmdf;
	tsq = sqr (tsince);
	xnode = xnoddf + xnodcf * tsq;
	tempa = 1.0 - c1 * tsince;
	tempe = (satdata->bstar) * c4 * tsince;
	templ = t2cof * tsq;
	if (isimp == 0)
	{
	    delomg = omgcof * tsince;
	    delm = xmcof*(pow((1.0 + eta * cos(xmdf)), 3.0) - delmo);
	    temp = delomg + delm;
	    xmp = xmdf + temp;
	    omega = omgadf - temp;
	    tcube = tsq * tsince;
	    tfour = tsince * tcube;
	    tempa = tempa - d2 * tsq - d3 * tcube - d4 * tfour;
	    tempe = tempe + (satdata->bstar) * c5 * (sin(xmp) - sinmo);
	    templ = templ + t3cof * tcube + tfour * (t4cof + tsince * t5cof);
	}
	a = aodp * sqr(tempa);
	e = (satdata->eo) - tempe;;
	xl = xmp + omega + xnode + xnodp*templ;
	beta = sqrt(1.0 - sqr(e));
	xn = xke / pow(a,1.5);
	/* Long period periodics */
	axn = e * cos(omega);
	temp = 1.0 / (a * sqr(beta));
	xll = temp * xlcof * axn;
	aynl = temp * aycof;
	xlt = xl + xll;
	ayn = e * sin(omega) + aynl;
	
	/* Solve Kepler's Equation */
	capu = fmod2p(xlt - xnode);
	temp2 = capu;
	i=1;
	do {
	    sinepw = sin(temp2);
	    cosepw = cos(temp2);
	    temp3 = axn * sinepw;
	    temp4 = ayn * cosepw;
	    temp5 = axn * cosepw;
	    temp6 = ayn * sinepw;
	    epw = (capu - temp4 + temp3 - temp2) / (1.0 - temp5 - temp6) + temp2;
	    temp7 = temp2;
	    temp2 = epw;
	    i++;
	} while ((i<=10) && (fabs(epw - temp7) > _e6a));
	/* Short period preliminary quantities */
	ecose = temp5 + temp6;
	esine = temp3 - temp4;
	elsq = sqr(axn) + sqr(ayn);
	temp = 1.0 - elsq;
	pl = a * temp;
	r = a * (1.0 - ecose);
	temp1 = 1.0 / r;
	rdot = xke * sqrt(a) * esine * temp1;
	rfdot = xke * sqrt(pl) * temp1;
	temp2 = a * temp1;
	betal = sqrt(temp);
	temp3 = 1.0 / (1.0 + betal);
	cosu = temp2 * (cosepw - axn + ayn * esine * temp3);
	sinu = temp2 * (sinepw - ayn - axn * esine * temp3);
	u = atan2(sinu, cosu);
	sin2u = 2.0 * sinu * cosu;
	cos2u = 2.0 * sqr(cosu) - 1.0;
	temp = 1.0 / pl;
	temp1 = CK2 * temp;
	temp2 = temp1 * temp;
        /* Update for short periodics */
	rk = r * (1.0 - 1.5 * temp2 * betal * x3thm1) + 0.5 * temp1 * x1mth2 * cos2u;
	uk = u - 0.25 * temp2 * x7thm1 * sin2u;
	xnodek = xnode + 1.5 * temp2 * cosio * sin2u;
	xinck = (satdata->xincl) + 1.5 * temp2 * cosio * sinio * cos2u;
	rdotk = rdot - xn * temp1 * x1mth2 * sin2u;
	rfdotk = rfdot + xn * temp1 * (x1mth2 * cos2u + 1.5 * x3thm1);
	/* Orientation vectors */
	MV.v[0] = -sin(xnodek) * cos(xinck);
	MV.v[1] = cos(xnodek) * cos(xinck);
	MV.v[2] = sin(xinck);
	
	NV.v[0] = cos(xnodek);
	NV.v[1] = sin(xnodek);
	NV.v[2] = 0;
	for (i=0;(i<3);i++)
	{
		UV.v[i] = MV.v[i] * sin(uk) + NV.v[i] * cos(uk);
		VV.v[i] = MV.v[i] * cos(uk) - NV.v[i] * sin(uk);
        }

        /* position + velocity */
	for (i=0;(i<3);i++)
	{
		pos->v[i] = rk * UV.v[i];
		vel->v[i] = rdotk * UV.v[i] + rfdotk * VV.v[i];
        }
}



void precessionRM(double mjd, AtRotMat Rm)
{
  double   t, zeta, z, theta;

  t = ( mjd - MJD_J2000 )/36525.0;

  zeta  = ( 2306.2181*t + 0.30188*t*t + 0.017998*t*t*t ) * DEG2RAD / 3600.0;
  z     = ( 2306.2181*t + 1.09468*t*t + 0.018203*t*t*t ) * DEG2RAD / 3600.0;
  theta = ( 2004.3109*t - 0.42665*t*t - 0.041833*t*t*t ) * DEG2RAD / 3600.0;

  Rm[0][0] =  cos(zeta)*cos(theta)*cos(z) - sin(zeta)*sin(z);
  Rm[1][0] = -sin(zeta)*cos(theta)*cos(z) - cos(zeta)*sin(z);
  Rm[2][0] = -sin(theta)*cos(z);
  Rm[0][1] =  cos(zeta)*cos(theta)*sin(z) + sin(zeta)*cos(z);
  Rm[1][1] = -sin(zeta)*cos(theta)*sin(z) + cos(zeta)*cos(z);
  Rm[2][1] = -sin(theta)*sin(z);
  Rm[0][2] =  cos(zeta)*sin(theta);
  Rm[1][2] = -sin(zeta)*sin(theta);
  Rm[2][2] =  cos(theta);
}
