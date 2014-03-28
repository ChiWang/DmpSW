/*
 *  $Id: DmpBindingCore.cc, 2014-03-28 20:13:43 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpRunMode.h"
#include "DmpDetectorID.h"
#include "DmpVDataManager.h"
#include "DmpElementManager.h"
#include "DmpServiceManager.h"
#include "DmpAlgorithmManager.h"

//-------------------------------------------------------------------
// wrapper for DmpVOutDataManger
/*
using namespace boost::python;
struct DmpVDataManagerWrap : DmpVDataManager, boost::python::wrapper<DmpVDataManager>{

  void SetOutDataName(const std::string &n){
    if(override SetOutDataName = this->get_override("SetOutDataName")){
      return SetOutDataName(const std::string&);
    }
    return DmpVDataManager::SetOutDataName(const std::string&);
  }
  void Def_SetOutDataName(const std::string&){
    return this->DmpVDataManager::SetOutDataName(const std::string&);
  }
};
*/

//-------------------------------------------------------------------
BOOST_PYTHON_MODULE(libDmpCore){
  using namespace boost::python;

  // DmpPhase
  //enum_<DmpCore::DmpEPhase>("DmpEPhase")
  //  .value("kQuarter",  DmpCore::kQuarter)
  //  .value("kPrototype",DmpCore::kPrototype)
  //  .value("kProduct",  DmpCore::kProduct)
  //;

  // DmpRunMode
  enum_<DmpDetector::DmpERunMode>("DmpERunMode")
    .value("kUnknow",   DmpDetector::kUnknow)
    .value("k0Compress",DmpDetector::k0Compress)
    .value("kCompress", DmpDetector::kCompress)
    .value("kCalPed",   DmpDetector::kCalPed)
    .value("kCalADC",   DmpDetector::kCalADC)
  ;

  // DmpDetectorID
  enum_<DmpDetector::DmpEDetectorID>("DmpEDetectorID")
    .value("kPsd",  DmpDetector::kPsd)
    .value("kStk",  DmpDetector::kStk)
    .value("kBgo",  DmpDetector::kBgo)
    .value("kNud",  DmpDetector::kNud)
    .value("kWhole",DmpDetector::kWhole)
  ;

  // DmpVDataManager, only derived classes will use them
  class_<DmpVDataManager,boost::noncopyable>("DmpVDataManager",no_init)
    .def("SetOutDataPath",  &DmpVDataManager::SetOutDataPath)
    .def("AppendDataNote",  &DmpVDataManager::AppendDataNote)
    .def("GetOutDataPath",  &DmpVDataManager::GetOutDataPath)
    .def("GetOutDataName",  &DmpVDataManager::GetOutDataName)
  ;

  // DmpElementManager
// *
// *  TODO: how to bind template class?
// *
  //template<typename DmpElement>
  //class_<DmpElementManager<DmpElement>,boost::noncopyable>("DmpElementManager",no_init)
  //  .def("ListAllElements", &DmpElementManager<DmpElement>::ListAllElements)
  //  .def("Append",          &DmpElementManager<DmpElement>::Append)
  //  .def("Replace",         &DmpElementManager<DmpElement>::Replace)
  //;
  // DmpServiceManager
  //class_<DmpServiceManager,DmpServiceManager*>("DmpServiceManager",no_init);
  //scope().attr("gSvcMgr") = gSvcMgr;
  // DmpAlgorithmManager
  //class_<DmpAlgorithmManager,DmpAlgorithmManager*,bases<DmpElementManager>>("DmpAlgorithmManager",no_init);
  //scope().attr("gAlgMgr") = gAlgMgr;
}

