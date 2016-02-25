#include "Eraser.h"

Eraser::Eraser(int radius)
    : DrawTool(radius, radius){
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
  Mask const * mask = getMask();
  int height = mask -> getHeight();
  int width = mask -> getWidth();
  int bufferHeight = buffer -> getHeight();
  ColorData backgroundColor = buffer -> getBackgroundColor();
  x -= width/2;
  y = bufferHeight - y - height/2;
  float ** influence = mask -> getInfluence();
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      buffer -> setPixel(x + i, y + j, backgroundColor);
    }
  }
}
