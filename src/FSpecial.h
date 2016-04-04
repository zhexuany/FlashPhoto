//
// FilterSharpen.h
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.

#ifndef FSEPCIAL_H
#define FSEPCIAL_H
#include <string>
#include "Filter.h"
#include "ColorData.h"
#include "PixelBuffer.h"
class PixelBuffer;
class FSpecial : public Filter{
public:
  FSpecial();
  ~FSpecial();
  void applyFilter(PixelBuffer* imageBuffer);
  std::string getName();
};

#endif // FSEPCIAL_H
