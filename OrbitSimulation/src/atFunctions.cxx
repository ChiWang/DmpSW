/**
 * @file atFunctions.cc
 * @brief This file contains functions coming from the atFunc 
 * @author Giuseppe Romeo
 * @date Created:  Nov 15, 2005
 * 
 * $Header: /nfs/slac/g/glast/ground/cvs/ScienceTools-scons/orbitSim/src/atFunctions.cxx,v 1.2 2008/09/25 17:20:28 vernaleo Exp $
 */
#include "../include/atFunctions.h"

/*
#include <stdexcept>
#include <string>



#include <iostream>
#include <iomanip>
#include <sstream>

#include "st_stream/Stream.h"
#include "st_stream/StreamFormatter.h"
#include "st_stream/st_stream.h"
*/



int                         /* Making an Inverse Rotation Matrix     */
atInvRotMat(                /*                 ver 1.0  92/07/01  ay */
	    AtRotMat rm,    /* input: rotation matrix */
	    AtRotMat rm2)   /* output: inversed rotation matrix */
{ 
  int   i1, i2;
  for (i1=0; i1<3; i1++) {
    for (i2=0; i2<3; i2++) { rm2[i1][i2] = rm[i2][i1]; }
    }
  return (NORMAL_END);
}


                                         
/* 
 * product of two rotation matrices rm2 = rm1 rm0
 * no checking for consistency for unitarity is done.
 *						n.kawai 93.01.13
 */

int atRMProd(
	AtRotMat rm0,	/* input: rotation matrix to be multiplied*/
	AtRotMat rm1,	/* input: rotation matrix to multiply*/
	AtRotMat rm2)	/* output: product */
{
    int i,j, k;
    
    for (i=0; i<3; i++) {
	for (j=0; j<3; j++) {
	    rm2[i][j] = 0;
	    for (k=0; k<3; k++) {
		rm2[i][j] += rm1[i][k]*rm0[k][j];
	    };
	};
    };
    return (NORMAL_END);
}




/* 
 * examine earth occultation of specified direction (YEARTH)
 */
int atEarthOccult(
	AtVect satVect,	/* input: satellite pos. in equatorial coord. */ 
	AtVect xVect,	/* input: direction to be examined. (normalized) */ 
	AtVect sunVect,	/* input: vector to the sun */
	int *flag, 	/* output: condition 0:sky, 1:dark, 2:bright earth */
	double *el)	/* output: elevation angle of z from the earth edge */ 
{
    double earthSize, xDist, dot, zCross, satDistance;
    AtRotMat rm;
    AtVect satV, earthVect, xV;
    
    atInvVect(satVect, earthVect);
    satDistance = atNorm(earthVect);

    earthSize = asin(EARTH_RADIUS / satDistance);

    atAngDistance(xVect, earthVect, &xDist);
    *el = xDist - earthSize;
    
    if (*el <= - EPS) {
	atSetRotMatZX(sunVect, satVect, rm);
	atRotVect(rm, satVect, satV);
	atRotVect(rm, xVect, xV);
	dot = atScalProd(earthVect, xVect);
	zCross = satV[2] + xV[2]* (dot 
		- sqrt( EARTH_RADIUS * EARTH_RADIUS 
		- satDistance * satDistance + dot * dot));
	if (zCross < 0.) {
	    *flag = 1;		/* Dark Earth */
	} else {
	    *flag = 2;		/* Bright Earth */
	}
    } else {
	*flag = 0;
    }
    return 0;
} 


int                     /* Making an inverse vector        */
atInvVect(              /*          ver 1.0  92/07/01      */
        AtVect x,       /* in: vector */
        AtVect y)       /* out: reversed vector */
{ 
  y[0] = -x[0];  y[1] = -x[1];  y[2] = -x[2];
  return (NORMAL_END);
}


/* 
 * Absolute size of A VECTOR.
 */
double atNorm(	/* output: normalized vector*/
	AtVect x)	/* input: vector */
{
    return sqrt(atScalProd(x, x) );
} 



/* 
 * calc Scalar Product (Naiseki, Dot-prooduct) of two vectors 
 */
double atScalProd(	/* output: scaler (inner) product of x and y */
	AtVect x, 	/* input */
	AtVect y)	/* input */

{
  return (x[0]*y[0] + x[1]*y[1] + x[2]*y[2]);
}



int                 /* Finding angular distance                 */
atAngDistance(      /*                   ver 1.0   92/07/01  ay */
        AtVect x,   /* input: */
        AtVect y,   /* input: */
        double *r)  /* output: angular distance between x and y in radian */
{
  double  d1;
  d1 = ( x[0]*y[0] + x[1]*y[1] + x[2]*y[2] ) / atNorm(x) / atNorm(y) ;
  if ( d1 > 1.0-EPS ) { d1 = 1.0; }
  if ( d1 < -1.0+EPS ) { d1 = -1.0; }
  *r = acos( d1 );
  if ( *r < 0.0 || *r > PI ) { return (-1); }
  return (NORMAL_END);
}


/* 
 * ROTATION MATRIX defined by New Z-axis and a vector in (+)X-Z half plane.
 */
int atSetRotMatZX(
	AtVect zAxis,	/* input: vector defining new z-axis */
	AtVect xAxis,	/* input: vector in new +X-Z half plane */
	AtRotMat rm)	/* output: rotation matrix */
{
    AtVect x, y, z, yAxis;
    int i, code;
    
    atVectProd(zAxis, xAxis, yAxis);
    if ((code = atNormVect(zAxis, z))!=0) return code;
    if ((code = atNormVect(yAxis, y))!=0) return code;
    atVectProd(y, z, x);
    
    for (i=0; i<3; i++) {
	rm[0][i] = x[i];
	rm[1][i] = y[i];
	rm[2][i] = z[i];
    };
    return 0;
}    



int                     /* Making a vector prodact          */
atVectProd(             /*           ver 1.0  92/07/01  ay  */
        AtVect x,       /* input */
        AtVect y,       /* input */
        AtVect z)       /* output: vector (outer) product of x and y */
{
  z[0] = x[1]*y[2] - x[2]*y[1];
  z[1] = x[2]*y[0] - x[0]*y[2];
  z[2] = x[0]*y[1] - x[1]*y[0];
  return (NORMAL_END);
}



int atEllipsoido(
	AtPolarVect *xp, /* input: vector in celestial coordinate */ 
	double *latt,	/* output: latitude on the earth surface */
	double *heigh)	/* output: altitude from the earth surface */
	
{
    /* Initialized data */
    static double eps = 1e-7;
    static int nrmax = 5;

    /* Local variables */
    double beta, gamm, sing, latt2, rc, s, d__1;
    int nr;

    /* RS,DS -) HEIGH, LATT  (DISTORTIION OF THE EARTH) */
    nr = 0;
    s = 1e99;
    *latt = xp->lat;
    while(nr != nrmax && s > eps) {
	d__1 = cos(*latt);
	d__1 = 1./ (1. - EARTH_E2 * (d__1 * d__1));
	rc = EARTH_RADIUS * sqrt((1. - EARTH_E2)*d__1);
	beta = *latt+EARTH_E2*sin(*latt*2)*d__1/2.0;
	gamm = beta - *latt;
	sing = sin(gamm);
	d__1 = rc * sing;
	*heigh = sqrt(xp->r * xp->r - d__1 * d__1) - rc * cos(gamm); 
	latt2 = xp->lat - asin(*heigh * sing / xp->r);
	s = fabs(latt2 - *latt);
	*latt = latt2;
	++nr;
    }
    return 0;
}

int atGeodetic(
	double mjd,	/* input: time in MJD */
	AtVect x,	/* input: vector in sidereal equatorial coordinate */ 
	AtVect y)	/* output: vector in geodetic coordinate at mjd , 
			i.e. x-axis at (long, lat)=(0,0), and z at N-pole*/ 
{
    int code1;
    AtRotMat rm;

    code1 = atSetGeoRM(mjd, rm);
    atRotVect(rm, x, y);
    return code1;
}

/* 
 * calc rotation matrix for converting celestial position (J2000)
 *	to the geographic position on earth 
 */


int atSetGeoRM(
	double mjd,	/* input: time in MJD */
	AtRotMat rm)	/* output: rotation matrix  from J2000 to geographic,
			i.e. x-axis at (long, lat)=(0,0), and z at N-pole*/ 
	
{
    double gsttod;
    int code1;
    static AtVect z_axis = {0.,0.,1.};

    code1 = atSidereal(mjd, &gsttod);
    atSetRotMat(z_axis, gsttod, rm);
    return code1;
}

/* 
 * calc Greenwich sidereal time (KOSEJI)
 */
int atSidereal(
	double mjd,		/* input: time in MJD */
	double *gsttod) 	/* output: Greenwich sidereal time (radian)
				 at mjd true of date*/ 
{
    /* Local variables */
    static double d, m, x;

    d = (double) ((int) (mjd));
    x = (d - 15020.) / 36525.;
    m = (mjd - d) * 24. * 60.;
    *gsttod = (x * 3.8708e-4 + 36000.7689) * x + 99.6909833 + m * .25068447;
    *gsttod = fmod(*gsttod, 360.) * DEG2RAD;
    return 0;
}

/* 
 * CALC MATRIX FOR Rotation of coordinate with AXIS AND ROLL ANGLE.
 */
 
int atSetRotMat(
	AtVect axis,	/* input: rotation axis of coord, should be non zero*/
	double roll,	/* input: roll angle around axis (radian) */
	AtRotMat rm)	/* output: rotation matrix */
{
    AtVect normAxis;
    double cosRoll, c1, sinRoll;
    int i, i1, i2, cond;

    cond = atNormVect(axis, normAxis);
    if (cond == NORMAL_END) {
	cosRoll = cos(roll);
	c1 = 1-cosRoll;
	sinRoll = sin(roll);
	for (i=0; i<3; i++) {
	    i1 = (i+1)%3;
	    i2 = (i+2)%3;
	    rm[i][i]  = cosRoll + normAxis[i]*normAxis[i] *c1;
	    rm[i1][i] = normAxis[i]*normAxis[i1]*c1 - normAxis[i2]*sinRoll;
	    rm[i2][i] = normAxis[i]*normAxis[i2]*c1 + normAxis[i1]*sinRoll;
	};
    };
    return cond;
}

/* Converting the coordinate from Cartesian to Polar (RECPOL) */

int           
atVectToPol( AtVect x, AtPolarVect *y) {
  double  norm01, c, s;
  norm01 = x[0]*x[0] + x[1]*x[1];
  if ( (y->r = sqrt( norm01 + x[2]*x[2] )) == 0.0 ) { 
    y->lon = y->lat = 0.0;
    return (NULL_VECTOR); 
    }
  norm01 = sqrt( norm01 );
  y->lat = asin( x[2]/y->r );
  c = x[0]/norm01;  s = x[1]/norm01;
  if (norm01 < EPS) { y->lon = 0.0; }
  else if ( fabs( s ) < EPS ) { y->lon = (1.0 - c/fabs(c))*PI/2.0; }
  else { y->lon = atan((1.0-c)/s)*2.0; }
  while( y->lon >= 2.*PI ) { y->lon -= 2.*PI; }
  while( y->lon < 0.0 )    { y->lon += 2.*PI; }
  return (NORMAL_END);
}


/* 
 * Normalizing a vector  	ver 1.0  92/07/01  ay
 *             			ver 1.5  93/01/26  n.kawai    
 */
 
int atNormVect(
	   AtVect x,       /* input:  vector */	 
	   AtVect y)       /* output: normalized vector*/ 
{  
  int    k1;
  double nrm = x[0]*x[0]+x[1]*x[1]+x[2]*x[2];
  if( nrm == 0.0 ) { 
    for (k1=0; k1<3;k1++) { y[k1]=0.0; }
    return (NULL_VECTOR);
    } 
  else if (nrm == 1.0) { 
    nrm = sqrt( nrm ); 
    for (k1=0; k1<3;k1++) { y[k1]=x[k1]; } 
    }
  else { 
    nrm = sqrt( nrm ); 
    for (k1=0; k1<3;k1++) { y[k1]=x[k1]/nrm; } 
    }
  return (NORMAL_END);
}

                                         
/* 
 * ROTATE A VECTOR WITH ROTATION MATRIX.
 */

int atRotVect(
	AtRotMat rm,	/* input: rotation matrix */
	AtVect x,	/* input: vector */
	AtVect y)	/* output: vector */
{
    int i,j;
    
    for (i=0; i<3; i++) {
    	y[i] = 0;
	for (j=0; j<3; j++) {
	    y[i] += rm[i][j]*x[j];
	};
    };
    return (NORMAL_END);
}

/* calculates ra and dec of sun for mjd, returns as a 3-vect */

int atSun(double mjd, AtVect pos)
{
  /* taken from Christina William's version of Frank Marshall's version
     of the 1994 nautical almanac page c24, accurate to 0.01 degrees
     from 1950 to 2050 */

  /* typos fixed algorithm checked vs. 1995 Nautical Almanc, p. C24. 
     Name of internal atPolarVect changed from y50P to yP to protect 
     the innocent. Conversion to jd now uses global variable MJD2000 */

  AtPolarVect yP;
  double l, g, elon, obl, snl, jd, sunra, sundec;

  /* The fitting fprmula in this function use a variant form of MJD */
  jd = mjd - MJD2000 + 0.5;

  /* l is mean longitude of the sun, corrected for aberration */
  l = 280.466 + 0.9856474 * jd;
  while (l > 360.0)
    l = l - 360.0;
  while (l < 0.0)
    l = l + 360.0;

  /* g is mean anomaly */
  g = 357.528 + 0.9856003 * jd;
  while (g > 360.0)
    g = g - 360.0;
  while (g < 0.0)
    g = g + 360.0;

  /* elon is ecliptic longitude */
  elon = l + sin(g/RAD2DEG) * 1.915 + sin(2.0*g/RAD2DEG) * 0.02;

  /* obl is obliquity of the ecliptic */
  obl = 23.440 - (0.0000004 * jd) ;
  snl = sin(elon/RAD2DEG);
  sunra = RAD2DEG * atan2(snl * cos(obl/RAD2DEG), cos(elon/RAD2DEG));

  if (sunra < 0.0)
    sunra = sunra + 360.0;

  sundec = RAD2DEG * asin( sin(obl/RAD2DEG) * snl); /* dec in degrees */

  yP.lon = sunra/RAD2DEG; /* convert back to radians (yes, it's inefficient) */
  yP.lat = sundec/RAD2DEG; /* convert back to radians (yes, it's inefficient) */
  yP.r = 60.0;
  atPolToVect(&yP,pos);

  return 0 ;
}



int            /* Converting the coordinate from Polar to Cartesian (POLREC) */
atPolToVect(   /*                           ver 1.0  92/07/01  ay            */
        AtPolarVect *x,         /* input */
        AtVect y)               /* output: result */
{
  y[0] = x->r * cos( x->lat ) * cos( x->lon );
  y[1] = x->r * cos( x->lat ) * sin( x->lon );
  y[2] = x->r * sin( x->lat );
  return (NORMAL_END);
}

/*                                                                     */
/*     Originally coded in fortran (MJULIA) by K.Mitsuda.              */
/*     Translated in C and revised by A.Yoshida for ASTRO-D.           */
/*                                                                     */
int               /* Converting UT to Modified Julian Day (MJULIA)     */
atMJulian(        /*                            ver 1.0  92/07/02  ay  */
        AtTime *time,          /* input:  yr,mo,dy,hr,mn,sc,ms */
        double *mjd)           /* output: Modified Julian Day */
     /* Note: Day of the week is given by ( (mjd+3)%7 )  (0=SUN, 1=MON, etc) */
{
  double  y,m,d;
  if (time->mo > 2) { y = time->yr;      m = time->mo; }
  else              { y = time->yr - 1;  m = time->mo + 12; }
  if (time->yr < 10)       { y += 2000.0; }
  else if (time->yr < 100) { y += 1900.0; }
  d = time->dy + ( time->hr + ( time->mn + ( time->sc + time->ms/1000.0 )
                     /60.0 ) /60.0 ) /24.0;
  *mjd = ( floor(y*365.25) - 678912.0 )  /* <- should be calculated first */   
            + floor(y/400.0) - floor(y/100.0)
                                + floor((m-2.0)*30.59) + d ;
  return (NORMAL_END);
}

/* 
 * convert equatorial coordinate systems correcting for precession (SAISA)
 */
int atPrecession(
	double mjd0,	/* input: modified Julian Day */
	AtVect x0,	/* input: vector in equatorial coordiante at mjd0 */ 
	double mjd,	/* input: modified Julian Day */
	AtVect x)	/* output: vector in equatorial coordiante at mjd1 */ 
{
    AtRotMat rm;

    atPrecessRM(mjd0, mjd, rm);
    atRotVect(rm, x0, x);
    return 0;
} 


/*
 * Find Rotation Matrix for conversion of equatorial coordinate systems
 * correcting for precession (SAISA)
 */
int atPrecessRM(
	double mjd0,	/* input: modified Julian Day for the original coord*/
	double mjd,	/* input: modified Julian Day for the new coord*/
	AtRotMat rm)	/* output: rotation matrix to correct precession*/
{
  AtRotMat RmAto2000, RmBto2000, Rm2000toB;

  precessionRM(mjd0, RmAto2000);
  precessionRM(mjd,  RmBto2000);
  atInvRotMat(RmBto2000, Rm2000toB);
  atRMProd(RmAto2000, Rm2000toB, rm);
  return 0;
}



/* 
 * multiply a vector (z = f*x)
 *			           		 ver 1.5  93/01/25  n.kawai  
 */

int atMultVect(
	double f,	/* in: multiplicand for x */
	AtVect x,	/* in: vector */
	AtVect z)	/* out: answer*/
{
    z[0] = f*x[0];
    z[1] = f*x[1];
    z[2] = f*x[2];
    return (NORMAL_END);
}
