#!/bin/csh
#+
#+  $Id: pre-install.csh, 2014-05-09 15:16:54 DAMPE $
#+  Author(s):
#+    Chi WANG (chiwang@mail.ustc.edu.cn) 26/02/2013
#+    Fabio GARGANO  (fabio.gargano@ba.infn.it)    06/02/2014
#+------------------------------------------------------------
#+  Description:
#+      1. check basic environment
#+      2. create all dictionaries
#+------------------------------------------------------------
#+  History:
#+      modified for tcsh shells 06/02/2014 (Fabio)
#+


echo "---->   Checking Environment..."

set EnvVarToCheck = "$ROOTSYS $G4INSTALL $G4LIB_USE_GDML "
foreach var ($EnvVarToCheck)
if (`env | grep $var | wc -l` < 1) then
    echo    "ERROR:  no shell variable \$var"
    exit 1
endif  
end

#+  Event
#----------------------------------------------------
set package="Event"
echo "---->   Creating Dictionary..."

foreach subDir (`ls $package`)
  if(! -d $package/$subDir ) then
    continue
  endif
  pushd $package/$subDir >&/dev/null
  \rm -f ./*/Dictionary*
  ./createDictionary
  popd >&/dev/null
end

