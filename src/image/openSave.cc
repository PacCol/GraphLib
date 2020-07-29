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
  
    struct jpeg_decompress_struct imageInfo;
    struct my_error_mgr jerr;

    // We search potential errors
    imageInfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = my_error_exit;

    if(setjmp(jerr.setjmp_buffer)) {
      throw std::runtime_error("Error : in Image::Image : can't decode this file");
      jpeg_destroy_decompress(&imageInfo);
      fclose(inputImageFile);
    }

    // We decompress the image
    jpeg_create_decompress(&imageInfo);
    jpeg_stdio_src(&imageInfo, inputImageFile);
    jpeg_read_header(&imageInfo, TRUE);
    jpeg_start_decompress(&imageInfo);

    // We store the image informations into privates variables
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

  // Else if the image is a png file...
  else if(fileType == "png") {
    
    // We start the decompression
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop imageInfo = png_create_info_struct(png);
    png_init_io(png, inputImageFile);
    png_read_info(png, imageInfo);

    // We store the image informations into privates variables
    width = png_get_image_width(png, imageInfo);
    height = png_get_image_height(png, imageInfo);
    colorType = png_get_color_type(png, imageInfo);
    bitDepth = png_get_bit_depth(png, imageInfo);

    // We continue to read the image
    png_read_update_info(png, imageInfo);
    
    // We create a table to store the pixels values
    png_bytep * rowPointers;
    rowPointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    
    // We fill in this table
    for(unsigned int y = 0; y < height; y++) {
      rowPointers[y] = (png_byte*)malloc(png_get_rowbytes(png,imageInfo));
    }

    // We finish the decompression
    png_read_image(png, rowPointers);
    png_destroy_read_struct(&png, &imageInfo, NULL);
    
    // We define some informations
    pixelSize = 3;
    colorSpace = 2;
    
    // We are computing the row stride
    unsigned int rowStride = width * pixelSize;
    
    // We convert the row pointers to a std::vector<std::vector<uint8_t>>
    
    // For each line of the image...
    for(unsigned int i = 0; i < height; i++) {
      
      // We create a vector to save this line
      std::vector<uint8_t> line;
      // We reserve the row stride
      line.reserve(rowStride);
      
      // For each pixel of this line...
      for(unsigned int j = 0; j < width; j++) {
        
        // We store the value of the pixel into a variable
        png_bytep pixel = &(rowPointers[i][j * pixelSize]);
        
        // We add the RGB values into the vector
        line.push_back(pixel[0]);
        line.push_back(pixel[1]);
        line.push_back(pixel[2]);
      }
      // We add the line into the pixels vector
      pixels.push_back(line);
    }
  }

  // Else if the file type is not supported...
  else {
    throw std::runtime_error("Error : in Image::Image : " + fileType + " is not a supported file type");
  }

  // We close the image file
  fclose(inputImageFile);
}

void Image::save(char * fileName, int quality, std::string fileType) {

  // We try to create the image file
  FILE * outputImageFile;
  if ((outputImageFile = fopen(fileName, "wb")) == NULL) {
    throw std::runtime_error("Error : in Image::save : can't create this file");
  }
  
  // If the image to save will be a jpeg file...
  if(fileType == "jpg" || fileType == "jpeg") {
    
    struct jpeg_compress_struct imageInfo;
    struct jpeg_error_mgr jerr;

    imageInfo.err = jpeg_std_error(&jerr);

    // We start to compress the image
    jpeg_create_compress(&imageInfo);
    jpeg_stdio_dest(&imageInfo, outputImageFile);
  
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
      JSAMPROW rowPointer[1];

      // We read the image vector line per line
      rowPointer[0] = const_cast<JSAMPROW>(vecLine.data());

      // And we write the image
      jpeg_write_scanlines(&imageInfo, rowPointer, 1);
    }

    // Then we finish the decompression
    jpeg_finish_compress(&imageInfo);
    jpeg_destroy_compress(&imageInfo);
  }
  
  // Else if the image will be a png file...
  else if(fileType == "png") {
    
    /*png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop imageInfo = png_create_info_struct(png);
    png_init_io(png, outputImageFile);

    png_set_IHDR(png, imageInfo, width, height, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, imageInfo);
    png_set_filler(png, 0, PNG_FILLER_AFTER);
    
    png_bytep * rowPointers = NULL;
    
    

    png_write_image(png, rowPointers);
    png_write_end(png, NULL);

    png_destroy_write_struct(&png, &imageInfo);*/
  }
  
  // Else if the file type is not supported...
  else {
    throw std::runtime_error("Error : in Image::save : " + fileType + " is not a supported file type");
  }

  // We close the image file
  fclose(outputImageFile);
}
