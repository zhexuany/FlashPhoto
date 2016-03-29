#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "PixelBuffer.h"
#include "ColorData.h"
#include <cstdlib>
#include <png.h>
#include <jpeglib.h>
#include <setjmp.h>

class ImageLoader  {
 public :
  ImageLoader();
  ~ImageLoader();
  PixelBuffer* loadpng(FILE *fp, long &Height, long &Width);
  void loadjpg(const char* Name);
};

#endif // CALLIGRAPHYPEN_H
