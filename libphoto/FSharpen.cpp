//
// FSharpen.cpp
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.


#include "FSharpen.h"
#include "ColorData.h"
#include "PixelBuffer.h"
/**
This is the FSharpen class, it is used for the quantize image filters.  It inherits from the FBlur class, so it only needs to buildKernel, not apply it.
*/
FSharpen::FSharpen(){}
FSharpen::~FSharpen(){}
/**
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

///get class name for filter
std::string FSharpen::getName(){
  return "FSharpen";
}
