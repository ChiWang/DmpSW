
#   Event of DAMPE software

##  What are in here:
    1.  all event classes are in this package.

##  Usage
    1.  cd into sub-detector
    2.  execute "./createDictionary" to create dictionary of this sub-detector
    3.  execute "scons" to create shared library of Event package(at where is SConstruct)

    4.  link the created library and include header files, when other packages want to use some thing in Event

##  Development guid

    all the event classes of Sub-detector inherit from DmpVEvtSubDet(in Kernel package)

