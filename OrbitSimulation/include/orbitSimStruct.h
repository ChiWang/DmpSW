/**
 * @file orbitSimStruct.h
 * @brief This file contains all structures definition used by the orbit Simulator.
 * @author Giuseppe Romeo
 * @date Created:  Nov 15, 2005
 * 
 * $Header: /nfs/slac/g/glast/ground/cvs/ScienceTools-scons/orbitSim/orbitSim/orbitSimStruct.h,v 1.3 2009/05/06 15:25:37 vernaleo Exp $
 */

#ifndef orbitSimStruct_h
#define orbitSimStruct_h

#include <string>

#ifdef __cplusplus
extern "C" {
#endif

  /**
   * @brief Structure that contains all the necessary parameters
   * 
   * This structure contains all the parameters needed 
   * by the orbit simulator
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  May 04, 2009
   */

typedef struct {
  /// starting time in MJD
  double start_MJD;    
  /// stopping time in MJD
  double stop_MJD;    
  /// SATname
  std::string SATname; 
  /// Timeline file name, path included
  std::string TLname; 
  /// Timeline type (TAKO, ASFLOWN, or SINGLE)
  std::string TLtype;      
  /// Ephemeris file name, path included  
  std::string EPHname;  
  /// function name to read/propagate ephemeris   
  std::string EPHfunc; 
  /// conversion factor to convert in Km    
  double Units;  
  /// Ephemeris resolution, and therefore   
  /// orbit simulator resolution in minutes
  double Resolution;   
  /// Initial RA                    
  double Ira;   
  /// Initial DEC      
  double Idec;       
  /// Output file where attitude will be written
  /// in FT2 format
  std::string OutFile; 
  /// Optional file used for ascii dump      
  std::string OptFile;  
  /// SAA file definition    
  std::string saafile;      
  /// Flag which is used to decide if Earth avoidance should be enabled, default is yes.
  int occflag;
  /// Earth Avoidance Angle value, default is 30 degrees
  double EAA;
  ///Earth LIMB TRACING exclusion start time (MJD)
  double ELT_OFF_START;
  ///Earth LIMB TRACING exclusion stop time (MJD)
  double ELT_OFF_STOP;
  /// Verbosity level
  int chat;
  /// Debug mode
  bool debug;

 } InitI;




  /**
   * @brief Structure that contains parameters for the profile survey
   * 
   * This structure contains all the parameters that 
   * specify a profiled survey
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
typedef struct {
  /// this is the ROCKSTART in mjd, or when the profile survey cycle is sopposed to begin 
  double epoch;
  /// default offset when ROCKSTART is in the future
  double defofst;
  /// array containing 17 angles in degrees for the offset
  double ofsts[17];
  /// array containing 17 time in seconds
  double times[17];

 } SurProf;




  /**
   * @brief Structure that contains time parameters
   * 
   * This structure contains all time parameters
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
typedef struct	{
  /// year 
  int yr;
  /// month
  int mo; 	
  /// day
  int dy; 	
  /// hour
  int hr; 	
  /// minute
  int mn; 	
  /// sec
  int sc; 
  /// millisec
  float ms; 
} AtTime;




  /**
   * @brief Structure that contains Two Line Elements (TLE)  parameters
   * 
   * This structure contains all the parameters
   * contained in the NORAD Two Line Element file
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
typedef struct atElemTle{
  /// Time structure
  AtTime tm;
  /// Time stamp in MJD when the parameters are good from
  double mjd;
  /// Fraction of second of the time stamp
  double isc;
  /// Satellite Number
  int SatNum, 
  /// Revolution number at epoch
    EpochRev;
  ///First time derivative of mean motion.
  double xndt2o,
  ///Second time derivative of mean motion.
    xndd6o,
  ///BSTAR drag term
    bstar,
  ///Inclination in the xplane
    xincl,
  ///Right ascension of the ascending node.
    xnodeo,
  ///Eccentricity.
    eo,
  ///Argument of perigee.
    omegao,
  ///Mean anomaly.
    xmo,
  ///Mean motion.
    xno;
  /// exponential part of xndd6o
  int iexp, 
  /// exponential part of bstar
     ibexp;      
} atElemTle;



  /**
   * @brief Structure that contains 3D vector plus its magnitude
   * 
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Mar 14, 2007
   */


typedef struct vector {
  /// 3-dimensional vector, the fourth element contains the magnitude
	double v[4];
}vector ;


/// Three-dimensional Cartesian Vector
typedef double AtVect[3];

/// 3 x 3 Rotation Matrix
typedef double AtRotMat[3][3];

  /**
   * @brief Structure that contains 3 Euler angles
   * 
   * Euler angle notation of rotation. (usually z-y-z)
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
typedef struct {
  /// First Euler Angle (radian)
  double phi; 
  /// Second Euler Angle (radian)
  double theta;
  /// Third Euler Angle (radian)
  double psi;
}	AtEulerAng;




  /**
   * @brief Three-dimensional Vector in Polar coordinate.
   * 
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */	
typedef struct	{
  /// radial component 
  double r;
  /// longitude or R.A. (radian)
  double lon;
  /// latitude or declination (radian)
  double lat;
} AtPolarVect;





/*
typedef struct EphemData {
  /// time stamp in MJD format
  double *MJD;
  /// array for the X position in EC system
  double *X;
  /// array for the Y position in EC system
  double *Y;
  /// array for the Z position in EC system
  double *Z;
  /// array for the Latitude in EC system
  double *Lat;
  /// array for the Longitude in EC system
  double *Long;
  /// array for the Height in EC system
  double *Alt;
  /// array for the velocity compenent in RA in EC system
  double *VelRA;
  /// array for the velocity compenent in DEC in EC system
  double *VelDEC;
  /// Ephemeredis Period, not used with the available Ephemeredis
  double Period, 
  /// SemiMajorAxis, not used with the available Ephemeredis
     SemiMajorAxis;
  /// Number of entries in each array
  int ent;
} EphemData;
*/


#ifdef __cplusplus
}
#endif



#endif
