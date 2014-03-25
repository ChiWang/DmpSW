/*
 *  $Id: DmpEventBgoLinkDef.h, 2014-02-25 10:15:15 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ struct DmpPMTBgo+;
#pragma link C++ class DmpEvtBgoHit+;
// *
// *  TODO: delete DmpEvtBgoRaw, and rewrite RDC using DmpBgoHit
// *
//#pragma link C++ class DmpEvtBgoRaw+;
#pragma link C++ class DmpEvtBgoShower+;
#pragma link C++ class DmpRecordBgoPed+;

#endif

