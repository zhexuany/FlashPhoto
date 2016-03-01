#ifndef WATERCOLOR_H
#define WATERCOLOR_H

#include "Drawtool.h"
#include "PixelBuffer.h"
#include "ColorData.h"

class WaterColor : public DrawTool {
 public :
  WaterColor(ColorData* toolColor, int radius);
  ~WaterColor();
  void fillInfluence();
};

#endif // WATERCOLOR_H
