#ifndef FQUANTIZE_H
#define FQUANTIZE_H
#include <string>
#include "Filter.h"
#include "ColorData.h"
class PixelBuffer;
class FQuantize : public Filter{
public:
  FQuantize();
  ~FQuantize();
  void applyFilter(PixelBuffer* imageBuffer);
  std::string getName();
  void setFilterParameter(float parameter);
private:
  PixelBuffer* imageBuffer;
  ColorData white;
  ColorData black;
  float threshold;
};
#endif //FQUANTIZE_H
