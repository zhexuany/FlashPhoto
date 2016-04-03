//
// FilterSharpen.cpp
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.


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
