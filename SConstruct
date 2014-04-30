'''
 *  $Id: SConstruct, 2014-04-30 17:44:25 DAMPE $
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
 *----------------------------------------------------------
'''

import os

# functions
#--------------------------------------------------------------------
def checkSysEnv(var):
    if not os.environ.has_key(var):
        print "\tERROR:\tNot has environment variable: %s" % var
        Exit(1)

def useCLHEP(aEnv):
    aEnv.ParseConfig("clhep-config --include --libs")

def useRoot(aEnv):
    checkSysEnv('ROOTSYS')
    aEnv.ParseConfig("root-config --cflags --libs")
    #aEnv.Append(LIBS=['RooFitCore','RooFit'])

def useGeant4(aEnv):
    checkSysEnv('G4INSTALL')
    g4sys=os.environ['G4INSTALL']
    aEnv.PrependENVPath('PATH', g4sys+'/../../../bin')
    aEnv.ParseConfig("geant4-config --cflags --libs")

def useBoostPython(aEnv):
    aEnv.ParseConfig("python-config --include --libs")
    aEnv.Append(LIBS=['boost_python'])
    #aEnv.Append(LIBS=['boost_program_options-mt'])

def useOpenMP(aEnv):
    aEnv.MergeFlags('-fopenmp')

def ProcessThisDir(fromPath,toPath):
    for tmp in os.listdir(fromPath):
        if "." in tmp[0] or "scons" in tmp or "test" in tmp:   continue
        if os.path.isdir(fromPath+tmp):  ProcessThisDir(fromPath+tmp,toPath+tmp)
        else: Default(Command(toPath+'/'+tmp,fromPath+'/'+tmp,Copy("$TARGET","$SOURCE")))

# set basical environment
#--------------------------------------------------------------------
envBase = Environment(ENV = os.environ)

# set general variables
#--------------------------------------------------------------------
version='0.0.1'
#prefix='/usr/local'
prefix='Install'
if os.environ.has_key('DMPSWSYS'):
    prefix=os.environ['DMPSWSYS']
else:
    UsrPrefix=raw_input('Where to install DMPSW (press Enter to use default "%s"):'%prefix)
    UsrPrefix=UsrPrefix.strip()
    if UsrPrefix:
        prefix=UsrPrefix
prefix=os.path.abspath(prefix)
print "install DMPSW into: ",prefix
subDetectors=['Psd','Stk','Bgo','Nud']

# invoke *.scons file of top-1 packages
#--------------------------------------------------------------------
pkgList='TestRelease,Kernel,Event,Geometry,Simulation,RawDataConversion'
#pkgList='TestRelease,Kernel,Event,Geometry,Simulation,RawDataConversion'
#,Analysis,Calibration,Generation,Reconstruction,Visualization'
pkgList=ARGUMENTS.get('package',pkgList)
pkgList=pkgList.split(',')
subScript=[]
for key in pkgList:
    subScript=subScript+[key+'/'+key+'.scons']

SConscript(subScript,exports=['prefix','version','envBase','subDetectors','useRoot','useGeant4','useBoostPython','useCLHEP','useOpenMP','ProcessThisDir'])

