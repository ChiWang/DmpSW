/*
 *  $Id: DmpRdcAlgorithm.h, 2014-03-09 23:07:54 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 13/12/2013
*/

#ifndef DmpRdcAlgorithm_H
#define DmpRdcAlgorithm_H

#include <map>
#include <fstream>      // ifstream*
#include <string>

/*
 *  DmpRdcAlgorithm
 *
*/

namespace DmpAlgorithm{
namespace Rdc{
  extern ifstream  *gInputData;    // pointer of input data
  extern short gTrigger;
  bool ConvertEventHeader();
  namespace Psd{
    extern std::map<int,int>  connector;
    extern short trigger;
    bool SetConnector(std::string);
    bool ConvertEvent();
  }
  namespace Stk{
    extern std::map<int,int>  connector;
    extern short trigger;
    bool SetConnector(std::string);
    bool ConvertEvent();
  }
  namespace Bgo{
    /*
     * Connector: FEE channel <--> Detector
     * connector[FEEID*1000+ChannelID][LBSD_ID]
     * LBSD_ID = Layer_id*10000+Bar_id*100+Side_id*10+Dy_id
     *
    */
    extern std::map<int,int>  connector;
    extern short trigger;
    bool SetConnector(std::string);
    bool ConvertEvent();
  }
  namespace Nud{
    extern std::map<int,int>  connector;
    extern short trigger;
    bool SetConnector(std::string);
    bool ConvertEvent();
  }
}
  //void SetInputData(ifstream *p)    {fInputData = p;}
}

typedef DmpAlgorithm::Rdc   DmpRdcAlg;

#endif

