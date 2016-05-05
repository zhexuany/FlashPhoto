//
// FChannel.cpp
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.


#include "FChannel.h"
#include "PixelBuffer.h"

/**
This is the FChannel class, it is used for all the channel image filters .  applyFilter describes how this filter will be applied to every pixel in the image.
*/
FChannel::FChannel(){
}
FChannel::~FChannel(){
}
void FChannel::applyFilter(PixelBuffer* imageBuffer){
  int width = imageBuffer -> getWidth();
  int height = imageBuffer -> getHeight();
  ColorData parameter = getColorParameter();
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      ColorData currPixel = imageBuffer -> getPixel(i, j);
      ColorData newPixel = currPixel * parameter;
      imageBuffer -> setPixel(i, j, newPixel);
    }
  }
}

std::string FChannel::getName(){
  return "FChannel";
}

