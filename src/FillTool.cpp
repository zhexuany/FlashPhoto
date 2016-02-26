#include "FillTool.h"

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

void FillTool::print(int x, int y, int prevX, int prevY, PixelBuffer* buffer) {
  applyInfluence(x, y, buffer);
  buffer -> setBackgroundColor(m_toolColor);
}

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

bool FillTool::compareColorData(ColorData x, ColorData y) {
	if (x.getRed() == y.getRed() && x.getBlue() == y.getBlue() && x.getGreen() == y.getGreen()) {
		return true;
	} else {
		return false;
	}
}

