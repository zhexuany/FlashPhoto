#ifndef FTHRESHOLD_H
#define FTHRESHOLD_H
#include "FThreshold.h"
#include "ColorData.h"
#include "PixelBuffer.h"

FThreshold::FThreshold(){
  black = ColorData(0, 0, 0);
  white = ColorData(1, 1, 1);
}

void FThreshold::applyFilter(PixelBuffer * imageBuffer){
  int width = imageBuffer -> getWidth();
  int height = imageBuffer -> getHeight();
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      ColorData currPixel = imageBuffer -> getPixel(i, j);
      float grayscale = currPixel.getLuminance();
      // if the grayscale is larger than parameter, then set pixel as white
      // otherwise, set current pixel as black
      if(grayscale > threshold){
        imageBuffer -> setPixel(i, j, white);
      } else {
        imageBuffer -> setPixel(i, j, black);
      }
    }
  }
}

std::string FThreshold::getName(){
  return "FThreshold";
}

void FThreshold::setFilterParameter(float parameter){
  this -> threshold = parameter;
}
#endif //FTHRESHOLD_H
