#ifndef CALLIGRAPHYPEN_H
#define CALLIGRAPHYPEN_H

#include "Drawtool.h"
#include "PixelBuffer.h"
#include "ColorData.h"

class CalligraphyPen : public DrawTool {
 public :
  CalligraphyPen(ColorData* toolColor, int height, int width);
  ~CalligraphyPen();
  void fillInfluence();
  string getName();
};

#endif // CALLIGRAPHYPEN_H
