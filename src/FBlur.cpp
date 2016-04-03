//
// FilterBlur.h
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.


#include "FBlur.h"
#include "ColorData.h"
#include "PixelBuffer.h"
FBlur::FBlur(){
}

void FBlur::applyFilter(PixelBuffer* imageBuffer){
  kernel =  getKernel();
  int width = imageBuffer -> getWidth();
  int height = imageBuffer -> getHeight();
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      float newRed = 0;
      float newGreen = 0;
      float newBlue = 0;
      for(size_t row = 0; row < kernel.size(); row++){
        for(size_t col = 0; col < kernel[row].size(); col++){
          int imageI = (i - kernel.size()/2 + row + width) % width;
          int imageJ = (j - kernel[row].size()/2 + col + height) % height;
          ColorData currPixel = imageBuffer -> getPixel(imageI, imageJ);
          newRed += currPixel.getRed() * kernel[row][col];
          newBlue += currPixel.getBlue() * kernel[row][col];
          newGreen += currPixel.getGreen()*kernel[row][col];
        }
      }
      ColorData newPixel = ColorData(newRed, newGreen, newBlue);
      //truncate values smaller than 0.0 and larger than 1.0
      newPixel = newPixel.clampedColor();
      imageBuffer -> setPixel(i, j, newPixel);
    }
  }
}

kernelType FBlur::getKernel(){
  kernelRow row;
  int radius = std::ceil(getFloatParameter());
  //any integer divied by 2 will give us another integer.
  //multiply it by 2 and puls 1 will give us a odd number
  int kSize = 2*radius/2+1;
  kernelType filter(kSize, kernelRow(kSize));
  float factor =(float) kSize*kSize;
  for (size_t row = 0; row < filter.size(); row++) {
    for (size_t col = 0; col < filter[row].size(); col++){
      filter[row][col] = 1/factor;
    }
  }
  return filter;
}

std::string FBlur::getName(){
  return "FBlur";
}
