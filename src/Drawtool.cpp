#include "ColorData.h"
#include "Drawtool.h"

DrawTool::DrawTool(int red, int green, int blue){
  m_CurrentColor = new ColorData(red, green, blue);
  // can change mask setting in its subclass
  m_mask = new Mask(maskHeight, maskWidth);
}

DrawTool::~DrawTool(){
  delete m_CurrentColor;
  delete m_mask;
}

Mask const * const DrawTool::getMask() const {
  return m_mask;
}
