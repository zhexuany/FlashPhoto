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
  void setFilterParameter(float threshold);
private:
  ColorData white;
  ColorData black;
  float threshold;
};
#endif //FSATURATION_H
