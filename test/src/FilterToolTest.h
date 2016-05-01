#include <cxxtest/TestSuite.h>
#include <libphoto.h>
#include <cstdlib>
#include <string>
using std::string;
//
// created by Zhexuan Yang on 29/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.
//


//This file is used to test all filter effect which is defined in libphoto
class FilterToolTest : public CxxTest::TestSuite {
public:
  ImageHandler* imageLoader;
  string pngFile = "input/water.png";
  string jpgFile = "input/water.jpg";
  string outputPngFile = "output/water_test.png";
  string verifyPngFile = "verify/edge.png";
  int height;
  int width;
  ColorData backgroundColor;
  void setUp(){
    height = 0;
    width = 0;
    imageLoader = new ImageHandler();
    backgroundColor = ColorData(1.0, 1.0, 0.9);
  }

  void tearDown(){
    delete imageLoader;
  }

  PixelBuffer* readFile(string filePath){
    return imageLoader -> loadimage(filePath, height, width, backgroundColor);
  }

  void testEdgeDetection(){
    Filter * edge = new FEdgeDetection();
    PixelBuffer* buffer = readFile(pngFile);
    if(buffer == nullptr){
      std::cout << "error loading pic\n";
      exit(0);
    }
    edge -> applyFilter(buffer);
    imageLoader -> saveimage(outputPngFile, buffer);
    string testString = "diff ";
    testString.append(verifyPngFile);
    testString.append(" ");
    testString.append(outputPngFile);
    system(testString.c_str());
    delete buffer;
  }

};
