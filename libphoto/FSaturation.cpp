//
// FSaturation.cpp
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.


#include "FSaturation.h"
/**
This is the FSaturation class, it is used for the saturation image filters.  This does not use kernels so it only has to deal with applying the filter
*/
FSaturation::FSaturation(){
}
FSaturation::~FSaturation(){
}
///apply filter effect to PixelBuffer* buffer passed into this function
void FSaturation::applyFilter(PixelBuffer* imageBuffer){
  int width = imageBuffer -> getWidth();
  int height = imageBuffer -> getHeight();
  float saturation = getFloatParameter();
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      ColorData currPixel = imageBuffer -> getPixel(i, j);
      float grayscale = currPixel.getLuminance();
      ColorData newPixel =
        currPixel * saturation - ColorData(grayscale, grayscale, grayscale)
        *(saturation - currPixel.getAlpha());
      newPixel = newPixel.clampedColor();
      imageBuffer -> setPixel(i, j, newPixel);
    }
  }
}

///get class name for filter
std::string FSaturation::getName(){
  return "FSaturation";
}
