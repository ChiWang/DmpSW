/*
 *  $Id: DmpEventKernelLinkDef.h, 2014-06-11 22:06:35 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link off all namespaces;
// Rdc
#pragma link C++ class DmpEvtRdcHeader+;
#pragma link C++ class DmpEvtRdcMSD+;
// simulation
#pragma link C++ class DmpEvtMCPrimaryParticle+;

#endif
