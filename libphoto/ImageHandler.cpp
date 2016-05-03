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
        savepng(filename, buffer -> getHeight(), buffer -> getWidth(), buffer);
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
void ImageHandler::savepng(const std::string fileName, int height, int width, PixelBuffer* bufferToSave) {
		//Taken from iteration 2 solution
    png_image image;
    
    memset(&image, 0, (sizeof image));
    image.height = bufferToSave->getHeight();
    image.width = bufferToSave->getWidth();
    image.version = PNG_IMAGE_VERSION;
    image.opaque = NULL;
    image.format = PNG_FORMAT_RGBA;
    
    png_bytep buffer = new png_byte[PNG_IMAGE_SIZE(image)];
    
    for (int y = image.height-1; y >= 0; y--) {
        for (int x = 0; x < image.width; x++) {
            ColorData currentPixel = bufferToSave->getPixel(x, y);
            buffer[((image.height-(y+1))*image.width+x)*4] = (png_byte) (currentPixel.getRed()*255.0);
            buffer[((image.height-(y+1))*image.width+x)*4+1] = (png_byte) (currentPixel.getGreen()*255.0);
            buffer[((image.height-(y+1))*image.width+x)*4+2] = (png_byte) (currentPixel.getBlue()*255.0);
            buffer[((image.height-(y+1))*image.width+x)*4+3] = (png_byte) (currentPixel.getAlpha()*255.0);
        }
    }
    
    if (png_image_write_to_file(&image, fileName.c_str(), 0/*convert_to_8bit*/,
                                buffer, 0/*row_stride*/, NULL/*colormap*/) != 0) {
    } else {
    }
    
    delete[] buffer;
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
void ImageHandler::savejpg(FILE* outfile, int Height, int Width, PixelBuffer* bufferToSave) {
	//Taken from iteration 2 solution
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
    JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
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
    
    /* Step 2: spe cify data destination (eg, a file) */
    /* Note: steps 2 and 3 can be done in either order. */
    
    /* Here we use the library-supplied code to send compressed data to a
     * stdio stream.  You can also write your own code to do something else.
     * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
     * requires it in order to write binary files.
     */
    jpeg_stdio_dest(&cinfo, outfile);
    
    /* Step 3: set parameters for compression */
    
    /* First we supply a description of the input image.
     * Four fields of the cinfo struct must be filled in:
     */
    cinfo.image_width = bufferToSave->getWidth(); 	/* image width and height, in pixels */
    cinfo.image_height = bufferToSave->getHeight();
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
    jpeg_set_quality(&cinfo, 100/*quality*/, TRUE /* limit to baseline-JPEG values */);
    
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
    row_stride = cinfo.image_width * 3;	/* JSAMPLEs per row in image_buffer */
    
    const int width = bufferToSave->getWidth();
    const int height = bufferToSave->getHeight();
    JSAMPLE* image_buffer = new JSAMPLE[row_stride*cinfo.image_height];
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ColorData currentPixel = bufferToSave->getPixel(x, y);
            image_buffer[((height-(y+1))*width+x)*3] = (JSAMPLE) (currentPixel.getRed()*255.0);
            image_buffer[((height-(y+1))*width+x)*3+1] = (JSAMPLE) (currentPixel.getGreen()*255.0);
            image_buffer[((height-(y+1))*width+x)*3+2] = (JSAMPLE) (currentPixel.getBlue()*255.0);
        }
    }
    
    
    while (cinfo.next_scanline < cinfo.image_height) {
        /* jpeg_write_scanlines expects an array of pointers to scanlines.
         * Here the array is only one element long, but you could pass
         * more than one scanline at a time if that's more convenient.
         */
        row_pointer[0] = & image_buffer[cinfo.next_scanline * row_stride];
        (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }
    
    delete[] image_buffer;
    
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

bool ImageHandler::ispng(const std::string & name) {
    return hasSuffix(name, ".png");
}

bool ImageHandler::hasSuffix(const std::string & str, const std::string & suffix){
    return str.find(suffix,str.length()-suffix.length()) != std::string::npos;
}
