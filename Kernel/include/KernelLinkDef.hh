/*=====================================================================
 *   File:   KernelLinkDef.hh
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    13/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  14/12/2013   15:43:09
=====================================================================*/

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link off all namespaces;

#pragma link C++ namespace DmpParameter;
#pragma link C++ namespace DmpParameter::Psd;
#pragma link C++ namespace DmpParameter::Stk;
#pragma link C++ namespace DmpParameter::Bgo;
#pragma link C++ namespace DmpParameter::Nud;

#pragma link C++ class DmpEvtHeader+;
#pragma link C++ class DmpVEvtSubDet+;
#pragma link C++ class DmpVManager+;

#endif
