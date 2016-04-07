//
// FilterSharpen.h
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.


#ifndef FSHARPEN_H
#define FSHARPEN_H
#include <string>
#include "FBlur.h"
#include "ColorData.h"
class PixelBuffer;
class FSharpen : public FBlur{
public:
  FSharpen();
  ~FSharpen();
  std::string getName();
private:
  const int size = 3;
  const float DEFAULT_FACTOR = 1000.0;
};
#endif //FSHARPEN_H
