#include <cxxtest/TestSuite.h>
#include <libphoto.h>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
using std::string;
//
// created by Zhexuan Yang on 29/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.
//


//This file is used to test all filter effect which is defined in libphoto
class FilterToolTest : public CxxTest::TestSuite {
public:
  ImageHandler* imageLoader;
  string inputPrefix = "input";
  string outputPrefix = "output";
  string verifyPrefix = "verify";
  string pngFile = "water.png";
  string jpgFile = "water.jpg";
  string delimiter = "/";
  string redirectToFile = " > output/test";
  string testFile = "output/test";
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
  string getInputFile(){
    return inputPrefix + delimiter + pngFile;
  }

  string getOutputFile(string fileName){
    return outputPrefix + delimiter + fileName;
  }

  string getVerifyFile(string fileName){
    return verifyPrefix + delimiter + fileName;
  }
  void testEdgeDetection(){
    Filter* edge = new FEdgeDetection();
    string inputFile = getInputFile();
    PixelBuffer* buffer = readFile(inputFile);
    if(buffer == nullptr){
       std::cout << "error loading pic\n";
       exit(0);
    }
    edge -> applyFilter(buffer);
    string outputFile = getOutputFile("edge.png");
    imageLoader -> saveimage(outputFile, buffer);
    testOutputFile("edge.png", outputFile);
    delete buffer;
    delete edge;
  }

  void testOutputFile(string file, string outputFile){
    string testString = "diff ";
    testString.append( getVerifyFile(file) + " " + outputFile + redirectToFile);
    system(testString.c_str());
    std::ostringstream ss;
    ss << std::ifstream(testFile).rdbuf();
    string test = ss.str();
    TS_ASSERT_EQUALS(test.length(), 0);
    if(test.length() > 0){
      std::cerr << test << std::endl;
    }
  }

  void testThreshold(){
    Filter* threshold = new FThreshold();
    threshold -> setFilterParameter(0.5);
    string inputFile = getInputFile();
    PixelBuffer* buffer = readFile(inputFile);
    if(buffer == nullptr){
       std::cout << "error loading pic\n";
      exit(0);
    }
    threshold -> applyFilter(buffer);
    string outputFile = getOutputFile("threshold.png");
    imageLoader -> saveimage(outputFile, buffer);
    testOutputFile("threshold.png", outputFile);
    delete buffer;
    delete threshold;
  }

  void testChannel(){
    Filter* channel = new FChannel();
    channel -> setFilterParameter(ColorData(0, 1.0, 1.0));
    string inputFile = getInputFile();
    PixelBuffer* buffer = readFile(inputFile);
    if(buffer == nullptr){
      std::cout << "error loading pic\n";
      exit(0);
    }
    channel -> applyFilter(buffer);
    string outputFile = getOutputFile("channel.png");
    imageLoader -> saveimage(outputFile, buffer);
    testOutputFile("channel.png", outputFile);
    delete buffer;
    delete channel;
  }

  void testSharpen(){
    Filter* sharpen = new FSharpen();
    sharpen -> setFilterParameter(5.0);
    string inputFile = getInputFile();
    PixelBuffer* buffer = readFile(inputFile);
    if(buffer == nullptr){
      std::cout << "error loading pic\n";
      exit(0);
    }
    sharpen -> applyFilter(buffer);
    string outputFile = getOutputFile("sharpen.png");
    imageLoader -> saveimage(outputFile, buffer);
    testOutputFile("sharpen.png", outputFile);
    delete buffer;
    delete sharpen;
  }

  void testSaturate(){
    string inputFile = getInputFile();
    PixelBuffer* buffer = readFile(inputFile);
    if(buffer == nullptr){
      std::cout << "error loading pic\n";
      exit(0);
    }
    Filter* satur = new FSaturation();
    satur -> setFilterParameter(2.0);
    satur -> applyFilter(buffer);
    string outputFile = getOutputFile("satur.png");
    imageLoader -> saveimage(outputFile, buffer);
    testOutputFile("satur.png", outputFile);
    delete satur;
    delete buffer;
  }

  void testQuantize(){
    string inputFile = getInputFile();
    PixelBuffer* buffer = readFile(inputFile);
    if(buffer == nullptr){
      std::cout << "error loading pic\n";
      exit(0);
    }
    Filter* quan = new FQuantize();
    quan -> setFilterParameter(8.0);
    quan -> applyFilter(buffer);
    string outputFile = getOutputFile("quan.png");
    imageLoader -> saveimage(outputFile, buffer);
    testOutputFile("quan.png", outputFile);
    delete quan;
    delete buffer;
  }

  void testSpecial(){
    string inputFile = getInputFile();
    PixelBuffer* buffer = readFile(inputFile);
    if(buffer == nullptr){
      std::cout << "error loading pic\n";
      exit(0);
    }
    Filter* spec = new FSpecial();
    spec -> applyFilter(buffer);
    string outputFile = getOutputFile("spec.png");
    imageLoader -> saveimage(outputFile, buffer);
    testOutputFile("spec.png", outputFile);
    delete spec;
    delete buffer;
  }

  void testBlur(){
    string inputFile = getInputFile();
    PixelBuffer* buffer = readFile(inputFile);
    if(buffer == nullptr){
      std::cout << "error loading pic\n";
      exit(0);
    }
    Filter* blur = new FBlur();
    blur -> setFilterParameter(5.0);
    blur -> applyFilter(buffer);
    string outputFile = getOutputFile("blur.png");
    imageLoader -> saveimage(outputFile, buffer);
    testOutputFile("blur.png", outputFile);
    delete blur;
    delete buffer;
  }

  void testMBlurNorthSouth(){
    string inputFile = getInputFile();
    PixelBuffer* buffer = readFile(inputFile);
    if(buffer == nullptr){
      std::cout << "error loading pic\n";
      exit(0);
    }
    Filter* mBlur = new FMotionBlur();
    mBlur -> setFilterParameter(5.0);
    mBlur -> setBlurDirection(FMotionBlur::DIR_N_S);
    mBlur -> applyFilter(buffer);
    string outputFile = getOutputFile("n_s_blur.png");
    imageLoader -> saveimage(outputFile, buffer);
    testOutputFile("n_s_blur.png", outputFile);
    delete mBlur;
    delete buffer;
  }

  void testMBlurWestEast(){
    string inputFile = getInputFile();
    PixelBuffer* buffer = readFile(inputFile);
    if(buffer == nullptr){
      std::cout << "error loading pic\n";
      exit(0);
    }
    Filter* mBlur = new FMotionBlur();
    mBlur -> setFilterParameter(5.0);
    mBlur -> setBlurDirection(FMotionBlur::DIR_E_W);
    mBlur -> applyFilter(buffer);
    string outputFile = getOutputFile("e_w_blur.png");
    imageLoader -> saveimage(outputFile, buffer);
    testOutputFile("e_w_blur.png", outputFile);
    delete mBlur;
    delete buffer;
  }

  void testMBlurNE_SW(){
    string inputFile = getInputFile();
    PixelBuffer* buffer = readFile(inputFile);
    if(buffer == nullptr){
      std::cout << "error loading pic\n";
      exit(0);
    }
    Filter* mBlur = new FMotionBlur();
    mBlur -> setFilterParameter(5.0);
    mBlur -> setBlurDirection(FMotionBlur::DIR_NE_SW);
    mBlur -> applyFilter(buffer);
    string outputFile = getOutputFile("ne_sw_blur.png");
    imageLoader -> saveimage(outputFile, buffer);
    testOutputFile("ne_sw_blur.png", outputFile);
    delete mBlur;
    delete buffer;
  }

  void testMBlurNW_SE(){
    string inputFile = getInputFile();
    PixelBuffer* buffer = readFile(inputFile);
    if(buffer == nullptr){
      std::cout << "error loading pic\n";
      exit(0);
    }
    Filter* mBlur = new FMotionBlur();
    mBlur -> setFilterParameter(5.0);
    mBlur -> setBlurDirection(FMotionBlur::DIR_NW_SE);
    mBlur -> applyFilter(buffer);
    string outputFile = getOutputFile("nw_se_blur.png");
    imageLoader -> saveimage(outputFile, buffer);
    testOutputFile("nw_se_blur.png", outputFile);
    delete mBlur;
    delete buffer;
  }


};
