
##  How to run

    1.  install DMPSW firstly (refer to: ../README.md/How to install DMPSW)
    2.  copy $DMPSWSYS/TestRelease/JobOpt_DmpSimulation to anywhere and execute it.

##  To Do List

    1.  gdml for kBT2012
    2.  use DmpPhase to choose run
    1.  binding more functions into python, like phase


##  Simulation  package of Dampe software

    *Goal
        create one shared library.

    *Usage
        use python script to control simulation, see example in ./share/JobOpt_DmpSimulation

    *Output (root file of whole detector, which has the same structure as the output file of Rdc)


##  Note

    1.  if we have set Sensitive Detector, we don't need to write user Stepping Action class.
    2.  delete class SimSubDetHit : public G4VHit, since we have wrotten EvtHit class in Event package, we used EvtHit collection in Sensitive Detector class
    3.  delete class SimSubDetDigi : public G4VDigi, since we have wrotten EvtHit class, and there is a data member could save digits information in this EvtHit class.
    4.  delete concrete digitization class (drive from G4VDigitizerModule). Do digitize in SimDataManager::Digitize(), and this function will invoked from UserEventAction::EndofEventAction()


