#ifndef StkParamDef_h
#define StkParamDef_h

namespace StkParamDef { 
  enum viewType { kYview = 0,
		  kXview = 1};

  //row number in state vector for x and y views
  enum viewRow  { kXrow = 0,
		  kYrow = 2};

  const double Xstrips_z[6]    = {76.54, 108.54, 140.54, 172.54, 204.54, 236.54};
  const double Xstrips_z_b[6]  = {76.22, 108.22, 140.22, 172.22, 204.22, 236.22};
  const double Ystrips_z[6]    = {74.22, 106.22, 138.22, 170.22, 202.22, 234.22};
  const double Ystrips_z_b[6]  = {73.9,  105.9,  137.9,  169.9,  201.9,  233.9};

  const double SiHitResolution = 0.1; //very rough!!! constant position resolution

  const int nStripsPerLadder   = 768;
  //int nChannelsPerLadder = 384;
  const double activeTileSize = 92.928;
  const double activeEdge = -activeTileSize/2.; //=46.464
  const double pitch   = 0.121;
  const double ROpitch = 0.242;

  const double TilesSeparation = 0.08;
  const double SiliconGuardRing = 1.036;
  const double BlockSizeXY = 380.24;
  // x blocks: 0 -> -x, 1 -> -x, 2 -> +x, 3 -> +x 
  // y blocks: 0 -> -y, 1 -> +y, 2 -> -y, 3 -> +y
  //                                                                     |-----|-----|     
  //      Block 0-0 placed at x= -190.16, y= -190.16                     |  1  |  3  |
  //      Block 0-1 placed at x= -190.16, y= 190.16                      |     |     |
  //      Block 1-0 placed at x= 190.16, y= -190.16                      |-----|-----|
  //      Block 1-1 placed at x= 190.16, y= 190.16                       |     |     |
  const double  blockCenterLeft  = -190.16; //2 blocks on the left (0, 1)      |  0  |  2  |
  const double  blockCenterRight =  190.16; //2 blocks on the left (2, 3)      |-----|-----| 

}

#endif
