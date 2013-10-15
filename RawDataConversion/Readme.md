
#   Raw Data Conversion  Module of Dampe software

    *Goal
        create one commond "dmpRdc" (Or, dmpRecL0)

    *Object
        whole detector

    *Usage
        1. dmpRecL0                                 // read DmpRdcInput.infor at where execute the command
        2. dmpRecL0 /path/DmpRdcInput_XXXX.infor    // read pointed DmpRdcInput_XXX.infor

    *Input
        *   rawDataName.dat, which is detector output
        *   connector       // defaut reading path: /prefix/share/connection for release

    *Output (root file of whole detector, with 5 treees)
        rawDataName-rec0.root

##  Structure

    *   DmpRdc

    *   Header

    *   Psd

    *   Stk

    *   Bgo

    *   Nud

    *   share       // example of dmpRec0Input.infor

##  Development

    1.  cp *.scons SConstruct   // *.scons is invoked for whole software install, with default option debug=0
    2.  scons debug=1           // create commond at local directory for tunning
    3.  scons -c                // clean up


##  Note:
        1)  first of all, confirm that datalongth of each sub-detector.
                will be used by constructor in Conversion/src/DmpRDCManager.cc
        2)  only override Conversion function the sub-detector you are developing.
                you can comment the Conversion function of the rest sub-detector for convenient


