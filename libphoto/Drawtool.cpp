#include "Drawtool.h"
using std::cout;
using std::cerr;
using std::endl;

/**
This is the DrawTool class.  Every DrawTool inherits from here, this is used for all pens in the UI.
* Overloaded constructor taking in a color \n
* color for tool, width of drawtool, height of drawtool \n
* constructor \n
*/
DrawTool::DrawTool(ColorData* toolColor, int width, int height){
  m_toolColor = toolColor;
  m_mask = new Mask(width, height);
  allowDrag = true;
  fillInfluence();
}
/**
* Overloaded constructor with a default color of black \n
* width of drawtool, height of drawtool \n
* constructor \n
*/
DrawTool::DrawTool(int width, int height){
  m_toolColor = new ColorData(0, 0, 0);
  m_mask = new Mask(width, height);
  fillInfluence();

}

DrawTool::DrawTool(PixelBuffer* newBuffer, int width, int height){
  imageBuffer = newBuffer;
  m_toolColor = new ColorData(0, 0, 0);
  m_mask = new Mask(width, height);
  fillInfluence();

}
/**
 Destructor for the drawtool \n
* none \n
* destructor \n
*/
DrawTool::~DrawTool(){
  delete m_toolColor;
  delete m_mask;
}
/**
 Gets the current mask for the draw tool \n
* none \n
* Returns a const pointer to the mask \n
*/
Mask const * DrawTool::getMask() const {
  return m_mask;
}
/**
 Gets the tool color \n
* none \n
* Const pointer to the ColorData of the current tool \n
*/
ColorData const * DrawTool::getToolColor() const{
  return m_toolColor;
}
/**
 Sets the tool color \n
* The ColorData to change the tool to \n
* void \n
*/
void DrawTool::setToolColor(ColorData* color){
  m_toolColor = color;
}
/**
 Apply the mask to the buffer at x,y and fill gap from prevX, prevY \n
* x coord, y coord, previous x coord, previous y coord, the pixel buffer to draw on \n
* void \n
*/
void DrawTool::paint(int x, int y, int prevX, int prevY, PixelBuffer* buffer){
    applyInfluence(x, y, buffer);
    float xIncrement = prevX;
    float yIncrement = prevY;
    float distance = sqrt(std::abs(pow(x-prevX, 2) + pow(y-prevY,2)));
    float xDiff = (x-prevX)/distance;
    float yDiff = (y-prevY)/distance;
    for (int i = 0; i < distance; i++) {
        applyInfluence(xIncrement, yIncrement, buffer);
        xIncrement += xDiff;
        yIncrement += yDiff;
    }
}
/**
 Apply the mask to the buffer centered at x,y \n
* x coord, y coord, buffer to draw on \n
* void \n
*/
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

/**
 Print the influence of the current mask \n
* none \n
* void \n
*/
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
/**
 Virtual function to set influence on the mask, should be overrode in sub class \n
* none \n
* void \n
*/
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

string DrawTool::getName(){
  return "DrawTool";
}
