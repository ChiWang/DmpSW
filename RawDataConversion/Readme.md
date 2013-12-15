
#   RawDataConversion of DAMPE software

    *Goal
        create one commond "dmpRdc", and then install this command

    *Usage
        mode 1. single data mode
            "dmpRdc    /Path/RawDatName.dat"
            Read dataName.dat from /Path, and save results at ./(where you execute command dmpRdc)
        mode 2. batch mode
            2.1 default read "DmpRdcInput.infor" at ./(where you excute dmpRdc) if without argument
            "dmpRdc"
            2.2 read pointed "*RdcInput.infor"
            "dmpRdc /Path/*RdcInput.infor"
    *Input
        *   RawDataName.dat or *RdcInput.infor
        *   Connector files

    *Output
        RawDataName-raw.root

##  Structure

    *DmpRdc     // main function and manager class

    *Psd        // implement key functions of Psd

    *Stk

    *Bgo

    *Nud

    *share       // example of DmpRdcInput.infor. all "Connector" files. test input data

##  Development

    1. cd DmpRdc then generate the dictionary of DampRdc
        execute "./createDictionaty.sh"
    2. create command "dmpRdc"
        execute "scons" at where is SConstruct

