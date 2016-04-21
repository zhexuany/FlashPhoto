//
// FilterFactory.h
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.
#ifndef FILTER_FACTORY_H
#define FILTER_FACTORY_H
#include <vector>
class Filter;
class PixelBuffer;
class FilterFactory {
public:
  enum FILTERS{
      FILTER_THRESHOLD = 0,
      FILTER_CHANNEL = 1,
      FILTER_SATURATION = 2,
      FILTER_QUANTIZE = 3,
      FILTER_BLUR = 4,
      FILTER_MOTION_BLUR = 5,
      FILTER_SHARPEN = 6,
      FILTER_DETECT_EDGES = 7,
      FILTER_SPECIAL = 8,
      NUMFILTERS = 9
  };
  static int getNumFilters();
  static Filter* createFilter(int filterID);
};
#endif // FILTER_FACTORY_H
