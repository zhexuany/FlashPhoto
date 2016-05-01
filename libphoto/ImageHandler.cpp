#include "ImageHandler.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
using std::cout;
using std::endl;
ImageHandler::ImageHandler(){}
ImageHandler::~ImageHandler(){}

/*
* \Save an image to the file
* \filename, height of image, width of image, image
* \void
*/
void ImageHandler::saveimage(const std::string & filename, PixelBuffer* buffer) {
    if (isjpeg(filename)) {
        savejpg(fopen(filename.c_str(), "wb"), buffer -> getHeight(), buffer -> getWidth(), buffer);
    } else if(ispng(filename)) {
        savepng(fopen(filename.c_str(), "wb"), buffer -> getHeight(), buffer -> getWidth(), buffer);
    } else {
        std::cout << "Error saving image" << std::endl;
    }
}

/*
* \Load an image in to the pixel buffer
* \filename, height reference, width reference
* \The pixel buffer with the image loaded
*/
PixelBuffer* ImageHandler::loadimage(const std::string & filename, int &height, int &width, ColorData backgroundColor) {
  //TODO need write a function call ispng
    if (isjpeg(filename)) {
        PixelBuffer *newBuffer = loadjpg(fopen(filename.c_str(), "rb"), height, width, backgroundColor);
        return newBuffer;
    } else if(ispng(filename)) {
        PixelBuffer *newBuffer = loadpng(filename, height, width, backgroundColor);
        return newBuffer;
    } else {
        return NULL;
    }
}

/*
* \Save a png to the file
* \file pointer, height of image, width of image, image
* \void
*/
void ImageHandler::savepng(FILE *fp, int height, int width, PixelBuffer* buffer) {
    int pixel_size = 3;
    int depth = 8;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    int x, y;
    png_byte ** row_pointers = NULL;
    png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
        goto png_create_write_struct_failed;
    }

    info_ptr = png_create_info_struct (png_ptr);
    if (info_ptr == NULL) {
        goto png_create_info_struct_failed;
    }

    /* Set up error handling. */

    if (setjmp (png_jmpbuf (png_ptr))) {
        goto png_failure;
    }

    /* Set image attributes. */

    png_set_IHDR (png_ptr,
                  info_ptr,
                  width,
                  height,
                  depth,
                  PNG_COLOR_TYPE_RGB,
                  PNG_INTERLACE_NONE,
                  PNG_COMPRESSION_TYPE_DEFAULT,
                  PNG_FILTER_TYPE_DEFAULT);

    /* Initialize rows of PNG. */

    row_pointers = (png_byte**)png_malloc(png_ptr, height * sizeof (png_byte *));
    for (y = 0; y < height; ++y) {
        png_byte *row = (png_byte*)png_malloc(png_ptr, sizeof(int) * width * pixel_size);
        row_pointers[y] = row;
        ColorData color;
        int r,g,b;
        for (x = 0; x < width; ++x) {
            color = buffer->getPixel(x, height-y);
            r = (color.getRed()*255);
            g = (color.getGreen()*255);
            b = (color.getBlue()*255);
            *row++ = r;
            *row++ = g;
            *row++ = b;
        }
    }

    /* Write the image data to "fp". */

    png_init_io (png_ptr, fp);
    png_set_rows (png_ptr, info_ptr, row_pointers);
    png_write_png (png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    for (y = 0; y < height; y++) {
        png_free (png_ptr, row_pointers[y]);
    }
    png_free (png_ptr, row_pointers);

 png_failure:
 png_create_info_struct_failed:
    png_destroy_write_struct (&png_ptr, &info_ptr);
 png_create_write_struct_failed:
    fclose (fp);
    return;
}

/*
* \Load a png from the file
* \file pointer, height of image, width of image
* \PixelBuffer containing the image
*/
PixelBuffer* ImageHandler::loadpng(const std::string fileName, int &Height, int &Width, ColorData backgroundColor) {
   PixelBuffer* loadedImageBuffer = NULL;
    
    png_image image;
    memset(&image, 0, (sizeof image));
    image.version = PNG_IMAGE_VERSION;
    
    if (png_image_begin_read_from_file(&image, fileName.c_str())) {
        
        loadedImageBuffer = new PixelBuffer(image.width, image.height, ColorData(0.0,0.0,0.0));
        
        png_bytep buffer;
        image.format = PNG_FORMAT_RGBA;
        buffer = new png_byte[PNG_IMAGE_SIZE(image)];
        Height = image.height;
		Width = image.width;
        if (buffer && png_image_finish_read(&image, NULL, buffer, 0, NULL)) {
            
            for (int y = 0; y < (int)image.height; y++) {
                for (int x = 0; x < (int)image.width; x++) {
                    int r, g, b, a = 0;
                    r = (int)buffer[(y*image.width*4)+(x*4)];
                    g = (int)buffer[(y*image.width*4)+(x*4)+1];
                    b = (int)buffer[(y*image.width*4)+(x*4)+2];
                    a = (int)buffer[(y*image.width*4)+(x*4)+3];
                    loadedImageBuffer->setPixel(x, image.height-(y+1), ColorData(r/255.0f,g/255.0f,b/255.0f,a/255.0f));
                }
            }
            
        }
        
        delete[] buffer;
    }
    
    return loadedImageBuffer;
}

/*
* \Load a jpg from the file
* \file pointer, height of image, width of image
* \PixelBuffer containing the image
*/
PixelBuffer* ImageHandler::loadjpg(FILE* infile, int& Height, int& Width, ColorData backgroundColor)
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
    PixelBuffer* newBuffer = new PixelBuffer(Width, Height, backgroundColor);

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
            newBuffer->setPixel((int)x, (Height - cinfo.output_scanline), ColorData(r / 255, g / 255, b / 255));
        }
    }
    fclose(infile);
    (void)jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    return newBuffer;
}

/*
* \save a jpg to the file
* \file pointer, height of image, width of image, image
* \void
*/
void ImageHandler::savejpg(FILE* outfile, int height, int width, PixelBuffer* buffer) {
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  int row_stride;		/* physical row width in image buffer */
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);

  if (outfile == NULL) {
    exit(1);
  }
  jpeg_stdio_dest(&cinfo, outfile);

  cinfo.image_width = width; 	
  cinfo.image_height = height;
  cinfo.input_components = 3;		
  cinfo.in_color_space = JCS_RGB; 	
  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, 100, TRUE);
  jpeg_start_compress(&cinfo, TRUE);

  row_stride = width * 3;	/* JSAMPLEs per row in image_buffer */
  unsigned char *raw_image = NULL;
  raw_image = (unsigned char *)malloc(row_stride);
  while (cinfo.next_scanline < cinfo.image_height) {
      int w,r,g,b;
      ColorData color;
      for (w = 0; w < width; w++) {
          color = buffer->getPixel(w, height-cinfo.next_scanline-1);
          r = (color.getRed()*255);
          g = (color.getGreen()*255);
          b = (color.getBlue()*255);
          raw_image[w*3] = (char)r;
          raw_image[(w*3)+1] = (char)g;
          raw_image[(w*3)+2] = (char)b;
      }
    //row_pointer[0] = & image_buffer[cinfo.next_scanline * row_stride];
    (void) jpeg_write_scanlines(&cinfo, &raw_image, 1);
  }

  free(raw_image);
  jpeg_finish_compress(&cinfo);
  fclose(outfile);
  jpeg_destroy_compress(&cinfo);

  /* And we're done! */
}

bool ImageHandler::isjpeg(const std::string & name) {
    return hasSuffix(name, ".jpg")|| hasSuffix(name, ".jpeg");
}

bool ImageHandler::ispng(const std::string & name) {
    return hasSuffix(name, ".png");
}

bool ImageHandler::hasSuffix(const std::string & str, const std::string & suffix){
    return str.find(suffix,str.length()-suffix.length()) != std::string::npos;
}
