#include "FSpecial.h"
FSpecial::FSpecial(){
}

FSpecial::~FSpecial(){
}
void FSpecial::applyFilter(PixelBuffer* imageBuffer){
  imageBuffer -> convertToLuminance();
}

std::string FSpecial::getName(){
  return "FSpecial";
}
