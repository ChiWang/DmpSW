
#   Kernel of DAMPE offline software

##  What are in here:

    1.  parameters and enum type for whole detector

    2.  use boost python (in DmpBindingCore.cc) bind interface to control static data member gPhase in common abstract class DmpVDataManager

    3.  scripts to set environment


##  Usage:

    1.  compile in top directory (execute "scons package=Kernel")

    2.  other packages which want to use the created library libDmpCore.so, in their job option scripts.

    3.  you can use it in python:
        *   python
        *   import libDmpCore
        *   library.<Tab>
