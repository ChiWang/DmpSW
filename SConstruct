#=====================================================================
#   File:   SConstruct
#   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    01/10/2013
#---------------------------------------------------------------------
#   Description:
#       prefix/bin
#       prefix/include
#       prefix/lib
#       prefix/share
#
#---------------------------------------------------------------------
#   History:
#                           Last update:  25/12/2013   15:31:35
#=====================================================================

import os

##  check requirements
if not os.environ.has_key('ROOTSYS'):
    print 'root is not set up.'
    Exit(1)
if not os.environ.has_key('G4INSTALL'):
    print 'geant4 is not set up.'
    Exit(1)
if not os.environ.has_key('G4LIB_USE_GDML'):
    print 'GDML is not set up.'
    Exit(1)

# set installation path, and derive prefix into sub-level environment
prefix=raw_input('Where to install DMPOS [default is "/usr/local"]: ')
if prefix=="":
    prefix='/usr/local'
prefix=os.path.abspath(prefix)
Export('prefix')

# copy some excutable files into /prefix/bin
for key in ['dmpsw-config','thisdmpsw.sh','thisdmpsw.csh']:
    Default(Command(prefix+'/bin/'+key,key,Copy("$TARGET","$SOURCE")))

# invoke top1 modules' SConscript
subScript=[]
for key in ['Kernel','Event','RawDataConversion','Analysis']:
#for key in ['Analysis','Calibration','Event','Generation','Geometry','Kernel','RawDataConversion','Reconstruction','Simulation','Visualization']:
    subScript=subScript+[key+'/'+key+'.scons']
SConscript(subScript,exports='prefix')


