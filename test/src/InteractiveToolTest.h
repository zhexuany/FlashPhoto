#ifndef __PENTEST_H
#define __PENTEST_H

#include <cxxtest/TestSuite.h>
#include <libphoto.h>

//
// A simple test suite: Just inherit CxxTest::TestSuite and write tests!
//


class InteractiveToolTest : public CxxTest::TestSuite {
  ColorData* backgroundColor;
  ColorData* toolColor;
  const Mask * mask;
  double _delta;
public:
  //declare a temporary Pixel buffer for testing
  void setUp(){
    _delta = 0.01;
    backgroundColor = new ColorData(1, 1, 0.9);
    toolColor = new ColorData(0, 0, 0);
  }

  //delete buffer
  void tearDown(){
    delete backgroundColor;
    delete toolColor;
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
    PixelBuffer *buffer = new PixelBuffer(800, 800, ColorData(1, 1, 0.9));
    DrawTool* crayon = new Crayon(toolColor, 20);
    mask = crayon -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 20);
    crayon -> applyInfluence(25, 25, buffer);
    testBuffer(25, 25, buffer);
    delete buffer;
  }

  void testFillTool(){
    PixelBuffer *buffer = new PixelBuffer(800, 800, ColorData(1, 1, 0.9));
    DrawTool* fillTool = new FillTool(toolColor, 800, 800);
    mask = fillTool -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 800);
    fillTool -> applyInfluence(25, 25, buffer);
    for(int i = 0; i < buffer -> getWidth(); i++){
      for(int j = 0; j < buffer -> getHeight(); j++){
        testColorData(*toolColor, buffer -> getPixel(i, j));
      }
    }
    delete buffer;
  }

  void testPen(){
    PixelBuffer *buffer = new PixelBuffer(800, 800, ColorData(1, 1, 0.9));
    //default backgroundColor data is (0, 0, 0)
    DrawTool* pen = new Pen(toolColor, 3);
    mask = pen -> getMask();
    //pen -> printfInfluence();
    TS_ASSERT_EQUALS(mask -> getHeight(), 3);
    // apply mask at 25 25 with radius 3
    pen -> applyInfluence(25, 25, buffer);
    testBuffer(25, 25, buffer);
    delete buffer;
  }

  void testSparyCan(){
    PixelBuffer *buffer = new PixelBuffer(800, 800, ColorData(1, 1, 0.9));
    int width = 41;
    DrawTool* sparyCan = new SprayCan(toolColor, width);
    mask = sparyCan -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), width);
    sparyCan -> applyInfluence(25, 25, buffer);
    testBuffer(25, 25, buffer);
    delete buffer;
  }

  void testEraser(){
    PixelBuffer *buffer = new PixelBuffer(800, 800, ColorData(1, 1, 0.9));
    DrawTool* eraser = new Eraser(21);
    mask = eraser -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 21);
    eraser -> applyInfluence(25, 25, buffer);
    int height = mask-> getHeight();
    int width = mask -> getWidth();
    int bufferHeight = buffer -> getHeight();
    int x = - width/2 + 25;
    int y = bufferHeight - 25 - height/2;
    float ** influence = mask -> getInfluence();
    for(int i =0; i < mask -> getWidth(); i++){
      for(int j = 0; j < mask -> getHeight(); j++){
        if(influence[i][j] == 1.0) {
          testColorData(*backgroundColor, buffer -> getPixel(x + i, y + j));
        }
      }
    }
    delete buffer;
  }

  void testCalligraphyPen(){
    PixelBuffer *buffer = new PixelBuffer(800, 800, ColorData(1, 1, 0.9));
    DrawTool* calligraphyPen = new CalligraphyPen(toolColor, 5, 15);
    mask = calligraphyPen -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 15);
    TS_ASSERT_EQUALS(mask -> getWidth(), 5);
    calligraphyPen -> applyInfluence(25, 25, buffer);
    testBuffer(25, 25, buffer);
    delete buffer;
  }

  void testHightlighter(){
    PixelBuffer *buffer = new PixelBuffer(800, 800, ColorData(1, 1, 0.9));
    DrawTool* highlighter = new Highlighter(toolColor, 5, 15);
    mask = highlighter -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 15);
    TS_ASSERT_EQUALS(mask -> getWidth(), 5);
    highlighter -> applyInfluence(25, 25, buffer);
    testBuffer(25, 25, buffer);
    delete buffer;
  }

  void testWaterColor(){
    PixelBuffer *buffer = new PixelBuffer(800, 800, ColorData(1, 1, 0.9));
    DrawTool* waterColor = new WaterColor(toolColor, 21);
    mask = waterColor -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 21);
    waterColor -> applyInfluence(25, 25, buffer);
    testBuffer(25, 25, buffer);
    delete buffer;
  }

  void testBuffer(int x, int y, PixelBuffer* buffer){
    int height = mask-> getHeight();
    int width = mask -> getWidth();
    int bufferHeight = buffer -> getHeight();
    x -= width/2;
    y = bufferHeight - y - height/2;
    float ** influence = mask -> getInfluence();
    // printfInfluence();
    for(int i = 0; i < width; i++){
      for(int j = 0; j < height; j++){
        ColorData newColor =((*toolColor)*influence[i][j])
          + *backgroundColor*(1 - influence[i][j]);
        ColorData currentColor = buffer -> getPixel(x+i, y+j);
        testColorData(newColor, currentColor);
      }
    }

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
