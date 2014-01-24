
#   Kernel of DAMPE offline software

##  What are in here:
    1.  common abstract classes
        If only one package will use an abstract class, just put it in the certain package instead of in here.
    2.  Parameters of sub-detector
        we summarize of parameters in the namespace DmpParameter.
    3.  if some classes will be used in the common abstract classes(for instance: DmpEvtHeader will be use in DmpVEvtManager)
        we put them(DmpEvtHeader) at here, in order to reduce dependency of Kernel from other package

##  Usage:
    1.  cd into trunk, where has the SConstruct file
    2.  execute "scons package=Kernel" to create shared library of Kernel package

    this package will create a shared library, other packages which want to use it, just link the created library and include header files

