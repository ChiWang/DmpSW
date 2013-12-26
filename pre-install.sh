#! /bin/bash
#=====================================================================
#   File:   pre-install.sh
#   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    26/12/2013
#---------------------------------------------------------------------
#   Description:
#       use this script to create all dictionaries
#---------------------------------------------------------------------
#   History:
#                           Last update:  26/12/2013   13:27:40
#=====================================================================

#+  Kernel
pushd Kernel 1>/dev/null
  ./createDictionary
popd 1>/dev/null

#+  Event
pushd Event/Bgo 1>/dev/null
  ./createDictionary
popd 1>/dev/null

pushd Event/Psd 1>/dev/null
  ./createDictionary
popd 1>/dev/null

pushd Event/Nud 1>/dev/null
  ./createDictionary
popd 1>/dev/null

#+  RDC
pushd RawDataConversion/DmpRdc 1>/dev/null
  ./createDictionary
popd 1>/dev/null


