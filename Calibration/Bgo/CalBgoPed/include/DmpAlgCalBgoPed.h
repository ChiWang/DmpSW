/*
 *  $Id: DmpAlgCalBgoPed.h, 2014-07-24 09:35:59 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/07/2014
*/

#ifndef DmpAlgCalBgoPed_H
#define DmpAlgCalBgoPed_H

#include "DmpVAlg.h"
#include <vector>

class DmpEvtRdcHeader;
class TClonesArray;
class TH1F;

class DmpAlgCalBgoPed : public DmpVAlg{
/*
 *  DmpAlgCalBgoPed
 *
 */
public:
  DmpAlgCalBgoPed();
  ~DmpAlgCalBgoPed();

  //void Set(const std::string &type,const std::string &value);
  // if you need to set some options for your algorithm at run time. Overload Set()
  bool Initialize();
  bool ProcessThisEvent();
  bool Finalize();

private:
typedef  std::map<std::string,TH1F*>
  DmpEvtRdcHeader       *fRawDataEvtHeader;
  TClonesArray          *fRawDataBgo;
  TClonesArray          *fCalDataBgo;
  std::map<std::string,TH1F*>    fPedHistOneBar;

};

#endif

