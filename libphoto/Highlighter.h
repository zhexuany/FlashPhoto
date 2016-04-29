#ifndef HIGHLIGHTER_H
#define  HIGHLIGHTER_H

#include "Drawtool.h"
#include "PixelBuffer.h"
#include "ColorData.h"
class Highlighter : public DrawTool {
 public:
  Highlighter(ColorData* toolColor, int width, int height);
  ~Highlighter();
  void fillInfluence();
  void applyInfluence(int x, int y, PixelBuffer* buffer);
  string getName();
};
#endif
