//
// FilterMotionBlur.h
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.


#ifndef FMOTIONBLUR_H
#define FMOTIONBLUR_H
#include <string>
#include "FBlur.h"
#include "ColorData.h"
class PixelBuffer;
class FMotionBlur : public FBlur{
public:
  FMotionBlur();
  ~FMotionBlur();
  std::string getName();
private:
  const int size = 9;
};
#endif //FMOTIONBLUR_H
