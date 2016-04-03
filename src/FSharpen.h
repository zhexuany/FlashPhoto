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
  ColorData white;
  ColorData black;
  float threshold;
};
#endif //FSHARPEN_H
