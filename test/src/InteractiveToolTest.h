#ifndef __PENTEST_H
#define __PENTEST_H

#include <cxxtest/TestSuite.h>
#include "PixelBuffer.h"
#include "ColorData.h"
#include "DrawTool.h"
#include "Pen.h"
#include "Eraser.h"
#include "Mask.h"
#include "SprayCan.h"
#include "Blur.h"
#include "Crayon.h"
#include "FillTool.h"
#include "Highlighter.h"
#include "Stamp.h"
#include "CalligraphyPen.h"
#include "WaterColor.h"

//
// A simple test suite: Just inherit CxxTest::TestSuite and write tests!
//


class InteractiveToolTest : public CxxTest::TestSuite {
  PixelBuffer *buffer;
  ColorData* color;
  const Mask * mask;
  int size;
public:
  //declare a temporary Pixel buffer for testing
  void setUp(){
    size = 30;
    buffer = new PixelBuffer(50, 50, ColorData(0, 0, 0));
    color = new ColorData(0, 0, 0);
  }

  //delete buffer
  void tearDown(){
    delete buffer;
  }

  void testBlur(){
    DrawTool* blur = new Blur(30);
    mask = blur -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 30);
  }

  void testStamp(){
    //PixelBuffer* init = new PixelBuffer(0, 0, *color);
    //DrawTool* stamp = new Stamp(init, 0, 0);
  }

  void testCrayon(){
    DrawTool* crayon = new Crayon(color, 20);
    mask = crayon -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 20);
  }
  void testFillTool(){
    DrawTool* fillTool = new FillTool(color, 50, 50);
    mask = fillTool -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 50);
  }

  void testPen(){
    DrawTool* pen = new Pen(color, 3);
    mask = pen -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 3);
  }

  void testSparyCan(){
    DrawTool* sparyCan = new SprayCan(color, 41);
    mask = sparyCan -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 41);
  }

  void testEraser(){
    DrawTool* eraser = new Eraser(21);
    mask = eraser -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 21);
  }

  void testCalligraphyPen(){
    DrawTool* calligraphyPen = new CalligraphyPen(color, 5, 15);
    mask = calligraphyPen -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 15);
    TS_ASSERT_EQUALS(mask -> getWidth(), 5);
  }

  void testHightlighter(){
    DrawTool* highlighter = new Highlighter(color, 5, 15);
    mask = highlighter -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 15);
    TS_ASSERT_EQUALS(mask -> getWidth(), 5);
  }

  void testWaterColor(){
    DrawTool* waterColor = new WaterColor(color, 21);
    mask = waterColor -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 21);
  }

  void testMask(){
  }

  void testColorData(){
    TS_ASSERT_EQUALS(color -> getRed(), 0);
    TS_ASSERT_EQUALS(color -> getBlue(), 0);
    TS_ASSERT_EQUALS(color -> getGreen(), 0);
  }
};
#endif // __PENTEST_H
