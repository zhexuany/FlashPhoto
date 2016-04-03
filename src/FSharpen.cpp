#include "FSharpen.h"
#include "ColorData.h"
#include "PixelBuffer.h"

FSharpen::FSharpen(){
}

void FSharpen::applyFilter(PixelBuffer* imageBuffer){
  int width = imageBuffer -> getWidth();
  int height = imageBuffer -> getHeight();
}

std::string FSharpen::getName(){
  return "FSharpen";
}

void FSharpen::setFilterParameter(float parameter){
  this -> sharpen = parameter;
}
