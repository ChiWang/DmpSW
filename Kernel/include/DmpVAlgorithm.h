/*
 *  $Id: DmpVAlgorithm.h, 2014-03-25 18:57:58 chi $
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
  virtual bool Initialize()=0;
  virtual bool ProcessThisEvent()=0;
  virtual bool Finialize()=0;

public:
  std::string   Name() const   {return fName;}

protected:
  DmpVService*  Service(const std::string &name) const;

private:
  std::string   fName;

};

#endif

