
#   Event of DAMPE software

##  What are in here:
    1.  all event classes are in this package.

##  Usage
    1.  cd into sub-detector
    2.  execute "./newDictionary" to create dictionary of this sub-detector
    3.  execute "scons" to create shared library of Event package(at where is SConstruct)

    4.  link the created library and include header files, when other packages want to use some thing in Kernel

##  Development guid

    all the event classes of Sub-detector inherit from DmpEvtSubDet(in Kernel package)

