/*
 *  $Id: DmpRdcAlgBgo.h, 2014-03-10 13:31:51 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 09/03/2014
*/

#ifndef DmpRdcAlgorithmBgo_H
#define DmpRdcAlgorithmBgo_H

/*
 *  add more algorithmes of Bgo Rdc at here
 *
 *  The default algorithm in DmpRdc/include/DmpRdcAlgorithm.h
 *
 */

namespace DmpAlgorithm{
namespace Rdc{
namespace Bgo{
  namespace Quarter{
    void SetConnector(std::string);
    void ConvertOneEvent();
  }
  namespace Prototype{
    void SetConnector(std::string);
    void ConvertOneEvent();
  }
  namespace Product{
    void SetConnector(std::string);
    void ConvertOneEvent();
  }
}
}
}


#endif


