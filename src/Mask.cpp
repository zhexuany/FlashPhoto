#include "Mask.h"

Mask::Mask(int w, int h) : height(h), width(w) {
  influence = new double*[height];
  for(int i = 0; i < height; i++){
    influence[i]  = new float[width];
  }
}

Mask::~Mask(){
  for(int i = 0; i < height; i++){
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
float const ** const Mask::getInfluence() const{
  return influence;
}
