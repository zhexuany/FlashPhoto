#include "CalligraphyPen.h"

CalligraphyPen::CalligraphyPen(ColorData* toolColor, int width, int height)
    : DrawTool(toolColor, width, height){
  fillInfluence();
}

CalligraphyPen::~CalligraphyPen(){
}

void CalligraphyPen::fillInfluence(){
  Mask const * mask = getMask();
  float** influence = mask -> getInfluence();
  int width = mask -> getWidth();
  int height = mask -> getHeight();
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      influence[i][j] = 1.0;
    }
  }

}

string CalligraphyPen::getName(){
  return "CalligraphyPen";
}
