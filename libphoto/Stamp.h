#ifndef STAMP_H
#define STAMP_H

#include "Drawtool.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include <stdlib.h>

class Stamp : public DrawTool {
 public :
  Stamp(PixelBuffer* newBuffer, int stampWidth, int stampHeight);
  ~Stamp();
  void fillInfluence();
  void applyInfluence(int x, int y, PixelBuffer* buffer);
  string getName();
};

#endif
