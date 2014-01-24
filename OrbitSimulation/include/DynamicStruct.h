/**
 * @file DynamicStruct.h
 * @brief This file contains all dynamically allocated structures definition used by the orbit Simulator.
 * @author Giuseppe Romeo
 * @date Created:  Nov 15, 2005
 * 
 * $Header: /nfs/slac/g/glast/ground/cvs/ScienceTools-scons/orbitSim/orbitSim/DynamicStruct.h,v 1.3 2008/09/25 17:20:28 vernaleo Exp $
 */




#ifndef DynamicStruct_h
#define DynamicStruct_h

#include <vector>


#ifdef __cplusplus
extern "C" {
#endif



  /**
   * @brief Structure that contains all ephemeredis information
   * 
   * This structure contains ephemeredis information 
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */

  //typedef struct EphemData {
struct EphemData {

  ///Default Constructor
  EphemData(): MJD(1), X(1), Y(1), Z(1), Lat(1), Long(1), Alt(1), VelRA(1), VelDEC(1) {};

  /// time stamp in MJD format
  std::vector <double> MJD;
  /// array for the X position in EC system
  std::vector <double> X;
  /// array for the Y position in EC system
  std::vector <double> Y;
  /// array for the Z position in EC system
  std::vector <double> Z;
  /// array for the Latitude in EC system
  std::vector <double> Lat;
  /// array for the Longitude in EC system
  std::vector <double> Long;
  /// array for the Height in EC system
  std::vector <double> Alt;
  /// array for the velocity compenent in RA in EC system
  std::vector <double> VelRA;
  /// array for the velocity compenent in DEC in EC system
  std::vector <double> VelDEC;
  /// Ephemeredis Period, not used with the available Ephemeredis
  double Period, 
  /// SemiMajorAxis, not used with the available Ephemeredis
     SemiMajorAxis;
  /// Number of entries in each array
  int ent;
};








  /**
   * @brief Structure that contains all attitude information
   * 
   * This structure contains attitude information 
   * 
   * @author Giuseppe Romeo
   * @date Created:  Nov 15, 2005
   * @date Last Modified:  Feb 08, 2006
   */


  //typedef struct Attitude {
struct Attitude {

  /// Default Constructor
  Attitude(): mjd(1), X(1), Y(1), Z(1), SatRA(1), SatDEC(1), Xra(1), Xdec(1), Zra(1), Zdec(1), Lat(1), Lon(1), Hei(1), in_saa(1), in_occ(1){};



  /// mjd time stamp
  std::vector <double> mjd;

  /// X position in ECI
  std::vector <double> X;                                          
  /// Y position in ECI
  std::vector <double> Y;
  /// Z position in ECI
  std::vector <double> Z;
                 
  /// RA for Satellite position
  std::vector <double> SatRA;
  /// DEC for Satellite position
  std::vector <double> SatDEC;            
  /// RA for X-axis
  std::vector <double> Xra;
  /// DEC for X-axis
  std::vector <double> Xdec;                
  /// RA for Y-axis
  std::vector <double> Yra;
  /// DEC for Y-axis
  std::vector <double> Ydec;                
  /// RA for Z-axis
  std::vector <double> Zra;
  /// DEC for Z-axis
  std::vector <double>  Zdec;                
  /// Spacecraft Latitude
  std::vector <double> Lat;
  /// Spacecraft Longitude
  std::vector <double> Lon;
  /// Spacecraft Height
  std::vector <double> Hei;           

  /// Boolean to specify if spacecraft is in saa (1) or not (0)
  std::vector <int> in_saa;                       

  /// Boolean to specify if spacecraft is in occultation (1) or not (0)
  std::vector <int> in_occ;                       
                               

  /// Number of entries in each array
  int ent;
} ;



#ifdef __cplusplus
}
#endif



#endif
