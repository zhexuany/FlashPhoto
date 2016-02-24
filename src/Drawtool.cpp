#include "Drawtool.h"
using std::cout;
using std::cerr;
using std::endl;
// this cpp file may be not necessary. DrawTool serve as interface
DrawTool::DrawTool(ColorData* toolColor, int width, int height){
  m_toolColor = toolColor;
  m_mask = new Mask(width, height);
  fillInfluence();
}

DrawTool::~DrawTool(){
  delete m_toolColor;
  delete m_mask;
}

Mask const * DrawTool::getMask() const {
  return m_mask;
}

ColorData const * DrawTool::getToolColor() const{
  return m_toolColor;
}
void DrawTool::paint(int x, int y, PixelBuffer* buffer){
  ColorData const * currentColor = buffer -> getData();
  int height = m_mask-> getHeight();
  int width = m_mask -> getWidth();
  x -= width/2;
  y -= height/2;
  float ** influence = m_mask -> getInfluence();
  for(int i = 0; i < width; i++){
    for(int j = 0; i < height; j++){
      ColorData newColor = ((*m_toolColor)*influence[i][j])
                           + (*currentColor)*(1 - influence[i][j]);
      buffer -> setPixel(x++, y++, newColor);
    }
  }
}

void DrawTool::printfInfluence(){
  Mask const* mask = getMask();
  float** influence = mask -> getInfluence();
  int height = mask -> getHeight();
  int width = mask -> getWidth();
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      cout << influence[i][j] << " ";
    }
    cout << endl;
  }
}
/*This function need to be overloading in its derived class*/
void DrawTool::fillInfluence(){
  Mask const * mask = getMask();
  float** influence = mask -> getInfluence();
  int width = mask -> getWidth();
  int height = mask -> getHeight();
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      influence[i][j] = 0;
    }
  }
}
