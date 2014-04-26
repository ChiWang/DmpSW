#!  /bin/bash
:<<EOF
 *  $Id: thisdmpsw.sh, 2014-04-26 22:24:59 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 01/10/2013
 *---------------------------------------------------------------------
 *  source me(anywhere is Okay) to setup envirenment of DAMPE software
 *---------------------------------------------------------------------
EOF

#+  Set installation environment of DAMPE offline software 

if [ ! $DMPSWSYS ];then
  if [[ $0 == *bash ]];then
    export DMPSWSYS=$(cd `dirname $BASH_SOURCE`/..;pwd)
  else
    export DMPSWSYS=$(cd `dirname $0`/..;pwd)
  fi
  export DMPSWWORK=$HOME/dmpwork
  export PATH=$DMPSWSYS/bin:$PATH
  if [ $LD_LIBRARY_PATH ];then
    export LD_LIBRARY_PATH=$DMPSWSYS/lib:$DMPSWWORK/lib:$LD_LIBRARY_PATH
  elif [ $DYLD_LIBRARY_PATH ];then        # Mac OS
    export DYLD_LIBRARY_PATH=$DMPSWSYS/lib:$DMPSWWORK/lib:$DYLD_LIBRARY_PATH
  fi
fi

