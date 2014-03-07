#! /usr/bin/python

import libDmpSimulation as DmpSimulation

DmpSimulation.Initialize()
#DmpSimulation.Execute("default")   # visual mode
DmpSimulation.Execute("share/test.mac")
DmpSimulation.Execute("share/test.mac")
DmpSimulation.Clear()
