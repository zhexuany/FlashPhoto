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

PixelBuffer::PixelBuffer(int w, int h, ColorData backgroundColor, ColorData * pixels) : m_width(w), m_height(h) {
    m_backgroundColor = new ColorData(backgroundColor);
    m_defaultBackgroundColor = new ColorData(backgroundColor);
    m_pixels = new ColorData[w*h];
    //fillPixelBufferWithColor(backgroundColor);
    //m_pixels = pixels;
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

ColorData const * const PixelBuffer::getData() const {
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

void PixelBuffer::copyPixelBuffer(PixelBuffer sourceBuffer, PixelBuffer * destinationBuffer) {
    std::cout << "test" << std::endl;
    if (destinationBuffer->getWidth() != sourceBuffer.getWidth() || destinationBuffer->getHeight() != sourceBuffer.getHeight()) {
        cerr << "copyPixelBuffer: " << "dimension mismatch" << endl;
    }
    else {
        memcpy ( (void*)destinationBuffer->m_pixels, (void*) sourceBuffer.m_pixels, sizeof(ColorData)*destinationBuffer->m_height*destinationBuffer->m_width );
    }
}

/*PixelBuffer* PixelBuffer::operator= (PixelBuffer source) {
    if (m_width == source.getWidth() && m_height == source.getHeight()) {
        std::cout << "same size" << std::endl;
    } else {
        std::cout << "different size" << std::endl;
        this->m_width = source.getWidth();
        this->m_height = source.getHeight();
        this->m_pixels = new ColorData[this->m_width*this->m_height];
    }
    memcpy ((void*)this->m_pixels, (void*)source.m_pixels, sizeof(ColorData)*this->m_height*this->m_width);
    return this;
}
*/