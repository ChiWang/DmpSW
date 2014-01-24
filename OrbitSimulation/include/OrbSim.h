/**
 * @file OrbSim.h
 * @brief This file contains functions to parse an init file and start the attitude calculation.
 * @author Giuseppe Romeo
 * @date Created:  Nov 15, 2005
 * 
 * $Header: /nfs/slac/g/glast/ground/cvs/ScienceTools-scons/orbitSim/orbitSim/OrbSim.h,v 1.2 2008/09/25 17:20:28 vernaleo Exp $
 */

#ifndef OrbSim_h
#define OrbSim_h

#include "read_ephem.h"
#include "functions.h"

#ifdef __cplusplus
extern "C" {
#endif


  /// bufsz is the maximum length for a line contained in a file to be read
  const int bufsz = 600;



  //---------- FUNCTIONS ----------//

  /**
   * @brief Function that parses an init file
   * 
   * This function parses the content of a file,
   * specified as argument, into an InitI structure.
   * 
   * Possible returned velues are:
   * <ol>
   * <li> 0 when any of the 14 parameters are not found
   * <li> 1 otherwise
   * </ol>
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */
  int parseInit( const char *fname, InitI *inA);


  /**
   * @brief Function that calculates attitude based on TAKO Timeline
   * 
   * This function parses the content of a TAKO Timeline file,
   * and for each pointinf command, snapshot,  calculates the attitude profile. Each 
   * target is identified by using the separator "// ------------------------".
   * Three types of target are used:
   * <ol>
   * <li> pointed
   * <li> simple survey
   * <li> profiled survey
   * </ol>
   * Once the target has been identified, with the necessary 
   * parameters (ra & dec for pointed, offset or profile for survey)
   * an appropriate function is called to calculate the attitude:
   * <ol>
   * <li> MakeAtt for Pointed or Simple Survey
   * <li> MakeProfiled for Profiled Survey
   * </ol>
   * If a target starts before the beginning of the period of interest
   * then the attitude structure is reallocated, Ephemeredis are 
   * recalculated, and its attitude profile is calculated. The same is 
   * also true for any target that starts before the end of the period of 
   * interest. After parsing targets for the period of interest, saa
   * entry/exit are calculated, and also Earth Limb tracing is performed
   * for any intervals of time a given source is occulted by the Earth.
   * Finally, attitude only for the period of time of interest is returned.
   *
   * @param ini - structure containing all the needed parameters.
   * @param ephem - precalculated ephemeredis data.
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  March 28, 2007
   *
   */
  Attitude * makeAttTako(InitI *ini, EphemData *ephem);


  /**
   * @brief Function that calculates attitude based on AS-FLOWN Timeline
   * 
   * This function parses the content of an AS-FLOWN Timeline file,
   * and for each target calculates the attitude profile. 
   * Three types of target are used:
   * <ol>
   * <li> pointed
   * <li> simple survey
   * <li> profiled survey
   * </ol>
   * Once the target has been identified, with the necessary 
   * parameters (ra & dec for pointed, offset or profile for survey)
   * an appropriate function is called to calculate the attitude:
   * <ol>
   * <li> MakeAtt2 for Pointed or Simple Survey
   * <li> MakeProfiled for Profiled Survey
   * </ol>
   * If a target starts before the beginning of the period of interest
   * then the attitude structure is reallocated, Ephemeredis are 
   * recalculated, and its attitude profile is calculated. The same is 
   * also true for any target that start before the end of the period of 
   * interest. After parsing targets for the period of interest, saa
   * entry/exit are calculated, and also Earth Limb tracing is performed
   * for any intervals of time a given source is occulted by the Earth.
   * Finally, attitude only for the period of time of interest is returned.
   *
   * @param ini - structure containing all the needed parameters.
   * @param ephem - precalculated ephemeredis data.
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   *
   */
  Attitude * makeAttAsFl(InitI *ini, EphemData *ephem);




  /**
   * @brief Function that calculates attitude based on a SINGLE command
   * 
   * This function calculates the attitude profile for 
   * three types of target are used:
   * <ol>
   * <li> pointed
   * <li> simple survey
   * <li> profiled survey
   * </ol>
   * Functions called to do the actual attitude calculations are:
   * <ol>
   * <li> MakeAtt2 - for Pointed
   * <li> doSurvey - for Fixed Survey mode observation. This function does also
   * the offset change at the beginning of every orbit identified as going from
   * -z to + z axis.
   * <li> MakeProfiled - for Profiled Survey
   * </ol>
   *
   * @param ini - structure containing all the needed parameters.
   * @param ephem - precalculated ephemeredis data.
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   *
   */
  Attitude * doCmd(InitI *ini, EphemData *ephem);




  /**
   * @brief Function that parses a line from an AS_FLOWN Timeline
   * 
   * This function is called by makeAttAsFl to parse a line in 
   * the AS-FLOWN Timeline. Depending of the line, the function 
   * identifies the mode as 1 for SURVEY (both Fixed and Profiled)
   * or 2 for POINTED including Automatic Re-pointing. 
   *
   * A time stamp in the MJD format is returned.
   *
   * @param ln - line.
   * @param mode - this parameter specifies if a given target is a POINTED or SURVEY mode observation.
   * @param val1 - paramters specifying Target RA
   * @param val2 - paramters specifying Target DEC
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   *
   */
  double parseAsFline(char *ln, int *mode, double *val1, double *val2);


  /**
   * @brief Function that parses a line from an AS-FLOWN Timeline
   * 
   * This function is called by makeAttAsFl to parse a line in 
   * the AS-FLOWN Timeline that contains all the specifications
   * of the profile survey. Notice that if the profile epoch is
   * in the future, then the next survey target is considered to be 
   * a FIXED Survey, PROFILED if in the past.
   *
   *
   * @param ln - line.
   * @param profile - profile structure.
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   *
   */
  void parseProfile(char *ln, SurProf *profile);



  /**
   * @brief Function that returns anything contained
   * after a specified separator character. The function returns NULL
   * if the first character is "#"
   *
   *
   * @param ln - line of characters
   * @param find - separator character .
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   *
   */
  char *processline(char *ln, char find);


#ifdef __cplusplus
}
#endif



#endif
