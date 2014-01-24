
#   RawDataConversion of DAMPE software

    *Goal
        create one command "dmpRdc", and then install this command

    *Usage
        mode 1. single data mode
            "dmpRdc    /Path/RawDataName.dat"
            Read RawDataName.dat from /Path, and
            save results at ./(where you execute command dmpRdc)
        mode 2. batch mode
            2.1 read "DmpRdcInput.infor" at ./ defaultly
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

    1.  cd into trunk, where has the SConstruct file
    2.  execute "scons package=RawDataConversion" to create command "dmpRdc"

        Note:   be sure that compiled Kernel and Event packages already, if not, do:
        "scons package=Kernel,Event,RawDataConversion"

