//
// FSpecial.cpp
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.


#include "FSpecial.h"
/**
This is the FSharpen class, it is used for the special filter.  This turns the image to grayscale.
*/
FSpecial::FSpecial(){
}

FSpecial::~FSpecial(){
}

/*
 *\parama imageBuffer:current canvas buffer
 */
void FSpecial::applyFilter(PixelBuffer* imageBuffer){
  imageBuffer -> convertToLuminance();
}

std::string FSpecial::getName(){
  return "FSpecial";
}
