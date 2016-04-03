#include "FSharpen.h"
#include "ColorData.h"
#include "PixelBuffer.h"

FSharpen::FSharpen(){
}

void FSharpen::applyFilter(PixelBuffer* imageBuffer){
}

std::string FSharpen::getName(){
  return "FSharpen";
}

void FSharpen::setFilterParameter(float parameter){
  this -> sharpen = parameter;
}
