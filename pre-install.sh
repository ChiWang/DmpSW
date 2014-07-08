#! /bin/bash
:<<EOF
 *  $Id: pre-install.sh, 2014-06-12 21:42:00 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 26/12/2013
 *---------------------------------------------------
 *  Description:
 *      1. check basic environment
 *      2. create all dictionaries
 *---------------------------------------------------
EOF


#+ functions
#----------------------------------------------------
Usage(){
echo "
  Usage: (before install DMPSW, execute me)
    bash $0
"
  exit 1
}
if [[ $# -ne 0 ]];then
  Usage
fi

CheckEnv(){
  for var in $@;do
    if [[ `env | grep $var | wc -l` -lt 1 ]];then
      echo "    ERROR:  no shell variable \$$var"
      exit 1
    fi
  done
}

echo "---->   Checking Environment..."
CheckEnv ROOTSYS G4INSTALL G4LIB_USE_GDML

#+  Event
#----------------------------------------------------
package="Event"
echo "---->   Creating Dictionary..."
for subDir in `ls ./${package}`;do
  if [[ ! -d $package/$subDir ]];then
    continue
  fi
  pushd $package/$subDir 1>/dev/null
  /bin/rm -f ./*/Dictionary* >&/dev/null
  ./createDictionary
  popd  1>/dev/null
done


