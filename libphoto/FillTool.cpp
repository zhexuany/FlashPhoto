#include "FillTool.h"
/**
This is the FillTool class, it is used for all of custom fill tool.
*/
///For function descriptions please see the Blur class
FillTool::FillTool(ColorData* toolColor, int width, int height)
    : DrawTool(toolColor, width, height){
  fillInfluence();
  allowDrag = false;
}

FillTool::~FillTool(){
}

void FillTool::fillInfluence(){
  Mask const * mask = getMask();
  float** influence = mask -> getInfluence();
  int width = mask -> getWidth();
  int height = mask -> getHeight();
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
        influence[i][j] = 1.0;
    }
  }
}

///Special paint override since this technically applies to the entire buffer, not just the mask area
void FillTool::paint(int x, int y, int prevX, int prevY, PixelBuffer* buffer) {
  applyInfluence(x, y, buffer);
  buffer -> setBackgroundColor(m_toolColor);
}

///Apply to the entire buffer, the mask should be equivalent to the buffer
void FillTool::applyInfluence(int x, int y, PixelBuffer* buffer){
  Mask const * mask = getMask();
  int height = mask -> getHeight();
  int width = mask -> getWidth();
  ColorData backgroundColor = buffer -> getBackgroundColor();
  ColorData currentPixelColor;
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      currentPixelColor = buffer -> getPixel(i,j);
      if(compareColorData(backgroundColor, currentPixelColor)) {
        buffer -> setPixel(i, j, *m_toolColor);
	}
    }
  }
}

///Tells you if x and y are equal colors
bool FillTool::compareColorData(ColorData x, ColorData y) {
	if (x.getRed() == y.getRed() && x.getBlue() == y.getBlue() && x.getGreen() == y.getGreen()) {
		return true;
	} else {
		return false;
	}
}

string FillTool::getName(){
  return "FillTool";
}
