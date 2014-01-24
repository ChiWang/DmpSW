/**
 * @file IGRF_data.h
 * @brief Class to contain spherical harmonic coefficients for the
 * IGRF-11 model.
 * @author J. Chiang
 *
 * $Header: /nfs/slac/g/glast/ground/cvs/ScienceTools-scons/astro/astro/IGRF_data.h,v 1.1 2012/06/15 07:12:16 jchiang Exp $
 */

#ifndef astro_IGRF_data_h
#define astro_IGRF_data_h

#include <string>
#include <vector>

namespace astro {

class IGRF_data {

public:

   IGRF_data() : m_nmax(0), m_erad(0) {}

   IGRF_data(const std::string & filename);

   long int nmax() const {
      return m_nmax;
   }
   
   float erad() const {
      return m_erad;
   }

   const std::vector<float> & gh() const {
      return m_gh;
   }

private:

   long int m_nmax;
   float m_erad;
   std::vector<float> m_gh;

};

} // namespace astro

#endif // astro_IGRF_data_h
