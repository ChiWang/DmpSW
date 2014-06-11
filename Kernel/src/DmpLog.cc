/*
 *  $Id: DmpLog.cc, 2014-06-02 15:03:29 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 19/05/2014
 *    Andrii Tykhonov (Andrii.Tykhonov@cern.ch) 22/05/2014
*/

#include "DmpLog.h"

short DmpLog::logLevel  = DmpLog::INFO;
bool DmpLog::logShowFunctionHeader = false;

//-------------------------------------------------------------------
void DmpLog::SetLogLevel(const std::string &myLogLevel,bool show){
  if(myLogLevel == "NONE" || myLogLevel == "None" || myLogLevel == "none"){
    DmpLog::logLevel = DmpLog::NONE;
  }else if(myLogLevel == "ERROR" || myLogLevel == "Error" || myLogLevel == "error"){
    DmpLog::logLevel = DmpLog::ERROR;
  }else if(myLogLevel == "WARNING" || myLogLevel == "Warning" || myLogLevel == "warning"){
    DmpLog::logLevel = DmpLog::WARNING;
  }else if(myLogLevel == "INFO" || myLogLevel == "Info" || myLogLevel == "info"){
    DmpLog::logLevel = DmpLog::INFO;
  }else if(myLogLevel == "DEBUG" || myLogLevel == "Debug" || myLogLevel == "debug"){
    DmpLog::logLevel = DmpLog::DEBUG;
  }else{
    std::cout<<"\n\n\n\n\n[DmpLog::SetLogLevel] Unrecognized logging option - setting the default value = INFO\n\n\n\n\n"<<std::endl;
    DmpLog::logLevel = DmpLog::INFO;
  }
  DmpLog::logShowFunctionHeader = show;
}


