#ifndef FBLUR_H
#define FBLUR_H
#include <string>
#include "Filter.h"
#include "ColorData.h"
class PixelBuffer;
class FBlur : public Filter{
public:
  FBlur();
  ~FBlur();
  void applyFilter(PixelBuffer* imageBuffer);
  std::string getName();
  void setFilterParameter(float parameter);
private:
  PixelBuffer* imageBuffer;
  ColorData white;
  ColorData black;
  float threshold;
};
#endif //FBLUR_H
