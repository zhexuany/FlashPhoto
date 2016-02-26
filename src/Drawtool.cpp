#include "Drawtool.h"
using std::cout;
using std::cerr;
using std::endl;

// this cpp file may be not necessary. DrawTool serve as interface
DrawTool::DrawTool(ColorData* toolColor, int width, int height){
  m_toolColor = toolColor;
  m_mask = new Mask(width, height);
  allowDrag = true;
  fillInfluence();
}
DrawTool::DrawTool(int width, int height){
  m_toolColor = new ColorData(0, 0, 0);
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
void DrawTool::setToolColor(ColorData* color){
  m_toolColor = color;
}
void DrawTool::paint(int x, int y, int prevX, int prevY, PixelBuffer* buffer){
    applyInfluence(x, y, buffer);
    float xIncrement = prevX;
    float yIncrement = prevY;
    float distance = sqrt(std::abs(pow(x-prevX, 2) - pow(y-prevY,2)));
    float xDiff = (x-prevX)/distance;
    float yDiff = (y-prevY)/distance;
    int i;
    for (i = 0; i < distance; i++) {
        applyInfluence(xIncrement, yIncrement, buffer);
        xIncrement += xDiff;
        yIncrement += yDiff;
    }
}

void DrawTool::applyInfluence(int x, int y, PixelBuffer* buffer) {
  int height = m_mask-> getHeight();
  int width = m_mask -> getWidth();
  int bufferHeight = buffer -> getHeight();
  x -= width/2;
  y = bufferHeight - y - height/2;
  float ** influence = m_mask -> getInfluence();
  // printfInfluence();
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      ColorData currentColor = buffer -> getPixel(x+i, y+j);
      ColorData newColor =((*m_toolColor)*influence[i][j])
                          + currentColor*(1 - influence[i][j]);
      buffer -> setPixel(x + i, y + j, newColor);
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
      influence[i][j] = 1;
    }
  }
}
