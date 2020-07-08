#include <iostream>

#include "jpeg.h"

// We create a function to set the RGB values of a pixel
void jpegImage::setRgbColor(std::vector<uint8_t> rgbValues, unsigned int x, unsigned int y) {

  // If the X or Y value is out of range, we throw an error
  if(x >= width) {
    throw std::runtime_error("Error : in jpegImage::setRgbColor : The X value is out of range");
  }
  else if(y >= height) {
    throw std::runtime_error("Error : in jpegImage::setRgbColor : The Y value is out of range");
  }

  // If the image is monochrome, we throw an error
  if(pixelSize == 1) {
    throw std::runtime_error("Error : in jpegImage::setRgbColor : The image is monochrome");
  }

  // We set the RGB values
  for(int i = 0; i < 3; i++) {
    pixels[y][x * 3 + i] = rgbValues[i];
  }
}

// We create a function to set the luminance of a pixel
void jpegImage::setLuminance(uint8_t luminance, unsigned int x, unsigned int y) {
  std::cout << "New Luminance : " << +luminance << "\n";
}
