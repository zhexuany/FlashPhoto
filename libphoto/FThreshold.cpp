//
// FilterThreshold.cpp
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.

#ifndef FTHRESHOLD_H
#define FTHRESHOLD_H
#include "FThreshold.h"
/**
This is the FThreshold class, it is used for the quantize image filters.  This does not use kernels so it only has to deal with applying the filter.
*/
FThreshold::FThreshold(){
}

FThreshold::~FThreshold(){
}

///apply filter effect to PixelBuffer* buffer passed into this function
void FThreshold::applyFilter(PixelBuffer * imageBuffer){
  int width = imageBuffer -> getWidth();
  int height = imageBuffer -> getHeight();
  float threshold = getFloatParameter();
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      ColorData currPixel = imageBuffer -> getPixel(i, j);
      // if the grayscale is larger than parameter, then set pixel as white
      // otherwise, set current pixel as black
      int newRed = currPixel.getRed() > threshold ? 1.0: 0.0;
      int newBlue = currPixel.getBlue() > threshold ? 1.0 : 0.0;
      int newGreen = currPixel.getGreen() > threshold ? 1.0 : 0.0;
      imageBuffer -> setPixel(i, j, ColorData(newRed, newGreen, newBlue));

    }
  }
}

///get class name for filter
std::string FThreshold::getName(){
  return "FThreshold";
}

#endif //FTHRESHOLD_H
