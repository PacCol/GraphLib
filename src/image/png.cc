#include <iostream>
#include <algorithm>

// We include the libpng
#include <png.h>

#include "image.h"

// We create a function to open a png image
void Image::openPngImage(char* fileName) {

  // We try to open the image file
  FILE * inputImageFile;
  if((inputImageFile = fopen(fileName, "rb")) == NULL) {
    throw std::runtime_error("Error : in Image::openPngImage : can't open this file");
  }

  // We start the decompression
  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop imageInfo = png_create_info_struct(png);
  png_init_io(png, inputImageFile);
  png_read_info(png, imageInfo);

  // We store the image informations into privates variables
  width = png_get_image_width(png, imageInfo);
  height = png_get_image_height(png, imageInfo);
  unsigned int colorType = png_get_color_type(png, imageInfo);
  //unsigned int bitDepth = png_get_bit_depth(png, imageInfo);

  // If the color type is not supported we throw an error
  if(colorType == 3) {
    throw std::runtime_error("Error : in Image::openPngImage : this color type is not supported");
  }

  // We continue to read the image
  png_read_update_info(png, imageInfo);

  // We want to store the pixels into a vector
  pixels.resize(height, std::vector<png_byte>(width * pixelSize));
  std::vector<png_byte *> ppixels(height);
  std::transform(pixels.begin(), pixels.end(), ppixels.begin(), [](auto & vector){ return vector.data(); });

  // We finish the decompression
  png_read_image(png, ppixels.data());
  png_destroy_read_struct(&png, &imageInfo, NULL);

  // We close the image file
  fclose(inputImageFile);

  // We define the color space and the pixelSize
  // One value (monochrome)
  if(colorType == 0) {
    colorSpace = 1;
    pixelSize = 1;
  }
  // Three values (RGB)
  else if(colorType == 2) {
    colorSpace = 2;
    pixelSize = 3;
  }
  // Two values (monochrome with an alpha channel)
  else if(colorType == 4) {
    colorSpace = 0;
    pixelSize = 2;
    alphaUsed = true;
  }
  // Four values (RGB with an alpha channel)
  else if(colorType == 6) {
    colorSpace = 12;
    pixelSize = 4;
    alphaUsed = true;
  }
}

// We create a function to save a png image
void Image::savePngImage(char* fileName) {

  // We try to create the image file
  FILE * outputImageFile;
  if ((outputImageFile = fopen(fileName, "wb")) == NULL) {
    throw std::runtime_error("Error : in Image::savePngImage : can't create this file");
  }

  // We start to compress the image
  png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop imageInfo = png_create_info_struct(png);
  png_init_io(png, outputImageFile);

  // We configure the library
  if(alphaUsed) {
    if(colorSpace == 0 && pixelSize == 2) {
      png_set_IHDR(png, imageInfo, width, height, 8, PNG_COLOR_TYPE_GRAY_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    }
    else if(colorSpace == 12) {
      png_set_IHDR(png, imageInfo, width, height, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    }
  }
  else {
    if(colorSpace == 1) {
      png_set_IHDR(png, imageInfo, width, height, 8, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    }
    else if(colorSpace == 3) {
      png_set_IHDR(png, imageInfo, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    }
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

  // We close the image file
  fclose(outputImageFile);
}
