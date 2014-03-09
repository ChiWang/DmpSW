
#   Simulation  package of Dampe software

##  What are in here:

    1.  Simulation code for whole DAMPE

    2.  test macro file for simulation

    3.  example of run script: JobOpt_DmpSimulation


##  Usage:

    1.  install DMPSW firstly (refer to: ../README.md/{How to install DMPSW})

    2.  cd to TestRelease, and run JobOpt_DmpSimulation (or, copy job option to anywhere and execute at there)

    3.  *Output (root file of whole detector, which has the same structure as the output file of Rdc)


##  Note

    1.  if we have set Sensitive Detector, we don't need to write user Stepping Action class.

    2.  delete class SimSubDetHit : public G4VHit, since we have wrotten EvtHit class in Event package, we used EvtHit collection in Sensitive Detector class

    3.  delete class SimSubDetDigi : public G4VDigi, since we have wrotten EvtHit class, and there is a data member could save digits information in this EvtHit class.

    4.  delete concrete digitization class (drive from G4VDigitizerModule). Do digitize in SimDataManager::Digitize(), and this function will invoked from UserEventAction::EndofEventAction()


