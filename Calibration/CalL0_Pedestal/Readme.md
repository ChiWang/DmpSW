
##   Calibration Level-0: Pedestal

    *Goal
        create a commond "dmpCalL0"

    *Object
        whole detector

    *Usage
        1. dmpCalL0                                 // read DmpCalL0Input.infor at where execute the command
        2. dmpCalL0 /path/DmpCalL0Input_XXXX.infor  // read pointed DmpCalL0Input_XXX.infor

    *Input
        rawDataName-rec0.root, which is the output of dmpRDC(dmpRecL0)

    *Output (results of pedestals of 4 sub-detectors)
        rawDataName-cal0-psd.dat
        rawDataName-cal0-stk.dat
        rawDataName-cal0-bgo.dat
        rawDataName-cal0-nud.dat

##  Structure

###     dmpCalL0


###     psd

###     stk


###     bgo


###     nud


