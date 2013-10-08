
### DAMPE Reconstruction Level-1 Special For energy deposited in Bgo 

    *Goal
        create a command "dmpRecL1SBgoEng"

    *Object
        sub-detecotr Bgo 

    *Usage
        1. dmpRecL1SBgoEng                          // read DmpRecL1Input.infor at where execute the command
        2. dmpRecL1SBgoEng /path/DmpRecL1SBgoEngInput_XXXX.infor  // read pointed DmpRecL1SEngInput_XXX.infor

    *Input
        rawDataName1-rec1_rawDataName2-cal0.root            // output of dmpRecL1
        rawDataName3-cal0s-bgo-mip_rawDataName4-cal0.dat    // output of dmpCalL0SBgoMip
        rawDataName5-cal0s-bgo-rel_rawDataName6-cal0.dat    // output of dmpCalL0SBgoRel

    *Output (results of pedestals of 4 sub-detectors)
        rawDataName1-rec1S-bgoE_rawDataName2-cal0_rawDataName3-cal0s-bgoM_rawDataName4-cal0_rawDataName5-cal0s-bgoR_rawDataName6-cal0.root


##  Note:
    This
