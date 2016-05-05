#include "Pen.h"
using std::cerr;
Pen::Pen(ColorData* toolColor, int radius)
    : DrawTool(toolColor, radius, radius) {
  fillInfluence();
}

/**
This is the pen class.  It inherits from the DrawTool and only needs to deal with loading the influence matrix.  DrawTool applies the influence.
*/
///For function descriptions please see the Blur class
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
