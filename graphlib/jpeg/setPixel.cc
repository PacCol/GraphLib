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

  for(int i = 0; i < pixelSize; i++) {
    std::cout << "rgbValues : " << +rgbValues[i] << "\n";
    if(+rgbValues[i] > 255) {
      throw std::runtime_error("Error : in jpegImage::setRgbColor : The RGB values must be less than 256");
    }
  }

  // We set the RGB values
  for(int i = 0; i < pixelSize; i++) {
    pixels[y][x * pixelSize + i] = rgbValues[i];
  }
}
