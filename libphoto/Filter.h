//
// Filter.h
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.

#ifndef FILTER_H
#define FILTER_H
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include "ColorData.h"
class PixelBuffer;
class Filter {
public:
  Filter(){};
  virtual ~Filter(){};
  virtual void applyFilter(PixelBuffer* imageBuffer) = 0;
  virtual std::string getName() = 0;
  virtual void setFilterParameter(float parameter){ f_parameter = parameter;}
  virtual void setFilterParameter(ColorData parameter){ c_parameter = parameter;}
  void setBlurDirection(int direction){blurDirection = direction;}
  float getFloatParameter(){ return f_parameter;}
  ColorData getColorParameter(){return c_parameter;}
  int getBlurDiection(){return blurDirection;}
private:
  float f_parameter;
  ColorData c_parameter;
  int blurDirection;
};
#endif //FILTER_H
