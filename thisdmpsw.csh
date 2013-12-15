#! /bin/tcsh
#=====================================================================
#   File:   thisdmpsw.csh
#   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    01/10/2013
#---------------------------------------------------------------------
#   Description:
#
#       after installation, source this file in .zshrc(.bashrc), then you can use DampeSoftware
#---------------------------------------------------------------------
#   History:
#                           Last update:  14/12/2013   10:50:56
#=====================================================================

#+  Set DAMPE software developement environment         # for developer
if ( ! ($?DMPSWWORK) ) then
  if ( $#argv == 0 ) then
    set dir=$HOME/dmpsw_workdir
  else
    set dir=$argv[1]
  endif
  setenv DMPSWWORK $dir
  setenv PATH $DMPSWWORK/bin:$PATH
  if ( ($?LD_LIBRARY_PATH) ) then
    setenv LD_LIBRARY_PATH $DMPSWWORK/lib:$LD_LIBRARY_PATH
  endif
  if ( ($?DYLD_LIBRARY_PATH) ) then        # Mac OS
    setenv DYLD_LIBRARY_PATH $DMPSWWORK/lib:$DYLD_LIBRARY_PATH
  endif
  unset dir
endif

