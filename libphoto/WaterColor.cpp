#include "WaterColor.h"

WaterColor::WaterColor(ColorData* toolColor, int radius)
  : DrawTool(toolColor, radius, radius){
  fillInfluence();
}

WaterColor::~WaterColor(){
}

void WaterColor::fillInfluence(){
  Mask const * mask = getMask();
  float** influence = mask -> getInfluence();
  int width = mask -> getWidth();
  int height = mask -> getHeight();
  float dx, dy, dist;
  float radius = width / 2;
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      dx = (radius - i)*(radius - i);
      dy = (radius - j)*(radius - j);
      dist  = sqrt(dx + dy);
      if(dist <= radius){
        influence[i][j] = pow(((radius - dist) / radius), 2)*0.2;
      }else{
        influence[i][j] = 0.0;
      }
    }
  }

}
