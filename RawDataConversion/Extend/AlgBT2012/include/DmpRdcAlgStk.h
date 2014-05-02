/*
 *  $Id: DmpRdcAlgStk.h, 2014-05-02 14:35:58 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#ifndef DmpRdcAlgStk_H
#define DmpRdcAlgStk_H

#include "Rdc/DmpRdcVAlgSubDet.h"

class DmpRdcAlgStk : public DmpRdcVAlgSubDet{
/*
 *  DmpRdcAlgStk
 *
 *      This is the default Rdc Alg of Stk
 *
 *      User could write a new one, and
 *      append it into DmpAlgMgr in JobOpt file. Then,
 *      could run the new Alg.
 *
 */
public:
  DmpRdcAlgStk();
  ~DmpRdcAlgStk();
  bool ProcessThisEvent();      // convert one event

private:
  bool InitializeSubDet();      // setup connector, etc.
  void AppendThisSignal(const int&,const int&);

private:
  short     fFEEType;           // FEE type of this subDet
  short     fFEENo;             // number of FEE
};

#endif


