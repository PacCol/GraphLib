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
  colorType = png_get_color_type(png, imageInfo);
  //unsigned int bitDepth = png_get_bit_depth(png, imageInfo);

  // If the color type is a palette index, we convert it into RGB
  if(colorType == PNG_COLOR_TYPE_PALETTE) {
    png_set_palette_to_rgb(png);
    colorType = PNG_COLOR_TYPE_RGB;
  }

  // We define some informations
  if(colorType == PNG_COLOR_TYPE_GRAY) {
    pixelSize = 1;
    colorSpace = 1;
  }
  else if(colorType == PNG_COLOR_TYPE_GRAY_ALPHA) {
    pixelSize = 2;
    colorSpace = 1;
    alphaUsed = true;
  }
  else if(colorType == PNG_COLOR_TYPE_RGB) {
    pixelSize = 3;
    colorSpace = 2;
  }
  else if(colorType == PNG_COLOR_TYPE_RGBA) {
    pixelSize = 4;
    colorSpace = 2;
    alphaUsed = true;
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
  png_set_IHDR(png, imageInfo, width, height, 8, colorType, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

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
