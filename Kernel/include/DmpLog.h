/*
 *  $Id: DmpLog.h, 2014-05-19 12:03:07 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/05/2014
*/

#include <iostream>
#include <iomanip>

namespace DmpLog{
  enum{
    Debug = 1,
    Infor = 2,
    Warning = 4,
    Error = 8,
  };
  void SetLogLevel(const short &l);
  /*
   * LogLevel
   *     types: {error(8) | warning(4) | information(2) | debug(1)}
   *    0:      nothing
   *    1:      debug
   *    2:      infor.
   *    3:      debug + infor.
   *    4:      warning
   *    5:      warning + debug
   *    6:      warning + infor.
   *    7:      warning + infor. + debug
   *    8:      error
   *    9:      error + debug
   *    10:     error + infor.
   *    11:     error + infor. + debug
   *    12:     error + warning
   *    13:     error + warning + debug
   *    14:     error + warning + infor.
   *    15:     error + warning + infor. + debug
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


