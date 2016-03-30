#include "ImageHandler.h"
#include <iostream>
using std::cout;
using std::endl;
ImageHandler::ImageHandler(){}
  

ImageHandler::~ImageHandler(){
    
}

void ImageHandler::savepng(char* filename) {
    
}

//taken from https://www.w3.org/People/maxf/textorizer/textorizer.c
PixelBuffer* ImageHandler::loadpng(FILE *fp, long &Height, long &Width) {
    struct pixel
    {
        unsigned char r,g,b,a;
    };
    struct pixel *Pixels;
  long i,j,k;
  png_structp png_ptr;
  png_infop info_ptr;
  png_uint_32 width, height;
  png_bytep *row_pointers;
  int bit_depth, color_type;
  int interlace_type, compression_type, filter_type;
  

  /* create the png data structures */
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) return 0;

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
    return 0;
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
    return 0;
  }

  png_init_io(png_ptr, fp);

  png_read_info(png_ptr, info_ptr);

  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, 
               &interlace_type, &compression_type, &filter_type);

  /* tell libpng to strip 16 bit/color files down to 8 bits/color */
  png_set_strip_16(png_ptr);

  /* Extract multiple pixels with bit depths of 1, 2, and 4 from a single
   * byte into separate bytes (useful for paletted and grayscale images).
   */
  png_set_packing(png_ptr);
  
  /* Expand grayscale images to the full 8 bits from 1, 2, or 4 bits/pixel */
  if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand(png_ptr);
  
  /* Expand paletted colors into true RGB triplets */
  if (color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_expand(png_ptr);
  
  /* Expand paletted or RGB images with transparency to full alpha channels
   * so the data will be available as RGBA quartets.
   */
  if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
    png_set_expand(png_ptr);
  
  /* Add filler (or alpha) byte (before/after each RGB triplet) */
/*    if (bit_depth == 8 &&  */
/*        (color_type == PNG_COLOR_TYPE_RGB||color_type == PNG_COLOR_TYPE_GRAY)) */
  png_set_filler(png_ptr, 0x000000ff, PNG_FILLER_AFTER);  
  
  /* update info_ptr from the transforms. used to get a correct value for
   * png_get_rowbytes */
  png_read_update_info(png_ptr, info_ptr);

  /* allocate the memory to hold a row of the image */
  row_pointers = (png_bytep *)malloc(height*sizeof(png_bytep));
  for (i = 0; i < height; i++)
    row_pointers[i] = (png_bytep)malloc(png_get_rowbytes(png_ptr, info_ptr));

  png_read_image(png_ptr, row_pointers);

  /* malloc pixmap data */
  Width = width;
  Height = height;
  PixelBuffer *newBuffer = new PixelBuffer(Width, Height, ColorData(255,255,255));
  Pixels = (struct pixel *)malloc((size_t)Width*
                                         (size_t)Height*
                                         sizeof(struct pixel));
  k=0;
  for (i=0;i<Height;i++)
    for (j=0;j<Width;j++) {
      Pixels[k].r = row_pointers[i][4*j];
      Pixels[k].g = row_pointers[i][4*j+1];
      Pixels[k++].b = row_pointers[i][4*j+2];
    }
    
  double r,g,b;
  for (i=0;i<Height;i++)
    for (j=0;j<Width;j++) {
        r = Pixels[i*Width+j].r/255.0;
        g = Pixels[i*Width+j].g/255.0;
        b = Pixels[i*Width+j].b/255.0;
        
        newBuffer -> setPixel((int)j, Height-i, ColorData(r,g,b));
        
        /*
        std::cout << "r " << r << " g " <<  g << " b " << b << std::endl;
        ColorData colorTest = buffer -> getPixel((int)j, (int)i);
        std::cout << "set r " << colorTest.getRed() << " g " <<  colorTest.getGreen() << " b " << colorTest.getBlue() << std::endl;
         std::cout << "r " << r << " g " <<  g << " b " << b << std::endl;
        }*/
    }
    //buffer = new PixelBuffer(Width, Height, ColorData(255,255,255));
    //buffer = *newBuffer;
  /* read rest of file, and get additional chunks in info_ptr - REQUIRED */
  png_read_end(png_ptr, info_ptr);
  
  /* clean up after the read, and free any memory allocated - REQUIRED */
  png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);

  for (i = 0; i < height; i++)
    free(row_pointers[i]);
  free(row_pointers);
  return newBuffer;
}

PixelBuffer* ImageHandler::loadjpg(FILE* infile, long& Height, long& Width)
{
    double r, g, b;
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    if (infile == NULL) {
        perror("fopen fail");
        return 0;
    }
    jpeg_stdio_src(&cinfo, infile);
    (void)jpeg_read_header(&cinfo, TRUE);
    cinfo.out_color_space = JCS_RGB;
    (void)jpeg_start_decompress(&cinfo);
    JSAMPARRAY pJpegBuffer;

    int row_stride = cinfo.output_width * cinfo.output_components;
    pJpegBuffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, row_stride, 1);
    Height = cinfo.output_height;
    Width = cinfo.output_width;
    PixelBuffer* newBuffer = new PixelBuffer(Width, Height, ColorData(255, 255, 255));

    while (cinfo.output_scanline < cinfo.output_height) {
        (void)jpeg_read_scanlines(&cinfo, pJpegBuffer, 1);
        for (int x = 0; x < Width; x++) {
            r = pJpegBuffer[0][cinfo.output_components * x];
            if (cinfo.output_components > 2) {
                g = pJpegBuffer[0][cinfo.output_components * x + 1];
                b = pJpegBuffer[0][cinfo.output_components * x + 2];
            }
            else {
                g = r;
                b = r;
            }
            newBuffer->setPixel((int)x, Height - cinfo.output_scanline, ColorData(r / 255, g / 255, b / 255));
        }
    }
    fclose(infile);
    (void)jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    return newBuffer;
}
