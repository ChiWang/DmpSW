#! /bin/bash
#=============================================================================
#       FileName :          userootcint.sh
#       Version  :          0.0.1
#       Author   :          Chi WANG    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-12-11   16:15:20
#------------------------------------------------------------------------------
#       Description  :
#   Using rootcint
#       http://www.scons.org/doc/HTML/scons-user.html#chap-builders-writing
#       http://kalmanalignment.hepforge.org/svn/trunk/event/SConscript
#
#   Usage:
#       0.  bash thisFileName.sh
#       1.  define linkDef: XXXLinkDefXXX.hh
#       2.  define fileList:    will be used header files
#       3.  if need external header files, use includeDir1
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-12-11   21:50:35
#=============================================================================

includeDir="./include"
includeDir1="../DmpEvent/include"
srcDir="./src"

#+  auto define linkDef and fileList
nLinkDef=0
for file in `ls $includeDir`;do
    if [[ $file =~ "LinkDef" && $file =~ ".h" ]];then
        linkDef=$file
        let nLinkDef=$nLinkDef+1
    else
        fileList="$fileList $file"
    fi
    if [ $nLinkDef = "2" ];then
        echo "Error:    there're $nLinkDef LinkDef.h files..."
        echo "must re-write $0"
        exit 0
    fi
done
#+

#+  Error of "re-write" here:
#linkDef=
#fileList=
#

diction=`echo $linkDef | sed s/LinkDef//`
diction="${diction%.*}_Dict.cc"

echo "generating    $diction"
rootcint -f ${includeDir}/${diction} -c -p -I$includeDir -I$includeDir1 $fileList $linkDef
mv $includeDir/$diction $srcDir/$diction 2>/dev/null


