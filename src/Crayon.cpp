#include "Crayon.h"


Crayon::Crayon(ColorData* toolColor, int radius)
  : DrawTool(toolColor, radius, radius){
  fillInfluence();
}

Crayon::~Crayon(){
}

void Crayon::fillInfluence() {
  Mask const * mask = getMask();
  float** influence = mask -> getInfluence();
  int width = mask -> getWidth();
  int height = mask -> getHeight();
  float dx, dy, dist;
  float radius = width / 2;
  for(int i = 0; i < width; i++) {
    for(int j = 0; j < height; j++) {
      dx = (radius - i)*(radius - i);
      dy = (radius - j)*(radius - j);
      dist  = sqrt(dx + dy);
      int randNum = rand() % 2;
      if (dist <= radius) {
        influence[i][j] = (float) randNum;
      } else {
        influence[i][j] = 0.0;
      }
    }
  }
}
