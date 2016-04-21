#include "Highlighter.h"

Highlighter::Highlighter(ColorData* toolColor, int width, int height)
    : DrawTool(toolColor, width, height){
  fillInfluence();
}

Highlighter::~Highlighter(){
}
void Highlighter::fillInfluence(){
  Mask const * mask = getMask();
  float** influence = mask -> getInfluence();
  int width = mask -> getWidth();
  int height = mask -> getHeight();
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){
      influence[i][j] = 0.4;
    }
  }
}

void Highlighter::applyInfluence(int x, int y, PixelBuffer* buffer){
    ColorData const * toolColor = getToolColor();
    Mask const * mask = getMask();
    int height = mask-> getHeight();
    int width = mask -> getWidth();
    int bufferHeight = buffer -> getHeight();
    x -= width/2;
    y = bufferHeight - y - height/2;
    float ** influence = mask -> getInfluence();
    // printfInfluence();
    for(int i = 0; i < width; i++){
      for(int j = 0; j < height; j++){
        ColorData currentColor = buffer -> getPixel(x+i, y+j);
        float intensity = influence[i][j]* currentColor.getLuminance();
        ColorData newColor = (*toolColor)*intensity
          + currentColor*(1.0 - intensity);
        buffer -> setPixel(x+i, y+j, newColor);
      }
    }
}
