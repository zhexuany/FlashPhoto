#ifndef FTHRESHILD_H
#define FTHRESHILD_H
#include <string>
#include "Filter.h"
#include "ColorData.h"
#include <iostream>
class PixelBuffer;
class FThreshold : public Filter{
public:
  FThreshold();
  ~FThreshold();
  void applyFilter(PixelBuffer* imageBuffer);
  std::string getName();
  void setFilterParameter(float parameter);
private:
  ColorData white;
  ColorData black;
  float threshold;
};
#endif //FTHRESHILD_H
