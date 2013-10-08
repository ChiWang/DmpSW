/*=============================================================================
#       FileName :          DmpDcdRunMode.hh
#       Version  :          0.0.1
#       Author   :          USTC    (chiwang@mail.ustc.edu.cn)
#       Time     :          2013-08-11   12:56:58
#
#------------------------------------------------------------------------------
#       Description  :
#           need confirm!
#
#
#------------------------------------------------------------------------------
#       History  :
#                                          Update:  2013-08-11   13:23:57
=============================================================================*/

#ifndef DmpDcdRunMode_H
#define DmpDcdRunMode_H

enum DmpDcdRunMode {
  kMixed     = 0,       // only for Event Header, if sub-detectors setted different mode, run mode of Event Header is kMixed
  k0Compress = 1,       // zero compress
  kCompress  = 5,       // compress mode
  kCalPed    = 6,       // Calibrate pedestal
  kCalFEE    = 9,       // ADC Calibration

};

#endif


