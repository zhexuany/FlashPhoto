#include "SprayCan.h"
using std::cerr;
SprayCan::SprayCan(ColorData* toolColor, int radius)
    :DrawTool(toolColor, radius, radius){
  fillInfluence();
}

SprayCan::~SprayCan(){
}

void SprayCan::fillInfluence(){
  Mask const * mask = getMask();
  float** influence = mask -> getInfluence();
  int width = mask -> getWidth();
  int height = mask -> getHeight();
  if(width != height){
    cerr << "Mask dimension does not agree\n";
  }
  int xStart = 0;
  int yStart = 0;
  float val = 0.0;
  while(width > 0){
    if(width == 1){
      influence[yStart][xStart] = 0.20;
      break;
    }
    for(int i = 0; i < width - 1; i++){
      influence[yStart][xStart + i] = val;
    }
    for(int i = 0; i < width - 1; i++){
      influence[yStart + i][xStart + width - 1] = val;
    }
    for(int i = 0; i < width - 1; i++){
      influence[yStart + width - 1][xStart + width - 1 - i] = val;
    }
    for(int i = 0; i < width - 1; i++){
      influence[yStart + width - 1 - i][xStart] = val;
    }
    val += 0.01;
    xStart++;
    yStart++;
    width -= 2;
  }
  // int centre = width/2;
  // int distance = centre*centre;
  // for(int i = 0; i < width; i++){
  //   for(int j = 0; j < width; j++){
  //     if(((i - centre)*(i - centre) + (j - centre)*(j - centre)) > distance)
  //       influence[i][j] = 0;
  //   }
  // }
}
