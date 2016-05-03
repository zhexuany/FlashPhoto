#ifndef __PENTEST_H
#define __PENTEST_H

#include <cxxtest/TestSuite.h>
#include <libphoto.h>

//
// created by Zhexuan Yang on 29/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.
//


class InteractiveToolTest : public CxxTest::TestSuite {
public:
  ColorData* backgroundColor;
  ColorData* toolColor;
  const Mask * mask;
  double _delta;
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
    PixelBuffer *buffer = new PixelBuffer(800, 800, ColorData(1, 1, 0.9));
    int filterHeight = 3;
    int filterWidth = 3;
    float filter[3][3] =
      {
        {0.0, 0.2, 0.0},
        {0.2, 0.2, 0.2},
        {0.0, 0.2, 0.0}
      };
    DrawTool* blur = new Blur(30);
    mask = blur -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 30);
    int x = 25, y = 25;
    blur -> applyInfluence(x, y, buffer);
    int height = mask -> getHeight();
    int width = mask -> getWidth();
    int bufferHeight = buffer -> getHeight(); // canvas's buffer's height
    int bufferWidth = buffer -> getWidth();
    x -= width/2;
    y = bufferHeight - y - height/2;
    float** influence = mask -> getInfluence();

    for (int i = 0; i < width; i++) {
      for (int j = 0; j < height; j++) {

        float red = 0.0, green = 0.0, blue = 0.0;

        for (int filterY = 0; filterY < filterHeight; filterY++) {
          for (int filterX = 0; filterX < filterWidth; filterX++) {
            int X = x + ((i - filterWidth / 2 + filterX + width) % width);
            int Y = y + ((j - filterHeight / 2 + filterY + height) % height);

            if (X < 0 || X >= bufferWidth || Y < 0 || Y >= bufferHeight) {
              continue;
            }
            //for testing, currentPixelColor is just backgroundColor
            ColorData currentPixelColor = *backgroundColor;
            red += (float) (currentPixelColor.getRed() * filter[filterY][filterX]);
            green += (float) (currentPixelColor.getGreen() * filter[filterY][filterX]);
            blue += (float) (currentPixelColor.getBlue() * filter[filterY][filterX]);
          }
        }

        ColorData newPixel = ColorData(red, green, blue);
        newPixel = newPixel.clampedColor();

        if (influence[i][j] > 0.0) {
          if (x + i > 0 && x + i < bufferWidth -1 && y + j > 0 && y + j < bufferHeight -1) {
            testColorData(newPixel, buffer -> getPixel(x + i, y + j));
          }
        }
      }
    }
    delete buffer;
  }

  void testStamp(){
    ColorData color = ColorData(0.2, 0.2, 0.2);
    PixelBuffer* init = new PixelBuffer(30, 30, color);
    PixelBuffer *buffer = new PixelBuffer(800, 800, ColorData(1, 1, 0.9));
    DrawTool* stamp = new Stamp(init, 30, 30);
    int x = 25, y = 25;
    stamp -> applyInfluence(x, y, buffer);
    mask = stamp -> getMask();
    int height = mask -> getHeight();
    int width = mask -> getWidth();
    int bufferHeight = buffer -> getHeight();
    ColorData currentPixelColor;
    x -= width/2;
    y = bufferHeight - y - height/2;

    for(int i = 0; i < width; i++){
      for(int j = 0; j < height; j++){
        testColorData(color, buffer -> getPixel(x + i, y + j));
      }
    }
  }

  void testCrayon(){
    PixelBuffer *buffer = new PixelBuffer(800, 800, ColorData(1, 1, 0.9));
    DrawTool* crayon = new Crayon(toolColor, 20);
    mask = crayon -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 20);
    crayon -> applyInfluence(25, 25, buffer);
    testBuffer(25, 25, buffer);
    crayon -> applyInfluence(125, 25, buffer);
    testBuffer(125, 25, buffer);
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
    pen -> applyInfluence(125, 25, buffer);
    testBuffer(125, 25, buffer);
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
    sparyCan -> applyInfluence(125, 25, buffer);
    testBuffer(125, 25, buffer);
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
    calligraphyPen -> applyInfluence(125, 25, buffer);
    testBuffer(125, 25, buffer);
    delete buffer;
  }

  void testHightlighter(){
    PixelBuffer *buffer = new PixelBuffer(800, 800, ColorData(1, 1, 0.9));
    DrawTool* highlighter = new Highlighter(toolColor, 5, 15);
    mask = highlighter -> getMask();
    TS_ASSERT_EQUALS(mask -> getHeight(), 15);
    TS_ASSERT_EQUALS(mask -> getWidth(), 5);
    //we check two seperate position
    highlighter -> applyInfluence(25, 25, buffer);
    testBuffer(25, 25, buffer);
    highlighter -> applyInfluence(100, 25, buffer);
    testBuffer(100, 25, buffer);
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

  void testColorDataOperator(){
    ColorData a = ColorData();
    ColorData b = ColorData();
    TS_ASSERT_EQUALS(a, b);
  }

  void testPixelBuffer(){
    PixelBuffer* a = new PixelBuffer(80, 80, ColorData());
    PixelBuffer* b = new PixelBuffer(80, 80, ColorData());
    //testPixel(*a, *b)
    if(*a == *b){
      TS_ASSERT_EQUALS(1, 1);
    }
    else{
      TS_ASSERT_EQUALS(1, 0);
    }
    delete a;
    delete b;
  }

};
#endif // __PENTEST_H
