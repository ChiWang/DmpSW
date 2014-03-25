/*
 *  $Id: DmpVAlgorithm.h, 2014-03-22 23:08:26 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 22/03/2014
*/


#ifndef DmpVAlgorithm_H
#define DmpVAlgorithm_H

#include <string>

class DmpVService;
class DmpVAlgorithm{
/*
 * DmpVAlgorithm
 *
 * drive yourself algorithm from this class, and thn
 * could register your algorithm into dampe software.
 *
 *
 *
 */
public:
  DmpVAlgorithm(const std::string &n):fName(n){}
  virtual ~DmpVAlgorithm(){}
  std::string   GetName() const   {return fName;}
  DmpVService*  Service(const std::string &name) const;

private:
  std::string   fName;

};

#endif

