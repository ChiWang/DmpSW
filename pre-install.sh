#! /bin/bash
#=====================================================================
#   File:   pre-install.sh
#   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    26/12/2013
#---------------------------------------------------------------------
#   Description:
#       1. check basic environment
#       2. create all dictionaries
#---------------------------------------------------------------------
#   History:
#                           Last update:  24/01/2014   13:35:43
#=====================================================================


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
  \rm ./*/Dictionary* 2>/dev/null
  ./createDictionary
  popd  1>/dev/null
done

