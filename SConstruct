#=====================================================================
#   File:   SConstruct
#   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    01/10/2013
#---------------------------------------------------------------------
#   Description:
#           Install method in this file
#       1. use basical softwares: root geant4
#       2. installation layout
#           prefix/bin
#           prefix/include
#           prefix/lib
#           prefix/share
#       3. if you want to re-install some packages:
#           scons package=package_1,package_2,package_3
#
#---------------------------------------------------------------------
#   History:
#                           Last update:  22/01/2014   23:53:57
#=====================================================================

import os

# functions
#--------------------------------------------------------------------
def checkEnvironment(VarList):
    print "Checking basic environment"
    for var in VarList:
        if not os.environ.has_key(var):
            print '\tERROR:\tDoes not has environment variable: %s' %var
            Exit(1)

# set basical environment
#--------------------------------------------------------------------
requirement=['ROOTSYS','G4INSTALL','G4LIB_USE_GDML']
checkEnvironment(requirement)
envBase = Environment(ENV = os.environ)
    # set Geant4 environment
g4sys=os.environ['G4INSTALL']
envBase.PrependENVPath('PATH', g4sys+'/../../../bin')
envBase.ParseConfig("geant4-config --cflags --libs")
    # set Root environment
envBase.ParseConfig("root-config --cflags --libs")

# set general varables
#--------------------------------------------------------------------
prefix='/usr/local'
if os.environ.has_key('DMPOSSYS'):
    prefix=os.environ['DMPOSSYS']
else:
    UsrPrefix=raw_input('Where to install DMPOS [default is "/usr/local"]: ')
    if UsrPrefix is None:
        prefix=UsrPrefix
prefix=os.path.abspath(prefix)
subDetectors=['Psd','Stk','Bgo','Nud']

# special C++ flags for DAMPE (mode)
#--------------------------------------------------------------------
if int(ARGUMENTS.get('debug',1)):
    envBase.Append(CCFLAGS = ['-g','-DDmp_DEBUG'])
else:
    envBase.Append(CCFLAGS = ['-DDmp_RELEASE'])

# invoke *.scons file of top-1 packages
#--------------------------------------------------------------------
pkgList='Kernel,Event,RawDataConversion,Analysis,Geometry'
    #'Calibration,Generation,Geometry,Reconstruction,Simulation,Visualization'
pkgList=ARGUMENTS.get('package',pkgList)
pkgList=pkgList.split(',')
subScript=[]
for key in pkgList:
    subScript=subScript+[key+'/'+key+'.scons']

SConscript(subScript,exports=['envBase','prefix','subDetectors'])


