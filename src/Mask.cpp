#include "Mask.h"

Mask::Mask(int w, int h) : weight(w), height(h){
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

float const ** const Mask::getInfluence() const{
  return influence;
}
