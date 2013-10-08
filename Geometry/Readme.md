$Id: GDML README $
-------------------------------------------------------------------

     =========================================================
                     DAMPE GDML Description
     =========================================================

GDML files of detector in Geometry,

will be used in Simulation and Visualization.


What every file it is ?
1. Main.gdml: Main GDML file of DAMPE detector descrption(Not completed!).
2. BGO.gdml: GDML file of BGO subdetector descrption.
3. layer.gdml: Sub GDML file descrpting a BGO layer, it will be invoked in BGO.gdml.
4. material.xml: It's a common material XML file. All material definition are written in it. Every subdetector's GDML file can invoke it.
5. Gtest: a small Geant4 program to test GDML.


How to build this example ?
$cd Gtest
$make
$gdml_det ../layer.gdml        (if you want to test a layer, use this command)
$gdml_det ../BGO.gdml          (if you want to test whole BGO detector, use this command. It will cost very much time in reading sub GDML files, please be patient!)

when you want to run a event, you can type:
/run/beamOn 1

and then the hit in various of BGO strip will be output on the screen like this:
This hit is in BGOStrip_12 of layer_05.

