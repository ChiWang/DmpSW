
#   Calibration  Module of Dampe software


##  Structure

    *   CalL0_Pedestal

    create one commond "dmpCalL0" for whole detector to find pedestal

    *   Bgo_Special (Psd_Special, Stk_Special, Nud_Special)

    Special calibrations of sbu-detector Bgo. 4 directories for 4 sub-detectors(Psd, Stk, Bgo, Nud).

        *   Mip
        create one commond "dmpCalL0SBgoMip" for Bgo to find Mip

        *   Relation
        create one commond "dmpCalL0SBgoRel" for Bgo to find Relation

    *   CalL1_Goal-1

    create one commond "dmpCalL1" for whole detector for Goal-1

    *   CalL2_Goal-2

    create one commond "dmpCalL2" for whole detector for Goal-2


##  Development

    1.  cd into the directory where could create a single commond       // like dmpCalL0SBgoMip, cd Bgo_Special/Mip
    2.  cp *.scons SConstruct   // *.scons is invoked for whole software install, with default option debug=0
    3.  scons debug=1           // create commond dmpCalL0SBgoMip at local directory for tunning
    4.  scons -c                // clean up


