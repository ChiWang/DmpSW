
##  To Do List

    1.  ./Stk. All named DmpSimXXX.hh
    2.  Simulcation.scons


#   Simulation  Module of Dampe software

    *Goal
        create one commond "dmpSim"

    *Object
        whole detector

    *Usage
        1. dmpSim                               // read DmpSimInput.infor at where execute the command
        2. dmpSim /path/DmpSimInput_XXXX.infor  // read pointed DmpSimInput_XXX.infor

    *Input
        *   DmpSimInput.infor                   // output of dmpGenertor
        *   /trunk/Geometry/*gdml               // GDML files

    *Output (root file of whole detector, with 5 treees. same as reconstruction/rawDataName-rec0.root)
        *   rawDataName-rec0-sim.root

##  Structure

    *   DmpSim

    *   Header

    *   Psd

    *   Stk

    *   Bgo

    *   Nud

    *   share       // example of DmpSimInput.infor

##  Development

    1.  cp *.scons SConstruct   // *.scons is invoked for whole software install, with default option debug=0
    2.  scons debug=1           // create commond at local directory for tunning
    3.  scons -c                // clean up


