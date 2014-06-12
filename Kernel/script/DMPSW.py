#! /usr/bin/python
'''
 *  $Id: DMPSW.py, 2014-05-27 00:08:29 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
 *-----------------------------------------------------
 *      All jop option files need import this file
 *-----------------------------------------------------
'''

#-------------------------------------------------------------------
# Load basic environment of DAMPE software
import os
import sys
sys.setdlopenflags(0x100|0x2)
import libDmpKernel as DmpKernel

Core = DmpKernel.DmpCore.GetInstance()
SvcMgr = Core.ServiceManager()
AlgMgr = Core.AlgorithmManager()
prefix=os.getenv('DMPSWSYS')
IOSvc = SvcMgr.Get("DmpIOSvc")


