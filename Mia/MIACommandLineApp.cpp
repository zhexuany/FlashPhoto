#include "MIACommandLineApp.h"

MIACommandLineApp::MIACommandLineApp(){
  m_buffer = new PixelBuffer(0, 0, ColorData());
  m_loader = new ImageHandler();
}

MIACommandLineApp::~MIACommandLineApp(){
  delete m_loader;
}

void MIACommandLineApp::handleBlur(float parameter){
  Filter *blur = new FBlur();
  blur -> setFilterParameter(parameter);
  blur -> applyFilter(m_buffer);
}


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


void MIACommandLineApp::handleEdgeDetect(){
  Filter *edge = new FEdgeDetection();
  edge -> applyFilter(m_buffer);
}



void MIACommandLineApp::handleMultgb(ColorData color){
  Filter *channel = new FChannel();
  channel -> setFilterParameter(color);
  channel -> applyFilter(m_buffer);
}



void MIACommandLineApp::handleQuant(int parameter){
  Filter *quant = new FQuantize();
  quant -> setFilterParameter(parameter);
  quant -> applyFilter(m_buffer);
}



void MIACommandLineApp::handleSatur(float parameter){
  Filter *satur = new FSaturation();
  satur -> setFilterParameter(parameter);
  satur -> applyFilter(m_buffer);
}


void MIACommandLineApp::handleSharpen(int parameter){
  Filter *sharpen = new FSharpen();
  sharpen -> setFilterParameter(parameter);
  sharpen -> applyFilter(m_buffer);
}


void MIACommandLineApp::handleThresh(float parameter){
  Filter* threshold = new FThreshold();
  threshold -> setFilterParameter(parameter);
  threshold -> applyFilter(m_buffer);
}

