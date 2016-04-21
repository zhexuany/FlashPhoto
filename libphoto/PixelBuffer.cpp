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

void PixelBuffer::setPixel(int x, int y, const ColorData& newPixel) {
    if ((x < 0) || (x >= m_width) || (y < 0) || (y >= m_height)) {
        //cerr << "setPixel: x,y out of range: " << x << " " << y << endl;
    }
    else {
        int index = x + m_width*(y);
        m_pixels[index] = newPixel;
    }
}

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