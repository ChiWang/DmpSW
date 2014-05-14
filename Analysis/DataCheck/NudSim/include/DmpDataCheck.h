
#ifndef DmpDataCheck_H
#define DmpDataCheck_H

#include "DmpVAlg.h"

class DmpDataCheck : public DmpVAlg{
/*
 *  DmpDataCheck
 *
 */
public:
  DmpDataCheck(const std::string&);
  ~DmpDataCheck();

  virtual bool Initialize();
  virtual bool ProcessThisEvent();
  virtual bool Finalize();

};

#endif

