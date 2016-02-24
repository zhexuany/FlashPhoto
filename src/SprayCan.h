#ifndef SPRAYCAN_H
#define SPRAYCAN_H
#include "Drawtool.h"
#include "PixelBuffer.h"
#include "ColorData.h"

#include "Drawtool.h"
class SprayCan : public DrawTool{
 public :
  SprayCan(ColorData* toolColor, int radius);
  ~SprayCan();
  void fillInfluence();
};

#endif // SPRAYCAN_H
