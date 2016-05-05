#include "Stamp.h"

/**
This is the Stamp class, it inherits from DrawTool.  This will take a loaded image and apply it to the canvas.  The image is loaded in the mask variable
*/
///For function descriptions please see the Blur class
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
  ColorData stampPixelColor ;
  //x and y is buffer location
  //i  and j are the location of mask
  x -= width/2;
  y = bufferHeight - y - height/2;
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      stampPixelColor = imageBuffer -> getPixel(i,j);
      float alpha = stampPixelColor.getAlpha();
      ColorData currentPixelColor = buffer -> getPixel(x + i, y + j);
        buffer -> setPixel(x + i, y + j, stampPixelColor*alpha + currentPixelColor*(1 - alpha));
    }
  }
}

string Stamp::getName(){
  return "Stamp";
}
