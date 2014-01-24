/**
 * @file functions.h
 * @brief This file contains some utilities functions
 * @author Giuseppe Romeo
 * @date Created:  Nov 15, 2005
 * 
 * $Header: /nfs/slac/g/glast/ground/cvs/ScienceTools-scons/orbitSim/orbitSim/functions.h,v 1.4 2009/06/23 17:51:24 vernaleo Exp $
 */


#ifndef Functions_h
#define Functions_h

#include "orbitSimStruct.h"
#include "DynamicStruct.h"


#ifdef __cplusplus
extern "C" {
#endif


  //#include <stdio.h>
#include <math.h>

  //#include <regex.h>

/// Minutes in a day
#define minInDay 1440.0
/// Seconds in a day
#define secInDay 86400.0

  /// Moon Radius
#define MOON_RADIUS 1738.

  /// astronomical unit
#define AU 149597870.
  /// tolerance or errors
#define EPS 1.e-12
  ///MJD date for the epoch 1950
#define MJD_B1950 33281.923
  ///MJD date for the epoch 2000
#define MJD_J2000 51544.500



  /// GLAST Slew rate in degrees per minutes
#define SLEW_RATE 7.5    
  /// GLAST Sun Limit in degrees
#define SUN_LIMIT 10.0   
  /// Starting time in MJD format for GLAST clocks
#define MJDREF 51910.00



/* defined constants */
#ifndef _xmnpda
/// minutes in a day
#define _xmnpda 1440.0
/// seconds in a day
#define _secday 86400.0
  ///Earth rotations/siderial day 
#define _omega_E 1.00273790934
  /// two thirds
#define _tothrd (2.0/3.0)
  /// J2 Harmonic (WGS '72)
#define J2 1.0826158E-3
  /// J3 Harmonic (WGS '72)
#define XJ3  -2.53881E-6
  /// J4 Harmonic (WGS '72)
#define _J4value -1.65597E-6
  /// Numerical constant for 1.0E-6
#define _e6a 1.0E-6
  /// pi with many more digits
#define _pi 3.1415926535897932384626433279 
/// Numerical constant
#define _ae 1.0
/* WGS '72 - constants */
/// Earth gravitational constant
#define ge 398600.8        
/// Earth equatorial radius - kilometers 
#define xkmper 6378.137 
  /// Earth Geopotential constant
#define CK2 (1.0826158E-3 / 2.0)
  /// Earth Geopotential constant
#define CK4 (-3.0 * -1.65597E-6 / 8.0)
#endif








  /**
   * @brief Function that calculates the spacecraft position and velocity
   * 
   * 
   * This routine calculates spacecraft position and velocity based of
   * a set of parameters contained in the NORAD Two Line Element file.
   * sgp4 stands for Simplified General Perturbator no.4
   *
   *
   * @param t - time elapsed since the TLE epoch
   * @param pos - vector containing the spacecraft position in the ECI system
   * @param vel - vector containing the spacecraft velocity in the ECI system
   * @param satdata - strcuture containing all parameters coming from the TLE file
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
void sgp4(double t, vector *pos, vector *vel, atElemTle *satdata);



  /**
   * @brief Function that re-calculates the elements of an AtTime
   * structure when a fraction of time is added to one of its members
   * 
   * 
   * This routine is called by tlederive when any given time resolution
   * is added to one of its members, mostly the minute of second member.
   * The routine re-calculates all its member incrementing those that needed
   * to be incremented
   *
   *
   * @param tz - structure AtTime that needs to be re-arranged
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
void correctTm(AtTime *tz);


  /**
   * @brief Function that calculates the cube of a number
   * in double precision
   * 
   * 
   *
   *
   * @param x - input value
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
double cube(double x);



  /**
   * @brief Function that calculates the square root of a number
   * in double precision
   * 
   * 
   *
   *
   * @param x - input value
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
double sqr(double x);


  /**
   * @brief Function that calculates the modulus in 2*pi
   * of an angle
   * 
   *
   * @param x - input value
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
double fmod2p(double x);


  /**
   * @brief Function that calculates the modulus of
   * an input value
   * 
   *
   *
   * @param arg1 - input value
   * @param arg2 - modulus
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
double modulus (double arg1, double arg2);




  /**
   * @brief Function reads the content of a TLE file
   * 
   *
   *
   * This functions reads the content of lines that
   * match the specified satellite name, in this case GLAST.
   * The parameters contained in these lines are then read into
   * the TLE structure. If the epoch of the TLE parameters is
   * before the specified start time, and error is called, and
   * a NULL Ephemeredis structure is returned. Also, if the TLE
   * epoch is older than 30 days a warning is issued.
   *
   * @param Nl - number of lines contained in the array ln
   * @param CheckSatName - Satellite Name, in this case GLAST
   * @param ln - array of chars containing the TLE parameters
   * @param tle - structure for the TLE parameters
   * @param sta - start time in mjd
   * @param sto - end time in mjd
   * @param resol - time resolution.
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
int readTLE(const int Nl, char* CheckSatName, char ln[][100], 
	    atElemTle *tle, double sta, double sto, double resol);








  /**
   * @brief Function that converts calendar time,
   * as in year, month, day of the month, hours, minutes, seconds
   * into MJD time format.
   * 
   *
   * @param iyyy - year
   * @param mm - month
   * @param id - day of the month
   * @param hour - hours
   * @param min - minutes
   * @param sec - seconds
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
double do_cal2mjd(int iyyy, int mm, int id, int hour, int min, int sec);



  /**
   * @brief Function that converts MJD time format
   * into calendar time, that is year,  month, day of the month,
   * hours, minute, seconds
   * 
   * @param MJD - time in mjd as input value
   * @param iyyy - year
   * @param mm - month
   * @param id - day of the month
   * @param hour - hours
   * @param min - minutes
   * @param sec - seconds
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
void do_mjd2cal(double MJD, int *iyyy, int *mm, int *id, int *hour, int *min, int *sec);


  /**
   * @brief Function that converts UTC time,
   * as in year, day of the year, hours, minutes, seconds
   * into MJD time format.
   * 
   *
   * @param iyyy - year
   * @param doy - day of the year
   * @param hour - hours
   * @param min - minutes
   * @param sec - seconds
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
double do_utcj2mjd (int iyyy, int doy, int hour, int min, int sec);



  /**
   * @brief Function that converts MJD time in
   * UTC time as in year, day of the year, hours, minutes, seconds
   * 
   * @param mjd - mjd time, input value
   * @param yyy - year
   * @param doy - day of the year
   * @param hh - hours
   * @param mm - minutes
   * @param ss - seconds
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
void do_mjd2utc(double mjd, int *yyy, int *doy, int *hh, int *mm, int *ss);



  /**
   * @brief Function that converts Mission Elapsed Time in
   * MJD time format.
   * 
   * @param mjd - mjd time, input value
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
double do_met2mjd(double mjd);

  /**
   * @brief Function that converts MJD time to 
   * Mission Elapsed Time.
   * 
   * @param mjd - mjd time, input value
   * 
   * @author J. Vernaleo
   * @date Created:  Sep 08, 2008
   * @date Last Modified:  Sep 08, 2008
   */
double do_mjd2met(double met);

  /**
   * @brief Function that calculates the  Rotation Matrix at the specified time
   * 
   * @param mjd - time in mjd, input value
   * @param Rm - rotation matrix to correct precession, output value
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
void precessionRM(double mjd, AtRotMat Rm);



  /**
   * @brief Function that checks if a specified string
   * matches a specified string pattern. The match can take
   * place anywhere in the passed string; however, if the first
   * character in the string pattern is "^", the match MUST 
   * take place at the beginning, while if the last character
   * is "$", only the terminal part of the two strings must match.
   * The function returns zero if the match is not satisfied.
   * 
   * @param string - input string 
   * @param pattern - input regular expression pattern 
   *
   * @author Giuseppe Romeo
   * @date Created:  July 31, 2007
   */

  int match_str(const char *string, const char *pattern);



  /**
   * @brief Function that converts the passed string
   * to capital case. This function is called by match_str
   * in order to make a case insensitive match.
   * 
   * @param string - input string 
   * @param len - string length
   *
   * @author Giuseppe Romeo
   * @date Created:  July 31, 2007
   */

  char * capitalize_str(const char *str, const int len);




  /**
   * @brief Function that verifies is two passed pattern strings
   * separated by empty spaces (>= 0) are present in the passed string.
   * The function behavior is similar to match_str.
   * 
   * @param string - input string 
   * @param pattern1 - pattern string 1
   * @param pattern2 - pattern string 2
   *
   * @author Giuseppe Romeo
   * @date Created:  July 31, 2007
   */
  int match2str(const char *string, const char *pattern1, const char *pattern2);



  /**
   * @brief This function is a replacement for:
   * (match((const char*) ln, "^[0-9]{4}-[0-9]{3}-[0-9]{2}:[0-9]{2}:[0-9]{2}.[0-9]{6}[ ]*[|][ ]*[A-Za-z]+[ ]*[|][ ]*Maneuver[ ]*[|]") == 1)
   * since regular expressions are not available in Win32
   *
   * @param string - input string 
   *
   * @author Giuseppe Romeo
   * @date Created:  July 31, 2007
   */
  int checkManeuver (const char *str);




  /**
   * @brief This function is a replacement for:
   * match((const char*) ln, "^[0-9]{4}-[0-9]{3}-[0-9]{2}:[0-9]{2}:[0-9]{2}.[0-9]{6}[ ]*[|][ ]*Maneuver[ ]*[|][ ]*Zenith[ ]*Point[ ]*[|]")
   * since regular expressions are not available in Win32
   *
   * @param string - input string 
   *
   * @author Giuseppe Romeo
   * @date Created:  July 31, 2007
   */

  int checkManZenith(const char *str);



  /**
   * @brief This function verifies that the passed string does match
   * "^[0-9]{4}-[0-9]{3}-[0-9]{2}:[0-9]{2}:[0-9]{2}.[0-9]{6}", which
   * is the format for a date string in UTC. The function is called by
   * both checkManZenith and checkManeuver
   *
   * @param string - input string 
   *
   * @author Giuseppe Romeo
   * @date Created:  July 31, 2007
   */

  int checkDate (char *str);




  /**
   * @brief Function that checks is a passed string contains any other
   * character other than digits. The function is called by doCmd to check
   * that parameters such as rocking offset or epoch are indeed numbers.
   * 
   * @param str - input string
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   */
int chkStr(char *str);



  /**
   * @brief Function that extracts the time stamp from a line taken from an
   * AS-FLOWN timeline. The time in UTC, is then converted in mjd format.
   *
   * 
   * @param ln - input characters
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   */
double getMJD(char *ln);



  /**
   * @brief Function that calculates the interpolated y value 
   * when the location of two points in the plane is specified 
   * together with the x value of the interpolated point. 
   * This function is called by MakeSurvey, DoSlew, MakePointed
   * getPhase to get an Ephemeredis point outside the time boundary.
   *
   * 
   * @param y1 - y coordinate of point 1; input
   * @param y2 - y coordinate of point 2; input
   * @param x1 - x coordinate of point 1; input
   * @param x2 - x coordinate of point 2; input
   * @param x0 - x coordinate of interpolated point; input
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   */
double InterPVect(double y1, double y2, double x1, double x2, double x0);



  /**
   * @brief Function that calculates the transpose of a matrix
   *
   * 
   * @param rm - input matrix
   * @param Trm - transpose matrix; output
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   */
void TransposeM (AtRotMat rm, AtRotMat Trm);



  /**
   * @brief Function that creates a unit matrix
   *
   * 
   * @param rm - input matrix
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   */
void setUnit(AtRotMat rm);



  /**
   * @brief Function that rotates a given matrix counter-clockwise along 
   * the local x-axis of a given angle
   *
   * 
   * @param a - input angle in radians
   * @param rm - input matrix
   * @param Rmat - rotated matrix; output
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   */
void RotateOnX(double a, AtRotMat rm, AtRotMat Rmat);



  /**
   * @brief Function that rotates a given matrix counter-clockwise along 
   * the local y-axis of a given angle
   *
   * 
   * @param a - input angle in radians
   * @param rm - input matrix
   * @param Rmat - rotated matrix; output
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   */
void RotateOnY(double a, AtRotMat rm, AtRotMat Rmat);



  /**
   * @brief Function that rotates a given matrix counter-clockwise along 
   * the local z-axis of a given angle
   *
   * 
   * @param a - input angle in radians
   * @param rm - input matrix
   * @param Rmat - rotated matrix; output
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   */
void RotateOnZ(double a, AtRotMat rm, AtRotMat Rmat);




  /**
   * @brief Function that calculates the two constants that defines
   * a great circle passing for both the start and the ending point of a slew maneuvering. 
   *
   * 
   * This function finds the constants that specify the great circle
   * passing for both position 1 and 2. The great circle is defined as:
   * x*sinC2+y*cosC2+z/(sqrt((1/C1)^2 - 1))=0. The great circle found is
   * then used to calculate the slew profile.
   *
   * @param pos1 - cartesian vector to position 1; input
   * @param pos2 - cartesian vector to position 2; input
   * @param consts - two-dimensional array for the great circle definition; output
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   */
void getconsts( AtVect pos1,   AtVect pos2, double *consts);



  /**
   * @brief Function that does the actual calculation for the slew profile
   *
   * 
   *
   * This routine calculates where the spacecraft should be along
   * the great circle assuming that it leaves position 1, and covers
   * equal angles in equal times.
   *
   * @param xyz1 - Initial position 1; input
   * @param xyz2 - Final position 2; input
   * @param theta1 - angular separation in radians from position 1; input
   * @param theta2 - angular separation in radians from position 2; input
   * @param consts - constants that identify the great circle passing from point 1 and 2; input
   * @param xyz - calculated position; output
   * @param fact - signs for the square root in the function for the great circle
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   */
void getXYZ(AtVect xyz1, AtVect xyz2, double theta1, double theta2, double *consts, AtVect xyz, double fact);


  /**
   * @brief Function that calculates the determinant of a
   * 3 x 3 matrix whose rows are given by the 3 passed cartesian
   * vectors. 
   *
   * 
   *
   *
   * @param ra - position vector for row 1
   * @param rb - position vector for row 2
   * @param rc - position vector for row 3
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   */
double getDet(AtVect ra, AtVect rb, AtVect rc);



  /**
   * @brief Function that creates a cartesian unit vector based
   * on ra and dec
   *
   * 
   * @param ra - input RA
   * @param dec - input declination
   * @param xyz - unit vector generated from ra and dec
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   */
void rade2xyz( double ra,  double dec, AtVect xyz);



  /**
   * @brief Function that calculates the angular separation along a great circle
   * of two pints when RA and DEC is specified for each of them.
   *
   * 
   * @param pra - RA of point 1; input
   * @param pdec - DEC of point 1; input
   * @param ra - RA of point 2; input
   * @param dec - DEC of point 2; input
   * @param theta - angular separation; output
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   */
void angularSep(double pra, double pdec, double ra, double dec, double *theta);



  /**
   * @brief Function that calculates the time in minutes or fraction of minutes
   * necessary to lsew along a great circle from point 1 to point 2.
   *
   * 
   * @param pra - RA of point 1; input
   * @param pdec - DEC of point 1; input
   * @param ra - RA of point 2; input
   * @param dec - DEC of point 2; input
   * @param res - time resolution as fraction of a day; input
   * @param slewt - slew time; output
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   */
void getslewtime(double pra, double pdec, double ra, double dec, double res, double *slewt);



  /**
   * @brief Function that determines the minimum and maximum latitude and longitude 
   * values for the saa polygon.  These values are used later to quickly eliminate 
   * points as being potential points in the saa polygon.
   *
   * 
   * @param lon - array of longitude points
   * @param lat - array of latitude points
   * @param num_saa - size of each of the above arrays
   * @param minLon - minimum in Longitude
   * @param maxLon - maximum in Longitude
   * @param minLat - minimum in Latitude
   * @param maxLat - maximum in Latitude
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   */
int find_minmax(double *lon, double *lat, int num_saa, double *minLon, double *maxLon, double *minLat, double *maxLat);




  /**
   * @brief Function that determines the slope and intercept for every line which
   * makes up the saa polynomial. (Note: longitude is y axis, latitude the x axis)
   *
   * 
   * @param lon - array of longitude points
   * @param lat - array of latitude points
   * @param num_saa - size of each of the above arrays
   * @param slopes - array containing slopes
   * @param intercepts - array containing intercepts
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   */
int calculate_slopes(double *lon, double *lat, int num_saa, double *slopes, double *intercepts);




  /**
   * @brief Function that determines if a specified point is inside
   * the saa polygon determined by the passed longitude/latitude arrays
   *
   * 
   * @param dlat - latitude for the specified point
   * @param dlon - longitude for the specified point
   * @param lattable - array of latitude points
   * @param lontable - array of longitude points
   * @param slopes - array containing slopes
   * @param intercepts - array containing intercepts
   * @param num_saa - size of each of the above arrays
   * @param minLon - minimum in Longitude
   * @param maxLon - maximum in Longitude
   * @param minLat - minimum in Latitude
   * @param maxLat - maximum in Latitude
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   */
int pt_in_polygon(double dlat, double dlon,
		  double lattable[], double lontable[],
		  double slopes[], double intercepts[], int num_saa,
		  double minLon, double maxLon, double minLat, double maxLat);




  /**
   * @brief Function that finds the attitude of the
   * spacecraft during any SURVEY observation.
   *
   * 
   * This function calculates the attitude of the spacecraft 
   * while performing SURVEY mode observation. The attitude is
   * found by calculating the rotation matrix that transforms the local
   * spacecraft system of reference into the ECI system, and viceversa.
   * This overall rotation matrix is found through a series of
   * individual rotations. 
   *
   * @param mjd - time stamp in MJD format; input
   * @param vSat - vector in ECI system of the sapcecraft; input
   * @param vNVel - normalized velocity vector in the ECI system; input
   * @param SurvOfs - Survey rocking offset; input
   * @param RVal - array containing all the attitude information; output
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   */
void GetPos(double mjd, AtVect vSat, AtVect vNVel, double SurvOfs, double *RVal);



  /**
   * @brief Function that finds the attitude of the
   * spacecraft during any POINTED observation.
   *
   * 
   * This function calculates the attitude of the spacecraft 
   * while performing POINTED mode observation. The attitude is
   * found by calculating the rotation matrix that transforms the local
   * spacecraft system of reference into the ECI system, and viceversa.
   * This overall rotation matrix is found through a series of
   * individual rotations. 
   *
   * @param mjd - time stamp in MJD format; input
   * @param vSat - vector in ECI system of the sapcecraft; input
   * @param vNVelS - normalized velocity vector in the ECI system; input
   * @param ra - RA where the spacecraft z-axis is pointing; input
   * @param dec - DEC where the spacecraft z-axis is pointing; input
   * @param RaDe - array containing all the attitude information; output
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   */
void GetPointedPos(double mjd, AtVect vSat, AtVect vNVelS, double ra, double dec, double *RaDe);



#ifdef __cplusplus
}
#endif


#endif

