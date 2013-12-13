

DAMPE Software kernel:

    1.  commom abstract classes, not one package will use those classes. (If only one package will use a abstract class, we put it in the certain package).

    2.  this package not depend on other package, so, if like DmpEvtHeader(it is not a abstruct class,) we must put it in here.

Usage:

    1.  execute "./createDictionary" to create Kernel_Dict.h and Kernel_Dict.cc

    2.  execute "scons" to create shared library.


