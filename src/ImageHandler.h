#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include "PixelBuffer.h"
#include "ColorData.h"
#include <cstdlib>
#include <png.h>
#include <jpeglib.h>
#include <setjmp.h>
#include <string>

class ImageHandler{
public :
  ImageHandler();
  ~ImageHandler();
  PixelBuffer* loadimage(const std::string & filename, int &height, int &width);
  void saveimage(const std::string & filename, int height, int width, PixelBuffer *buffer);
private :
  bool isjpeg(const std::string & name);
  bool ispng(const std::string & name);
  bool isValidImageFileName(const std::string & name);
  bool isValidFile(const std::string & name);
  bool hasSuffix(const std::string & str, const std::string & suffix);
  void savepng(FILE* file, int height, int width, PixelBuffer *buffer);
  void savejpg(FILE* infile, int height, int width, PixelBuffer *buffer);
  PixelBuffer* loadpng(FILE *fp, int &height, int &width);
  PixelBuffer* loadjpg(FILE *infile, int &height, int &width);
};

#endif // IMAGEHANDLER_H
