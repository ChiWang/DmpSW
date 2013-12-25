#=====================================================================
#   File:   SConstruct
#   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    01/10/2013
#---------------------------------------------------------------------
#   Description:

#---------------------------------------------------------------------
#   History:
#                           Last update:  25/12/2013   15:31:35
#=====================================================================

# release version
ReleaseVersion='DmpSW_v1.0.0'

import os

# set installation path, and derive PREFIX into sub-level environment
PREFIX=ARGUMENTS.get('prefix',os.path.abspath('.'))
#PREFIX=ARGUMENTS.get('prefix','/usr/local')
PREFIX=PREFIX+'/'+ReleaseVersion
Export('PREFIX')

# creat common installation directories if not exist
for key in ['bin','lib','include','share']:
    sub_dir=PREFIX+'/'+key
    if not (os.path.exists(sub_dir)):
        os.makedirs(sub_dir)

# copy some excutable files into /prefix/bin
#import shutil
for key in ['dmpsw-config','thisdmpsw.sh','thisdmpsw.csh']:
    Default(Command(PREFIX+'/bin/'+key,key,Copy("$TARGET","$SOURCE")))

# invoke top1 modules' SConscript
subScript=[]
for key in ['Analysis','Calibration','Event','Generation','Geometry','Kernel','RawDataConversion','Reconstruction','Simulation','Visualization']:
    subScript=subScript+[key+'/'+key+'.scons']
SConscript(subScript,exports='PREFIX')



