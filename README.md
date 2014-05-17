DMPSW
=====
> *
> *  TODO: Update readme.   (marked by TODO)
> *

##  Requirement

DMPSW will uses tools Root, Geant4 Boost and SCons. You must install them firstly by following the guide below if you do not have them.

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
        
        5) cmake -DCMAKE_INSTALL_PREFIX=<myG4Path>/geant4.9.6-install -DGEANT4_INSTALL_DATA=ON -DGEANT4_USE_GDML=ON -DGEANT4_USE_OPENGL_X11=ON -DGEANT4_INSTALL_EXAMPLES=ON <myG4Path>
        /geant4.9.6.p02
        
        6) make -j2 (for duo-core machine)
        
        7) make install
        
        Note: because of the datafile it takes up to an hour to config and install.

Install Boost

        1) yum install python-devel

        2) download boost-*.tar.gz from http://www.boost.org/users/download/#live

        3) install it

            3.1) ./bootstrap.sh
            3.2) ./b2 install --prefix=/usr --libdir=/usr/lib(or_lib64) --includefir=/usr/include --build-type=minimal variant=release

Install SCons

        1) download scons-2.3.0.tar.gz from http://www.scons.org/download.php
        
        2) unpack scons-2.3.0.tar.gz, using following command
            tar -zxvf scons-2.32.tar.gz
        
        3) cd ./scons-2.32 , install scon as README.txt said
            python setup.py install     (root user)
        
        4) type command:
            scons --help

##  How to install DMPSW

    Suppose you (or your administrator) did not install DMPSW, which means "echo $DMPSWSYS" is blank.
    If, already has "$DMPSWSYS", skip to the next section "re-install DMPSW"

Installation

    1.  create dictionary, do:
        ./pre-install.(c)sh

    2.  install whole DMPSW, do:
        scons
        Then, DMPSW will ask you where to install it, the default prefix=./Install

Set Environment

    1.  source /prefix/bin/thisdmpsw.(c)sh (at anywhere is ok)

##  re-install DMPSW

    If you update some codes(modified locally, or update from git(or svn) server)
        just execute "scons" at top directory

    If you want to re-install some certain packges
        execute "scons package=package_name_1,name_2,name_3" at top directory

##  Development guide (TODO)

    Fisrt of all, you should install it as last section (How to install DMPSW) stated.

    It could be helpful if you understand the naming convention in:
        http://dpnc.unige.ch/dampe/dokuwiki/doku.php?id=dampesoftware:namingconvention

    There are 6 key steps while developing DMPSW.

    0)  cd into certain package and update it

    1)  SConstruct(UNDER CERTAIN PACKAGE) file existing?
        if there is not a file named SConstruct, do:    "cp *.scons SConstruct"

    2)  development circle
            compile --> runn to debug --> compile...
            * compile:   "scons"
            * execute the command just created
            * clean up: "scons -c"

    3)  commit work
            svn commit
            then, add the commit note at the head of the opened file.

    NOTE:   If the package you are developing need a new dependence of other package, please send a group email.


## Structure after installation

These directories (or link) below are in "/prefix"
*   bin
*   lib
*   include
*   share
*   log ??

1.  bin (executable files)

        thisdmpsw.(c)sh     // shell environment
        dmpsw-config        // compilation options
        >dmpSim              // Simulation of DAMPE
        >dmpRdc              // Reconstruction Level-0:  Raw Data Conversion
        >dmpPed              // Calibration Level-0: find pedestal
        >dmpRecL1            // Reconstruction Level-1:  cal. data without pedestal
        >dmpBgoMip           // Calibration Level-0-Special-Bgo: find Mip
        >dmpBgoRel           // Calibration Level-0-Special-Bgo: find Relation
        >dmpCalL0SPsdX       // Calibration Level-0-Special-Psd: XXXXX
        >dmpCalL0SStkX       // Calibration Level-0-Special-Stk: XXXXX
        >dmpCalL0SNudX       // Calibration Level-0-Special-Nud: XXXXX
        >dmpCalL1            // Calibration Level-0: find XXXXX
        >dmpRecL2            // Reconstruction Level-2:  ..... waiting to add

2.  lib (shared libraries)

        libDmpCore.so
        libDmpEvent.so
        libDmpSim.so
        libDmpRdc.so
        libDmpAnalysis.so

3.  include (needed header files while using libraries)

4.  share (common files)

        Geometry            // all GDML files
        Connector           // FEE <--> Detector connection files
        Simulation          // macro files for default visual mode
        TestRelease         // all JobOpt_* files

5.  log ( records of error information and request infor.)

        *   dmpPed_request.log
                request_time    dmpPed_version  hexDataName_raw.root
        *   bgo_ped_error-requestTime-verison-hexDataName.log    warning information

## Convention

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
        Geometry:           Gem

3.  class (format: Dmp{AP}{SpecialKey}{Dominant}{sub-detector}. example: DmpRdcManager)

        * Dmp
            Prefix of any class
        * {AP}
            Abbreviation of Package as mentioned above
        * {SpecialKey}
            normal class:   no SpecialKey;
            vertial class:  V
        * {Dominant}
            explain the usefulness. Example:    DmpRdcManager
        * {sub-detector}
            whole detector: no;
            sub-detector:   Psd, Stk, Bgo, Nud

4.  command ( format: dmp{AP}{Level}{Detector}. example: dmpSim) (TODO)

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

        *.h    header file, all must in directory "include"
        *.cc    source file, all must in directory "src"
            The main function for create a command in /path/src/Dmp{AP}Main.cc

    5.3  FileName.scons

        compilation files which will be used by build tool "SCons".

    5.4  JobOpt_* file

        running time script. For example: JobOpt_DmpSimulation is used to run simulation

    5.5  FileName.cnct

        dectector <-> FEE, connection information.

##  Data names (TODO)

1   raw data(binary file, all DAMPE scientific data)

      Suppose real data name is "hexDataName.dat", simulation data is "sim_hexDataName.dat".
      We can not distinguish them, except the name...

2   raw data(root file, all DAMPE scientifc data)

      hexDataName_raw.root
          // CMD: dmpRdc;   Input:  hexDataName.dat or sim_hexDataName.dat

3   common calibration, pedestal

      psd_pedestal.root

      stk_pedestal.root

      bgo_pedestal.root
          variable:
              version:    dmpPed_version
              data name:  hexDataName_raw.root (Used which data to calibration Pedestal)
              LBSDIDCollection
              meanCollection
              sigmaCollection

      nud_pedestal.root

          // CMD:   dmpPed;   Input:  hexDataName_raw.root
          use one hexDataName_raw.root, subDet_pedestal.root add one entry

      Some other output:
          *   dmpPed_request.log
                  request_time    dmpPed_version  hexDataName_raw.root
          *   bgo_ped_error-request_time-dmpPed_verison-hexDataName_raw.log    warning information

4   no pedestal data

      DAMPE_hexDataName.root
          // CMD:   dmpDataFactory;   Input:  hexDataName_raw.root   and 4 root files in 3.3, but only one entry

          //-----------------------------------------------------------------------------------------------//
          ##  every event has information of dmpPed_version and pedestal from which hexDataName_raw.root   ##
          //-----------------------------------------------------------------------------------------------//

5   special

    5.1   Psd special

    5.2   Stk special

    5.3   Bgo special

      5.3.1 Mips

      bgo_mip.root
          variable:
              version:    dmpBgoMip_version
              data name:  DAMPE_hexDataName.root (Used which data to calibration Mip)
              LBSDIDCollection
              meanCollection
              sigmaCollection
          // CMD:   dmpBgoMip;  Input:  DAMPE_hexDataName.root
              Some other output:
                  *   dmpBgoMip_request.log
                          request_time    dmpBgoMip_version  DAMPE_hexDataName.root
                  *   bgo_mip_error-request_time-dmpBgoMip_verison-DAMPE_hexDataName.log    warning information

      5.3.2 Relation

      bgo_relation.root
          variable:
              version:    dmpBgoRel_version
              data name:  DAMPE_hexDataName.root (Used which data to calibration relation)
              LBSDIDCollection
              meanCollection
              sigmaCollection
          // CMD:   dmpBgoRel;  Input:  DAMPE_hexDataName.root
              Some other output:
                  *   dmpBgoRel_request.log
                          request_time    dmpBgoRel_version  DAMPE_hexDataName.root
                  *   bgo_rel_error-request_time-dmpBgoRel_verison-DAMPE_hexDataName.log    warning information

    5.4   Nud special

6   reconstruction

    6.1   Psd special

    6.2   Stk special

    6.3   Bgo special

        6.3.1 Hit -> energy in bar
          
          //---------------------------------------------------------------------------------------------------//
          ##  every event has information of dmpBgoMip_version and Mip from which DAMPE_hexDataName_raw.root   ##
          ##  every event has information of dmpBgoRel_version and Rel from which DAMPE_hexDataName_raw.root   ##
          //---------------------------------------------------------------------------------------------------//

    6.4   Nud special

## Others

1.  All personal test must in "test" directory, you can create "test" directory at wherever you need. Then other people will not waste their time on checking test.


