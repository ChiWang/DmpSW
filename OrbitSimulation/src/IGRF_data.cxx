/**
 * @file IGRF_data.cxx
 * @brief Definition of class to contain spherical harmonic coefficients
 * for the IGRF-11 model.
 * @author J. Chiang
 *
 * $Header: /nfs/slac/g/glast/ground/cvs/ScienceTools-scons/astro/src/IGRF_data.cxx,v 1.1 2012/06/15 07:12:16 jchiang Exp $
 */

#include <cstdlib>

#include <fstream>
#include <sstream>
#include <stdexcept>

#include "../include/Util.h"

#include "../include/IGRF_data.h"

namespace astro {

IGRF_data::IGRF_data(const std::string & filename) {
   std::vector<std::string> lines;
   std::ifstream infile(filename.c_str());
   if (!infile.is_open()) {
      std::ostringstream message;
      message << "Error opening file: " << filename;
      throw std::runtime_error(message.str());
   } 
   std::string line;
   while (std::getline(infile, line, '\n')) {
      lines.push_back(line);
   }
   infile.close();
   std::vector<std::string> tokens;
   // Extract degree and order of model and Earth radius
   facilities::Util::stringTokenize(lines.at(1), " ", tokens, true);
   m_nmax = static_cast<long int>(std::atoi(tokens.at(0).c_str()));
   m_erad = static_cast<float>(std::atof(tokens.at(1).c_str()));
   // Read the spherical harmonic coefficients
   long int nm(m_nmax*(m_nmax + 2));
   long int j(2);
   for (long int i(0); i < nm; i++, j++) {
      facilities::Util::stringTokenize(lines.at(j), " ", tokens, true);
      m_gh.push_back(static_cast<float>(std::atof(tokens.at(0).c_str())));
   }
}

} // namespace astro
