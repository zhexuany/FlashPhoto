#include "Eraser.h"
/**
This is the eraser pen class, it inherits from DrawTool and is used for the eraser 
*/
///For function descriptions please see the Blur class
Eraser::Eraser(int radius)
    : DrawTool(radius, radius){
  fillInfluence();
  allowDrag = true;
}

Eraser::~Eraser(){
}

///Linear falloff circle pattern
void Eraser::fillInfluence(){
  Mask const * mask = getMask();
  float** influence = mask -> getInfluence();
  int width = mask -> getWidth();
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

///Custom apply influence function since we are "erasing" the background
void Eraser::applyInfluence(int x, int y, PixelBuffer* buffer){
  Mask const * mask = getMask();
  int height = mask -> getHeight();
  int width = mask -> getWidth();
  int bufferHeight = buffer -> getHeight();
  float** influence = mask -> getInfluence();
  ColorData backgroundColor = buffer -> getBackgroundColor();
  x -= width/2;
  y = bufferHeight - y - height/2;

  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      if(influence[i][j] == 1.0)
        buffer -> setPixel(x + i, y + j, backgroundColor);
    }
  }
}

string Eraser::getName(){
  return "Eraser";
}
