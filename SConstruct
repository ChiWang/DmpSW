#=============================================================================
#       FileName :          SConstruct
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-01   12:44:32
#
#------------------------------------------------------------------------------
#       Description  :
#   *   set PREFIX, and database
#   *   all the top-1 module *scons will use PREFIX from this file
#
#       Usage   :
#   *   Refer to "Installation in README.md" (Or: https://github.com/ChiWang/DmpSW/blob/master/README.md)
#
#       --------------
#       ###  NOTE  ###
#       --------------
#   *   modify ReleaseVersion before release!
#   *   current directory as default installation path for debug, better set as /usr/local for release version
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-04   11:47:12
#=============================================================================

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

# set database path
DataBase=ARGUMENTS.get('database',PREFIX+'/database')
if (DataBase != PREFIX+'/database'):
    DataBase=DataBase+'/DAMPEDataBase'
    os.makedirs(DataBase)
    os.symlink(DataBase,PREFIX+'/database')        #  create link to PREFIX/database

# creat files in database
for key in ['raw','calibration','reconstruction','distribution','simulation']:
    sub_dir=DataBase+'/'+key
    if not (os.path.exists(sub_dir)):
        os.makedirs(sub_dir)

# copy some excutable files into /prefix/bin
#import shutil
for key in ['dmpsw-config','thisdmpsw.sh']:
    Default(Command(PREFIX+'/bin/'+key,key,Copy("$TARGET","$SOURCE")))

# invoke top1 modules' SConscript
subScript=[]
for key in ['Analysis','Calibration','Event','Generation','Geometry','Kernel','RawDataConversion','Reconstruction','Simulation','Visualization']:
    subScript=subScript+[key+'/'+key+'.scons']
SConscript(subScript,exports='PREFIX')



