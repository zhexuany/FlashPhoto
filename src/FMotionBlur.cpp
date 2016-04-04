//
// FilterMotionBlur.h
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.


#include "FMotionBlur.h"
#include "ColorData.h"
#include "PixelBuffer.h"
FMotionBlur::FMotionBlur(){
  setFilterParameter(size);
  kernelType kernel(size, kernelRow(size));
  int direction = (int)getFloatParameter();
  for(int i = 0; i < size; i++){
    kernel[i][i] = 1.0/(float)size;
  }
  setKernel(kernel);
}


std::string FMotionBlur::getName(){
  return "FMotionBlur";
}
