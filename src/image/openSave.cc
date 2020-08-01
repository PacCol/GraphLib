#include <iostream>

#include <algorithm>

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

// We create a class to create the Image object
Image::Image(char* fileName, std::string fileType) {

  // We try to open the image file
  FILE * inputImageFile;
  if((inputImageFile = fopen(fileName, "rb")) == NULL) {
    throw std::runtime_error("Error : in Image::Image : can't open this file");
  }

  // If the image is a jpeg file...
  if(fileType == "jpg" || fileType == "jpeg") {

    // We crete a jpeg decompression structure
    struct jpeg_decompress_struct imageInfo;
    struct my_error_mgr jerr;

    // We search potential errors
    imageInfo.err = jpeg_std_error(&jerr.pub);

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
    alphaUsed = false;

    // We are computing the row stride
    int rowStride = width * pixelSize;

    // We reserve the output height
    pixels.reserve(height);

    // For each line
    while(imageInfo.output_scanline < height) {

      // We create a vector to store the scanned line
      std::vector<uint8_t> scannedLine(rowStride);
      scannedLine.reserve(rowStride);
      uint8_t* p = scannedLine.data();

      // We read the image
      jpeg_read_scanlines(&imageInfo, &p, 1);

      // We put the new line into a vector
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
    //unsigned int colorType = png_get_color_type(png, imageInfo);
    //unsigned int bitDepth = png_get_bit_depth(png, imageInfo);
    alphaUsed = true;

    // We define some informations
    pixelSize = 4;
    colorSpace = 2;

    // We continue to read the image
    png_read_update_info(png, imageInfo);

    // We want to store the pixels into a vector
    pixels.resize(height, std::vector<png_byte>(width * pixelSize));
    std::vector<png_byte *> ppixels(height);
    std::transform(pixels.begin(), pixels.end(), ppixels.begin(), [](auto & vector){ return vector.data(); });

    // We finish the decompression
    png_read_image(png, ppixels.data());
    png_destroy_read_struct(&png, &imageInfo, NULL);
  }

  // Else if the file type is not supported...
  else {
    throw std::runtime_error("Error : in Image::Image : " + fileType + " is not a supported option");
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

    // If the image has an alpha channel, we delete it
    if(alphaUsed) {
      removeAlphaChannel();
    }

    // We create a jpeg compression structure
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

    // We check the pixelSize
    if(pixelSize == 1) {
      throw std::runtime_error("Error : in Image::save : can't save a monochrome image as PNG");
    }

    // We start to compress the image
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop imageInfo = png_create_info_struct(png);
    png_init_io(png, outputImageFile);

    // We configure the library
    // If the alpha channel is used, we save it
    if(alphaUsed) {
      png_set_IHDR(png, imageInfo, width, height, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    }
    // Else we save the RGB values
    else {
      png_set_IHDR(png, imageInfo, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    }

    // We continue to compress the image
    png_write_info(png, imageInfo);

    // We get the pixels values
    std::vector<png_byte *> ppixels(height);
    std::transform(pixels.begin(), pixels.end(), ppixels.begin(), [](auto & vector){ return vector.data(); });
    png_write_image(png, ppixels.data());

    // We finish the compression
    png_write_end(png, NULL);
    png_destroy_write_struct(&png, &imageInfo);
  }

  // Else if the file type is not supported...
  else {
    throw std::runtime_error("Error : in Image::save : " + fileType + " is not a supported option");
  }

  // We close the image file
  fclose(outputImageFile);
}
