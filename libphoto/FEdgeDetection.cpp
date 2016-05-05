//
// FEdgeDetection.cpp
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.
#include "FEdgeDetection.h"

/**
This is the FEdgeDetection class, it is used for all of the edge detection image filter.  This inherits from the FBlur class since the applyFilter function is the same due to kernels.
*/
FEdgeDetection::FEdgeDetection(){
}

FEdgeDetection::~FEdgeDetection(){
}

///create kernel matrix for edge detecting
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

///get class name for filter
std::string FEdgeDetection::getName(){
  return "FEdgeDetection";
}

