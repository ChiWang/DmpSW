
##      Those files (*.cnct) will be used in DmpSoftware/RawDataConversion/Bgo/src/DmpRdcBgo.cc

##      NOTE:
        *   must named as Layer_i.cnct
        *   set the format as BgoConnectionMethod stated
        *   Layer_0 to Layer_14: from top to bottom

        -------------------------
        **  if changed channel **
        -------------------------

        1.  mkdir connector_back_$date
        2.  copy all files into backup directory
        3.  modify connector in Layer_i.cnct
        4.  record change information in BgoConnectorChangeNote.md

