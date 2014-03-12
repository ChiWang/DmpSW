
#   Kernel of DAMPE offline software

##  What are in here:

    1.  parameters and enum type for whole detector

    2.  bind interface to python (in DmpBindingCore.cc)

    3.  scripts to set environment (./script)


##  Usage:

    1.  install DMPSW firstly (refer to: ../README.md/{How to install DMPSW})

    2.  other packages which want to use the created library libDmpCore.so, in their job option scripts.

    3.  you can use it in python:
        $   python
        >   import libDmpCore
        >   library.<Tab>


