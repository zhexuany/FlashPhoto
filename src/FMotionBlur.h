//
// FilterMotionBlur.h
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.


#ifndef FMOTIONBLUR_H
#define FMOTIONBLUR_H
#include <string>
#include "Filter.h"
#include "ColorData.h"
class PixelBuffer;
class FMotionBlur : public Filter{
public:
  FMotionBlur();
  ~FMotionBlur();
  void applyFilter(PixelBuffer* imageBuffer);
  std::string getName();
  void setFilterParameter(float parameter);
private:
  PixelBuffer* imageBuffer;
  ColorData white;
  ColorData black;
  float threshold;
};
#endif //FMOTIONBLUR_H
