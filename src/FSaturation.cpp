#include "FSaturation.h"
FSaturation::FSaturation(){
}

void FSaturation::applyFilter(PixelBuffer* imageBuffer){
  int width = imageBuffer -> getWidth();
  int height = imageBuffer -> getHeight();
  float saturation = getFloatParameter();
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      ColorData currPixel = imageBuffer -> getPixel(i, j);
      float grayscale = currPixel.getLuminance();
      ColorData newPixel = currPixel * saturation - ColorData(grayscale, grayscale, grayscale)*(saturation - currPixel.getAlpha());
      newPixel = newPixel.clampedColor();
      imageBuffer -> setPixel(i, j, newPixel);
    }
  }
}

std::string FSaturation::getName(){
  return "FSaturation";
}
