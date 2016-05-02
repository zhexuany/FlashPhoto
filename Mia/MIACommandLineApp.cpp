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
  PixelBuffer* inBuffer = readFile(input);
  PixelBuffer* outBuffer = readFile(output);
  if(inBuffer == nullptr || outBuffer == nullptr) return 0;
  if(inBuffer != outBuffer) return 0;
  return 1;
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


void MIACommandLineApp::handleSharpen(float parameter){
  Filter *sharpen = new FSharpen();
  sharpen -> setFilterParameter(parameter);
  sharpen -> applyFilter(m_buffer);
}


void MIACommandLineApp::handleThresh(float parameter){
  Filter* threshold = new FThreshold();
  threshold -> setFilterParameter(parameter);
  threshold -> applyFilter(m_buffer);
}

