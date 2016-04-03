#include "FSharpen.h"
#include "ColorData.h"
#include "PixelBuffer.h"

FSharpen::FSharpen(){
  black = ColorData(0, 0, 0);
  white = ColorData(1, 1, 1);
}

void FSharpen::applyFilter(PixelBuffer* imageBuffer){
  int width = imageBuffer -> getWidth();
  int height = imageBuffer -> getHeight();
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
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

std::string FSharpen::getName(){
  return "FSharpen";
}

void FSharpen::setFilterParameter(float parameter){
  this -> threshold = parameter;
}
