#ifndef FCHANNEL_H
#define FCHANNEL_H
#include <string>
#include "Filter.h"
#include "ColorData.h"
class PixelBuffer;
class FChannel : public Filter{
public:
  FChannel();
  ~FChannel();
  void applyFilter(PixelBuffer* imageBuffer);
  std::string getName();
  void setFilterParameter(float parameter);
private:
  PixelBuffer* imageBuffer;
  ColorData white;
  ColorData black;
  float threshold;
};
#endif //FCHANNEL_H
