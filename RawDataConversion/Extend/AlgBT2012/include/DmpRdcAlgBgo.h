/*
 *  $Id: DmpRdcAlgBgo.h, 2014-05-02 14:16:47 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#ifndef DmpRdcAlgBgo_H
#define DmpRdcAlgBgo_H

#include "Rdc/DmpRdcVAlgSubDet.h"

class DmpRdcAlgBgo : public DmpRdcVAlgSubDet{
/*
 *  DmpRdcAlgBgo
 *
 *      This is the default Rdc Alg of Bgo
 *
 *      User could write a new one, and
 *      append it into DmpAlgMgr in JobOpt file. Then,
 *      could run the new Alg.
 *
 */
public:
  DmpRdcAlgBgo();
  ~DmpRdcAlgBgo();
  bool ProcessThisEvent();      // convert one event

private:
  bool InitializeSubDet();      // setup connector, etc.
  void AppendThisSignal(const int&,const int&);

private:
  short     fFEEType;           // FEE type of this subDet
  short     fFEENo;             // number of FEE
};

#endif


