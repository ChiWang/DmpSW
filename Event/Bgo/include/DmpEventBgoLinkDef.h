/*
 *  $Id: DmpEventBgoLinkDef.h, 2014-04-24 10:30:11 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class DmpEvtRdcBgoMSD+;

// *
// *  TODO: delete old event classes(DmpEvtBgoPMT, DmpEvtBgoMSD) for Rdc and Sim.  Need to define new event class for sim.
// *
#pragma link C++ struct DmpEvtBgoPMT+;
#pragma link C++ class DmpEvtBgoMSD+;
#pragma link C++ class DmpEvtBgoShower+;
// *
// *  TODO: add calibration classes at here
// *
#pragma link C++ struct DmpCalBgoPMT+;
#pragma link C++ struct DmpCalBgoMSD+;

#endif

