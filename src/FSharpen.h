//
// FilterSharpen.h
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.


#ifndef FSHARPEN_H
#define FSHARPEN_H
#include <string>
#include "Filter.h"
#include "ColorData.h"
class PixelBuffer;
class FSharpen : public Filter{
public:
  FSharpen();
  ~FSharpen();
  void applyFilter(PixelBuffer* imageBuffer);
  std::string getName();
  void setFilterParameter(float parameter);
private:
  float sharpen;
};
#endif //FSHARPEN_H
