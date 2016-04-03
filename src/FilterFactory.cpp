//
// FilterFactory.cpp
//
// created by Zhexuan Yang on 01/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.

#include "FilterFactory.h"
#include "FBlur.h"
#include "FChannel.h"
#include "FEdgeDetection.h"
#include "FMotionBlur.h"
#include "FQuantize.h"
#include "FSharpen.h"
#include "FThreshold.h"
#include "FSaturation.h"
#include "PixelBuffer.h"
//TODO special tool

int FilterFactory::getNumFilters() {return NUMFILTERS;}

Filter* FilterFactory::createFilter(int filterID){
    Filter* filter;
    switch(filterID) {
        case FILTER_THRESHOLD:
            filter = new FThreshold();
            break;
        case FILTER_CHANNEL:
            filter = new FChannel();
            break;
        case FILTER_SATURATION:
            filter = new FSaturation();
            break;
        case FILTER_QUANTIZE:
            filter = new FQuantize();
            break;
        case FILTER_BLUR:
            filter = new FBlur();
            break;
        case FILTER_MOTION_BLUR:
            filter = new FMotionBlur();
            break;
        case FILTER_SHARPEN:
            filter = new FSharpen();
            break;
        case FILTER_DETECT_EDGES:
            filter = new FEdgeDetection();
            break;
    }
    return filter;
}
