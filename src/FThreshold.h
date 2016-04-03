//
// FilterThreshold.h
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.

#ifndef FTHRESHILD_H
#define FTHRESHILD_H
#include <string>
#include "Filter.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include <iostream>

class FThreshold : public Filter{
public:
  FThreshold();
  ~FThreshold();
  void applyFilter(PixelBuffer* imageBuffer);
  std::string getName();
};

#endif //FTHRESHILD_H
