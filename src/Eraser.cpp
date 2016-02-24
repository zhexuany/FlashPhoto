#include "Eraser.h"

Eraser::Eraser(ColorData* backgroundColor, int radius)
    : DrawTool(backgroundColor, radius, radius){
  fillInfluence();
}

Eraser::~Eraser(){
}

void Eraser::fillInfluence(){
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

void Eraser::paint(int x, int y, PixelBuffer* buffer){
  ColorData backgroundColor = buffer -> getBackgroundColor();
  Mask const * mask = getMask();
  int height = mask -> getHeight();
  int width = mask -> getWidth();
  x -= width/2;
  y -= height/2;
  for(int i = 0; i< height; i++){
    for(int j = 0; j < width; j++){
      buffer -> setPixel(x, y, backgroundColor);
    }
  }
}
