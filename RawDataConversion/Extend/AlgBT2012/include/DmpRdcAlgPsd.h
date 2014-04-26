/*
 *  $Id: DmpRdcAlgPsd.h, 2014-04-17 10:56:32 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#ifndef DmpRdcAlgPsd_H
#define DmpRdcAlgPsd_H

#include "Rdc/DmpRdcVAlgSubDet.h"

class DmpRdcAlgPsd : public DmpRdcVAlgSubDet{
/*
 *  DmpRdcAlgPsd
 *
 *      This is the default Rdc Alg of Psd
 *
 *      User could write a new one, and
 *      append it into DmpAlgMgr in JobOpt file. Then,
 *      could run the new Alg.
 *
 */
public:
  DmpRdcAlgPsd();
  ~DmpRdcAlgPsd();
  bool ProcessThisEvent();      // convert one event

private:
  bool InitializeSubDet();      // setup connector, etc.
  void AppendThisSignal(const int&,const float&);

};

#endif


