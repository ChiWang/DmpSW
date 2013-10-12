#!  /bin/bash
#=============================================================================
#       FileName :          thisdmpsw.sh
#       Version  :          0.0.1
#       Author   :          Chi Wang    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-10-01   10:53:23

#------------------------------------------------------------------------------
#       Description  :
#           *   after installation, source this file in .zshrc(.bashrc), then you can use DampeSoftware
#
#       **  NOTE  **
#           *   this file must in /prefix/bin
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-10-01   18:56:05
#=============================================================================


#+  Set DAMPE software environment
if [ ! $DMPSWSYS ];then
    PWD=`pwd`
    export DMPSWSYS=${PWD%"/bin"}
    unset $PWD
    export DMPSWDB=$DMPSWSYS/database
    export PATH=$DMPSWSYS/bin:$PATH
    export LD_LIBRARY_PATH=$DMPSWSYS/lib:$LD_LIBRARY_PATH
fi

