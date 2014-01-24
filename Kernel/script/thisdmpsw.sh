#!  /bin/bash
#=====================================================================
#   File:   thisdmpsw.sh
#   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    01/10/2013
#---------------------------------------------------------------------
#   Description:
#       source thie file:
#       1)  cd /prefix
#       2)  source ./bin/thisdmpsw.(c)sh
#
#---------------------------------------------------------------------
#   History:
#                           Last update:  26/12/2013   01:39:05
#=====================================================================

#+  Set installation environment of DAMPE offline software 

if [ ! $DMPSWSYS ];then
  export DMPSWSYS=`pwd`
  export PATH=$DMPSWSYS/bin:$PATH
  if [ $LD_LIBRARY_PATH ];then
    export LD_LIBRARY_PATH=$DMPSWSYS/lib:$LD_LIBRARY_PATH
  elif [ $DYLD_LIBRARY_PATH ];then        # Mac OS
    export DYLD_LIBRARY_PATH=$DMPSWSYS/lib:$DYLD_LIBRARY_PATH
  fi
fi

