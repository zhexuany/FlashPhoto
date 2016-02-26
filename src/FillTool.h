#ifndef FILLTOOL_H
#define FILLTOOL_H
#include "Drawtool.h"
#include "PixelBuffer.h"
#include "ColorData.h"
// mask for eraser is cycle with 21 pixel
class FillTool : public DrawTool{
public:
  FillTool(ColorData* toolColor, int height, int width);
  ~FillTool();
  void print(int x, int y, int prevX, int prevY, PixelBuffer* buffer);
  void applyInfluence(int x, int y, PixelBuffer* buffer);
  void fillInfluence();
private:
  bool compareColorData(ColorData x, ColorData y);
};

#endif
