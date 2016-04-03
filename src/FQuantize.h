//
// FilterQuantize.h
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.


#ifndef FQUANTIZE_H
#define FQUANTIZE_H
#include <string>
#include <cmath>
#include "Filter.h"
#include "ColorData.h"
class PixelBuffer;
class FQuantize : public Filter{
public:
  FQuantize();
  ~FQuantize();
  void applyFilter(PixelBuffer* imageBuffer);
  std::string getName();
private:
};
#endif //FQUANTIZE_H
