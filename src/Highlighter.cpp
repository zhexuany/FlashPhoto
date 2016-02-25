#include "Highlighter.h"

Highlighter::Highlighter(ColorData* toolColor, int width, int height)
    : DrawTool(toolColor, width, height){
  fillInfluence();
}

Highlighter::~Highlighter(){
}

void Highlighter::fillInfluence(){
  Mask const * mask = getMask();
  float** influence = mask -> getInfluence();
  int width = mask -> getWidth();
  int height = mask -> getHeight();
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      influence[i][j] = 0.4;
    }
  }
}


void Highlighter::paint(int x, int y, int prevX, int prevY, PixelBuffer* buffer) {
  applyInfluence(x, y, buffer);
}
