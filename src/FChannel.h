#ifndef FCHANNEL_H
#define FCHANNEL_H
#include <string>
#include "Filter.h"
#include "ColorData.h"

class FChannel : public Filter{
public:
  FChannel();
  ~FChannel();
  void applyFilter(PixelBuffer* imageBuffer);
  std::string getName();
};

#endif //FCHANNEL_H
