#include "MIACommandLineApp.h"
//
// created by Zhexuan Yang on 29/4/2016
// Copyright (c) 2016 Zhexuan Yang. All rights reserved.
//

///create a instance for MIA command line mode
MIACommandLineApp::MIACommandLineApp(){
  m_buffer = new PixelBuffer(0, 0, ColorData());
  m_loader = new ImageHandler();
}
///destructor for MIACommandLineApp 
MIACommandLineApp::~MIACommandLineApp(){
  delete m_loader;
  if(m_buffer) delete m_buffer;
}

///apply Blur filter effect
void MIACommandLineApp::handleBlur(float parameter){
  Filter *blur = new FBlur();
  blur -> setFilterParameter(parameter);
  blur -> applyFilter(m_buffer);
  delete blur;
}


///apply compare two pictures. return 1 if they are smae, 0 if they are different
int MIACommandLineApp::handleCompare(string input, string output){
  int height, width;
  PixelBuffer* inBuffer = m_loader -> loadimage(input, width, height, ColorData());
  PixelBuffer* outBuffer = m_loader -> loadimage(output, width, height, ColorData());
  if(inBuffer == nullptr || outBuffer == nullptr) return 0;
  int res = 1;
  if(*inBuffer != *outBuffer)
    res = 0;
  delete inBuffer;
  delete outBuffer;
  return res;
}


///apply Edge detction filter effect
void MIACommandLineApp::handleEdgeDetect(){
  Filter *edge = new FEdgeDetection();
  edge -> applyFilter(m_buffer);
  delete edge;
}



///apply Multirgb filter effect
void MIACommandLineApp::handleMultgb(ColorData color){
  Filter *channel = new FChannel();
  channel -> setFilterParameter(color);
  channel -> applyFilter(m_buffer);
  delete channel;
}



///apply Quantize filter effect
void MIACommandLineApp::handleQuant(int parameter){
  Filter *quant = new FQuantize();
  quant -> setFilterParameter(parameter);
  quant -> applyFilter(m_buffer);
  delete quant;
}



///apply Saturate filter effect
void MIACommandLineApp::handleSatur(float parameter){
  Filter *satur = new FSaturation();
  satur -> setFilterParameter(parameter);
  satur -> applyFilter(m_buffer);
  delete satur;
}


///apply Sharpen filter effect
void MIACommandLineApp::handleSharpen(int parameter){
  Filter *sharpen = new FSharpen();
  sharpen -> setFilterParameter(parameter);
  sharpen -> applyFilter(m_buffer);
  delete sharpen;
}


///apply Threshold filter effect
void MIACommandLineApp::handleThresh(float parameter){
  Filter* threshold = new FThreshold();
  threshold -> setFilterParameter(parameter);
  threshold -> applyFilter(m_buffer);
  delete threshold;
}

