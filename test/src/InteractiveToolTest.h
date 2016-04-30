#ifndef __PENTEST_H
#define __PENTEST_H

#include <cxxtest/TestSuite.h>
#include <libphoto.h>

//
// A simple test suite: Just inherit CxxTest::TestSuite and write tests!
//


class InteractiveToolTest : public CxxTest::TestSuite {
  PixelBuffer *buffer;
  ColorData* backgroundColor;
  const Mask * mask;
  int size;
public:
  //declare a temporary Pixel buffer for testing
  void setUp(){
    size = 30;
    backgroundColor = new ColorData(1, 1, 0.95);
    buffer = new PixelBuffer(50, 50, ColorData(1, 1, 0.95));
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
    //PixelBuffer* init = new PixelBuffer(0, 0, *backgroundColor);
    //DrawTool* stamp = new Stamp(init, 0, 0);
  }

  void testCrayon(){
    DrawTool* crayon = new Crayon(backgroundColor, 20);
    mask = crayon -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 20);
  }

  void testFillTool(){
    DrawTool* fillTool = new FillTool(backgroundColor, 50, 50);
    mask = fillTool -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 50);
  }

  void testPen(){
    //default backgroundColor data is (0, 0, 0)
    DrawTool* pen = new Pen(backgroundColor, 3);
    mask = pen -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 3);
    // apply mask at 25 25
    pen -> paint(25, 25, 20, 20, buffer);
    ColorData res = buffer -> getPixel(25, 25);
    testColorData(res);
    res = buffer -> getPixel(20, 20);
}

  void testSparyCan(){
    DrawTool* sparyCan = new SprayCan(backgroundColor, 41);
    mask = sparyCan -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 41);
  }

  void testEraser(){
    DrawTool* eraser = new Eraser(21);
    mask = eraser -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 21);
  }

  void testCalligraphyPen(){
    DrawTool* calligraphyPen = new CalligraphyPen(backgroundColor, 5, 15);
    mask = calligraphyPen -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 15);
    TS_ASSERT_EQUALS(mask -> getWidth(), 5);
  }

  void testHightlighter(){
    DrawTool* highlighter = new Highlighter(backgroundColor, 5, 15);
    mask = highlighter -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 15);
    TS_ASSERT_EQUALS(mask -> getWidth(), 5);
  }

  void testWaterColor(){
    DrawTool* waterColor = new WaterColor(backgroundColor, 21);
    mask = waterColor -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 21);
  }

  void testMask(){
  }

  void testColorData(ColorData res){
    TS_ASSERT_EQUALS(backgroundColor -> getRed(), res.getRed());
    TS_ASSERT_EQUALS(backgroundColor -> getBlue(), res.getBlue());
    TS_ASSERT_EQUALS(backgroundColor -> getGreen(), res.getGreen());
  }

  void testColorData(){
    TS_ASSERT_EQUALS(backgroundColor -> getRed(), 0);
    TS_ASSERT_EQUALS(backgroundColor -> getBlue(), 0);
    TS_ASSERT_EQUALS(backgroundColor -> getGreen(), 0);
  }
};
#endif // __PENTEST_H
