#ifndef SPRAYCAN_H
#define SPRAYCAN_H
#include "Drawtool.h"
class SprayCan : public DrawTool{
 public :
  SprayCan(ColorData* toolColor, int radius);
  ~SprayCan();
  void fillInfluence();
  void paint(int x, int y, int prevX, int prevY, PixelBuffer* buffer);
};

#endif // SPRAYCAN_H
