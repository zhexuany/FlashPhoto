//
// FBlur.h
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.
#include "FBlur.h"
#include "ColorData.h"
#include "PixelBuffer.h"

FBlur::FBlur(){}
FBlur::~FBlur(){}

kernelType FBlur::buildKernel(int radius){
  return boxFilter(radius);
}

void FBlur::applyFilter(PixelBuffer* imageBuffer){
  // if kernel is already initialized, do not need initialize it again.
  kernel = buildKernel(std::round(getFloatParameter()));

  // printKernel();

  if(getName() == "FEdgeDetection"){
    imageBuffer -> convertToLuminance();
  }

  int width = imageBuffer -> getWidth();
  int height = imageBuffer -> getHeight();
  //create a new pixel buffer for storing the convolution result.
  PixelBuffer* newImageBuffer
    = new PixelBuffer(width, height, imageBuffer -> getBackgroundColor());
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      float newRed = 0;
      float newGreen = 0;
      float newBlue = 0;
      for(size_t filterI = 0; filterI < kernel.size(); filterI++){
        for(size_t filterJ = 0; filterJ < kernel[filterI].size(); filterJ++){
          //The location imageI and imageJ is calculated so that
          //for the center element of the filter it'll be i, j
          int imageI = (i - kernel.size()/2 + filterI + width) % width;
          int imageJ = (j - kernel[filterI].size()/2 + filterJ + height) % height;
          ColorData currPixel = imageBuffer -> getPixel(imageI, imageJ);
          newRed += currPixel.getRed() * kernel[filterI][filterJ];
          newGreen += currPixel.getGreen()*kernel[filterI][filterJ];
          newBlue += currPixel.getBlue()*kernel[filterI][filterJ];
        }
      }
      ColorData newPixel = ColorData(newRed, newGreen, newBlue);
      newPixel = newPixel.clampedColor();
      newImageBuffer -> setPixel(i, j, newPixel);
    }
  }
  newImageBuffer -> copyPixelBuffer(newImageBuffer, imageBuffer);
}

kernelType FBlur::emptyFilter(int radius){
  //any integer divied by 2 will give us another integer.
  //multiply it by 2 and puls 1 will give us a odd number
  int kSize = 2*(radius/2)+1;
  kernelType filter(kSize, kernelRow(kSize));
  for (size_t filterI = 0; filterI < filter.size(); filterI++) {
    for (size_t filterJ = 0; filterJ < filter[filterI].size(); filterJ++){
      filter[filterI][filterJ] = 0;
    }
  }
  return filter;
}

kernelType FBlur::boxFilter(int radius){
  //any integer divied by 2 will give us another integer.
  //multiply it by 2 and puls 1 will give us a odd number
  int kSize = 2*(radius/2)+1;
  kernelType filter(kSize, kernelRow(kSize));
  float factor =(float) kSize*kSize;
  for (size_t filterI = 0; filterI < filter.size(); filterI++) {
    for (size_t filterJ = 0; filterJ < filter[filterI].size(); filterJ++){
      filter[filterI][filterJ] = 1/factor;
    }
  }
  return filter;
}
//TODO need fix a bug on this function
kernelType FBlur::GaussianBlur(float sigma){
  int kSize = 2*std::round(std::sqrt(-std::log(0.3)*2*sigma*sigma)) + 1;
  float squareSigma = sigma*sigma;
  float constant = 2 * M_PI * squareSigma;
  kernelType gaussianKernel(kSize, kernelRow(kSize));
  for (int i = 0; i <= kSize; i++) {
    for (int j = 0; j <= kSize; j++) {
      gaussianKernel[i][j]
        = (1 / constant) * std::exp(-(i * i + j * j ) / (squareSigma));
    }
  }
  return gaussianKernel;
}

void FBlur::printKernel(){
  for(size_t i = 0; i < kernel.size(); i++){
    for(size_t j = 0; j < kernel.size(); j++){
      std::cout << kernel[i][j] << "   ";
    }
    std::cout << "\n";
  }
}

std::string FBlur::getName(){
  return "FBlur";
}
