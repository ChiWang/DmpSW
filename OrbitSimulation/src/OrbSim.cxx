/**
 * @file OrbSim.cc
 * @brief This file contains functions to parse an init file and start the attitide calculation.
 * @author Giuseppe Romeo
 * @date Created:  Nov 15, 2005
 * 
 * $Header: /nfs/slac/g/glast/ground/cvs/ScienceTools-scons/orbitSim/src/OrbSim.cxx,v 1.9 2009/12/16 23:20:39 elwinter Exp $
 */

#include "../include/orbitSimStruct.h"
#include "../include/OrbSim.h"

#include <cstdlib>
#include <stdio.h>

#include <stdexcept>
#include <string>

#include <iostream>
#include <iomanip>
#include <sstream>

#include "../include/Stream.h"
#include "../include/StreamFormatter.h"
#include "../include/st_stream.h"


  /// Stream to control output through verbosity level
st_stream::StreamFormatter losf("OrbSim", "", 2);

int parseInit( const char *fname, InitI *inA) {

  FILE *inf;
  char ln[bufsz];
  const int itm = 12;
  int it = 0;
  
  losf.setMethod("parseInit");


  if ( (inf=fopen(fname,"r")) == NULL) {
    std::string name(fname);
    throw std::runtime_error("Cound not open init file:\n" + name );

  } else {

    while(fgets(ln, bufsz,inf)) {
      //      printf("Found line: %s\n", ln);
      ln[strlen(ln) -1] = '\0';
      
      while (match_str((const char*)ln, "^ ") == 1) {
	char *tln = processline(ln, ' ');
	strcpy(ln, tln);

      }

      if(match_str((const char*)ln, "^#") == 1) {
	//	printf("Ignored line: %s\n", ln);
	continue;
      } else if(match_str((const char*)ln, "^start_MJD") == 1) {
	double t = -1.0;;
	char *jnk = processline(ln, '=');
	if (jnk != NULL) {
	  sscanf(jnk, "%lf", &t);
	  if(t>0.0){
	    inA->start_MJD = t;
	    it++;
	  }
	}
      } else if(match_str((const char*)ln, "^stop_MJD") == 1) {
	double t = -1.0;
	char *jnk = processline(ln, '=');
	if (jnk != NULL) {
	  sscanf(jnk, "%lf", &t);
	  if(t>0.0){
	    inA->stop_MJD = t;
	    it++;
	  }
	}

      } else if(match_str((const char*)ln, "^EAA") == 1) {
	double t = 99999.0;
	char *jnk = processline(ln, '=');
	if (jnk != NULL) {
	  sscanf(jnk, "%lf", &t);
	  if((t>=0.0 && t<=180.0)){
	    inA->EAA = t;
	  }
	}

      } else if(match_str((const char*)ln, "^Initial_RA") == 1) {
	double t = 99999.0;
	char *jnk = processline(ln, '=');
	if (jnk != NULL) {
	  sscanf(jnk, "%lf", &t);
	  if((t>=0.0 && t<=360.0) || (t>= -180.0 && t<= 180.0)){
	    inA->Ira = t;
	    it++;
	  }
	}

      }else if(match_str((const char*)ln, "^Initial_DEC") == 1) {
	double t = 99999.0;
	char *jnk = processline(ln, '=');
	if (jnk != NULL) {
	  sscanf(jnk, "%lf", &t);
	  if((t>=-90.0 && t<= 90.0) || (t>= 0.0 && t<=180.0)){
	    inA->Idec = t;
	    it++;
	  }
	}

      }else if(match_str((const char*)ln, "^Earth_Avoid") == 1) {
	int flgocc = 1;
	char *jnk = processline(ln, '=');
	if (jnk != NULL) {
	  sscanf(jnk, "%d", &flgocc);
	  if(flgocc <= 0){
	    inA->occflag = 0;
	    losf.out() << "Earth avoidance is disabled\n\n";
	  } else if ( flgocc >= 1){
	    inA->occflag = 1;
	  }
	}

      }  else if(match_str((const char*)ln, "^SATName") == 1) {
	char *jnk = processline(ln, '=');
	if(jnk != NULL) {

	  // Removing initial space in any
	  while(jnk[0] == ' '){
	    ++jnk;
	  }

	  int lenj = strlen(jnk);
	  if(lenj > 0 && jnk[0] != '#') {
	    char *TL;
	    if(jnk[0] == '|'){
	      TL = strtok(jnk, "#");
	    } else {
	      TL = strtok(jnk, " #");
	    }
	    int len = strlen(TL);
	    if(len > 0){
	      inA->SATname.assign(TL);
	      it++;
	    } else {
	      inA->SATname.assign("Not specified");

	    }
	  }
	}
      }else if(match_str((const char*)ln, "^Timeline") == 1) {
	char *jnk = processline(ln, '=');
	if(jnk != NULL) {

	  // Removing initial space in any
	  while(jnk[0] == ' '){
	    ++jnk;
	  }

	  int lenj = strlen(jnk);
	  if(lenj > 0 && jnk[0] != '#') {
	    char *TL;
	    if(jnk[0] == '|'){
	      TL = strtok(jnk, "#");
	    } else {
	      TL = strtok(jnk, " #");
	    }
	    int len = strlen(TL);
	    if(len > 0){
	      inA->TLname.assign(TL);
	      it++;
	    } else {
	      inA->TLname.assign("Not specified");

	    }
	  }
	}
      } else if(match_str((const char*)ln, "^TLType") == 1) {
	char *jnk = processline(ln, '=');
	if(jnk != NULL) {

	  // Removing initial space in any
	  while(jnk[0] == ' '){
	    ++jnk;
	  }
	  int lenj = strlen(jnk);
	  if(lenj > 0 && jnk[0] != '#') {
	    char *TL = strtok(jnk, " #");
	    inA->TLtype.assign(TL);
	    int len = strlen(TL);
	    if(len > 0){
	      inA->TLtype.assign(TL);
	      it++;
	    }

	  } else {
	    inA->TLtype.assign("Not Specified");
	  }
	}
      } else if(match_str((const char*)ln, "^EphemName") == 1) {
	char *jnk = processline(ln, '=');
	if(jnk != NULL) {

	  // Removing initial space in any
	  while(jnk[0] == ' '){
	    ++jnk;
	  }
	  int lenj = strlen(jnk);
	  if(lenj > 0 && jnk[0] != '#') {
	    char *TL = strtok(jnk, " #");
	    int len = strlen(TL);
	    if(len > 0){
	      inA->EPHname.assign(TL);
	      it++;
	    }
	  } else {
	    inA->EPHname.assign("Not Specified");
	  }
	}
      }  else if(match_str((const char*)ln, "^EphemFunc") == 1) {
	char *jnk = processline(ln, '=');
	if(jnk != NULL) {

	  // Removing initial space in any
	  while(jnk[0] == ' '){
	    ++jnk;
	  }
	  int lenj = strlen(jnk);
	  if(lenj > 0) {
	    char *TL = strtok(jnk, " #");
	    int len = strlen(TL);
	    if(len > 0 && jnk[0] != '#'){
	      inA->EPHfunc.assign(TL);
	      it++;
	    }
	  } else {
	      inA->EPHfunc.assign("Not Specified");
	  }
	}
      } else if(match_str((const char*)ln, "^OutPutFile") == 1) {
	char *jnk = processline(ln, '=');
	if(jnk != NULL) {

	  // Removing initial space in any
	  while(jnk[0] == ' '){
	    ++jnk;
	  }
	  int lenj = strlen(jnk);
	  if(lenj > 0 && jnk[0] != '#') {
	    char *TL = strtok(jnk, " #");
	    int len = strlen(TL);
	    if(len > 0){
	      inA->OutFile.assign(TL);
	      it++;
	    }
	  } else {
	    inA->OutFile.assign("Not Specified");

	  }
	}
      } else if(match_str((const char*)ln, "^OptFile") == 1) {
	char *jnk = processline(ln, '=');
	if(jnk != NULL) {

	  // Removing initial space in any
	  while(jnk[0] == ' '){
	    ++jnk;
	  }
	  int lenj = strlen(jnk);
	  if(lenj > 0 && jnk[0] != '#') {
	    char *TL = strtok(jnk, " #");
	    int len = strlen(TL);
	    if(len > 0){
	      inA->OptFile.assign(TL);
	    }
	  } 
	}
      } else if(match_str((const char*)ln, "^saafile") == 1) {
	char *jnk = processline(ln, '=');
	if(jnk != NULL) {

	  // Removing initial space in any
	  while(jnk[0] == ' '){
	    ++jnk;
	  }
	  int lenj = strlen(jnk);
	  if(lenj > 0 && jnk[0] != '#') {
	    char *TL = strtok(jnk, " #");
	    int len = strlen(TL);
	    if(len > 0){
	      inA->saafile.assign(TL);
	      it++;
	    }
	  } else {
	    inA->saafile.assign("Not Specified");

	  }
	}
      } else if(match_str((const char*)ln, "^Units") == 1) {
	double t = -1.0;
	char *jnk = processline(ln, '=');
	if (jnk != NULL) {
	  sscanf(jnk, "%lf", &t);
	  if(t > 0.0){
	    inA->Units = t;
	    it++;
	  }
	}

      } else if(match_str((const char*)ln, "^Resolution") == 1) {
	double t = -1.0;
	char *jnk = processline(ln, '=');
	if (jnk != NULL) {
	  sscanf(jnk, "%lf", &t);
	  if(t > 0.0){
	    inA->Resolution = t;
	    it++;
	  }
	}

      } else if(match_str((const char*)ln, "^Chatter") == 1) {
	char *jnk = processline(ln, '=');
	if (jnk != NULL) {
	  int t = -1;
	  sscanf(jnk, "%d", &t);
	  if(t > 0){
	    inA->chat = t;
	  }
	}
      } else if(match_str((const char*)ln, "^Debug") == 1) {
	char *jnk = processline(ln, '=');
	if (jnk != NULL) {
	  int t = -1;
	  sscanf(jnk, "%d", &t);
	  if(t > 0){
	    inA->debug = t;
	  }
	}
      }

    }
  }

  int rv = 1;

  // Some checks


  if(!((match_str( inA->TLtype.c_str(), "^TAKO$") == 1) ||
       (match_str( inA->TLtype.c_str(), "^ASFLOWN$") == 1) ||
       (match_str( inA->TLtype.c_str(), "^SINGLE$") == 1))){
    it--;
  }

  if(!((match_str( inA->EPHfunc.c_str(), "^yyyy_eph$") == 1) ||
       (match_str( inA->EPHfunc.c_str(), "^xyzll_eph$") == 1) || 
       (match_str( inA->EPHfunc.c_str(), "^tlederive$") == 1))){
    it--;
  }


  if(it != itm){
    rv = 0;
  }

  return rv;

}


char *processline(char *ln, char find) {

  char *first_ptr;
  char *last_ptr ;

  int nl = strlen(ln);
  int i = 0;

  last_ptr = ln;
  first_ptr = ln;

  if(first_ptr[0] == '#'){
    return NULL;
  }
  
  while(first_ptr[0] != find && i<nl){

    //    printf("%s:%d, in processline, first=%c\n", __FILE__,__LINE__, first_ptr[0]);
    if(*first_ptr == '\0')
      break;

    ++first_ptr;
    i++;
  }


  if(*first_ptr == '\0'){

    throw std::runtime_error("\nCannot parse line\n\n");
  }
 
  *first_ptr = '\0';
  ++first_ptr;

  //  printf("First=%s, Last=%s\n", first_ptr, last_ptr);
  return first_ptr;
}




Attitude * makeAttTako(InitI *ini, EphemData *ephem) {

  FILE *ITL;
  FILE *OutF = NULL;
  double Timespan, res;
  int inum, oinum, i;


  double org_stT = ini->start_MJD;
  double org_enT = ini->stop_MJD;

  losf.setMethod("makeAttTako");
  losf.err().precision(15);
  losf.info().precision(15);

  Timespan = (ini->stop_MJD-ini->start_MJD);
  res = ini->Resolution;
  inum = (int)((Timespan+res/2.0)/res);
  Attitude *OAtt = allocateAttitude(inum);

  if ( OAtt == (Attitude *)NULL) {
    throw std::runtime_error("\nERROR: In makeAttTako, cannot allocate attitude data structure\n\n");
  }

  oinum = inum;


  char ln[bufsz];

  if ( (ITL=fopen(ini->TLname.c_str(),"r")) == NULL) {
    std::string fname(ini->TLname);
    throw std::runtime_error("\nCound not open Timeline file "+fname);
  } else {  
    double pra = ini->Ira;
    double pdec = ini->Idec;

    double res = ini->Resolution/1440.0;  //convert resolution in days for mjd
    int flg = 0;
    double mjdt = 0.0;
    int mode = -1;
    double offset = -999.0;
    double ra = -999.0;
    double dec = -999.0;
    double mjds = 0.0;
    double mjde = 0.0;
    SurProf profile;

    double lastend = 0.0;

    // Removing initial part which is not used


    while(fgets(ln, bufsz, ITL)) {
      if (strncmp(ln, "// ------------------------", 27) == 0){
	break;
      }
    }


    while(fgets(ln, bufsz, ITL)) {


      if(strlen(ln) == 1){
	continue;
      }
      if((match_str((const char*) ln, " Survey ") == 1) &&
	 (match_str((const char*) ln, " Begin ") == 1)){


	mode = 1;
	mjdt = getMJD(ln);
	//	printf("SURVEY from %s ==> %f\n", ln, mjdt);

	while(fgets(ln, bufsz, ITL)) {
	  if (strncmp(ln, "// ------------------------", 27) == 0){
	    break;
	  }else if ((match_str((const char*) ln, " offset ") == 1)){
	    char *jnk = processline(ln, '=');
	    if (jnk != NULL) {
	      sscanf(jnk, "%lf", &offset);
	    }
	  } else if((match_str((const char*) ln, " Slew ") == 1) && 
		    (match_str((const char*) ln, " End ") == 1)) {
	    mjds =getMJD(ln);

	  } else if ((match_str((const char*) ln, " Survey ") == 1) &&
		     (match_str((const char*) ln, " End ") == 1)) {
	    mjde =getMJD(ln);

	  }

	}

	// There could be cases where there is no slewing,
	// in such cases the end slew is the same as the 
	// starting of the observation.

	if(mjds == 0.0){
	  mjds = mjdt;
	}
	

	//  Some sanity checks

	if(offset <-180.0 || offset > 180.0){
	  losf.err()  << "\t\t\tERROR:\nFixed Survey Observation starting at MJD " << mjdt << "\nDOES NOT have a proper offset (" << offset << ")\n\n";

	  flg = 3;
	}
	if(mjde < mjdt){
	  losf.err()  << "\t\t\tERROR:\nFixed Survey Observation starting at MJD " << mjdt << "\nwill end at an earlier time " << mjde << "\n\n";
	  flg = 3;
	}
	if(mjde < mjds){
	  losf.err()  << "\t\t\tERROR:\nFixed Survey Observation starting at MJD " << mjdt << "\nends at " << mjde << ", but the end slew is at " << mjds << "\n\n";

	  flg = 3;
	}

      } else if((match_str((const char*) ln, " Obs ") == 1) &&
	       (match_str((const char*) ln, " Begin ") == 1)){

	mode = 2;
	mjdt = getMJD(ln);
	//	printf("POINTED from %s ==> %f\n", ln, mjdt);
	while(fgets(ln, bufsz, ITL)) {

	  if (strncmp(ln, "// ------------------------", 27) == 0){
	    break;
	  }else if ((match_str((const char*) ln, " RA ") == 1) &&
		    (match_str((const char*) ln, "^//") == 1)){
	    char *jnk = processline(ln, '=');
	    if (jnk != NULL) {
	      sscanf(jnk, "%lf", &ra);
	    }
	  }else if ((match_str((const char*) ln, " dec ") == 1) &&
		    (match_str((const char*) ln, "^//") == 1)){
	    char *jnk = processline(ln, '=');
	    if (jnk != NULL) {
	      sscanf(jnk, "%lf", &dec);
	    }
	  } else if((match_str((const char*) ln, " Slew ") == 1) && 
		    (match_str((const char*) ln, " End ") == 1) &&
		    (mode != -1)) {
	    mjds =getMJD(ln);

	  } else if ((match_str((const char*) ln, " Obs ") == 1) &&
		     (match_str((const char*) ln, " End ") == 1)&&
		    (mode != -1)) {
	    mjde =getMJD(ln);

	  }

	}


	// There could be cases where there is no slewing,
	// in such cases the end slew is the same as the 
	// starting of the observation.

	if(mjds == 0.0){
	  mjds = mjdt;
	}
	

	//  Some sanity checks

	if(ra <0.0 || ra > 360.0){
	  losf.err() << "\t\t\tERROR:\nPointed Observation starting at MJD " << mjdt << "\nDOES NOT have a proper RA (" << ra << ")\n\n";
	  flg = 3;
	}
	if(dec <-90.0 || dec > 90.0){
	  losf.err() << "\t\t\tERROR:\nPointed Observation starting at MJD " << mjdt << "\nDOES NOT have a proper DEC (" << dec << ")\n\n";
	  flg = 3;
	}
	if(mjde < mjdt){
	  losf.err() << "\t\t\tERROR:\nPointed Observation starting at MJD " << mjdt << "\nwill end at an earlier time " << mjde << "\n\n";
	  flg = 3;
	}
	if(mjde < mjds){
	  losf.err() << "\t\t\tERROR:\nPointed Observation starting at MJD " << mjdt << "\nends at " << mjde << ", but the end slew is at " << mjds << "\n\n";
	  flg = 3;
	}

      } else if((match_str((const char*) ln, " Profile ") == 1) &&
	       (match_str((const char*) ln, " Begin ") == 1)){
	mode = 3;
	mjdt = getMJD(ln);

	while(fgets(ln, bufsz, ITL)) {

	  if (strncmp(ln, "// ------------------------", 27) == 0){
	    break;
	  } else if((match_str((const char*) ln, " Slew ") == 1) && 
		    (match_str((const char*) ln, " End ") == 1)) {
	    mjds =getMJD(ln);

	  } else if ((match_str((const char*) ln, " Profile ") == 1) &&
		     (match_str((const char*) ln, " End ") == 1)) {
	    mjde =getMJD(ln);

	  }else if((match_str((const char*) ln, " Rocking ") == 1) && 
		    (match_str((const char*) ln, " Profile:") == 1)) {
	    if((fgets(ln, bufsz, ITL)) != NULL){
	      if(match_str((const char*) ln, " ROCKSTART ") == 1){
		char *jnk = processline(ln, '=');
		if (jnk != NULL) {
		  char date[17];
		  double ep;
		  sscanf(jnk, "%s (%lf)", date, &ep);
		  profile.epoch = do_met2mjd(ep);
		}
		   
	      }
	    } else {
	      throw std::runtime_error("ERROR: Could read TAKO Timeline any further\n");
	    }

	    if((fgets(ln, bufsz, ITL)) != NULL){
	      if(match_str((const char*) ln, " ROCKDEFAULT ") == 1){
		char *jnk = processline(ln, '=');
		double to;
		if (jnk != NULL) {
		  sscanf(jnk, "%lf", &to);
		  profile.defofst = to;
		}
	      }

	    } else {
	      throw std::runtime_error("ERROR: Could read TAKO Timeline any further\n");
	    }



	    if((fgets(ln, bufsz, ITL)) != NULL){
	      if((match_str((const char*) ln, " ROCKTIME ") == 1) &&
		 (match_str((const char*) ln, " ROCKANGLE") == 1)){
		int i = 0;
		for(i=0; i<17; i++){
		  if((fgets(ln, bufsz, ITL)) != NULL){
		    int idx;
		    double tm, an;
		    char jnk[24];
		    sscanf(ln, "%s%02d %lf %lf", jnk, &idx, &tm, &an);
		    losf.info(6) << "While Reading line: "<<ln<<"\n"<<i<<") Got Angle: "<<an<<"Time: "<<tm<<"\n";
		    profile.ofsts[i] = an;
		    profile.times[i] = tm;
		  } else {
		    throw std::runtime_error("ERROR: Could read TAKO Timeline any further\n");
		  }
		}
	      }
	    } else {
	      throw std::runtime_error("ERROR: Could read TAKO Timeline any further\n");
	    }

	  }

	}
      }
      
      losf.info(3) << "mode="<<mode<<", mjdt="<<mjdt<<", mjds="<<mjds<<", mjde="<<mjde<<"\n";


      if(flg > 0){
	continue;
      }

      losf.info(4) << "About to check reallocation\n";

      if(mjde <= ini->start_MJD){
	flg = 100;
      }else if (mjdt < ini->start_MJD && mjde > ini->start_MJD){

	losf.info(4) << "reallocating attitude structure\n";

	ini->start_MJD = mjds;
	ephem = deallocateEphem(ephem);
	FILE *ephF = fopen(ini->EPHname.c_str(),"r");

	if(match_str( ini->EPHfunc.c_str(), "^yyyy_eph$") == 1){
	  ephem = yyyy_eph(ephF, ini->start_MJD, ini->stop_MJD, \
			   ini->Units, ini->Resolution);
	}else if(match_str( ini->EPHfunc.c_str(), "^xyzll_eph$") == 1){
	  ephem = xyzll_eph(ephF, ini->start_MJD, ini->stop_MJD, \
			    ini->Units, ini->Resolution);
	}else if(match_str( ini->EPHfunc.c_str(), "^tlederive$") == 1){
	  ephem = tlederive(ephF, ini->start_MJD, ini->stop_MJD, \
			    ini->Units, ini->Resolution, ini->SATname );
	}

	fclose(ephF);

	Timespan = (ini->stop_MJD-ini->start_MJD);
	res = ini->Resolution;
	inum = (int)((Timespan+res/2.0)/res);
	inum++;
	OAtt = reallocateAttitude(inum, OAtt);

	if ( OAtt == (Attitude *)NULL) {
	  throw std::runtime_error("ERROR: Cannot Allocate attitude data structure\nExiting..............\n");
	}

      } else if(mjdt < ini->stop_MJD &&  mjde > ini->stop_MJD){
	losf.info(4) << "Reallocating items: stop_MJD=" << ini->stop_MJD << ", inum=" << inum << "\n";


	ini->stop_MJD = mjde;
	ephem = deallocateEphem(ephem);
	FILE *ephF = fopen(ini->EPHname.c_str(),"r");


	if(match_str( ini->EPHfunc.c_str(), "^yyyy_eph$") == 1){
	  ephem = yyyy_eph(ephF, ini->start_MJD, ini->stop_MJD, \
			   ini->Units, ini->Resolution);
	}else if(match_str( ini->EPHfunc.c_str(), "^xyzll_eph$") == 1){
	  ephem = xyzll_eph(ephF, ini->start_MJD, ini->stop_MJD, \
			    ini->Units, ini->Resolution);
	}else if(match_str( ini->EPHfunc.c_str(), "^tlederive$") == 1){
	  ephem = tlederive(ephF, ini->start_MJD, ini->stop_MJD, \
			    ini->Units, ini->Resolution,ini->SATname );
	}


	fclose(ephF);


	Timespan = (ini->stop_MJD-ini->start_MJD);
	res = ini->Resolution;
	inum = (int)((Timespan+res/2.0)/res);
	inum++;
	OAtt = reallocateAttitude(inum, OAtt);

	if ( OAtt == (Attitude *)NULL) {
	  throw std::runtime_error("ERROR: Cannot Allocate attitude data structure\nExiting..............\n");
	}


      } else if (mjdt >= ini->stop_MJD){
	losf.info(4) << "Reached end of loop\n";
	break;
      }


      if(flg == 0){

	if(lastend > 0.0){
	  if(lastend < mjdt){
	    mjdt = lastend;
	  }
	}

	lastend = mjde;

	if(mode == 1 || mode == 2){
	  double lpos[2];
	  
	  losf.info(3) << "Calling MakeAtt with: mjdt="<<mjdt<<", mjde="<<mjde<<", mjds="<<mjds<<", pra="<<pra<<", pdec="<<pdec<<", offset="<<offset<<", ra="<<ra<<", dec="<<dec<<", mode="<<mode<<"\n";
	  MakeAtt(mjdt, mjde, mjds, pra, pdec, offset, ra, dec, 
		  mode, ini->Resolution, ephem, lpos, OAtt, ini->start_MJD);


// 	  if(mode == 1){
// 	    exit(0);
// 	  }

	  pra = lpos[0];
	  pdec = lpos[1];

	  //	  printf("Called MakeAtt with: mjdt=%f mjde=%f mjds=%f\npra=%f, pdec=%f offset=%f, ra=%f dec=%f mode=%d\n", mjdt, mjde, mjds, pra, pdec, offset, ra, dec, mode);
	  //	  printf ("1) i=45 ==> mjd=%f, i=46 ==> mjd=%f\n", OAtt->mjd[45], OAtt->mjd[46]);

  

// 	  if(pra == 0.0 && pdec == 0.0){
// 	    exit(1);
// 	  }

	} else if (mode == 3){

	  losf.info(3) << "Calling MakeProfiled with: mjdt="<<mjdt<<", mjde="<<mjde<<", mjds="<<mjds<<", pra="<<pra<<", pdec="<<pdec<<"\n";

	  MakeProfiled(mjdt, mjde, ini->Resolution, pra, pdec, profile.epoch, 
		       profile.times, profile.ofsts, ephem, OAtt, ini->start_MJD);

	  int idx = (int)(((mjde-ini->start_MJD))/ini->Resolution);
	  idx--;
	  pra = OAtt->Zra[idx];
	  pdec = OAtt->Zdec[idx];
	  //printf("Called MakeProfiled, mjdt=%f mjde=%18.10f startMJD=%18.10f Resol=%15.10f pra=%f pdec=%f idx=%d\n\n\n",  mjdt, mjde, ini->start_MJD, ini->Resolution, pra, pdec, idx);
	}

      }else if(flg == 100){
	if(mode == 2){
	  pra = ra;
	  pdec = dec;
	}else if (mode == 1){
	  double RaDec[2];
	  MakeSurvey(mjde, mjde, res, offset, ephem, OAtt, RaDec, 0, ini->start_MJD);
	  pra = RaDec[0];
	  pdec = RaDec[1];
	}
      }



      losf.info(3) << "Looping with start mjd = "<<mjdt<<"\n";
      flg = 0;
      mode = -1;
      mjdt = 0.0;
      mjds = 0.0;
      mjde = 0.0;
      offset = -999.0;
      ra = -999.0;
      dec = -999.0;


    }
  }

  if(ini->occflag == 1){
    // Getting the occultation

    occult ( ephem, ini->start_MJD, ini->stop_MJD, ini->Resolution,
	     OAtt, ini->EAA, ini->ELT_OFF_START, ini->ELT_OFF_STOP);

    doLimbTrace(ephem, ini->start_MJD, ini->stop_MJD, ini->Resolution, OAtt);
  
    int rechk = 0;

    if(rechk){
      occult ( ephem, ini->start_MJD, ini->stop_MJD, ini->Resolution,
	       OAtt, ini->EAA, ini->ELT_OFF_START, ini->ELT_OFF_STOP);

      doLimbTrace(ephem, ini->start_MJD, ini->stop_MJD, ini->Resolution, OAtt);
    }
  }

  saa( ephem, ini->saafile.c_str(), ini->start_MJD, ini->stop_MJD, ini->Resolution, OAtt);
  
  OAtt->ent = inum;

  if(!ini->OptFile.empty() ){
    if ( (OutF=fopen(ini->OptFile.c_str(),"w")) == NULL) {
      losf.err() << "Cound not open OutPut file " << ini->OptFile << "\n";
    }  
    fprintf(OutF, "     MJD          UTC            SAT_RA       SAT_DEC       X_RA       X_DEC       Y_RA       Y_DEC       Z_RA       Z_DEC       IN_SAA\n");
  }


  for(i=1; i<inum-1; i++){
    if(OAtt->mjd[i] >= org_stT && OAtt->mjd[i] <= org_enT) {
      int yyy, doy, hh, mm, ss;
      do_mjd2utc(OAtt->mjd[i], &yyy, &doy, &hh, &mm, &ss);
    

      if(!ini->OptFile.empty() && OutF != NULL){
	fprintf(OutF, " %15.8f   %d/%03d:%02d:%02d:%02d  %10.6f  %10.6f  %10.6f  %10.6f  %10.6f  %10.6f  %10.6f  %10.6f     %d\n", 
		OAtt->mjd[i], yyy, doy, hh, mm, ss,  OAtt->SatRA[i], OAtt->SatDEC[i], OAtt->Xra[i], OAtt->Xdec[i],
		OAtt->Yra[i], OAtt->Ydec[i], OAtt->Zra[i], OAtt->Zdec[i], OAtt->in_saa[i] );
      }

      /*
	printf( " %15.8f   %d/%03d:%02d:%02d:%02d  %10.6f  %10.6f  %10.6f  %10.6f  %10.6f  %10.6f  %10.6f  %10.6f\n", 
	OAtt->mjd[i], yyy, doy, hh, mm, ss,  OAtt->SatRA[i], OAtt->SatDEC[i], OAtt->Xra[i], OAtt->Xdec[i],
	OAtt->Yra[i], OAtt->Ydec[i], OAtt->Zra[i], OAtt->Zdec[i]);

      */


      if(i>1){
	
	if(fabs((OAtt->mjd[i]-OAtt->mjd[i-1])-ini->Resolution) > 0.00000000001){

	  losf.err() << "Something is wrong:i=" << (i-1) << " mjd=" << OAtt->mjd[i-1] << ",  i=" << i << " mjd=" << OAtt->mjd[i] << " ===> " << (fabs(OAtt->mjd[i]-OAtt->mjd[i-1])*1440.0) << "\n";

	}
      }
    }
    
  }

  Attitude *RAtt = allocateAttitude(oinum+1);
  if ( RAtt == (Attitude *)NULL) {
    throw std::runtime_error("ERROR: Cannot Allocate attitude data structure\nExiting..............\n");
  }  

  RAtt->ent = oinum;

  int k = 0;
  for(i=0; i<inum; i++){
    if(OAtt->mjd[i] >= org_stT && OAtt->mjd[i] <= org_enT) {
      int yyy, doy, hh, mm, ss;
      do_mjd2utc(OAtt->mjd[i], &yyy, &doy, &hh, &mm, &ss);
      if(OAtt->mjd[i] == ephem->MJD[i]){
	if(k > oinum){

	  losf.err() << "Expected " << oinum << " entries in the table, and obtained " << k << "\n";
	  throw std::runtime_error("ERROR: Something is wrong since tried to access array element beyond limits\n\n");
	}
	RAtt->mjd[k]    = OAtt->mjd[i];
	RAtt->X[k]      = ephem->X[i];
	RAtt->Y[k]      = ephem->Y[i];
	RAtt->Z[k]      = ephem->Z[i];
	RAtt->Lat[k]    = ephem->Lat[i];
	RAtt->Lon[k]    = ephem->Long[i];
	RAtt->Hei[k]    = ephem->Alt[i];
	RAtt->SatRA[k]  = OAtt->SatRA[i];
	RAtt->SatDEC[k] = OAtt->SatDEC[i];
	RAtt->Xra[k]    = OAtt->Xra[i];
	RAtt->Xdec[k]   = OAtt->Xdec[i];
	RAtt->Yra[k]    = OAtt->Yra[i];
	RAtt->Ydec[k]   = OAtt->Ydec[i];
	RAtt->Zra[k]    = OAtt->Zra[i];
	RAtt->Zdec[k]   = OAtt->Zdec[i];
	RAtt->in_saa[k] = OAtt->in_saa[i];
	k++;
      }

    }

  }

  //  OAtt = deallocateAttitude(OAtt);


  if(!ini->OptFile.empty() && OutF != NULL){
    fclose(OutF);
  }


  return RAtt;

}





Attitude * makeAttAsFl(InitI *ini, EphemData *ephem) {


  FILE *ITL;
  FILE *OutF = NULL;
  double Timespan, res;
  int inum, oinum, i;


  double org_stT = ini->start_MJD;
  double org_enT = ini->stop_MJD;

  losf.setMethod("makeAttAsFl");
  losf.err().precision(12);
  losf.info().precision(12);

  Timespan = (ini->stop_MJD-ini->start_MJD);
  res = ini->Resolution;
  inum = (int)((Timespan+res/2.0)/res);
  //  inum++;
  Attitude *OAtt = allocateAttitude(inum);

  if ( OAtt == (Attitude *)NULL) {
    throw std::runtime_error("ERROR: Cannot Allocate attitude data structure\nExiting..............\n\n");
  }

  oinum = inum;

/*
  This Ephem is needed to calculate pointing position during survey mode
  for time previous the given one
*/
  EphemData * Oephem;


  FILE *OephF = fopen(ini->EPHname.c_str(),"r");

  if(match_str( ini->EPHfunc.c_str(), "^yyyy_eph$") == 1){
    Oephem = yyyy_eph(OephF, ini->start_MJD, ini->stop_MJD, \
		     ini->Units, ini->Resolution);
  }else if(match_str( ini->EPHfunc.c_str(), "^xyzll_eph$") == 1){
    Oephem = xyzll_eph(OephF, ini->start_MJD, ini->stop_MJD, \
		      ini->Units, ini->Resolution);
  }else if(match_str( ini->EPHfunc.c_str(), "^tlederive$") == 1){
    Oephem = tlederive(OephF, ini->start_MJD, ini->stop_MJD, \
		       ini->Units, ini->Resolution, ini->SATname);
  }


  fclose(OephF);



  char ln[bufsz];

  if ( (ITL=fopen(ini->TLname.c_str(),"r")) == NULL) {
    std::string fname(ini->TLname);
    throw std::runtime_error("\nCound not open Timeline file "+fname);
  } else {  
    double pra = ini->Ira;
    double pdec = ini->Idec;

    double res = ini->Resolution/1440.0;  //convert resolution in days for mjd

    //    int flg = -1;

    int mode = -1;    // Used to distinguish between Survey (1) and Pointed (2)
    int type = -1;    // Used to distinguish between simple Survey (1) and Profiled survey (2)

    double offset = -999.0;
    double ra = -999.0;
    double dec = -999.0;
    double mjds = 0.0;
    double mjde = 0.0;
    double val1, val2;


    SurProf profile;
    int flgprof = 0;

    while(fgets(ln, bufsz, ITL)){
      int flgT = 1;

//       if(match((const char*) ln, "^[0-9]{4}-[0-9]{3}-[0-9]{2}:[0-9]{2}:[0-9]{2}.[0-9]{6}[ ]*[|][ ]*[A-Za-z]+[ ]*[|][ ]*Maneuver[ ]*[|]") == 1) {
      if(checkManeuver((const char*) ln) == 1) {
	mjde = parseAsFline(ln, &mode, &val1, &val2);
	//	printf("%s ===> Starting obs with mjde=%f, RA=%f, DEC=%f\n", ln, mjde, val1, val2);
      } else if(match_str((const char*) ln, "SS Param") == 1) {
	parseProfile(ln, &profile);
	flgprof = 1;
      } 

//       if((match((const char*) ln, "^[0-9]{4}-[0-9]{3}-[0-9]{2}:[0-9]{2}:[0-9]{2}.[0-9]{6}[ ]*[|][ ]*Maneuver[ ]*[|][ ]*Zenith[ ]*Point[ ]*[|]") == 1) && (flgprof == 0)){
      if((checkManZenith((const char*) ln) == 1) && (flgprof == 0)){
	losf.warn() << "\n##########################################################\n\n";
	losf.warn() << "\t\tWARNING\n\tNO SURVEY PROFILE DEFINED!\n   Could not calculate attitude between:\n       " << mjds << " and " << mjde << "\n" << "\n##########################################################\n\n";
	  flgT = -1;
	}else {

	  if(profile.epoch <= mjds){
	    type = 2;
	  }else {
	    type = 1;
	    offset = profile.defofst;
	  }

	}

      //  double org_stT = ini->start_MJD;
      //  double org_enT = ini->stop_MJD;

      if(mjds > 0 && mjds < mjde){

	if(mjds < org_stT && mjde > org_enT){

	  ini->start_MJD = mjds;
	  ephem = deallocateEphem(ephem);
	  FILE *ephF = fopen(ini->EPHname.c_str(),"r");


	  if(match_str( ini->EPHfunc.c_str(), "^yyyy_eph$") == 1){
	    ephem = yyyy_eph(ephF, ini->start_MJD, ini->stop_MJD, \
			      ini->Units, ini->Resolution);
	  }else if(match_str( ini->EPHfunc.c_str(), "^xyzll_eph$") == 1){
	    ephem = xyzll_eph(ephF, ini->start_MJD, ini->stop_MJD, \
			       ini->Units, ini->Resolution);
	  }else if(match_str( ini->EPHfunc.c_str(), "^tlederive$") == 1){
	    ephem = tlederive(ephF, ini->start_MJD, ini->stop_MJD, \
			      ini->Units, ini->Resolution,ini->SATname );
	  }



	  fclose(ephF);


	  Timespan = (ini->stop_MJD-ini->start_MJD);
	  res = ini->Resolution;
	  inum = (int)((Timespan+res/2.0)/res);
	  inum++;
	  OAtt = reallocateAttitude(inum, OAtt);

	  if ( OAtt == (Attitude *)NULL) {
	    throw std::runtime_error("ERROR: Cannot Allocate attitude data structure\nExiting..............\n\n");
	  }
	} else if (mjds < org_enT && mjde > org_enT ){

	  ini->stop_MJD = mjde;
	  Timespan = (ini->stop_MJD-ini->start_MJD);
	  res = ini->Resolution;
	  inum = (int)((Timespan+res/2.0)/res);
	  inum++;

	  ephem = deallocateEphem(ephem);
	  FILE *ephF = fopen(ini->EPHname.c_str(),"r");


	  if(match_str( ini->EPHfunc.c_str(), "^yyyy_eph$") == 1){
	    ephem = yyyy_eph(ephF, ini->start_MJD, ini->stop_MJD, \
			      ini->Units, ini->Resolution);
	  }else if(match_str( ini->EPHfunc.c_str(), "^xyzll_eph$") == 1){
	    ephem = xyzll_eph(ephF, ini->start_MJD, ini->stop_MJD, \
			       ini->Units, ini->Resolution);
	  }else if(match_str( ini->EPHfunc.c_str(), "^tlederive$") == 1){
	    ephem = tlederive(ephF, ini->start_MJD, ini->stop_MJD, \
			      ini->Units, ini->Resolution, ini->SATname);
	  }


	  fclose(ephF);


	  OAtt = reallocateAttitude(inum, OAtt);

	  if ( OAtt == (Attitude *)NULL) {
	    throw std::runtime_error("ERROR: Cannot Allocate attitude data structure\nExiting..............\n\n");
	  }
	} else if (mjds >= org_enT){
	  break;
	} else if (mjde < org_stT){
	  flgT = -1;
	}



	if(flgT == 1){
	  if((mode == 2) ||
	     (mode == 1 && type == 1)){
	    double lpos[2];
	    if(mode == 2){
	      ra = val1;
	      dec = val2;
	      offset = 0.0;
	    } else if (mode == 1){
	      ra = 0.0;
	      dec =0.0;
	      offset = profile.defofst;
	    }

	    MakeAtt2(mjds, mjde, pra, pdec, offset, ra, dec, 
		     mode, ini->Resolution, ephem, lpos, OAtt, ini->start_MJD);

	    pra = lpos[0];
	    pdec = lpos[1];

	  } else if((mode == 1) && (type == 2)){

	    MakeProfiled(mjds, mjde, ini->Resolution, pra, pdec, profile.epoch, 
			 profile.times, profile.ofsts, ephem, OAtt, ini->start_MJD);

	    //	  printf("Called MakeProfiled\n");
	    int idx = (int)(((mjde-ini->start_MJD)+ini->Resolution/0.5)/ini->Resolution);
	    pra = OAtt->Zra[idx];
	    pdec = OAtt->Zdec[idx];

	  
	  }
	}

	if (mjds >= org_enT){
	  losf.warn(1) << "Observation at " << mjde << " is outside the limits\n";
	  break;
	}

      }

      mjds = mjde;
      //      mjde = 0.0; 


    }


  }

  saa( ephem, ini->saafile.c_str(), ini->start_MJD, ini->stop_MJD, ini->Resolution, OAtt);

  if(ini->occflag == 1){
    // Getting the occultation

    occult ( ephem, ini->start_MJD, ini->stop_MJD, ini->Resolution,
	     OAtt, ini->EAA, ini->ELT_OFF_START, ini->ELT_OFF_STOP);
    doLimbTrace(ephem, ini->start_MJD, ini->stop_MJD, ini->Resolution, OAtt);
  
    int rechk = 0;

    if(rechk){
      occult ( ephem, ini->start_MJD, ini->stop_MJD, ini->Resolution,
	       OAtt, ini->EAA, ini->ELT_OFF_START, ini->ELT_OFF_STOP);
      doLimbTrace(ephem, ini->start_MJD, ini->stop_MJD, ini->Resolution, OAtt);
    }
  }

  OAtt->ent= inum;

  if(!ini->OptFile.empty() ){
    if ( (OutF=fopen(ini->OptFile.c_str(),"w")) == NULL) {
      losf.err() << "Cound not open OutPut file " << ini->OptFile << "\n";
    }  
    fprintf(OutF, "     MJD          UTC            SAT_RA       SAT_DEC       X_RA       X_DEC       Y_RA       Y_DEC       Z_RA       Z_DEC       IN_SAA\n");
  }

  for(i=1; i<inum-1; i++){
    if(OAtt->mjd[i] >= org_stT && OAtt->mjd[i] <= org_enT) {
      int yyy, doy, hh, mm, ss;
      do_mjd2utc(OAtt->mjd[i], &yyy, &doy, &hh, &mm, &ss);
    

      if(!ini->OptFile.empty() && OutF != NULL){
	fprintf(OutF, " %15.8f   %d/%03d:%02d:%02d:%02d  %10.6f  %10.6f  %10.6f  %10.6f  %10.6f  %10.6f  %10.6f  %10.6f     %d\n", 
		OAtt->mjd[i], yyy, doy, hh, mm, ss,  OAtt->SatRA[i], OAtt->SatDEC[i], OAtt->Xra[i], OAtt->Xdec[i],
		OAtt->Yra[i], OAtt->Ydec[i], OAtt->Zra[i], OAtt->Zdec[i], OAtt->in_saa[i] );
      }


      if(i>1){
	
	if(fabs((OAtt->mjd[i]-OAtt->mjd[i-1])-ini->Resolution) > 0.00000000001){

	  losf.err() << "Something is wrong:i=" << (i-1) << " mjd=" << OAtt->mjd[i-1] << ",  i=" << i << " mjd=" << OAtt->mjd[i] << " ===> " << (fabs(OAtt->mjd[i]-OAtt->mjd[i-1])*1440.0) << "\n";

	}
      }
    }
    
  }

  if(!ini->OptFile.empty() && OutF != NULL){
    fclose(OutF);
  }

  Attitude *RAtt = allocateAttitude(oinum+1);
  if ( RAtt == (Attitude *)NULL) {
    throw std::runtime_error("ERROR: Cannot Allocate attitude data structure\nExiting..............\n\n");
  }  

  RAtt->ent = oinum;
  losf.info(3) << "Expected " << oinum << " entries in the table\n";
  int k = 0;
  for(i=0; i<inum; i++){
    if(OAtt->mjd[i] >= org_stT && OAtt->mjd[i] <= org_enT) {
      int yyy, doy, hh, mm, ss;
      do_mjd2utc(OAtt->mjd[i], &yyy, &doy, &hh, &mm, &ss);
      if(OAtt->mjd[i] == ephem->MJD[i]){
	if(k > oinum){
	  losf.err() << "Expected " << oinum << " entries in the table, and obtained " << k << "\n";
	  throw std::runtime_error("ERROR: Something is wrong since tried to access array element beyond limits\n\n");
	}
	RAtt->mjd[k]    = OAtt->mjd[i];
	RAtt->X[k]      = ephem->X[i];
	RAtt->Y[k]      = ephem->Y[i];
	RAtt->Z[k]      = ephem->Z[i];
	RAtt->Lat[k]    = ephem->Lat[i];
	RAtt->Lon[k]    = ephem->Long[i];
	RAtt->Hei[k]    = ephem->Alt[i];
	RAtt->SatRA[k]  = OAtt->SatRA[i];
	RAtt->SatDEC[k] = OAtt->SatDEC[i];
	RAtt->Xra[k]    = OAtt->Xra[i];
	RAtt->Xdec[k]   = OAtt->Xdec[i];
	RAtt->Yra[k]    = OAtt->Yra[i];
	RAtt->Ydec[k]   = OAtt->Ydec[i];
	RAtt->Zra[k]    = OAtt->Zra[i];
	RAtt->Zdec[k]   = OAtt->Zdec[i];
	RAtt->in_saa[k] = OAtt->in_saa[i];

	//	printf("%5d), mjd=%f\n", k, RAtt->mjd[k]);
	k++;
      } 

    } 

  }



  OAtt = deallocateAttitude(OAtt);
  return RAtt;

}

double parseAsFline(char *ln, int *mode, double *val1, double *val2){

  double mjd;

  char jnk[bufsz];
  strcpy (jnk, ln);
  char *TL = strtok(jnk, "|");

  int yyy, doy, hh, mm, ss;

  sscanf(TL, "%d-%d-%d:%d:%d", &yyy, &doy, &hh, &mm, &ss);

  mjd = do_utcj2mjd (yyy, doy, hh, mm, ss);
  TL = strtok(NULL, "|");
  TL = strtok(NULL, "|");

  if((match2str((const char*) ln, "Inertial", "Point") == 1) ||
     (match_str((const char*) ln, "AutoRepoint") == 1)){
    *mode = 2;
  } else if (match2str((const char*) ln, "Zenith", "Point") == 1) {
    *mode = 1;
  }

  TL = strtok(NULL, "|");
  *val1 = atof(TL);

  TL = strtok(NULL, "|");
  *val2 = atof(TL);


  return mjd;

}






Attitude * doCmd(InitI *ini, EphemData *ephem) {



  FILE *OutF = NULL;

  double Timespan = (ini->stop_MJD-ini->start_MJD);
  double res = ini->Resolution;
  int inum = (int)((Timespan+res/2.0)/res);


  losf.setMethod("doCmd");
  losf.err().precision(12);
  losf.info().precision(12);


  //  inum++;
  losf.info(3) << "About to allocate attitude to " << inum << " elements\n";


  Attitude *OAtt = allocateAttitude(inum);

  if ( OAtt == (Attitude *)NULL) {
    std::ostringstream oBuf;
    oBuf << __FILE__ <<":" << __LINE__ << " ERROR: Cannot Allocate attitude data structure\nExiting..............\n\n" <<std::ends;

    throw std::runtime_error(oBuf.str());
  }



  if(match_str((const char*)  ini->TLname.c_str(), "SURVEY") == 1){
    std::string jnk = ini->TLname;
    char *TL = strtok((char *)jnk.c_str(), "|");
    TL = strtok(NULL, "|");
    double offset;

    if(chkStr(TL) == 0){
      std::ostringstream oBuf;
      oBuf << __FILE__ <<":" << __LINE__ << " in doCmd: while I should be doing a SURVEY mode\nobservation, the offset indicated (" << TL << ") should be a number only!\nExiting now............\n\n" << std::ends;
      

      throw std::runtime_error(oBuf.str());
    }

    sscanf(TL, "%lf", &offset);
    if(offset > 90.0 || offset < -90.0){

      std::ostringstream oBuf;
      
      oBuf << __FILE__ <<":" << __LINE__ << " in doCmd: while I should be doing a SURVEY mode\nobservation, the offset indicated ( " << offset << ") is outside the limits\nEXITING NOW....................\n\n" <<std::ends;

      throw std::runtime_error(oBuf.str());
      
    } else {
      losf.info(3) << "OrbSim should be doing a single cmd about survey with offset=" << offset<< "\n";


      doSurvey(ini->start_MJD, ini->stop_MJD, ini->Resolution,
	       ini->Ira, ini->Idec, offset, ephem, OAtt);
    }
  }else if(match_str( ini->TLname.c_str(), "PROFILED") == 1){
    std::string jnk = ini->TLname;
    char *TL = strtok((char *)jnk.c_str(), "|");
    TL = strtok(NULL, "|");
    double epoch;
    
    const int sz = 17;

    int i;

    double ofst[sz];
    double tms[sz];

    if(chkStr(TL) == 0){

      std::ostringstream oBuf;
      
      oBuf << __FILE__ <<":" << __LINE__ << ",  in doCmd: while I should be doing a PROFILED SURVEY mode\nobservation, the epoch indicated (" << TL << ") should be a number only!\nExiting now............\n\n" << std::ends;

      throw std::runtime_error(oBuf.str());

    }
    sscanf(TL, "%lf", &epoch);

    if(epoch > ini->start_MJD ){
      
      std::ostringstream oBuf;
      oBuf << "\n" << __FILE__ << ":" << __LINE__ << "\nERROR: doCmd, the profile epoch is not within the windows of interest\nExiting now........................\n\n" << std::ends;
      throw std::runtime_error(oBuf.str());
      
    }

    TL = strtok(NULL, "|");
    while (*TL == ' ')
      ++TL;

    int iret = sscanf(TL, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &tms[0], &ofst[0], &tms[1], &ofst[1], &tms[2], &ofst[2], &tms[3], &ofst[3], &tms[4], &ofst[4], &tms[5], &ofst[5], &tms[6], &ofst[6], &tms[7], &ofst[7], &tms[8], &ofst[8], &tms[9], &ofst[9], &tms[10], &ofst[10], &tms[11], &ofst[11], &tms[12], &ofst[12], &tms[13], &ofst[13], &tms[14], &ofst[14], &tms[15], &ofst[15], &tms[16], &ofst[16]);

    if(iret != sz*2){

      std::ostringstream oBufT;
      
      oBufT << __FILE__ <<":" << __LINE__ << ", ERROR: doCmd, the profile for the survey MUST contain " << (sz*2) << " elements, but is has " << iret <<". Exiting now........................\n\n" << std::ends;
      

      throw std::runtime_error(oBufT.str());

    }

    for(i=0; i<sz-1; i++){
      if(tms[i+1] <= tms[i]){
	std::ostringstream oBufT;
      
	oBufT << __FILE__ <<":" << __LINE__ << ", doCmd, survey profile times must be increasing\n" << i << " ==> " << tms[i] << "\n" << (i+1) << " ==> " << tms[i+1] << "\nExiting now........................\n\n" << std::ends;

	throw std::runtime_error(oBufT.str());
      }
    }


    for(i=0; i<sz; i++){
      if(ofst[i] <= -90.0 || ofst[i] >= 90.0){
	std::ostringstream oBufT;
      
	oBufT << __FILE__ <<":" << __LINE__ << ", doCmd, survey profile offsets must be between -90.0 and 90.0\nExiting now........................\n\n" << std::ends;

	throw std::runtime_error(oBufT.str());
      }
    }


    MakeProfiled(ini->start_MJD, ini->stop_MJD, ini->Resolution, 
		 ini->Ira, ini->Idec, epoch, tms, ofst, ephem, OAtt, ini->start_MJD);

  } else if (match_str( ini->TLname.c_str(), "POINTED") == 1){

    std::string jnk = ini->TLname;
    char *TL = strtok((char *)jnk.c_str(), "|");
    TL = strtok(NULL, "|");
    double ra, dec, offset;

    offset = -9999.0;
    int flgE = 0;
    int mode = 2;
    double lpos[2];


    std::ostringstream eBufT;
    if(chkStr(TL) == 0){
      eBufT << "\n\nin doCmd: while I should be doing a POINTED mode\nobservation, the ra indicated (" << TL << ") should be a number only!\n\n";
      flgE++;
    }
    sscanf(TL, "%lf", &ra);
    if(ra < 0.0 || ra > 360.0){
      eBufT << "in doCmd: while I should be doing a POINTED mode\nobservation, the ra indicated (" << ra << ") is outside the limits (0; 360)\n\n";
      flgE++;
    }

    TL = strtok(NULL, "|");
    if(chkStr(TL) == 0){
      eBufT << "in doCmd: while I should be doing a POINTED mode\nobservation, the dec indicated (" << TL << ") should be a number only!\n\n";
      flgE++;
    }
    sscanf(TL, "%lf", &dec);
    if(dec < -90.0 || dec > 90.0){
      eBufT << "in doCmd: while I should be doing a POINTED mode\nobservation, the dec indicated (" << dec << ") is outside the limits (-90; 90)\n\n";
      flgE++;
    }

    if(flgE > 0){
      eBufT << "\nExiting now......................\n\n" << std::ends;

      throw std::runtime_error(eBufT.str());
    }



    MakeAtt2(ini->start_MJD, ini->stop_MJD, ini->Ira, ini->Idec, offset, ra, dec, 
	     mode, ini->Resolution, ephem, lpos, OAtt, ini->start_MJD);


  }else {
    
    std::ostringstream eBuf;
    eBuf << "\n"<<__FILE__ << ":" << __LINE__ << " ERROR: doCmd SINGLE command " << ini->TLname << " is unknown!\nExiting now........................\n\n" << std::ends;

    throw std::runtime_error(eBuf.str());

  }

  saa( ephem, ini->saafile.c_str(), ini->start_MJD, ini->stop_MJD, ini->Resolution, OAtt);

  if(ini->occflag == 1){
    // Getting the occultation

    occult ( ephem, ini->start_MJD, ini->stop_MJD, ini->Resolution,
	     OAtt, ini->EAA, ini->ELT_OFF_START, ini->ELT_OFF_STOP);
    doLimbTrace(ephem, ini->start_MJD, ini->stop_MJD, ini->Resolution, OAtt);
  
    int rechk = 0;

    if(rechk){
      occult ( ephem, ini->start_MJD, ini->stop_MJD, ini->Resolution,
	       OAtt, ini->EAA, ini->ELT_OFF_START, ini->ELT_OFF_STOP);
      doLimbTrace(ephem, ini->start_MJD, ini->stop_MJD, ini->Resolution, OAtt);
    }
  }

  if(!ini->OptFile.empty() ){
    if ( (OutF=fopen(ini->OptFile.c_str(),"w")) == NULL) {
      losf.err() << "Cound not open OutPut file " << ini->OptFile << "\n";
    }  
    fprintf(OutF, "     MJD          UTC            SAT_RA       SAT_DEC       X_RA       X_DEC       Y_RA       Y_DEC       Z_RA       Z_DEC       IN_SAA\n");
  }


  OAtt->ent= inum;
  int i;
  for(i=1; i<inum; i++){
    int yyy, doy, hh, mm, ss;
    do_mjd2utc(OAtt->mjd[i], &yyy, &doy, &hh, &mm, &ss);
    

    if(!ini->OptFile.empty() && OutF != NULL){
      fprintf(OutF, " %15.8f   %d/%03d:%02d:%02d:%02d  %10.6f  %10.6f  %10.6f  %10.6f  %10.6f  %10.6f  %10.6f  %10.6f     %d\n", 
	      OAtt->mjd[i], yyy, doy, hh, mm, ss,  OAtt->SatRA[i], OAtt->SatDEC[i], OAtt->Xra[i], OAtt->Xdec[i],
	      OAtt->Yra[i], OAtt->Ydec[i], OAtt->Zra[i], OAtt->Zdec[i], OAtt->in_saa[i] );
    }

    if(i>1){
      if(fabs((OAtt->mjd[i]-OAtt->mjd[i-1])-ini->Resolution) > 0.0000000001){

	  losf.err() << "Something is wrong:i=" << (i-1) << " mjd=" << OAtt->mjd[i-1] << ",  i=" << i << " mjd=" << OAtt->mjd[i] << " ===> " << (fabs(OAtt->mjd[i]-OAtt->mjd[i-1])*1440.0) << "\n";

      }
    }

  }


  if(!ini->OptFile.empty() && OutF != NULL){
    fclose(OutF);
  }

  int k = 0;
  for(i=0; i<inum; i++){

    if(OAtt->mjd[i] == ephem->MJD[i]){
      OAtt->X[i]      = ephem->X[i];
      OAtt->Y[i]      = ephem->Y[i];
      OAtt->Z[i]      = ephem->Z[i];
      OAtt->Lat[i]    = ephem->Lat[i];
      OAtt->Lon[i]    = ephem->Long[i];
      OAtt->Hei[i]    = ephem->Alt[i];
      k++;
    } else {
      losf.out() << __FILE__ <<":" << __LINE__ << ", " << i << ") OAtt->mjd[" << i << "]=" << OAtt->mjd[i] << ", ephem->MJD[" << i << "]=" << ephem->MJD[i] << "\n";

    }


    if(k > inum){
      std::ostringstream eBuf;
      eBuf << "\n"<<__FILE__ << ":" << __LINE__ << " ERROR: Something is wrong since tried to access array element beyond limits of the attitude structure\n\n" << std::ends;

      throw std::runtime_error(eBuf.str());
    }

  }

  if(k != inum){
    std::ostringstream eBuf;
    eBuf << "\n"<<__FILE__ << ":" << __LINE__ << " ERROR: Expected " << inum << " elements, but found " << k << " in the attitude structure\n\n" << std::ends;

    throw std::runtime_error(eBuf.str());
  }

  return OAtt;
}


void parseProfile(char *ln, SurProf *profile){

  double mjd;

  char jnk[bufsz];
  strcpy (jnk, ln);
  char *TL = strtok(jnk, "|");

  int yyy, doy, hh, mm, ss;

  sscanf(TL, "%d-%d:%d:%d:%d", &yyy, &doy, &hh, &mm, &ss);

  mjd = do_utcj2mjd (yyy, doy, hh, mm, ss);
  TL = strtok(NULL, "|");
  TL = strtok(NULL, "|");
  const int len = strlen(TL);
  char *jnk2 = NULL;
  jnk2 = (char *) malloc((len) * sizeof(char));

  strcpy(jnk2, TL);
  char *Pf = strtok(jnk2, ",");

  int i = 0;
  int ia = 0;
  int it = 0;
  for(i=0; i<36; i++){
    double val;
    sscanf(Pf, "%lf", &val);
    if(i<17){
      profile->ofsts[ia] = val;
      ia++;
    } else if(i<=17 && i<34){
      profile->times[it] = val;
      it++;
    } else if (i == 34){
      profile->defofst = val;
    } else if (i == 35){
      profile->epoch = do_met2mjd(val);
    }

    Pf = strtok(NULL, ",");
  }

  free (jnk2);

  return;
}
