#! /bin/bash
#=====================================================================
#   File:   pre-install.sh
#   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    26/12/2013
#---------------------------------------------------------------------
#   Description:
#       use this script to create all dictionaries
#---------------------------------------------------------------------
#   History:
#                           Last update:  22/01/2014   11:33:33
#=====================================================================


#+ functions
#----------------------------------------------------
Usage(){
echo "
  Usage:
"
  exit 1
}
if [[ $# -ne 0 ]];then
  Usage
fi

#+  Event
#----------------------------------------------------
package="Event"
for subDir in `ls ./${package}`;do
  if [[ ! -d $package/$subDir ]];then
    continue
  fi
  pushd $package/$subDir 1>/dev/null
  \rm ./*/Dictionary* 2>/dev/null
  ./createDictionary
  popd  1>/dev/null
done


