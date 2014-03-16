/*
 *  $Id: DmpBindingCore.cc, 2014-03-12 11:20:13 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpCore.h"
#include "DmpBindingCore.h"
#include "DmpVOutDataManager.h"

//-------------------------------------------------------------------
// wrapper for DmpVOutDataManger
/*
using namespace boost::python;
struct DmpVOutDataManagerWrap : DmpVOutDataManager, boost::python::wrapper<DmpVOutDataManager>{

  void SetOutDataName(const std::string &n){
    if(override SetOutDataName = this->get_override("SetOutDataName")){
      return SetOutDataName(const std::string&);
    }
    return DmpVOutDataManager::SetOutDataName(const std::string&);
  }
  void Def_SetOutDataName(const std::string&){
    return this->DmpVOutDataManager::SetOutDataName(const std::string&);
  }
};
*/

//-------------------------------------------------------------------
BOOST_PYTHON_MODULE(libDmpCore){
  using namespace boost::python;

  // DmpCore
  enum_<DmpCore::DmpEPhase>("DmpEPhase")
    .value("kQuarter",  DmpCore::kQuarter)
    .value("kPrototype",DmpCore::kPrototype)
    .value("kProduct",  DmpCore::kProduct)
  ;

  enum_<DmpCore::DmpERunMode>("DmpERunMode")
    .value("kUnknow",   DmpCore::kUnknow)
    .value("kCompress", DmpCore::kCompress)
    .value("kCalPed",   DmpCore::kCalPed)
    .value("kCalADC",   DmpCore::kCalADC)
  ;

  enum_<DmpCore::DmpEDetectorID>("DmpEDetectorID")
    .value("kPsd",  DmpCore::kPsd)
    .value("kStk",  DmpCore::kStk)
    .value("kBgo",  DmpCore::kBgo)
    .value("kNud",  DmpCore::kNud)
    .value("kWhole",DmpCore::kWhole)
  ;

  // DmpBindingCore
  DmpBindingEntrance::Core::Psd();
  DmpBindingEntrance::Core::Stk();
  DmpBindingEntrance::Core::Bgo();
  DmpBindingEntrance::Core::Nud();

  // DmpVDataManager, only derived classes will use them
  class_<DmpVOutDataManager,boost::noncopyable>("DmpVOutDataManager",no_init)
    .def("SetOutDataPath",&DmpVOutDataManager::SetOutDataPath)
    .def("GetOutDataPath",&DmpVOutDataManager::GetOutDataPath)
    .def("GetOutDataName",&DmpVOutDataManager::GetOutDataName)
  ;

}

