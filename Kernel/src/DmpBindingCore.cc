/*
 *  $Id: DmpBindingCore.cc, 2014-04-07 19:59:22 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpRunMode.h"
#include "DmpDetectorID.h"
#include "DmpVIOSvc.h"
#include "DmpElementManager.h"
#include "DmpServiceManager.h"
#include "DmpAlgorithmManager.h"
#include "DmpVRunTimeOptionSvc.h"

//-------------------------------------------------------------------
    // Wrapper DmpVRunTimeOptionSvc
struct DmpVRunTimeOptionSvcWrapper : public DmpVRunTimeOptionSvc, boost::python::wrapper<DmpVRunTimeOptionSvc>{
  void Set(const std::string &type, DmpDetector::DmpEDetectorID id, const std::string &argv){
    this->get_override("Set")(type,id,argv);
  }
};

//-------------------------------------------------------------------
BOOST_PYTHON_MODULE(libDmpCore){
  using namespace boost::python;

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

  // DmpVIOSvc, only derived classes will use them
  class_<DmpVIOSvc,boost::noncopyable>("DmpVIOSvc",no_init)
    .def("SetOutDataPath",  &DmpVIOSvc::SetOutDataPath)
    .def("AppendDataNote",  &DmpVIOSvc::AppendDataNote)
    .def("GetOutDataPath",  &DmpVIOSvc::GetOutDataPath)
    .def("GetOutDataName",  &DmpVIOSvc::GetOutDataName)
  ;

  // DmpServiceManager
  class_<DmpServiceManager,boost::noncopyable>("DmpServiceManager",no_init)
    .def("GetInstance", &DmpServiceManager::GetInstance,return_value_policy<reference_existing_object>())
    .staticmethod("GetInstance")
    .def("Append",  &DmpServiceManager::Append)
    .def("Replace", &DmpServiceManager::Replace)
    .def("ListAllElements", &DmpServiceManager::ListAllElements)
// *
// *  TODO: how to get a Svc in python script??
// *
    //.def("Get",     &DmpServiceManager::Get)
  ;

  // DmpAlgorithmManager
  class_<DmpAlgorithmManager,boost::noncopyable>("DmpAlgorithmManager",no_init)
    .def("GetInstance", &DmpAlgorithmManager::GetInstance,return_value_policy<reference_existing_object>())
    .staticmethod("GetInstance")
    .def("Append",  &DmpAlgorithmManager::Append)
    .def("Replace", &DmpAlgorithmManager::Replace)
    .def("ListAllElements",&DmpAlgorithmManager::ListAllElements)
  ;

  // DmpVRunTimeOptionSvc
  class_<DmpVRunTimeOptionSvcWrapper,boost::noncopyable>("DmpVRunTimeOptionSvc",no_init)
    .def("Set", pure_virtual(&DmpVRunTimeOptionSvc::Set))
  ;

}


