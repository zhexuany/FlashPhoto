#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include "PixelBuffer.h"
#include "ColorData.h"
#include <cstdlib>
#include <png.h>
#include <jpeglib.h>
#include <setjmp.h>

class ImageHandler  {
 public :
  ImageHandler();
  ~ImageHandler();
  PixelBuffer* loadpng(FILE *fp, long &Height, long &Width);
  PixelBuffer* loadjpg(FILE *infile, long &Height, long &Width);
  void savepng(FILE* file, int height, int width);
  void savejpg(FILE* infile, int height, int width, PixelBuffer *buffer);
};

#endif // IMAGEHANDLER_H
