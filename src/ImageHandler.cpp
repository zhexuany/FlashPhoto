#include "ImageHandler.h"
#include <iostream>
using std::cout;
using std::endl;
ImageHandler::ImageHandler(){}
ImageHandler::~ImageHandler(){}

/*
* \Save an image to the file
* \filename, height of image, width of image, image
* \void
*/
void ImageHandler::saveimage(const std::string & filename, int height, int width, PixelBuffer* buffer) {
    if (isjpeg(filename)) {
        savejpg(fopen(filename.c_str(), "wb"), buffer -> getHeight(), buffer -> getWidth(), buffer);
    } else {
        savepng(fopen(filename.c_str(), "wb"), buffer -> getHeight(), buffer -> getWidth(), buffer);
    }
}

/*
* \Load an image in to the pixel buffer
* \filename, height reference, width reference
* \The pixel buffer with the image loaded
*/
PixelBuffer* ImageHandler::loadimage(const std::string & filename, int &height, int &width) {
  //TODO need write a function call ispng
    if (isjpeg(filename)) {
        PixelBuffer *newBuffer = loadjpg(fopen(filename.c_str(), "rb"), height, width);
        return newBuffer;
    } else {
      //TODO possible bug
        PixelBuffer *newBuffer = loadpng(fopen(filename.c_str(), "rb"), height, width);
        return newBuffer;
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

    /* The routine has successfully written the file, so we set
       "status" to a value which indicates success. */


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
PixelBuffer* ImageHandler::loadpng(FILE *fp, int &Height, int &Width) {
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

  //TODO put this into deconstructor
  for (i = 0; i < height; i++)
    free(row_pointers[i]);
  free(row_pointers);
  return newBuffer;
}

/*
* \Load a jpg from the file
* \file pointer, height of image, width of image
* \PixelBuffer containing the image
*/
PixelBuffer* ImageHandler::loadjpg(FILE* infile, int& Height, int& Width)
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

/*
* \save a jpg to the file
* \file pointer, height of image, width of image, image
* \void
*/
void ImageHandler::savejpg(FILE* outfile, int height, int width, PixelBuffer* buffer) {
    /* This struct contains the JPEG compression parameters and pointers to
   * working space (which is allocated as needed by the JPEG library).
   * It is possible to have several such structures, representing multiple
   * compression/decompression processes, in existence at once.  We refer
   * to any one struct (and its associated working data) as a "JPEG object".
   */
  struct jpeg_compress_struct cinfo;
  /* This struct represents a JPEG error handler.  It is declared separately
   * because applications often want to supply a specialized error handler
   * (see the second half of this file for an example).  But here we just
   * take the easy way out and use the standard error handler, which will
   * print a message on stderr and call exit() if compression fails.
   * Note that this struct must live as long as the main JPEG parameter
   * struct, to avoid dangling-pointer problems.
   */
  struct jpeg_error_mgr jerr;
  /* More stuff */
    //JSAMPROW buffer;
  int row_stride;		/* physical row width in image buffer */

  /* Step 1: allocate and initialize JPEG compression object */

  /* We have to set up the error handler first, in case the initialization
   * step fails.  (Unlikely, but it could happen if you are out of memory.)
   * This routine fills in the contents of struct jerr, and returns jerr's
   * address which we place into the link field in cinfo.
   */
  cinfo.err = jpeg_std_error(&jerr);
  /* Now we can initialize the JPEG compression object. */
  jpeg_create_compress(&cinfo);

  /* Step 2: specify data destination (eg, a file) */
  /* Note: steps 2 and 3 can be done in either order. */

  /* Here we use the library-supplied code to send compressed data to a
   * stdio stream.  You can also write your own code to do something else.
   * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
   * requires it in order to write binary files.
   */
  if (outfile == NULL) {
    exit(1);
  }
  jpeg_stdio_dest(&cinfo, outfile);

  /* Step 3: set parameters for compression */

  /* First we supply a description of the input image.
   * Four fields of the cinfo struct must be filled in:
   */
  cinfo.image_width = width; 	/* image width and height, in pixels */
  cinfo.image_height = height;
  cinfo.input_components = 3;		/* # of color components per pixel */
  cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
  /* Now use the library's routine to set default compression parameters.
   * (You must set at least cinfo.in_color_space before calling this,
   * since the defaults depend on the source color space.)
   */
  jpeg_set_defaults(&cinfo);
  /* Now you can set any non-default parameters you wish to.
   * Here we just illustrate the use of quality (quantization table) scaling:
   */
  jpeg_set_quality(&cinfo, 100, TRUE /* limit to baseline-JPEG values */);

  /* Step 4: Start compressor */

  /* TRUE ensures that we will write a complete interchange-JPEG file.
   * Pass TRUE unless you are very sure of what you're doing.
   */
  jpeg_start_compress(&cinfo, TRUE);

  /* Step 5: while (scan lines remain to be written) */
  /*           jpeg_write_scanlines(...); */

  /* Here we use the library's state variable cinfo.next_scanline as the
   * loop counter, so that we don't have to keep track ourselves.
   * To keep things simple, we pass one scanline per call; you can pass
   * more if you wish, though.
   */
  row_stride = width * 3;	/* JSAMPLEs per row in image_buffer */
    unsigned char *raw_image = NULL;
    raw_image = (unsigned char *)malloc(row_stride);
  while (cinfo.next_scanline < cinfo.image_height) {
    /* jpeg_write_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could pass
     * more than one scanline at a time if that's more convenient.
     */
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

  /* Step 6: Finish compression */

  jpeg_finish_compress(&cinfo);
  /* After finish_compress, we can close the output file. */
  fclose(outfile);

  /* Step 7: release JPEG compression object */

  /* This is an important step since it will release a good deal of memory. */
  jpeg_destroy_compress(&cinfo);

  /* And we're done! */
}

bool ImageHandler::isjpeg(const std::string & name) {
    return hasSuffix(name, ".jpg")|| hasSuffix(name, ".jpeg");
}

bool ImageHandler::hasSuffix(const std::string & str, const std::string & suffix){
    return str.find(suffix,str.length()-suffix.length()) != std::string::npos;
}
