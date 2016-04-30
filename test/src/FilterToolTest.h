#include <cxxtest/TestSuite.h>
#include "PixelBuffer.h"
#include "ColorData.h"
#include "FEdgeDetection.h"
#include "FSaturation.h"
#include "FThreshold.h"
#include "FilterFactory.h"
#include "FBlur.h"
#include "FMotionBlur.h"
#include "FSharpen.h"
#include "FChannel.h"
#include "FQuantize.h"
#include "FSpecial.h"
#include "Filter.h"
#include "ImageHandler.h"


class FilterToolTest : public CxxTest::TestSuite {
  public:
  void setUp(){
  }

  void tearDown(){
  }
};
