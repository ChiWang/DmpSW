
#   Event of DAMPE software

##  What are in here:

    1.  all event classes are in this package.

##  Usage

    1.  execute "bash pre-install.sh" to create dictionary of this sub-detector

    2.  compile in top directory (execute "scons package=Kernel")

    3.  execute "scons package=Event" to create shared library of Event package

    this package will create a shared library, other packages which want to use it, just link the created library and include header files

