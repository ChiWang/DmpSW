
##  To Do List

    1.  modify names as our name conention (http://dpnc.unige.ch/dampe/dokuwiki/doku.php?id=dampesoftware:namingconvention)
    2.  split event classes into Event module


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

    1.  cd into trunk, where has the SConstruct file
    2.  execute "scons package=Simulation" to create command "dmpRdc"

        Note:   be sure that compiled Kernel and Event packages already, if not, do:
        "scons package=Kernel,Event,Simulation"

