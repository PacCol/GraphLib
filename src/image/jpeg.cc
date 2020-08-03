#include <iostream>

// We include the libjpeg
#include <jpeglib.h>
#include <setjmp.h>

#include "image.h"

struct my_error_mgr {
  struct jpeg_error_mgr pub;
  jmp_buf setjmp_buffer;
};

// We create a function to open a jpeg image
void Image::openJpegImage(char* fileName) {

  // We try to open the image file
  FILE * inputImageFile;
  if((inputImageFile = fopen(fileName, "rb")) == NULL) {
    throw std::runtime_error("Error : in Image::openJpegImage : can't open this file");
  }

  // We create a jpeg decompression structure
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

  // We check the colorSpace
  if(colorSpace != 1 || colorSpace != 3 || colorSpace != 12) {
    throw std::runtime_error("Error : in Image::openJpegImage : this color space is not supported");
  }

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

  // We close the image file
  fclose(inputImageFile);
}

// We create a function to save a jpeg image
void Image::saveJpegImage(char* fileName, unsigned int quality) {

  // We check some parameters
  if(alphaUsed && pixelSize == 2) {
    throw std::runtime_error("Error : in Image::saveJpegImage : the alpha channel can't be saved for monochrome image");
  }

  // We try to create the image file
  FILE * outputImageFile;
  if ((outputImageFile = fopen(fileName, "wb")) == NULL) {
    throw std::runtime_error("Error : in Image::saveJpegImage : can't create this file");
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

  // We close the image file
  fclose(outputImageFile);
}
