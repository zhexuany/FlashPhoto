#ifndef PEN_H
#define PEN_H
#include "Drawtool.h"

class Pen : public DrawTool {
 public:
  Pen(ColorData* toolColor, int height, int width);
  ~Pen();
  void fillInfluence();
};
#endif
