/*
 *  $Id: DmpCalAlgBgoPed.h, 2014-05-16 01:56:32 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 16/05/2014
*/

#ifndef DmpCalAlgBgoPed_H
#define DmpCalAlgBgoPed_H

#include "DmpVAlg.h"

class TClonesArray;
class TH1F;

class DmpCalAlgBgoPed : public DmpVAl{
/*
 *  DmpCalAlgBgoPed
 *
 */
public:
  DmpCalAlgBgoPed();
  ~DmpCalAlgBgoPed();
  bool Initialize();
  bool ProcessThisEvent();  // get entry and fill
  bool Finalize();

private:
  std::vector<TH1F*>    fHist1FSet;
  TClonesArray          *fBgoBarSet;

};

#endif


