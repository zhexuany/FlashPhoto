//
// FilterSharpen.cpp
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.


#include "FSharpen.h"
#include "ColorData.h"
#include "PixelBuffer.h"

FSharpen::FSharpen(){
  kernelType kernel(size, kernelRow(size));
  float factor = getFloatParameter();
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
    kernel[i][j] = -1.0;
    }
  }
  std::cout << factor;
  kernel[size/2][size/2] = 9.0 + factor/DEFAULT_FACTOR;
  setKernel(kernel);
}

std::string FSharpen::getName(){
  return "FSharpen";
}
