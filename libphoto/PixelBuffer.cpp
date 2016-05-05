//
//  PixelBuffer.cpp
//  Originally created by the CSci-3081W TAs.
//

#include <iostream>
#include <cstring>
#include "PixelBuffer.h"
#include "ColorData.h"

using std::cerr;
using std::endl;
using std::fill;

/**
This is the pixelbuffer class.  This is the screen the user sees.  Use the encapsulated functions, they help a lot.
*/
PixelBuffer::PixelBuffer(int w, int h, ColorData backgroundColor) : m_width(w), m_height(h) {
    m_backgroundColor = new ColorData(backgroundColor);
    m_defaultBackgroundColor = new ColorData(backgroundColor);
    m_pixels = new ColorData[w*h];
    fillPixelBufferWithColor(backgroundColor);
}

PixelBuffer::~PixelBuffer() {
    delete [] m_pixels;
    delete m_backgroundColor;
    delete m_defaultBackgroundColor;
}
///Get the pixel at the x and y coordinates
ColorData PixelBuffer::getPixel(int x, int y) const {
    ColorData pixelData;

    if ((x < 0) || (x >= m_width) || (y < 0) || (y >= m_height)) {
        //cerr << "getPixel: x,y out of range: " << x << " " << y << endl;
    }
    else {
        int index = x + m_width*(y);
        pixelData = m_pixels[index];
    }
    return pixelData;
}
///Set the pixel at the x and y coordinates to the newPixel value
void PixelBuffer::setPixel(int x, int y, const ColorData& newPixel) {
    if ((x < 0) || (x >= m_width) || (y < 0) || (y >= m_height)) {
        //cerr << "setPixel: x,y out of range: " << x << " " << y << endl;
    }
    else {
        int index = x + m_width*(y);
        m_pixels[index] = newPixel;
    }
}
///Get the pixel array
ColorData const * PixelBuffer::getData() const {
    return m_pixels;
}

int PixelBuffer::getHeight() const {
    return m_height;
}

int PixelBuffer::getWidth() const {
    return m_width;
}

ColorData PixelBuffer::getBackgroundColor() {
    return *m_backgroundColor;
}

ColorData PixelBuffer::getDefaultBackgroundColor() {
    return *m_defaultBackgroundColor;
}

void PixelBuffer::setBackgroundColor(ColorData* color) {
    if (m_backgroundColor) delete m_backgroundColor;
    m_backgroundColor = new ColorData(*color);
}

bool operator== (const PixelBuffer& a, const PixelBuffer& b){
  if(b.getWidth() != a.getWidth()) return false;
  if(b.getHeight() != a.getHeight()) return false;
  for(int i = 0; i < b.getWidth(); i++){
    for(int j = 0; j < b.getWidth(); j++){
      if(b.getPixel(i, j) != a.getPixel(i, j))
        return false;
    }
  }
  return true;
}
bool operator!= (const PixelBuffer& a, const PixelBuffer& b){
  return !(b == a);
}

void PixelBuffer::fillPixelBufferWithColor(ColorData color) {
    fill(m_pixels, m_pixels+m_width*m_height, color);
}

void PixelBuffer::copyPixelBuffer(PixelBuffer * sourceBuffer, PixelBuffer * destinationBuffer) {
    if (destinationBuffer->getWidth() != sourceBuffer->getWidth() || destinationBuffer->getHeight() != sourceBuffer->getHeight()) {
        cerr << "copyPixelBuffer: " << "dimension mismatch" << endl;
    }
    else {
        memcpy ( (void*)destinationBuffer->m_pixels, (void*) sourceBuffer->m_pixels, sizeof(ColorData)*destinationBuffer->m_height*destinationBuffer->m_width );
    }
}

void PixelBuffer::convertToLuminance(){
  for(int i = 0; i < m_width; i++){
    for(int j = 0; j < m_height; j++){
      ColorData currPixel = getPixel(i, j);
      float lumaince = currPixel.getLuminance();
      setPixel(i, j,  ColorData(lumaince, lumaince, lumaince));
    }
  }
}
