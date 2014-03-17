
// *
// *  TODO: Kernel
//
//      >>  add DmpVAlg, DmpAlgManager as a singleton
//      16/03/2014 >>  bingding some functions of DmpVDataManger, and then the derived class(Simulation and Rdc) could use it directly
//      16/03/2014 >>  add DmpVSvc, DmpSvcManager as a singleton.
//      12/03/2014 >>  delete DmpCore::EPhase, add DmpDetector::SubDet*::DmpESubDet*Phase, and create a global variable to store phase, bind Get(Set)SubDet*Phase(), too
//      12/03/2014 >>>     ERROR: can bind the function DmpDetector::Bgo::SetPhase()?? Why(missing variable type...)
//      11/03/2014 >>>  delete fInDataPath in DmpVDataManager 
//      11/03/2014 >>>  SetOutDataName(std::string), createOutDataName(std::string), merge them
//      11/03/2014 >>>  add TimpStamp() for default output data name
// *


// *
// *  TODO: Event
//
//      1.  save vector(fRunMode) wrong, fix it
//      2.  add digitization into EventAction.cc
//      3.  add PrintTime() in order to check time in Rdc
// *

// *
// *  TODO: Geometry
//
//      (X) 1.  Scons file
//      (X) 2.  schema files
//      3.  all phase gdml file
// *

// *
// *  TODO: Simulation
//
//      16/03/2014 >>  expose SimDataMgr to python instead of exposing set method 
//      17/03/2014 >>  fParser->Read(subDet*.gdml) respectively??
//      12/03/2014 >>  delete static data member to create singleton, only use static function and a static object in stack in this function
//      12/03/2014 >>  ?? Simulation/DmpSim/src/DmpEntranceSimulation.cc:37: error: ‘DmpEDetectorID’ is not a class or namespace (missing namespace)
//      (X) 1.  check run script
//      (X) 2.  add phase monitor, and then read gdml files automaticaly
// *


// *
// *  TODO: Rdc
//
//      0.  split RdcManager to RdcManager and RdcAlgorithm
//      0.1 implement Rdc algorithm in sebDet
//      0.2 how to choose different algorithm in run time python script ??!!
//      1.  JobOpt file
//      2.  Bgo part Conversion
//      3.  ConvertEventHeader()
//      4.  does it necessary to SetConnector Path in python ?? (no)
// *


