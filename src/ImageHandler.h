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
  void loadjpg(FILE *infile, long &Height, long &Width);
    void savepng(char* filename);
};

#endif // IMAGEHANDLER_H
