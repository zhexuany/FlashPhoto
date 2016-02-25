#include "SprayCan.h"
using std::cerr;
SprayCan::SprayCan(ColorData* toolColor, int radius)
    :DrawTool(toolColor, radius, radius){
  fillInfluence();
}

SprayCan::~SprayCan(){
}

void SprayCan::paint(int x, int y, int prevX, int prevY, PixelBuffer* buffer) {
  applyInfluence(x, y, buffer);
}

void SprayCan::applyInfluence(int x, int y, PixelBuffer* buffer) {
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

void SprayCan::fillInfluence(){
  Mask const * mask = getMask();
  float** influence = mask -> getInfluence();
  int width = mask -> getWidth();
  int height = mask -> getHeight();
  if(width != height){
    cerr << "Mask dimension does not agree\n";
  }
  float dx, dy, dist;
  int radius = width/2;
  for(int i = 0; i < width; i++){
    for(int j = 0; j < width; j++){
      dx = (radius - i)*(radius - i);
      dy = (radius - j)*(radius - j);
      dist  = sqrt(dx + dy);
      if(dist <= radius){
        influence[i][j] = ((radius - dist) / radius)*0.2;
      }else{
        influence[i][j] = 0.0;
      }
    }
  }

}

