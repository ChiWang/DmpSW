/*=====================================================================
 *   File:   DmpRecordBgoPed.h
 *   Author: Chi WANG  (chiwang@mail.ustc.edu.cn)    26/12/2013
 *---------------------------------------------------------------------
 *   Description:
 *
 *---------------------------------------------------------------------
 *   History:
 *                           Last update:  26/12/2013   21:22:38
=====================================================================*/

#ifndef DmpRecordBgoPed_H
#define DmpRecordBgoPed_H

#include "DmpVRecord.h"

class DmpRecordBgoPed : public DmpVRecord {
/*
 * DmpRecordBgoPed
 *
 *  used in dmpBgoPed
 */

 public:
  DmpRecordBgoPed();
  ~DmpRecordBgoPed();

 private:
  std::vector<int>      fLBSDCollection;
  std::vector<double>   fMeanCollection;
  std::vector<double>   fSigmaCollection;


  ClassDef(DmpRecordBgoPed,1)
};

#endif

