#ifndef FILTER_H
#define FILTER_H
#include <string>
#include "PixelBuffer.h"
class Filter {
public:
  virtual void applyFilter(PixelBuffer* imageBuffer) = 0;
  virtual std::string getName() = 0;
  virtual void setFilterParameter(float parameter) = 0;
};
#endif //FILTER_H
