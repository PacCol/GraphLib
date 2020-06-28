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
    throw std::runtime_error("Error : can't open this file");
    return;
  }

  // We search potential errors
  imageInfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;

  if (setjmp(jerr.setjmp_buffer)) {
    throw std::runtime_error("Error : can't decode this file");
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
    throw std::runtime_error("Error : The X value is out of range");
  }
  else if(y >= height) {
    throw std::runtime_error("Error : The Y value is out of range");
  }

  // If the image is monochrome, we throw an error
  if(pixelSize == 1) {
    throw std::runtime_error("Error : The image is monochrome");
  }

  // We create a vector
  std::vector<uint8_t> scannedPixel;

  // We push the pixels values in the vector
  for(int i = 0; i < 3; i++) {
    scannedPixel.push_back(pixels[y][x * pixelSize + i]);
  }

  // We return the scanned pixel
  return scannedPixel;
}

uint8_t jpegImage::getLuminance(int x, int y) {
  // If the image is monochrome
  if(pixelSize == 1) {
    // We just return the pixel value
    return pixels[y][x];
  }

  // Else if the image is colored
  else if (pixelSize == 3) {
    // We get the RGB pixel value
    std::vector<uint8_t> pixel = getRgbColor(x, y);

    // We get the luminance with this operation
    uint8_t luminance = (pixel[0] * 0.21 + pixel[1] * 0.71 + pixel[2] * 0.07);

    // We return the luminance
    return luminance;
  }
}

void jpegImage::resize(int newWidth) {
  // We check the new width value
  if(newWidth == 0) {
    throw std::runtime_error("Error : The new width can't be 0");
  }
  else if(newWidth > width) {
    throw std::runtime_error("Error : The new width can't be bigger");
  }
  else if(newWidth == width) {
    return;
  }

  int newHeight = newWidth * width / 1024 * 768 / width;
  std::cout << "newHeight : " << newHeight << "\n";

  std::vector<std::vector<uint8_t>> newPixels;

  for(int i = 0; i < newHeight; i++) {
    std::vector<uint8_t> newLine;

    for(int j = 0; j < newWidth; j++) {
      uint8_t R = pixels[i][j];
    }
    newPixels.push_back(newLine);
  }
}
