
#   Kernel of DAMPE offline software

##  What are in here:

    1.  parameters and enum type for whole detector

    2.  common abstract classes
        *   DmpVDataManager

    3.  scripts to set environment

##  Usage:

    1.  compile in top directory (execute "scons package=Kernel")

    2.  other packages will use the created library libDmpCore.so, in their job option scripts.

    3.  you can use it in python:
        *   python
        *   import libDmpCore
        *   library.<Tab>
