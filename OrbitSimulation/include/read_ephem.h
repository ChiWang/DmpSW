/**
 * @file read_ephem.h
 * @brief This file contains functions to read/calculate ephemeredis and the attitude calculation.
 * @author Giuseppe Romeo
 * @date Created:  Nov 15, 2005
 * 
 * $Header: /nfs/slac/g/glast/ground/cvs/ScienceTools-scons/orbitSim/orbitSim/read_ephem.h,v 1.3 2009/05/06 15:25:37 vernaleo Exp $
 */



#ifndef ReadEphem_h
#define ReadEphem_h

#include "orbitSimStruct.h"
#include "DynamicStruct.h"

#ifdef __cplusplus
extern "C" {
#endif


#include <string.h>




/// Another way to return a NULL attitude structure
#define EPHNO ((EphemData *)NULL)


/// Another way to return a NULL attitude structure
#define ATTNO ((Attitude *)NULL)








  /**
   * @brief Function that allocates dynamically memory 
   * 
   * This function allocates dynamically memory 
   * for the ephemeredis structure. This function
   * returns the pointer to the newly allocated
   * ephemeredis structure.
   * 
   *  @param num - size or each array in the ephemeredis structure
   *
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
//EphemData * allocateEphem(int num, EphemData *eph);
EphemData * allocateEphem(int num);



  /**
   * @brief Function that deallocates dynamically memory 
   * 
   * This function frees dynamically allocated memory 
   * for the ephemeredis structure. This function
   * returns the pointer to the newly allocated
   * ephemeredis structure.
   * 
   *  @param eph - pointer to the ephemeredis structure
   *
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
EphemData * deallocateEphem(EphemData *eph);



  /**
   * @brief Function that NASA FDF ephemeredis file
   * 
   * This function expects an ephemeredis file input of this format:
   * \%d \%d \%d \%d \%d \%d \%lf \%lf \%lf \%lf \%lf
   * where the integers are year, month, day of the month, hours
   * minutes and seconds; while the remaining doubles are respectively X, Y, Z, Latitude and Longitude in EC.
   * X, Y, Z are in decimegamters and get converted to km, and Lat and Long are
   * calculated (not used from the file). yyyy_eph returns a pointer to an
   * EphemData structure.
   * 
   * @param ifp - FILE pointer for the ephemeredis
   * @param StartTime - start time for the interval of interest. It is in mjd
   * @param EndTime - end time for the interval of interest. It is in mjd
   * @param Units - conversion factor to km
   * @param Resolution - time resolution in minutes, or fraction of minutes
   *
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
EphemData *yyyy_eph(FILE *ifp, double StartTime, double EndTime,
		     double Units, double Resolution);



  /**
   * @brief Function that STK format ephemeredis file
   * 
   * The xyzll_eph routine was written to ingest the STK generated ephemeris for Swift.
   * It is similiar to the yyyy_eph routine.  The differences include a comment line as 
   * the first line of data from STK and the latitude and longitude will be used 
   * directly from the STK data.  The altitude will be calculated, but is not currently
   * planned to be used.  xyzll_eph expects an ephemeredis file input of this format:
   * \%d\/\%d \%d\:\%d\:\%lf \%lf \%lf \%lf \%lf \%lf \%lf \%lf
   * which are respectively day of the year, year, hour, minute, seconds, fraction of a second,
   * X, Y, Z, (in  km) Latitude, Longitude, RA and DEC component velocity (degrees).
   * This function returns a pointer to an EphemData structure.
   * 
   * @param ifp - FILE pointer for the ephemeredis
   * @param StartTime - start time for the interval of interest. It is in mjd
   * @param EndTime - end time for the interval of interest. It is in mjd
   * @param Units - conversion factor to km
   * @param Resolution - time resolution in minutes, or fraction of minutes
   *
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
EphemData * xyzll_eph(FILE *ifp, double StartTime, double EndTime,
		      double Units, double Resolution);



  /**
   * @brief Function that propagate ephemeredis based on a NORAD Two Line Elements
   * 
   * This routine uses a provided NORAD Two Line Elements file
   * to calculate the Ephemeredis, that is satellite position and 
   * Latitude and Longitude. The routine uses readtle to read in the 
   * needed parameters from the TLE file, and sgp4 to calculate the
   * satellite position with the specified time resolution.
   * 
   * @param ifp - FILE pointer for the ephemeredis
   * @param StartTime - start time for the interval of interest. It is in mjd
   * @param EndTime - end time for the interval of interest. It is in mjd
   * @param Units - conversion factor to km
   * @param Resolution - time resolution in minutes, or fraction of minutes
   * @param SatN - Name of the Satellite
   *
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
EphemData * tlederive(FILE *ifp, double StartTime,
		      double EndTime, double Units, double Resolution, std::string SatN);

  /**
   * @brief Function that allocates dynamically memory 
   * 
   * This routine allocates dynamically memory for the attitude structure
   * 
   * @param num - size of each array in the structure
   *
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
Attitude * allocateAttitude(int num);


  /**
   * @brief Function that frees dynamically allocated memory 
   * 
   * This routine frees dynamically allocated memory for the 
   * attitude structure
   * 
   * @param att - attitude pointer 
   *
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
Attitude * deallocateAttitude(Attitude *att);



  /**
   * @brief Function that re-allocates dynamically memory 
   * 
   * This routine re-allocates dynamically memory for the 
   * attitude structure. It is used to resize the structure
   * if needed. This is achieved by using realloc
   * 
   * @param num - size of each array in the structure
   * @param att - attitude pointer 
   *
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
Attitude * reallocateAttitude(int num, Attitude *att);



  /**
   * @brief Function that calculates attitude profile
   * 
   * This routine is called by makeAttTako to calculate
   * the attitude profile for Pointed and Fixed Survey
   * mode observation. As first step, the routine calculates
   * the slew time and slew profile by calling DoSlew. The 
   * calculated slew time is compared with the passed one.
   * Then, depending on the 
   * observing mode, the routine calls MakeSurvey, for Survey 
   * observations, or MakePointed for Pointed observations. The 
   * attitude data are written to the passed attitude structure.
   * 
   * @param mjdt - start time for the interval of interest in mjd format
   * @param mjde - end time for the interval of interest in mjd format
   * @param mjds - end of slew time in mjd format
   * @param pra  - previous RA, used to calculate slew profile
   * @param pdec - previous DEC, used to calculate slew profile
   * @param pra  - previous RA, used to calculate slew profile
   * @param offset - rocking angle offset used for SURVEY observations
   * @param ra  - current RA, used to calculate slew profile and for Pointed observations
   * @param dec - current DEC, used to calculate slew profile and for Pointed observations
   * @param mode - observation mode, 1 for Fixed Survey, 2 for Pointed observation
   * @param res - time resolution as given at the input process
   * @param ephem - pointer to an ephemeredis structure
   * @param lpos - array that contains RA and DEC at mjde time; this will be used for the next round.
   * @param OAtt - Overall attitude structure
   * @param TS - start time in mjd for the attitude structure
   *
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
void MakeAtt(double mjdt, double mjde, double mjds, double pra, 
	     double pdec, double offset, double ra, double dec, int mode, 
	     double res, EphemData *ephem, double *lpos, Attitude *OAtt, double TS );




  /**
   * @brief Function that calculates attitude profile
   * 
   * This routine is called by makeAttTako to calculate
   * the attitude profile for Pointed and Fixed Survey
   * mode observation. As first step, the routine calculates
   * the slew time and slew profile by calling DoSlew. Then, 
   * depending on the observing mode, the routine calls 
   * MakeSurvey, for Survey observations, or MakePointed for 
   * Pointed observations. The attitude data are written to 
   * the passed attitude structure.
   * 
   * @param mjdt - start time for the interval of interest in mjd format
   * @param mjde - end time for the interval of interest in mjd format
   * @param pra  - previous RA, used to calculate slew profile
   * @param pdec - previous DEC, used to calculate slew profile
   * @param offset - rocking angle offset used for SURVEY observations
   * @param ra  - current RA, used to calculate slew profile and for Pointed observations
   * @param dec - current DEC, used to calculate slew profile and for Pointed observations
   * @param mode - observation mode, 1 for Fixed Survey, 2 for Pointed observation
   * @param res - time resolution as given at the input process
   * @param ephem - pointer to an ephemeredis structure
   * @param lpos - array that contains RA and DEC at mjde time; this will be used for the next round.
   * @param OAtt - Overall attitude structure
   * @param TS - start time in mjd for the attitude structure
   *
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
void MakeAtt2(double mjdt, double mjde, double pra, double pdec, 
	      double offset, double ra, double dec, int mode, double res, 
	      EphemData *ephem, double *lpos, Attitude *OAtt, double TS );




  /**
   * @brief Function that calculates attitude profile for
   * survey observations
   * 
   * This routine is used to calculate the attitude profile 
   * any Survey mode observation. Attitude is calculated by 
   * calling GetPos, which does most of the transformations
   * using Euler angles. The routine also does a Sun Avoidance
   * manuevering if the Sun angle is smaller than 10 degrees
   * or greater than 170. Called with mode=0, the routine simply
   * calculates the RA and DEC for the Z-axis at any specified time.
   * 
   * @param start - start time for the interval of interest in mjd format
   * @param end - end time for the interval of interest in mjd format
   * @param res - time resolution as given at the input process
   * @param offset - rocking angle offset used for SURVEY observations
   * @param ephem - pointer to an ephemeredis structure
   * @param rd - array that contains RA and DEC at end time; this will be used for the next round.
   * @param mode - if only RA and DEC at time t, the mode should be 0, 1 otherwise
   * @param OAtt - Overall attitude structure
   * @param TS - start time in mjd for the attitude structure
   *
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
void MakeSurvey(double start, double end, double res, double offset, 
		EphemData *ephem, Attitude *OAtt, double *rd, int mode, double TS);

  /**
   * @brief Function that calculates attitude profile for
   * survey observations.
   * 
   * This routine is used to calculate the attitude profile during
   * a Survey mode observation, but it also does the switch in the
   * rocking offset. Attitude is calculated by making calls to
   * MakeSurvey, and the code does the rocking offset change
   * when the spacecraft goes from -z to +z. This routine is called from
   * doCmd, when calculating the attitude profile in a \"SINGLE\"
   * timeline type for SURVEY mode observations. The routine calculates also
   * slew profile from a specified initial position.
   * 
   * @param start - start time for the interval of interest in mjd format
   * @param end - end time for the interval of interest in mjd format
   * @param res - time resolution as given at the input process
   * @param ira - previous ra position used to calculate slew profile
   * @param idec - previous dec position used to calculate slew profile
   * @param offset - rocking angle offset used for SURVEY observations
   * @param ephem - pointer to an ephemeredis structure
   * @param OAtt - Overall attitude structure
   *
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
void doSurvey(double start, double end, double res, double ira, double idec,
	      double offset, EphemData *ephem, Attitude *OAtt);






  /**
   * @brief Function that calculates the time needed to slew
   * from a fixed, known location, to another location during
   * survey mode observation.
   * 
   * This routine is used to calculate the time needed for the spacecraft
   * to slew from a well known location to another location in the sky
   * that will be reached during fixed survey observation
   * 
   * @param mjdi  - Initial start time for the slew, in MJD format
   * @param mjds  - refernce to a slew time in mjd format
   * @param ira   - initial ra position used to calculate slew profile
   * @param idec  - initial dec position used to calculate slew profile
   * @param LAtt  - Pointer to a local attitude structure
   * @param idx   - Index corresponding to mjdi for the attitude structure
   * @param start - Overall start time in MJD format
   * @param res   - Time resolution in fraction of a day
   *
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
  int getEndPoint (double mjdi, double *mjds, double ira, double idec, 
		   Attitude* LAtt, int idx, double start, double res);





  /**
   * @brief Function that calculates attitude profile for
   * profiled survey observations
   * 
   * This routine is used to calculate the attitude profile for
   * any Profiled Survey mode observation. Attitude is calculated by 
   * calling doProfiled, and stored in a temporary attitude structure.
   * This temp attitude structure is used to calculate slew profile from 
   * a previous specified location.
   *
   * @param start - start time for the interval of interest in mjd format
   * @param end - end time for the interval of interest in mjd format
   * @param res - time resolution as given at the input process
   * @param ira - previous ra position used to calculate slew profile
   * @param idec - previous dec position used to calculate slew profile
   * @param epoch - this is the beginning of the profile, or ROCKSTART
   * @param tms - array containing times for the survey profile
   * @param ofst - array containing offsets for the survey profile
   * @param ephem - pointer to an ephemeredis structure
   * @param OAtt - Overall attitude structure
   * @param begin - start time in mjd for the attitude structure
   *
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
void MakeProfiled(double start, double end, double res, double ira, double idec, double epoch, 
		  double *tms, double *ofst, EphemData *ephem, Attitude *OAtt, double begin);


  /**
   * @brief Function that calculates attitude profile for
   * profiled survey observations
   * 
   * This routine calculates the attitude profile for
   * any Profiled Survey mode observation. Attitude is calculated so that
   * the rocking offset will change equal amounts in equal times by calling
   * MakeSurvey with the appropriate offset.
   *
   * @param start - start time for the interval of interest in mjd format
   * @param end - end time for the interval of interest in mjd format
   * @param res - time resolution as given at the input process
   * @param tms - array containing times for the survey profile
   * @param ofst - array containing offsets for the survey profile
   * @param ephem - pointer to an ephemeredis structure
   * @param OAtt - temporary attitude structure.
   *
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
void doProfiled(double start, double end, double res, double *tms, 
		double *ofst, EphemData *ephem, Attitude *OAtt);




  /**
   * @brief Function that calculates slew profile for any
   * observation mode
   * 
   * This routine calculates the slew profile for any observation mode.
   * The angular separation between the two specified points is calculated;
   * then slew time is calculated using a specified slew rate. Finally, 
   * the profile is obtained by finding the great circle passing for 
   * the two points, nad making the spacecraft move along this circle while 
   * covering equal angle in equal times.
   *
   * @param start - start slew time in mjd format
   * @param mjds - end slew time in mjd format
   * @param pra - initial RA position
   * @param pdec - final DEC position
   * @param ra - final RA position
   * @param dec - final DEC position
   * @param res - time resolution as given at the input process
   * @param ephem - pointer to an ephemeredis structure
   * @param OAtt - Overall attitude structure.
   * @param TS - start time in mjd for the Overall Attitude structure
   *
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
void DoSlew(double start, double mjds, double pra, double pdec, double ra, 
	    double dec, double res, EphemData *ephem, Attitude *OAtt, double TS);




  /**
   * @brief Function that calculates attitude profile for any
   * pointed observation
   * 
   * This routine calculates the attitude profile for any pointed
   * observation.  Attitude is calculated by calling GePointedtPos,
   * which does most of the transformations using Euler angles.
   *
   * @param mjds - start time in mjd format for the interval of interest
   * @param mjde - end time in mjd format for the interval of interest
   * @param res - time resolution as given at the input process
   * @param ra - final RA position
   * @param dec - final DEC position
   * @param ephem - pointer to an ephemeredis structure
   * @param OAtt - Overall attitude structure.
   * @param TS - start time in mjd for the Overall Attitude structure
   *
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
void MakePointed(double mjds, double mjde, double res, double ra, 
		 double dec, EphemData *ephem, Attitude *OAtt, double TS);





/* CKS: The saa routine was formally called xtesaa. Since this was the method 
   chosen for Swift, I renamed it.
*/


  /**
   * @brief Function that calculates if the spacecraft is within
   * the SAA region
   * 
   * This routine determines if each ephemeris point is in or out of the SAA polygon.
   * A filename should be passed which defines SAA polygon (longitude/latitude pairs).
   * In addition to an ephemeris point being in the SAA polynomial, the ephem point 
   * prior will also be included as in the SAA polynomial,because somewhere between the 
   * two points is when the actual SAA is entered (we're rounding by one resolution).  
   * The end of an SAA already rounds to next resolution (the value remains true for full resolution).
   *  For this routine to work, the last latitude/longitude pair
   * must be the same as the first.
   *
   * @param EphemPtr - Pointer to the Ephemeredis structure
   * @param filename - name of the file containing the SAA polygon definition
   * @param StartTime - start time of the interval of interest in mjd format
   * @param EndTime - End time of the interval of interest in mjd format
   * @param Resolution - Time resolution for the Ephem and Attitude structures
   * @param att - attitude structure
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  May 04, 2009
   */
void saa(EphemData *EphemPtr, const char *filename, double StartTime, 
	 double EndTime, double Resolution, Attitude *att);



  /**
   * @brief Function that calculates if the spacecraft is Earth occulted
   * 
   * 
   * This routine determines if the spacecraft is Earth occulted. atSun and
   * atEarthOccult are doing all the calculations.
   *
   * @param EphemPtr - Pointer to the Ephemeredis structure
   * @param StartTime - start time of the interval of interest in mjd format
   * @param EndTime - End time of the interval of interest in mjd format
   * @param Resolution - Time resolution for the Ephem and Attitude structures
   * @param att - attitude structure
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
void occult(EphemData *EphemPtr, double StartTime, double EndTime,
	    double Resolution, Attitude *att, double EAA, double start_ELT, double stop_ELT);




  /**
   * @brief Function that perfoms Earth limb tracing
   * 
   * 
   * This routine perfoms Earth limb tracing manuevering for every time
   * interval during which he spacecraft is Earth occulted. The routine 
   * initially finds those intervals, then by calling getPhase gets the 
   * angles or phases between the vector from the center of Earth to the target
   * and the local z-axis both at the beginning and at the end of the
   * occultation, finally by calling doLocation, the spacecraft will cover equal 
   * angles in equal times in its pointing along the Earth limb.
   *
   *
   * @param EphemPtr - Pointer to the Ephemeredis structure
   * @param StartTime - start time of the interval of interest in mjd format
   * @param EndTime - End time of the interval of interest in mjd format
   * @param Resolution - Time resolution for the Ephem and Attitude structures
   * @param att - attitude structure
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
void doLimbTrace(EphemData *EphemPtr, double StartTime, double EndTime, double Resolution, Attitude *att );


  /**
   * @brief Function that calculates the angle between the y-axis
   * and the target
   * 
   * 
   * This routine calculates the angle between the vector for the Earth 
   * center to the target and the y-axis in the spacecraft system of reference.
   * Transformations from one system of reference to another is done using Euler angles.
   *
   *
   * @param EphemPtr - Pointer to the Ephemeredis structure
   * @param Resolution - Time resolution for the Ephem and Attitude structures
   * @param att - attitude structure
   * @param js - index of the arrays in the attitude structure for either start or end of occultation
   * @param jep - index of the arrays in the ephemeredis structure for either start or end of occultation
   * @param phase - the calculated angle.
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
void getPhase(EphemData *EphemPtr, double Resolution, Attitude *att, int js, int jep, double *phase );


  /**
   * @brief Function that calculates where along the Earth limb
   * the spacecraft should be pointing.
   * 
   * 
   * This routine calculates the location along the Earth limb
   * where the spacecraft is pointing during the Earth limb tracing
   * manuevering. The main idea is that along the Earth limb, the spacecraft
   * covers equal angles in equal times.
   *
   *
   * @param EphemPtr - Pointer to the Ephemeredis structure
   * @param Resolution - Time resolution for the Ephem and Attitude structures
   * @param att - attitude structure
   * @param k - index of the array containing the occulted data points.
   * @param js - index of the arrays in the attitude structure during occultation
   * @param jep - index of the arrays in the ephemeredis structure during occultation
   * @param phase - the calculated angle at the start of the occultation
   * @param incr - angular increment
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
void doLocation(EphemData *EphemPtr, double Resolution, Attitude *att, 
		int k, int js, int jep, double phase, double incr);




#ifdef __cplusplus
}
#endif



#endif
