
DmpSW
=====

DAMPE Software


##  Requirement

DMPSW will uses tools Root, Geant4 and SCons.

Install ROOT

        1) download root_v5.34.09.source.tar.gz from http://root.cern.ch/drupal/content/production-version-534
        
        2) unpack root_v5.34.09.source.tar.gz, for exmaple in directory <myRootPath>, using
            dgzip -dc root_v5.34.09.source.tar.gz | tar -xf -
        
        3) cd <myRootPath>/root
        
        4) ./configure <arch>        [change arch appropriately]
        
        5) make                   [or, make -j n for n core machines]

Install Geant4

        1) download geant4.9.6.p02.tar from http://geant4.web.cern.ch/geant4/support/download.shtml, using the button marked "GNU or Linux tar format, compre
        ssed using gzip (24.3Mb, 25480383 bytes)"
        
        2) unpack geant4.9.6.p02.tar, for example in directory <myG4Path>.
        
        3) mkdir geant4.9.6-build
        
        4) cd geant4.9.6-build
        
        5) cmake -DCMAKE_INSTALL_PREFIX=<myG4Path>/geant4.9.6-install -DGEANT4_INSTALL_DATA=ON -DGEANT4_USE_OPENGL_X11=ON -DGEANT4_INSTALL_EXAMPLES=ON <myG4Path>
        /geant4.9.6.p02
        
        6) make -j2 (for duo-core machine)
        
        7) make install
        
        Note: because of the datafile it takes up to an hour to config and install.
        Note: install GDML at the same time

Install SCons

        1) download scons-2.3.0.tar.gz from http://www.scons.org/download.php
        
        2) unpack scons-2.3.0.tar.gz, using following command
            tar -zxvf scons-2.32.tar.gz
        
        3) cd ./scons-2.32 , install scon as README.txt said
            python setup.py install     (root user)
        
        4) type command:
            scons --help

## How to install DMPSW

    ---------------------------------------------------------------------------------------------------------------------
    *****   Not used before publish DMPSW out of DAMPE group. Please skip to the next section "Development guide"   *****
    ---------------------------------------------------------------------------------------------------------------------

Installation:

    At current directory, execute installation command 

        scons options
            option 1:   prefix
            option 2:   database

    default prefix=/usr/local, you can point it by:

        scons prefix=/where/to/install

    defaultly, database(store all kinds of datas) will create in /prefix,
    but you can split database from software, this way is more conveniente for managing data.
    Using the option below in installation command:

        database=/where/is/database

    Note:   the path of database must be a absolute path

Set Environment

    source /prefix/bin/thisdmpsw.sh

##  Development guide

    It could be helpful if you understand the naming convention firstly at:
        http://dpnc.unige.ch/dampe/dokuwiki/doku.php?id=dampesoftware:namingconvention

    There are 6 key steps while developing DMPSW.

    0)  checkout(or update) whole trunk
            svn checkout http://dpnc.unige.ch/SVNDAMPE/DAMPE/DmpSoftware/trunk  --username=tutorial

    1)  source thisdmpsw.sh
            if "echo $DMPSWWORK" is blank, then do as follow:
            source thisdmpsw.sh         // this file in the dowloaded directory trunk
            then, "echo $DMPSWWORK" is not blank 
            // or, you can add the line above into $HOME/.bashrc(or .zshrc) instead of source it every time.

    2)  work on certian package
            cd into the package (or sub-directory you are working)
            commit work JUST IN THE WORKING DIRECTORY.

    3)  development circle
            compile --> running --> debug --> compile...
            * compile:   "scons"
                execute "scons" at where the SConstruct file at.( use the closest one SConstruct. Or, refer to Readme.md in the package)
            * running the command just created
                just type the command name
            * clean up: "scons -c"

    4)  commit work
            svn commit
            then, add the commit note at the head of the opened file.
            if work fine, then, svn update

    5)  use other package of DMPSW
            if the package you are developing need a new dependence of other package.

    In cause you get any error, please send a group email.

    Next is about structure of DMPSW, if you to know more clearly of DMPSW setup, please read below.


### Structure of installation (after installation) 

    -------------------------------------------------------------------------------------------------
    *****   Not used before publish DMPSW out of DAMPE group. Please skip to the next section   *****
    -------------------------------------------------------------------------------------------------

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
        dmpCalL0            // Calibration Level-0: find pedestal
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

  There are directories:
    *       raw
    *       calibration
    *       reconstruction
    *       distribution
    *       simulation

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

    5.5     simulation

        rawDataName-rec0-sim.root
              // CMD: dmpSim;   Input:  dmpGenertor-XXX???XXX.dat
              // the same as reconstruction/rawDatName-rec0.root

### Convention

1.  use detector names below ANY WHERE (except: data files are all lower case)

        Psd
        Stk
        Bgo
        Nud
        Header      // Event Header
        Dmg         // Data Management
        Stl         // Satellite

2.  Abbreviation of Package   (AP)

        Calibration:        Cal
        Reconstruction:     Rec
        RawDataConversion:  Rdc
        Simulatin:          Sim
        Visulization:       Vis
        Event:              Evt
        Analysis:           Ana
        Generation:         Gen
        DetectorCondition:  Dcd
        Geometry:           Gem

3.  class ( format: Dmp{AP}{SpecialKey}{Dominant}{sub-detector}. example: DmpRdcManager)

        * Dmp
            Prefix of any class
        * {AP}
            Abbreviation of Package as mentioned above
        * {SpecialKey}
            normal class:   no SpecialKey;
            vertial class:  V
            template class: T
        * {Dominant}
            explain the usefulness. Example:    DmpRdcManager
        * {sub-detector}
            whole detector: no;
            sub-detector:   Psd, Stk, Bgo, Nud, Header

4.  command ( format: dmp{AP}{Level}{Detector}. example: dmpSim)

        * dmp
            Prefix of command
        * {AP}
            Abbreviation of Package
        * {Level}
            only one command in a package:   no Level
            level from 0 to N
        * {Detector}
            for whole detector:     no Detector
            for sub-detector:       Psd, Stk, Bgo, Nud
        Note:   if a package create a shared library, name as libDmpXXXX.so

5.  file name

    5.1  Readme.md

        Except directores include and src, there is a file named Reade.md(or README.md) in all directories to explain:
        *   Goal
        *   Structure
        *   Usage
        *   Dependency
        *   Input and output
        *   Bug report
        *   Others

    5.2  coding file

        *.hh    header file, all must in directory "include"
        *.cc    source file, all must in directory "src"
            The main function for create a command in /path/src/CMDNamed.cc

    5.3  FileName.scons

        compilation files which will be used by build tool "SCons".

        Two kinds layout:
        * a CMD for certain sub-detector
            will not invoke other sub-detectors
        * a CMD for whole detector
            will invoke all sub-detectors

    5.4  interface of command of input files(batch mode)

            dmpRdc  DmpRecL0Input_XXX.infor
            *   prefix:     DmpeRecL0       // CMD name
            *   suffix:     .infor          // all use this
            *   middle:     Input_XXX       // note
    
    5.5  FileName.cnct

        dectector <-> FEE, connection information.

### Others

1.  All personal test must in "test" directory, you can create "test" directory at wherever you need. Then other people will not waste their time on checking test.

2.  We set macro definition of "Dmp_DEBUG" and "Dmp_RELEASE" in g++ while you using we setted SCons files, it will makes your code more flexible, for example:

    #ifdef Dmp_DEBUG
      cout<<"some thing you want to check"<<endl;
      // or some thing you need for debug.
    #endif
    #ifdef Dmp_RELEASE
      cout<<"This is release mode. I'm (this line) is useless"<<endl;
      // or some thing for release.
    #endif


