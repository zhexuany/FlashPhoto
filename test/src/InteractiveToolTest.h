#ifndef __PENTEST_H
#define __PENTEST_H

#include <cxxtest/TestSuite.h>
#include <libphoto/Pen.h>
#include <libphoto/ColorData.h>
#include <libphoto/Mask.h>
//
// A simple test suite: Just inherit CxxTest::TestSuite and write tests!
//


class InteractiveToolTest : public CxxTest::TestSuite {
  PixelBuffer *buffer;
  DrawTool *tool;
public:
  //declare a temporary Pixel buffer for testing
  void setUp(){
    buffer = new PixelBuffer(50, 50, ColorData(0, 0, 0));
  }
  //delete buffer
  void tearDown(){
    delete buffer;
  }

  void testTool(){
    TS_TRACE("Starting Pen test");
    ColorData toolColor(1, 1, 1);
    Pen pen(toolColor, 5);
    ColorData resColor = pen.getToolColor();
    TS_TRACE("Starting Pen's tool color");
    TS_ASSERT_EQUALS(toolColor.getRed(), res.getRed());
    TS_ASSERT_EQUALS(toolColor.getBlue(), res.getBlue());
    TS_ASSERT_EQUALS(toolColor.getGreen(), res.getGreen());
    TS_TRACE("Finishing Pen's tool color");
    Mask mask = pen.getMask();
    TS_ASSERT()
    TS_TRACE("Finishing Pen test");
  }

  void testMask(Mask mask, int length, int height){
    TS_TRACE("Starting to Mask Test");
    TS_TRACE("Starting to Mask Height Test");
    TS_ASSERT_EQUALS(dst_mask.getHeight(), height);
    TS_TRACE("Finishing to Mask Height Test");
    TS_TRACE("Starting to Mask Width Test");
    TS_ASSERT_EQUALS(dst_mask.getWidth(), width);
    TS_TRACE("Finishing to Mask Width Test");
    TS_TRACE("Starting to Mask Value Test");
    for(int i = 0; i < )
    TS_TRACE("Finishing to Mask Value Test");
    TS_TRACE("Starting to Mask Test");
  }

};
#endif // __PENTEST_H
