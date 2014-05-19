/*
 *  $Id: DmpLog.cc, 2014-05-19 17:41:22 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/05/2014
*/

#include "DmpLog.h"

bool DmpLog::PrintDebug = false;
bool DmpLog::PrintInfor = false;
bool DmpLog::PrintWarning = true;
bool DmpLog::PrintError = true;

void DmpLog::SetLogLevel(const short &LogLevel){
  PrintDebug = LogLevel%2/Debug;
  PrintInfor = (LogLevel%4)/Infor;
  PrintWarning = (LogLevel%8)/Warning;
  PrintError = (LogLevel%16)/Error;
}

