//
// FMotionBlur.h
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.


#include "FMotionBlur.h"
#include "ColorData.h"
#include "PixelBuffer.h"
FMotionBlur::FMotionBlur(){
}

kernelType FMotionBlur::buildKernel(int radius){
  kernelType kernel = emptyFilter(radius);
  int size = kernel.size();
  int direction = getBlurDiection();
  switch (direction) {
    case DIR_N_S:
      for(int i = 0; i < size; i++){
        kernel[size/2][i] = 1/(float)size;
      }
      break;
    case DIR_E_W:
      for(int i = 0; i < size; i++){
        kernel[i][size/2] = 1/(float)size;
      }
      break;
    case DIR_NE_SW:
      for(int i = 0; i < size; i++){
        kernel[i][i] = 1/(float)size;
      }
      break;
    case DIR_NW_SE:
      for(int i = 0; i < size; i++){
        kernel[size - i - 1][i] = 1 /(float)size;
      }
      break;
  }
  return kernel;
}

std::string FMotionBlur::getName(){
  return "FMotionBlur";
}
