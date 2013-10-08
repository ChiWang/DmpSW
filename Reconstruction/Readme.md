
#   Reconstruction  Module of Dampe software


##  Structure

    *   RecL1_NoPedestal

    create one commond "dmpRecL1" for whole detector get data without pedestal

    *   Bgo_Special (Psd_Special, Stk_Special, Nud_Special)

    Special calibrations of sbu-detector Bgo. 4 directories for 4 sub-detectors(Psd, Stk, Bgo, Nud).

        *   Energy

    *   CalL1_Goal-1

    create one commond "dmpRecL2" for whole detector for Goal-1



##  Development

    1.  cd into the directory where could create a single commond       // like dmpRecL1, cd RecL1_NoPedestal
    2.  cp *.scons SConstruct   // *.scons is invoked for whole software install, with default option debug=0
    3.  scons debug=1           // create commond dmpCalL0SBgoMip at local directory for tunning
    4.  scons -c                // clean up


