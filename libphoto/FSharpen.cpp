//
// FSharpen.cpp
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.


#include "FSharpen.h"
#include "ColorData.h"
#include "PixelBuffer.h"

FSharpen::FSharpen(){}
FSharpen::~FSharpen(){}
/*
 *\parama radius: the size of the kernel matrix
 *\return a kernel matirx will userd for convolution-based filter
 */
kernelType FSharpen::buildKernel(int radius){
  kernelType kernel(size, kernelRow(size));
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      kernel[i][j] = -1.0;
    }
  }
  kernel[size/2][size/2] = 9.0 + getFloatParameter() / DEFAULT_FACTOR;
  return kernel;
}

std::string FSharpen::getName(){
  return "FSharpen";
}
