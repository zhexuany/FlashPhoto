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
#include "FSpecial.h"
#include "PixelBuffer.h"
/**
This is the FilterFactory class, it is used to control the selection logic for filters.
*/
int FilterFactory::getNumFilters() {return NUMFILTERS;}
/**
 Creates a filter for the given ID \n
 param filterID which filter you want to created \n
 *return a filter instance \n
 */
Filter* FilterFactory::createFilter(int filterID){
    Filter* filter = NULL;
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
        case FILTER_SPECIAL:
            filter = new FSpecial();
            break;
    }
    return filter;
}
