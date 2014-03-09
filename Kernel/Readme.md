
#   Kernel of DAMPE offline software

##  What are in here:

    1.  parameters and enum type for whole detector

    2.  common abstract classes
        *   DmpVDataManager

    3.  scripts to set environment

    4.  boost python interface (DmpBindingCore.cc)

##  Usage:

    1.  compile in top directory (execute "scons package=Kernel")

    2.  other packages which want to use the created library libDmpCore.so, in their job option scripts.

    3.  you can use it in python:
        *   python
        *   import libDmpCore
        *   library.<Tab>
