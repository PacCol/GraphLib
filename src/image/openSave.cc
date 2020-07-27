#include <iostream>

// We include the libjpeg
#include <jpeglib.h>
#include <setjmp.h>

// We include the libpng
#include <png.h>

#include "image.h"

struct my_error_mgr {
  struct jpeg_error_mgr pub;
  jmp_buf setjmp_buffer;
};

typedef struct my_error_mgr * my_error_ptr;

void my_error_exit(j_common_ptr imageInfo) {
  my_error_ptr myerr = (my_error_ptr) imageInfo->err;
  (*imageInfo->err->output_message) (imageInfo);
  longjmp(myerr->setjmp_buffer, 1);
}

// We create a class to create the Image object
Image::Image(char* fileName, std::string fileType) {

  // We try to open the image file
  FILE * inputImageFile;
  if((inputImageFile = fopen(fileName, "rb")) == NULL) {
    throw std::runtime_error("Error : in Image::Image : can't open this file");
    abort();
  }
  
  // If the image is a jpeg file...
  if(fileType == "jpg" || fileType == "jpeg") {
  
    // We create the jpeg decompression struct
    struct jpeg_decompress_struct imageInfo;
    struct my_error_mgr jerr;

    // We search potential errors
    imageInfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = my_error_exit;

    if(setjmp(jerr.setjmp_buffer)) {
      throw std::runtime_error("Error : in Image::Image : can't decode this file");
      jpeg_destroy_decompress(&imageInfo);
      fclose(inputImageFile);
      abort();
    }

    // We decompress the image
    jpeg_create_decompress(&imageInfo);
    jpeg_stdio_src(&imageInfo, inputImageFile);
    jpeg_read_header(&imageInfo, TRUE);
    jpeg_start_decompress(&imageInfo);

    // We store the image informations into public variables
    width = imageInfo.output_width;
    height = imageInfo.output_height;
    colorSpace = imageInfo.out_color_space;
    pixelSize = imageInfo.output_components;

    // We are computing the row stride
    int rowStride = width * pixelSize;

    // We reserve the output height
    pixels.reserve(height);

    // For each line
    while(imageInfo.output_scanline < height) {
      std::vector<uint8_t> scannedLine(rowStride);
      scannedLine.reserve(rowStride);
      uint8_t* p = scannedLine.data();

      // We read the image
      jpeg_read_scanlines(&imageInfo, &p, 1);

      // We put the pixels values into a vector
      pixels.push_back(scannedLine);
    }

    // Then we finish the decompression
    jpeg_finish_decompress(&imageInfo);
    jpeg_destroy_decompress(&imageInfo);
  }

  // If the image is a png file...
  else if(fileType == "png") {
    
    
    
    
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    
    if(!png) {
      abort();
    }

    png_infop imageInfo = png_create_info_struct(png);
    
    if(!imageInfo) {
      abort();
    }

    if(setjmp(png_jmpbuf(png))) {
      abort();
    }

    png_init_io(png, inputImageFile);
    png_read_info(png, imageInfo);

    width = png_get_image_width(png, imageInfo);
    height = png_get_image_height(png, imageInfo);
    colorType = png_get_color_type(png, imageInfo);
    bitDepth = png_get_bit_depth(png, imageInfo);

    if(bitDepth == 16) {
      png_set_strip_16(png);
    }

    if(colorType == PNG_COLOR_TYPE_PALETTE) {
      png_set_palette_to_rgb(png);
    }

    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if(colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8) {
      png_set_expand_gray_1_2_4_to_8(png);
    }

    if(png_get_valid(png, imageInfo, PNG_INFO_tRNS)) {
      png_set_tRNS_to_alpha(png);
    }

    // These color_type don't have an alpha channel then fill it with 0xff.
    if(colorType == PNG_COLOR_TYPE_RGB || colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_PALETTE) {
      png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
    }

    if(colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY_ALPHA) {
      png_set_gray_to_rgb(png);
    }

    png_read_update_info(png, imageInfo);
    
    png_bytep * row_pointers;

    if(row_pointers) {
      abort();
    }

    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for(unsigned int y = 0; y < height; y++) {
      row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,imageInfo));
    }

    png_read_image(png, row_pointers);

    png_destroy_read_struct(&png, &imageInfo, NULL);
    
    pixelSize = 3;
    unsigned int rowStride = width * pixelSize;
    
    for(unsigned int i = 0; i < height; i++) {
      
      std::vector<uint8_t> line;
      line.reserve(rowStride);
      
      png_bytep row = row_pointers[i];
      
      for(unsigned int j = 0; j < height; j++) {
        
        png_bytep pixel = &(row[j * pixelSize]);
        
        line.push_back(pixel[0]);
        line.push_back(pixel[1]);
        line.push_back(pixel[2]);
      }
      
      pixels.push_back(line);
    }
  }

  // The file type is not supported
  else {
    throw std::runtime_error("Error : in Image::Image : " + fileType + " is not a supported file type");
  }

  // We close the image file
  fclose(inputImageFile);
}

void Image::save(char * fileName, int quality, std::string fileType) {

  struct jpeg_compress_struct imageInfo;
  struct jpeg_error_mgr jerr;

  // We try to create the image file
  FILE * outputJpegFile;
  if ((outputJpegFile = fopen(fileName, "wb")) == NULL) {
    throw std::runtime_error("Error : in Image::save : can't create this file");
    abort();
  }

  imageInfo.err = jpeg_std_error(&jerr);

  // We start to compress the image
  jpeg_create_compress(&imageInfo);
  jpeg_stdio_dest(&imageInfo, outputJpegFile);

  // We define some informations
  imageInfo.image_width = width;
  imageInfo.image_height = height;
  imageInfo.input_components = pixelSize;
  imageInfo.in_color_space = J_COLOR_SPACE(colorSpace);

  // We continue to compress the image
  jpeg_set_defaults(&imageInfo);
  jpeg_set_quality(&imageInfo, quality, TRUE);
  jpeg_start_compress(&imageInfo, TRUE);

  for(auto const& vecLine : pixels) {
    JSAMPROW rowPtr[1];

    // We read the image vector line per line
    rowPtr[0] = const_cast<JSAMPROW>(vecLine.data());

    // And we write the image
    jpeg_write_scanlines(&imageInfo, rowPtr, 1);
  }

  // Then we finish the decompression
  jpeg_finish_compress(&imageInfo);
  jpeg_destroy_compress(&imageInfo);

  // We close the image file
  fclose(outputJpegFile);
}
