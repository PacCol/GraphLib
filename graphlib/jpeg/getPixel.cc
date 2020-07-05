#include <iostream>

#include "jpeg.h"

// We create a function to return the requested RGB value
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
  // We reserve the pixelSize of a colored image
  scannedPixel.reserve(3);

  // We push the pixels values in the vector
  for(int i = 0; i < 3; i++) {
    scannedPixel.push_back(pixels[y][x * pixelSize + i]);
  }

  // We return the scanned pixel
  return scannedPixel;
}

// We create a function to return the luminance of a pixel
uint8_t jpegImage::getLuminance(int x, int y) {

  // If the X or Y value is out of range, we throw an error
  if(x >= width) {
    throw std::runtime_error("Error : The X value is out of range");
  }
  else if(y >= height) {
    throw std::runtime_error("Error : The Y value is out of range");
  }

  // We store the luminance into a variable
  uint8_t luminance = 0;

  // If the image is monochrome
  if(pixelSize == 1) {

    // We just return the pixel value
    luminance = pixels[y][x];
  }

  // Else if the image is colored
  else if (pixelSize == 3) {

    // We get the RGB pixel value
    std::vector<uint8_t> pixel = getRgbColor(x, y);

    // We get the luminance with this operation
    luminance = (pixel[0] * 0.21 + pixel[1] * 0.71 + pixel[2] * 0.07);
  }

  // We return the luminance
  return luminance;
}
