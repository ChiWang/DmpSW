/**
 * @file atFunctions.h
 * @brief This file contains functions coming from the atFunc library
 * @author Giuseppe Romeo
 * @date Created:  Nov 15, 2005
 * 
 * $Header: /nfs/slac/g/glast/ground/cvs/ScienceTools-scons/orbitSim/orbitSim/atFunctions.h,v 1.3 2008/09/25 17:20:28 vernaleo Exp $
 */


#ifndef atFunctions_h
#define atFunctions_h

#include "orbitSimStruct.h"
#include "functions.h"


#ifdef __cplusplus
extern "C" {
#endif


  //#include <stdio.h>
#include <math.h>
  //#include <regex.h>


/// Flag to denote that the function has sucessfully completed its job
#define NORMAL_END 0
/// Flag to denote unsuccessful processing
#define NULL_VECTOR -1
/// Earth first excentricity 
#define EARTH_E2 .0066934216
  /// mjd in 1950
#define MJD1950 33282.0
  /// mjd in 2000
#define MJD2000 51545.0
  /// Earth Radius
#define EARTH_RADIUS 6378.140

/// pi
#define PI 3.1415926535897932385
  /// 2 * pi
#define TWO_PI 6.283185307179586477
  /// Conversion factor from degree to radians
#define DEG2RAD 0.017453292519943295769
  /// Conversion factor from radians to degree
#define RAD2DEG 57.295779513082320877


  /**
   * @brief Function that converts AtTime structure in
   * mjd time
   * 
   *
   *
   * @param time - AtTime struture
   * @param mjd - mjd time
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */          
int  atMJulian( AtTime *time,  double *mjd);




  /**
   * @brief Function that converts polar geodetic coordinate
   *
   *
   * This routine converts polar geodetic coordinate latitude radial distance
   * to the geographic latitude and altitude from the earth surface
   * correcting for the ellipsoidal shape of the earth
   * 
   * @param xp - vector in celestial coordinate, input value
   * @param latt - latitude on the earth surface, output value
   * @param heigh - altitude from the earth surface, output value
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
int atEllipsoido(AtPolarVect *xp, double *latt,double *heigh);




  /**
   * @brief Function that converts sidereal equatorial coord to geodetic coordinate
   * 
   * @param mjd - time in MJD, input value
   * @param x - vector in sidereal equatorial coordinate, input value
   * @param y - vector in geodetic coordinate at mjd, output value
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
int atGeodetic(	double mjd, AtVect x, AtVect y);



  /**
   * @brief Function that converts sidereal equatorial coord to geodetic coordinate
   * 
   * @param mjd - time in MJD, input value
   * @param rm - rotation matrix  from J2000 to geographic, output value
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
int atSetGeoRM(double mjd, AtRotMat rm);




  /**
   * @brief Function that calculates Greenwich sidereal time
   * 
   * @param mjd - time in MJD, input value
   * @param gsttod - Greenwich sidereal time (radian) at mjd true of date, output value
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
int atSidereal( double mjd, double *gsttod);



  /**
   * @brief Function that calculates matrix for rotation of coordinate with axis and roll angle.
   * 
   * @param axis - rotation axis of coord, should be non zero, input value
   * @param roll - roll angle around axis (radian), input value
   * @param rm - rotation matrix, output value
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
int atSetRotMat(AtVect axis, double roll, AtRotMat rm);


  /**
   * @brief Function that converts the coordinate from Cartesian to Polar
   * 
   * @param x - cartesian vector, input value
   * @param y - polar vector, output value
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
int atVectToPol( AtVect x, AtPolarVect *y);



  /**
   * @brief Function that normalizes a vector
   * 
   * @param x - cartesian vector, input value
   * @param y - normalized vector, output value
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
int atNormVect( AtVect x,   AtVect y);



  /**
   * @brief Function that rotates a vector using a specified rotation matrix
   * 
   * @param rm - rotation matrix, input value
   * @param x - vector, input value
   * @param y - rotateed vector, output value
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
int atRotVect(AtRotMat rm, AtVect x, AtVect y);



  /**
   * @brief Function that calculates the Sun position in ECI
   * at the specified mjd time
   * 
   * @param mjd - time in MJD, input value
   * @param pos - vector to the Sun in AU, output value
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
int atSun(
	double mjd,	/* input: time in MJD */
	AtVect pos
);	/* output: vector to the sun in A.U.*/



  /**
   * @brief Function that converts Polar coordinates to Cartesian
   * 
   * @param x - polar vector, input value
   * @param y - cartesian vector, output value
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
int            /* Converting the coordinate from Polar to Cartesian (POLREC) */
atPolToVect(   /*                           ver 1.0  92/07/01  ay            */
        AtPolarVect *x,         /* input */
        AtVect y);




  /**
   * @brief Function that converts equatorial coordinate systems 
   * correcting for precession at time mjd, knowing the position at
   * at a previous time mjd0
   * 
   * @param mjd0 - initial time in mjd, input value
   * @param x0 - initial position, input value
   * @param mjd - current time in mjd, input value
   * @param x - current position at mjd, output value
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
int atPrecession(
	double mjd0,	/* input: modified Julian Day */
	AtVect x0,	/* input: vector in equatorial coordiante at mjd0 */ 
	double mjd,	/* input: modified Julian Day */
	AtVect x);	/* output: vector in equatorial coordiante at mjd1 */ 



  /**
   * @brief Function that finds Rotation Matrix for conversion 
   * of equatorial coordinate systems correcting for precession
   * 
   * @param mjd0 - initial time in mjd, input value
   * @param mjd - current time in mjd, input value
   * @param rm - rotation matrix to correct precession, output value
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
int atPrecessRM(
	double mjd0,	/* input: modified Julian Day for the original coord*/
	double mjd,	/* input: modified Julian Day for the new coord*/
	AtRotMat rm);	/* output: rotation matrix to correct precession*/




  /**
   * @brief Function that inverts a rotation matrix
   * 
   * @param rm - rotation matrix, input
   * @param rm2 - inverted rotation matrix, output
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
int atInvRotMat( AtRotMat rm, AtRotMat rm2); 



  /**
   * @brief Function that calculates the product of two matrices
   * 
   * @param rm0 - rotation matrix to be multiplied, input
   * @param rm1 - rotation matrix to multiply, input
   * @param rm2 - product, output
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
int atRMProd(	AtRotMat rm0, AtRotMat rm1, AtRotMat rm2);



  /**
   * @brief Function that examines Earth occultation of specified direction
   * 
   * @param satVect - satellite pos. in equatorial coord, input
   * @param xVect - direction to be examined, input
   * @param sunVect - vector to the sun, inout
   * @param flag - condition 0:sky, 1:dark, 2:bright earth; output
   * @param el - elevation angle of z from the earth edge; output
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
int atEarthOccult(
	AtVect satVect,	/* input: satellite pos. in equatorial coord. */ 
	AtVect xVect,	/* input: direction to be examined. (normalized) */ 
	AtVect sunVect,	/* input: vector to the sun */
	int *flag, 	/* output: condition 0:sky, 1:dark, 2:bright earth */
	double *el);	/* output: elevation angle of z from the earth edge */ 



  /**
   * @brief Function creates an inverse vector starting from
   * a given one
   * 
   * @param x - input vector
   * @param y - inverted vector; output
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
int atInvVect(  AtVect x,  AtVect y);



  /**
   * @brief Function that calculates the norm of a vector
   * 
   * @param x - input vector
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
double atNorm(	/* output: normalized vector*/
	      AtVect x);	/* input: vector */



  /**
   * @brief Function that calculates the scalar product
   * of two vectors
   * 
   * @param x - input vector
   * @param y - input vector
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
double atScalProd(	/* output: scaler (inner) product of x and y */
	AtVect x, 	/* input */
	AtVect y);	/* input */




  /**
   * @brief Function that calculates the angular distance of
   * two points as specified by two vectors
   * 
   * @param x - input vector
   * @param y - input vector
   * @param r - angular distance between x and y in radian; output
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
int atAngDistance(  AtVect x, AtVect y, double *r); 




  /**
   * @brief Function that finds the rotation matrix defined 
   * by New Z-axis and a vector in (+)X-Z half plane.
   * 
   * @param zAxis - input vector defining new z-axis 
   * @param xAxis - input vector in new +X-Z half plane
   * @param rm - rotation matrix; output
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
int atSetRotMatZX(
	AtVect zAxis,	/* input: vector defining new z-axis */
	AtVect xAxis,	/* input: vector in new +X-Z half plane */
	AtRotMat rm);	/* output: rotation matrix */




  /**
   * @brief Function that calculates the vector product
   * of two vectors
   * 
   * @param x - input vector 
   * @param y - input vector 
   * @param z - vector product; output
   *
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   */
int atVectProd (  AtVect x, AtVect y, AtVect z); 






int atMultVect(
	double f,	/* in: multiplicand for x */
	AtVect x,	/* in: vector */
	AtVect z);	/* out: answer*/


#ifdef __cplusplus
}
#endif


#endif
