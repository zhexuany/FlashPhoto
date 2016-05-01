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
  ColorData* color;
  const Mask * mask;
  double _delta;
  int size;
public:
  //declare a temporary Pixel buffer for testing
  void setUp(){
    _delta = 0.001;
    size = 30;
    backgroundColor = new ColorData(1, 1, 0.9);
    buffer = new PixelBuffer(50, 50, ColorData(1, 1, 0.9));
    color = new ColorData(0, 0, 0);
  }

  //delete buffer
  void tearDown(){
    delete buffer;
    delete backgroundColor;
    delete color;
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
    DrawTool* pen = new Pen(color, 3);
    mask = pen -> getMask();
    //pen -> printfInfluence();
    float** influence = mask -> getInfluence();
    TS_ASSERT_EQUALS(mask -> getHeight(), 3);
    // apply mask at 25 25 with radius 3
    pen -> applyInfluence(25, 25, buffer);
    for(int i = 0; i < mask -> getWidth()/2; i++){
      for(int j = 0; j < mask -> getHeight()/2; j++){
        ColorData currentColor = buffer -> getPixel(25 + i, 25 + j);
        ColorData newColor =((*color)*influence[i][j])
          + currentColor*(1 - influence[i][j]);
        testColorData(currentColor, newColor);
      }
    }
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

  void testColorData(ColorData src, ColorData dst){
    TS_ASSERT_DELTA( src.getRed(), dst.getRed(), _delta);
    TS_ASSERT_DELTA( src.getGreen(), dst.getGreen(), _delta);
    TS_ASSERT_DELTA( src.getBlue(), dst.getBlue(), _delta);
  }

  void testColorData(){
    TS_ASSERT_DELTA(backgroundColor -> getRed(), 1, _delta);
    TS_ASSERT_DELTA(backgroundColor -> getGreen(), 1, _delta);
    TS_ASSERT_DELTA(backgroundColor -> getBlue(), .9, _delta);
  }
};
#endif // __PENTEST_H
