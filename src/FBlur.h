//
// FilterBlur.h
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.


#ifndef FBLUR_H
#define FBLUR_H
#include <string>
#include <vector>
#include <iomanip>
#include "Filter.h"
#include "ColorData.h"
typedef std::vector<float> kernelRow;
typedef std::vector<kernelRow> kernelType;
class PixelBuffer;
class FBlur : public Filter{
public:
  FBlur();
  ~FBlur();
  void applyFilter(PixelBuffer* imageBuffer);
  std::string getName();
  kernelType getKernel();
private:
  kernelType kernel;
};
#endif //FBLUR_H
