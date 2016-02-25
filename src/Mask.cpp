#include "Mask.h"

Mask::Mask(int w, int h) : height(h), width(w) {
  influence = new float *[width];
  for(int i = 0; i < width; i++){
    influence[i]  = new float[height];
  }
}

Mask::~Mask(){
  for(int i = 0; i < width; i++){
    delete [] influence[i];
  }
  delete [] influence;
}

int Mask::getHeight() const{
  return height;
}
int Mask::getWidth() const{
  return width;
}
// influence need fill in different draw tool classes
float** Mask::getInfluence() const{
  return influence;
}
