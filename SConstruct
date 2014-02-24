'''
 *  $Id: SConstruct, 2014-02-24 14:06:12 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 24/02/2014
 *---------------------------------------------------
 *      setup install method in this file
 *  1. if you want to install the whole DMPSW, execute
 *      scons
 *      at current directory
 *  2. if you want to re-install some certain packages:
 *      scons package=package_1,package_2,package_3
 *  3. installation layout
 *      prefix/bin
 *      prefix/include
 *      prefix/lib
 *      prefix/share
'''

import os

# set basical environment
#--------------------------------------------------------------------
envBase = Environment(ENV = os.environ)
    # set Geant4 environment
g4sys=os.environ['G4INSTALL']
envBase.PrependENVPath('PATH', g4sys+'/../../../bin')
envBase.ParseConfig("geant4-config --cflags --libs")
envBase.Prepend(CPPFLAGS = '-DG4VIS_USE')       # set our -DRelease or -DDebug
envBase.Append(CPPFLAGS = ' -DG4UI_USE')
envBase.Append(CPPFLAGS = ' -DG4VIS_USE_OPENGLX')
    # set Root environment
envBase.ParseConfig("root-config --cflags --libs")

# set general variables
#--------------------------------------------------------------------
version='0.0.1'
#prefix='/usr/local'
prefix='Install'
if os.environ.has_key('DMPSWSYS'):
    prefix=os.environ['DMPSWSYS']
else:
    UsrPrefix=raw_input('Where to install DMPSW (press Enter to use default "%s"):'%prefix)
    if UsrPrefix is not None:
        prefix=UsrPrefix
prefix=os.path.abspath(prefix)
print "install DMPSW into: ",prefix
subDetectors=['Psd','Stk','Bgo','Nud']

# special C++ flags for DAMPE (mode)
#--------------------------------------------------------------------
if int(ARGUMENTS.get('release',0)):
    envBase.Append(CCFLAGS = ['-DDmp_RELEASE'])
else:
    envBase.Append(CCFLAGS = ['-g','-DDmp_DEBUG'])

# invoke *.scons file of top-1 packages
#--------------------------------------------------------------------
pkgList='Kernel,Event,RawDataConversion,Analysis,Geometry'
#,Simulation'
#pkgList='Simulation'
    #'Calibration,Generation,Geometry,Reconstruction,Simulation,Visualization'
pkgList=ARGUMENTS.get('package',pkgList)
pkgList=pkgList.split(',')
subScript=[]
for key in pkgList:
    subScript=subScript+[key+'/'+key+'.scons']

SConscript(subScript,exports=['envBase','version','prefix','subDetectors'])

