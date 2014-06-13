/*
 *  $Id: DmpCalAlgBgoPed.cc, 2014-05-16 01:53:56 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 03/04/2014
*/

#include "TClonesArray.h"

#include "DmpCalAlgBgoPed.h"
#include "DmpEventRaw.h"
#include "DmpEvtBgoHit.h"
#include "DmpIOSvc.h"
#include "TFile.h"
#include "TH1F.h"

//-------------------------------------------------------------------
DmpCalAlgBgoPed::DmpCalAlgBgoPed()
 :DmpVAlgorithm("Cal/Bgo/Ped")
{
}

//-------------------------------------------------------------------
bool DmpCalAlgBgoPed::Initialize(){
  DmpIOSvc::GetInstance()->ReadBranch();
}

//-------------------------------------------------------------------
bool DmpCalAlgBgoPed::ProcessThisEvent(){
}

//-------------------------------------------------------------------
bool DmpCalAlgBgoPed::Finalize(){
// *
// *  TODO: save output
// *
}

