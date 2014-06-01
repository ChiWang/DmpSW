/*
 *  $Id: DmpLog.h, 2014-05-19 12:03:07 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/05/2014
*/

#ifndef DmpLog_H
#define DmpLog_H

#include <iostream>
#include <iomanip>

namespace DmpLog{
  enum{
    Debug = 1,
    Infor = 10,
    Warning = 100,
    Error = 1000
  };
  void SetLogLevel(const short &l);
  /*
   * LogLevel
   *     types: {error(1000) | warning(100) | information(10) | debug(1)}
   */
  extern bool PrintDebug;
  extern bool PrintInfor;
  extern bool PrintWarning;
  extern bool PrintError;
}

#define LogDebug if(DmpLog::PrintDebug) \
    std::cout<<std::setiosflags(std::ios::left)<<std::setw(12)<<"  DEBUG: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<"  "

#define LogInfor if(DmpLog::PrintInfor) \
    std::cout<<std::setiosflags(std::ios::left)<<std::setw(12)<<"  INFOR: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<"  "

#define LogWarning if(DmpLog::PrintWarning) \
    std::cout<<std::setiosflags(std::ios::left)<<std::setw(12)<<"  WARNING: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<"  "

#define LogError if(DmpLog::PrintError) \
    std::cout<<std::setiosflags(std::ios::left)<<std::setw(12)<<"  ERROR: "<<__FILE__<<"("<<__LINE__<<"), in "<<__PRETTY_FUNCTION__<<"  "

#endif

