#ifndef ERASER_H
#define ERASER_H
#include "Drawtool.h"
#include "PixelBuffer.h"
#include "ColorData.h"
class CycleMask;
// mask for eraser is cycle with 21 pixel
class Eraser : public DrawTool{
public:
  Eraser(int radius);
  ~Eraser();
  void paint(int x, int y, PixelBuffer* buffer);
  void fillInfluence();
};

#endif
