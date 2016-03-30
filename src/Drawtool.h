#ifndef DRAWTOOL_H
#define DRAWTOOL_H
#include "PixelBuffer.h"
#include "Mask.h"
#include "ColorData.h"
#include <iostream>
#include <cmath>
#include <complex>
class DrawTool {
public:
    DrawTool(ColorData* toolColor, int width, int height);
    DrawTool(int width, int height);
    DrawTool(PixelBuffer* newBuffer, int width, int height);
    virtual ~DrawTool();
    virtual void fillInfluence();
    virtual void paint(int x, int y, int prevX, int prevY, PixelBuffer* buffer);
    virtual void applyInfluence(int x, int y, PixelBuffer* buffer);
    Mask const * getMask() const;
    ColorData const * getToolColor() const;
    void setToolColor(ColorData* color);
  // printfInfluence use for debuging
    void printfInfluence();
    bool allowDrag;
protected:
    Mask* m_mask;
    ColorData* m_toolColor;
    PixelBuffer* imageBuffer;
};
#endif
