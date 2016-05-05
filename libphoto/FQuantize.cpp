//
// FQuantize.cpp
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.


#include "FQuantize.h"
#include "ColorData.h"
#include "PixelBuffer.h"

/**
This is the FQuantize class, it is used for the quantize image filters.  This does not use kernels so it only has to deal with applying the filter
*/
FQuantize::FQuantize(){}
FQuantize::~FQuantize(){}
void FQuantize::applyFilter(PixelBuffer* imageBuffer){
  int width = imageBuffer -> getWidth();
  int height = imageBuffer -> getHeight();
  int quantize_bins = (int)getFloatParameter() - 1;
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      ColorData currPixel = imageBuffer -> getPixel(i, j);
      float newRed = std::round(currPixel.getRed()*quantize_bins)/(float)quantize_bins;
      float newGreen = std::round(currPixel.getGreen()*quantize_bins)/(float)quantize_bins;

      float newBlue = std::round(currPixel.getBlue()*quantize_bins)/(float)quantize_bins;
      imageBuffer -> setPixel(i, j, ColorData(newRed, newGreen, newBlue));
    }
  }
}

std::string FQuantize::getName(){
  return "FQuantize";
}

