/*
 *  $Id: DmpBindingCore.cc, 2014-04-08 12:51:08 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpRunMode.h"
#include "DmpDetectorID.h"
#include "DmpVIO.h"
#include "DmpVOption.h"
#include "DmpAlgorithmManager.h"

//-------------------------------------------------------------------
    // Wrapper DmpVOption
struct DmpVOptionWrapper : public DmpVOption, boost::python::wrapper<DmpVOption>{
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

  // DmpVIO, only derived classes will use them
  class_<DmpVIO,boost::noncopyable>("DmpVIO",no_init)
    .def("SetOutDataPath",  &DmpVIO::SetOutDataPath)
    .def("AppendDataNote",  &DmpVIO::AppendDataNote)
    .def("GetOutDataPath",  &DmpVIO::GetOutDataPath)
    .def("GetOutDataName",  &DmpVIO::GetOutDataName)
  ;

  // DmpVOption
  class_<DmpVOptionWrapper,boost::noncopyable>("DmpVOption",no_init)
    .def("Set", pure_virtual(&DmpVOption::Set))
  ;

  // DmpAlgorithmManager
  class_<DmpAlgorithmManager,boost::noncopyable>("DmpAlgorithmManager",no_init)
    .def("GetInstance", &DmpAlgorithmManager::GetInstance,return_value_policy<reference_existing_object>())
    .staticmethod("GetInstance")
    .def("Append",  &DmpAlgorithmManager::Append)
    .def("Replace", &DmpAlgorithmManager::Replace)
    .def("ListAllElements",&DmpAlgorithmManager::ListAllElements)
    .def("Initialize",&DmpAlgorithmManager::Initialize)
    .def("Finalize",&DmpAlgorithmManager::Finalize)
  ;
}


