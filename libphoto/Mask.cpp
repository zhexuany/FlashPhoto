#include "Mask.h"

/**
This is the mask class.  This describes the basic format for our DrawTools.  Every drawtool should have a mask
*/
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

/**
 Get the height of the mask \n
* none \n
* returns the height of the mask \n
*/
int Mask::getHeight() const{
  return height;
}
/**
 Get the width of the mask \n
* none \n
* returns the width of the mask \n
*/
int Mask::getWidth() const{
  return width;
}

/**
 Get the influence array of the mask \n
* none \n
* returns a pointer to the array of influence for the mask \n
*/
float** Mask::getInfluence() const{
  return influence;
}
