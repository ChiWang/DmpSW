/*
 *  $Id: DmpRdcConnectorInterface.cc, 2014-03-19 10:57:19 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/03/2014
*/

DmpRdcConnectorInterface* DmpRdcConnectorInterface::GetInstance(){
  static DmpRdcConnectorInterface  instance;
  return &instance;
}

DmpRdcConnectorInterface::~DmpRdcConnectorInterface(){
}

DmpRdcConnectorInterface::DmpRdcConnectorInterface(){
  for(short i=0;i<DmpDetector::gSubDetNo;++i){
    fConnectorPath[i]="default";
  }
}

