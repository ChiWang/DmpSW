/** @file IGRField.h
@brief declare class IGRField.h

$Header: /nfs/slac/g/glast/ground/cvs/ScienceTools-scons/astro/astro/IGRField.h,v 1.10 2012/06/15 18:30:36 jchiang Exp $
*/

#ifndef IGRFIELD_HH
#define IGRFIELD_HH

#include <map>
#include <string>
#include "../include/IGRF_data.h"

namespace astro {

/** 
* \class GPS
* \brief Wrapper class for access to the f2c based IGRF-10 geomagnetic field model in igrf_sub.cxx
*
Wrapper class for access to the f2c based IGRF-10 geomagnetic field model in igrf_sub.cxx, which
computes field parameters of the Earth magnetic field. It is valid between 1990. and 2010.
The magnetic field multipole expansion coefficients have been moved from separate files in 
the IGRF distribution to igrf_sub.cxx and everything has been put in a private namespace   
*/

class IGRField {
   protected:

// Class is singleton object. Multiple instances are not allowed to
// prevent possible problems with the fortran based code of the model
//   static IGRField m_model;

// Year for which the magnetic field should be calculated       
      float m_year;
// Dipole moment of the earth in G*R_earth^3
      float m_dipoleMoment;
// B field strength north      
      float m_bNorth;
// B field strength east            
      float m_bEast;
// B field strength down            
      float m_bDown;
// B field strength X      
      float m_bX;
// B field strength Y            
      float m_bY;
// B field strength Z           
      float m_bZ;
// B field strength abs           
       float m_bAbs;
// B field strength at the equator following field line           
      float m_bEquator;
// McIlwain L           
      float m_L;
// m_Babs/m_bEquator         
      float m_B;
// effective distance from the dipole center in units of R_earth     
      float m_R;
// effective magnetic latitude lambda    
      float m_lambda;
// invariant magnetic latitude based on Smart and Shea Adv. Space Res. 36 (2005) p.2012   
      float m_invariantLat;
// vertical rigidity cutoff;      
      float m_rigidityCutoff;

      float m_latitude;
      float m_longitude;
      float m_altitude;
      
// Singleton private constructor
      IGRField();  
      ~IGRField(){};   

// Set the year of the magnetic field     
      void setYear(const float year, char *DataPath);
      
   public: 
   
// Get singleton object
      static IGRField& Model();// { return m_model; };   

// Compute field parameters for a given latitude, longitude and altitude 
      int compute(const float latitude,const float longitude,const float altitude,const float year=-1, char *DataPath="/lustrehome/gargano/DAMPE/DAMPESW/DmpSoftware/branches/I_0.0_OrbitSimulation/data/");

// Get dipole moment
      float dipoleMoment() const { return m_dipoleMoment; };
// Get McIlwain L
      float L() const { return m_L;};
// Get B/B0
      float B() const { return m_B;};
// Get B_North
      float bNorth() const { return m_bNorth;};
// Get B_East
      float bEast() const { return m_bEast;};
// Get B_Down
      float bDown() const { return m_bDown;};
// Get B_X
      float bX() const { return m_bX;};
// Get B_Y
      float bY() const { return m_bY;};
// Get B_Z
      float bZ() const { return m_bZ;};
// Get absolute value of B
      float bAbs() const { return m_bAbs;};
// Get absolute value of B at the equator
      float bEquator() const { return m_bEquator;};
// Get vertical rigidity cutoff
      float verticalRigidityCutoff() const { return m_rigidityCutoff;};
// Get invariant latitude
      float invariantLatitude() const { return m_invariantLat;};
// Get R
      float R() const  { return m_R;};
#ifndef SWIG 
// Get lambda (but it is a python keyword, hence the following SWIG stuff
      float lambda() const { return m_lambda;};
#endif
      float _lambda() const { return m_lambda;};

#ifndef SWIG
   const IGRF_data & igrf_data(const std::string & filename);
#endif

private:

   std::map<std::string, astro::IGRF_data> m_IGRF_data_map;

};

}
#endif
