/*
 *  $Id: DmpEventBgoLinkDef.h, 2014-07-19 15:07:41 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class DmpEvtRdcBgoBar+;
#pragma link C++ class DmpEvtMCBgoBar+;
#pragma link C++ class DmpEvtBgoShower+;
//-------------------------------------------------------------------
// for Calibration
#pragma link C++ class DmpCalBgoBarPed+;
#pragma link C++ class DmpCalDataBgoMSDMip+;
#pragma link C++ class DmpCalDataBgoMSDRel+;

#endif

