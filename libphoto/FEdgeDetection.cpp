//
// FEdgeDetection.cpp
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.
#include "FEdgeDetection.h"

FEdgeDetection::FEdgeDetection(){
}

kernelType FEdgeDetection::buildKernel(int radius){
  setFilterParameter(size);
  kernelType kernel(size, kernelRow(size));
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      kernel[i][j] = -1.0;
    }
  }
  kernel[size/2][size/2] = 8.0;
  return kernel;
}
std::string FEdgeDetection::getName(){
  return "FEdgeDetection";
}

