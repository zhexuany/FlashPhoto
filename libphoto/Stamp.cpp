#include "Stamp.h"


Stamp::Stamp(PixelBuffer* newBuffer, int stampWidth, int stampHeight)
  : DrawTool(newBuffer, stampWidth, stampHeight){
  fillInfluence();
}

Stamp::~Stamp(){
}


void Stamp::fillInfluence(){
  Mask const * mask = getMask();
  float** influence = mask -> getInfluence();
  int width = mask -> getWidth();
  int height = mask -> getHeight();
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      influence[i][j] = 1;
    }
  }
}

void Stamp::applyInfluence(int x, int y, PixelBuffer* buffer){
  Mask const * mask = getMask();
  int height = mask -> getHeight();
  int width = mask -> getWidth();
  int bufferHeight = buffer -> getHeight();
  ColorData currentPixelColor;
  x -= width/2;
  y = bufferHeight - y - height/2;

  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      currentPixelColor = imageBuffer -> getPixel(i,j);
      buffer -> setPixel(x + i, y + j, currentPixelColor);
    }
  }
}

string Stamp::getName(){
  return "Stamp";
}
