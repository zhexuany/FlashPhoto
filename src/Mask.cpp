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

/*
* \Get the height of the mask
* \none
* \returns the height of the mask
*/
int Mask::getHeight() const{
  return height;
}
/*
* \Get the width of the mask
* \none
* \returns the width of the mask
*/
int Mask::getWidth() const{
  return width;
}

/*
* \Get the influence array of the mask
* \none
* \returns a pointer to the array of influence for the mask
*/
float** Mask::getInfluence() const{
  return influence;
}
