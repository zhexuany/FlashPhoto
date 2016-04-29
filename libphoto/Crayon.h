#ifndef CRAYON_H
#define CRAYON_H

#include "Drawtool.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include <stdlib.h>

class Crayon : public DrawTool {
 public :
  Crayon(ColorData* toolColor, int radius);
  ~Crayon();
  void fillInfluence();
  string getName();
};

#endif
