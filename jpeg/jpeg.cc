#include <iostream>
#include <jpeglib.h>
#include <setjmp.h>

#include "jpeg.h"

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

// We create a class to create jpegImage object
jpegImage::jpegImage(char* fileName) {
  struct jpeg_decompress_struct imageInfo;
  struct my_error_mgr jerr;

  // We try to open the image file
  FILE * jpegFile;
  if ((jpegFile = fopen(fileName, "rb")) == NULL) {
    throw std::runtime_error("Fatal error : can't open this file");
    return;
  }

  // We search potential errors
  imageInfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;

  if (setjmp(jerr.setjmp_buffer)) {
    throw std::runtime_error("Fatal error : can't decode this file");
    jpeg_destroy_decompress(&imageInfo);
    fclose(jpegFile);
    return;
  }

  // We decompress the image
  jpeg_create_decompress(&imageInfo);
  jpeg_stdio_src(&imageInfo, jpegFile);
  jpeg_read_header(&imageInfo, TRUE);
  jpeg_start_decompress(&imageInfo);

  // We store the image informations into public variables
  width = imageInfo.output_width;
  height = imageInfo.output_height;
  colorSpace = imageInfo.out_color_space;
  pixelSize = imageInfo.output_components;

  int rowStride = width * pixelSize;

  // We read the image line per line
  while(imageInfo.output_scanline < height) {
    std::vector<uint8_t> scannedLine(rowStride);
    uint8_t* p = scannedLine.data();
    jpeg_read_scanlines(&imageInfo, &p, 1);

    // We put the pixels values into a table
    pixels.push_back(scannedLine);
  }

  // Then we finish the decompression
  jpeg_finish_decompress(&imageInfo);
  jpeg_destroy_decompress(&imageInfo);

  // We close the image file
  fclose(jpegFile);
}

std::vector<uint8_t> jpegImage::getRgbColor(int x, int y) {
  // If the X or Y value is out of range, we throw an error
  if(x >= width) {
    throw std::runtime_error("Fatal error : The X value is out of range");
  }
  else if(y >= height) {
    throw std::runtime_error("Fatal error : The Y value is out of range");
  }
  
  // We create a vector
  std::vector<uint8_t> scannedPixel;

  // We push the pixels values in the vector
  for(int i = 0; i < pixelSize; i++) {
    scannedPixel.push_back(pixels[y][x * pixelSize + i]);
  }

  // Return the scanned pixel
  return scannedPixel;
}
