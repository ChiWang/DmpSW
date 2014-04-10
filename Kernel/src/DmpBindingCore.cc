/*
 *  $Id: DmpBindingCore.cc, 2014-04-08 12:51:08 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpRunMode.h"
#include "DmpDetectorID.h"
#include "DmpVOptionSvc.h"
#include "DmpVAlg.h"
#include "DmpVSvc.h"
#include "DmpAlgorithmManager.h"
#include "DmpServiceManager.h"

//-------------------------------------------------------------------
    // Wrapper DmpVOptionSvc
struct DmpVOptionSvcWrapper : public DmpVOptionSvc, boost::python::wrapper<DmpVOptionSvc>{
  void Set(const std::string &type, DmpDetector::DmpEDetectorID id, const std::string &argv){
    this->get_override("Set")(type,id,argv);
  }
  std::string Get(const std::string &type){
    return this->get_override("Get")(type);
  }
};
    // Wrapper DmpVAlg
struct DmpVAlgWrapper : public DmpVAlg, boost::python::wrapper<DmpVAlg>{
  DmpVAlgWrapper(const std::string &n):DmpVAlg(n){}
  bool Initialize(){
    return this->get_override("Initialize")();
  }
  bool ProcessThisEvent(){
    return this->get_override("ProcessThisEvent")();
  }
  bool Finalize(){
    return this->get_override("Finalize")();
  }
};
    // Wrapper DmpVSvc
struct DmpVSvcWrapper : public DmpVSvc, boost::python::wrapper<DmpVSvc>{
  DmpVSvcWrapper(const std::string &n):DmpVSvc(n){}
  bool Initialize(){
    return this->get_override("Initialize")();
  }
  bool Finalize(){
    return this->get_override("Finalize")();
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

  // DmpVOptionSvc
  class_<DmpVOptionSvcWrapper,boost::noncopyable>("DmpVOptionSvc",no_init)
    .def("Set", pure_virtual(&DmpVOptionSvc::Set))
    .def("Get", pure_virtual(&DmpVOptionSvc::Get))
  ;

  // DmpVAlg
  class_<DmpVAlgWrapper,boost::noncopyable>("DmpVAlg",init<std::string>())
    .def("Initialize",      pure_virtual(&DmpVAlg::Initialize))
    .def("ProcessThisEvent",pure_virtual(&DmpVAlg::ProcessThisEvent))
    .def("Finalize",        pure_virtual(&DmpVAlg::Finalize))
  ;

  // DmpVSvc
  class_<DmpVSvcWrapper,boost::noncopyable>("DmpVSvc",init<std::string>())
    .def("Initialize",      pure_virtual(&DmpVSvc::Initialize))
    .def("Finalize",        pure_virtual(&DmpVSvc::Finalize))
  ;

  // DmpAlgorithmManager
  class_<DmpAlgorithmManager,boost::noncopyable>("DmpAlgorithmManager",no_init)
    .def("GetInstance", &DmpAlgorithmManager::GetInstance,return_value_policy<reference_existing_object>())
    .staticmethod("GetInstance")
    .def("Append",  &DmpAlgorithmManager::Append)
    .def("Replace", &DmpAlgorithmManager::Replace)
    .def("ListAllElements",&DmpAlgorithmManager::ListAllElements)
    .def("Initialize",&DmpAlgorithmManager::Initialize)
// *
// *  TODO:  why can't bind Process()
// *
    //.def("Process"  &DmpAlgorithmManager::Process)
    .def("Finalize",&DmpAlgorithmManager::Finalize)
  ;

  // DmpServiceManager
  class_<DmpServiceManager,boost::noncopyable>("DmpServiceManager",no_init)
    .def("GetInstance", &DmpServiceManager::GetInstance,return_value_policy<reference_existing_object>())
    .staticmethod("GetInstance")
    .def("Append",  &DmpServiceManager::Append)
    .def("Replace", &DmpServiceManager::Replace)
    .def("ListAllElements",&DmpServiceManager::ListAllElements)
    .def("Initialize",&DmpServiceManager::Initialize)
    //.def("Get",     &DmpServiceManager::Get)
    .def("Finalize",&DmpServiceManager::Finalize)
  ;
}


