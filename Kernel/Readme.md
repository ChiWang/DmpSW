
#   Kernel of DAMPE software

##  What are in here:
    1.  common abstract classes
        If only one package will use an abstract class, just put it in the certain package instead of in here.
    2.  Parameters of sub-detector
        we summarize of parameters in the namespace DmpParameter.
    3.  if some classes will be used in the common abstract classes(for instance: DmpEvtHeader will be use in DmpEvtManager)
        we put them(DmpEvtHeader) at here, in order to reduce dependency of Kernel from other package

##  Usage:

    1.  execute "./createDictionary" to create dictionary of Kernel

    2.  execute "scons" to create shared library of Kernel

    3.  link the created library and include header files, when other packages want to use some thing in Kernel

