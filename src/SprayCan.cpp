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
  float dx, dy, dist;
  int radius = width/2;
  for(int i = 0; i < width; i++){
    for(int j = 0; j < width; j++){
      dx = (radius - i)*(radius - i);
      dy = (radius - j)*(radius - j);
      dist  = sqrt(dx + dy);
      if(dist <= radius){
        influence[i][j] = ((radius - dist) / radius)*0.2;
      }else{
        influence[i][j] = 0.0;
      }
    }
  }

}

