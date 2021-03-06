//
// FSaturation.h
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.


#ifndef FSATURATION_H
#define FSATURATION_H
#include <string>
#include "Filter.h"
#include "ColorData.h"
#include "PixelBuffer.h"
class FSaturation : public Filter{
public:
  FSaturation();
  ~FSaturation();
  void applyFilter(PixelBuffer* imageBuffer);
  std::string getName();
};
#endif //FSATURATION_H
