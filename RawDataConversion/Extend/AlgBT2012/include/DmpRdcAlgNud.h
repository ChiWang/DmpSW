/*
 *  $Id: DmpRdcAlgNud.h, 2014-05-02 14:16:48 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#ifndef DmpRdcAlgNud_H
#define DmpRdcAlgNud_H

#include "Rdc/DmpRdcVAlgSubDet.h"

class DmpRdcAlgNud : public DmpRdcVAlgSubDet{
/*
 *  DmpRdcAlgNud
 *
 *      This is the default Rdc Alg of Nud
 *
 *      User could write a new one, and
 *      append it into DmpAlgMgr in JobOpt file. Then,
 *      could run the new Alg.
 *
 */
public:
  DmpRdcAlgNud();
  ~DmpRdcAlgNud();
  bool ProcessThisEvent();      // convert one event

private:
  bool InitializeSubDet();      // setup connector, etc.
  void AppendThisSignal(const int&,const int&);

private:
  short     fFEEType;           // FEE type of this subDet

};

#endif


