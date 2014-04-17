/*
 *  $Id: DmpRdcAlgNud.h, 2014-04-17 09:10:34 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#ifndef DmpRdcAlgNud_H
#define DmpRdcAlgNud_H

#include "DmpRdcVAlgSubDet.h"

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
  bool Initialize();
  bool ProcessThisEvent();  // convert one event
  
private:
  bool SetupConnector();
  void AppendThisSignal(const int&,const float&);

};

#endif


