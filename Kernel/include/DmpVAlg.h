/*
 *  $Id: DmpVAlg.h, 2014-04-08 12:33:11 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 22/03/2014
*/

#ifndef DmpVAlg_H
#define DmpVAlg_H

#include <string>

class DmpVAlg{
/*
 * DmpVAlg
 *
 * drive yourself algorithm from this class, and thn
 * could register your algorithm into dampe software.
 *
 */
public:
  DmpVAlg(const std::string &n):fName(n){}
  virtual ~DmpVAlg(){}
  virtual bool Initialize()=0;
  virtual bool ProcessThisEvent()=0;
  virtual bool Finialize()=0;

public:
  std::string   Name() const   {return fName;}

private:
  std::string   fName;

};

#endif

