
DmpSW
=====

DAMPE Software


##  Installation

    At current directory, execute installation command "scons options" 

    default prefix=/usr/local, you can point it by:

        scons prefix=/where/to/install

    defaultly, database(store all kinds of datas) will create in /prefix,
    but you can split database from software, this way is more conveniente for managing data.
    Using the option below in installation command:

        database=/where/is/database

    Note:   the path of database must be a absolute path


##  Development guid

### Software structure of development

*   each module is a top-1 directory. Some modules (like RawDataConversion) depend on other modules, more details in their Readme.md
*   some top-1 directories (like Calibration) has top-2 direcotry if necessary.

### Structure of installation (after installation) 

These directories (or link) below will be created in "/prefix/DmpSW_Version"

  *   bin
  *   lib
  *   include
  *   share
  *   database

1.  bin (executable files)

  thisdmpsw.sh        // shell environment
  dmpsw-config        // compilation options
  dmpSim              // Simulation of DAMPE
  dmpRecL0            // Reconstruction Level-0:  Raw Data Conversion
  dmpCalL0Ped         // Calibration Level-0: find pedestal
  dmpRecL1            // Reconstruction Level-1:  cal. data without pedestal
  dmpCalL0SBgoMip     // Calibration Level-0-Special-Bgo: find Mip
  dmpCalL0SBgoRel     // Calibration Level-0-Special-Bgo: find Relation
  dmpCalL0SPsdX       // Calibration Level-0-Special-Psd: XXXXX
  dmpCalL0SStkX       // Calibration Level-0-Special-Stk: XXXXX
  dmpCalL0SNudX       // Calibration Level-0-Special-Nud: XXXXX
  dmpCalL1            // Calibration Level-0: find XXXXX
  dmpRecL2            // Reconstruction Level-2:  ..... waiting to add

2.  lib (shared libraries)

  libdmpAnalysis.so
  libdmpEvent.so

3.  include (needed header files while using libraries)

4.  share (common files)

  geometry                      // a directory store all GDML files
  connector                     // FEE <--> Detector connection files
  example/DmpRecL0Input.infor   // example of the input file for bantch mode of dmpRecL0
  example/analysis              // analysis example. How to use distribuition data to analysis

5.  database (a directory or a soft link. Refer to Installation option)

  there are directories:
    raw
    calibration
    reconstruction
    distribution
    simulation      // is the same as reconstruction/rawDatName-rec0.root

    5.1   raw
      real raw data, output from detector
      ??  name format

    5.2   calibration
      rawDataName-cal0-psd.dat
            // CMD:   dmpCalL0;   Input:  rawDataName-rec0.root
      rawDataName-cal0-stk.dat
            // CMD:   dmpCalL0;   Input:  rawDataName-rec0.root
      rawDataName-cal0-bgo.dat
            // CMD:   dmpCalL0;   Input:  rawDataName-rec0.root
      rawDataName-cal0-nud.dat
            // CMD:   dmpCalL0;   Input:  rawDataName-rec0.root
      rawDataName1-cal0s-bgo-mip_rawDataName2-cal0.dat
            // CMD:   dmpCalL0SBgoMip;  Input:  rawDataName1-rec1_rawDataName2-cal0.root
      rawDataName1-cal0s-bgo-rel_rawDataName2-cal0.dat
            // CMD:   dmpCalL0SBgoRel;  Input:  rawDataName1-rec1_rawDataName2-cal0.root

    5.3   reconstruction
      rawDataName-rec0.root
            // CMD: dmpRecL0(dmpRdc);   Input:  rawDataName.dat
      rawDataName1-rec1_rawDataName2-cal0-{all}.root
            // CMD: dmpRecL1;   Input:  rawDataName-rec1.root, rawDataName2-cal0-{all}.dat

    5.4   distribution
            ???

### How to debug? (Refer to Readme.md in each directory)

1.  cp *.scons SConstruct
2.  scons debug=1
3.  scons -c

    ## but there are some problems yet, like pathes(in code) for debug and for release are different 
    ?? using "/PREFIX/SubDirectoryName"

### Convention
1.  use detector names below ANY WHERE (except: data files are all lower case)
    *   Psd
    *   Stk
    *   Bgo
    *   Nud
    *   Header      // Event Header
    *   Dmg         // Data Management
    *   Stl         // Satellite

2.  Abbreviation of Top-1 Module   (ATM)
    *   Calibration:        Cal
    *   Reconstruction:     Rec
    *   RawDataConversion:  Rdc
    *   Simulatin:          Sim
    *   Visulization:       Vis
    *   Event:              Evt
    *   Analysis:           Ana
    *   Generation:         Gen
    *   DetectorCondition:  Dcd
    *   Geometry:           Gem

3.  class (DmpATM{SpecialKey}Dominant{sub-detector})
    * Dmp

        Prefix of class
    * ATM

        Abbreviation of Top-1 Module as mentioned above
    * {SpecialKey}

        normal class:   no SpecialKey
        vertial class:  V
    * Dominant

        explain the usefulness. Example:    DmpRdcManager
    * {sub-detector}
        if for whole detector:  no
        else:       Psd, Stk, Bgo, Nud, Header

4.  file name

    4.1  for code
    * header file: .hh      // in a directory "include", even only one header file
    * source file: .cc      // in a directory "src", include main function

    4.2  input files of command batch mode
        name as the command with the suffix "Input.infor" and change the first "D" as uppercase letter
        DmpRecL0Input.infor         // execute "dmpRecL0" will use DmpRecL0Input.infor defaultly
        DmpRecL0Input_XXXX.infor    // execute "dmpRecL0 DmpRecL0Input_XXX.infor"
    
    4.3  FileName.scons is a compilation file which will be used by build tool "SCons".
        Two kinds layout:
        *   a CMD for certain sub-detector
            FileName.scons in /path/CMDNamedDir/
        *   a CMD for whole detector
            FileName.scons at the same directory as /path/CMDNamedDir/

    4.4  Readme.md
        Except directores include, Scons, src, there is a file named Reade.md(or README.md) in all directories to explain:
        *   Structure
        *   Usage
        *   Relation of other modules
        *   Debug method
        *   Bug report
        *   Others
    4.5  Name.cnct
        dectector <-> FEE, connection information

5.  command (dmpATM{Level}{Detector})

    * dmp
        Prefix of command
    * ATM
        Abbreviation of Top-1 Module as mentioned above
    * {Level}
        only one command in a module:   no Level
        level from 0 to N
    * {Detector}
        for whole detector:     no Detector
        for sub-detector:       Psd, Stk, Bgo, Nud

6.  command named source files (CMDNamed.cc, all uppercase letter of first "D")

        The main function for create a command in /path/src/CMDNamed.cc


