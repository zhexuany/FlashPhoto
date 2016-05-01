#include "Pen.h"
using std::cerr;
Pen::Pen(ColorData* toolColor, int radius)
    : DrawTool(toolColor, radius, radius) {
  fillInfluence();
}

Pen::~Pen(){
}

void Pen:: fillInfluence(){
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
        influence[i][j] = 1.0;
      }else{
        influence[i][j] = 0.0;
      }
    }
  }
}

string Pen::getName(){
  return "Pen";
}
