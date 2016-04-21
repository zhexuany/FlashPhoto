//
// FEdgeDetection.h
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.
#ifndef FEDGEDETECTION_H
#define FEDGEDETECTION_H
#include <string>
#include <vector>
#include "FBlur.h"
#include "ColorData.h"
#include "PixelBuffer.h"
class FEdgeDetection : public FBlur{
public:
  FEdgeDetection();
  ~FEdgeDetection();
  std::string getName();
  kernelType buildKernel(int radius);
  //PixelBuffer ProcessImage(PixelBuffer* imageBuffer, float sigma, float lowThreshold, float hightThresold);
  //void PreProcessImage(float sigma);
  // void PostProcessImage();
  // void GaussianBlur();
  // void EdgeDetection();
  // void NonMaxSuppressin();
  // void Hystersis(float lowThreshold, float hightThresold);
private:
  const int size = 3;
};
#endif //FEDGEDETECTION_H
