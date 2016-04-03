//
// FilterEdgeDetection.h
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.


#ifndef FEDGEDETECTION_H
#define FEDGEDETECTION_H
#include <string>
#include "Filter.h"
#include "ColorData.h"
class PixelBuffer;
class FEdgeDetection : public Filter{
public:
  FEdgeDetection();
  ~FEdgeDetection();
  void applyFilter(PixelBuffer* imageBuffer);
  std::string getName();
  void setFilterParameter(float parameter);
private:
  PixelBuffer* imageBuffer;
  ColorData white;
  ColorData black;
  float threshold;
};
#endif //FEDGEDETECTION_H
