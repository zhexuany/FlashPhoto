#include "Pen.h"

Pen::Pen(ColorData* toolColor, int w, int h)
    : DrawTool(toolColor, w, h) {
  fillInfluence();
}

Pen::~Pen(){
}

void Pen:: fillInfluence(){
    Mask const * mask = getMask();
    float** influence = mask -> getInfluence();
    int width = mask -> getWidth();
    int height = mask -> getHeight();
    for(int i = 0; i < width; i++){
      for(int j = 0; j < height; j++){
        influence[i][j] = 0;
      }
    }
}

