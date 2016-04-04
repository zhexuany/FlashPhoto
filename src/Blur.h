#ifndef BLUR_H
#define BLUR_H

#include "Drawtool.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include <stdlib.h>

class Blur : public DrawTool {
 public :
  Blur(int radius);
  ~Blur();
  void fillInfluence();
  void applyInfluence(int x, int y, PixelBuffer* buffer);
};


#endif
