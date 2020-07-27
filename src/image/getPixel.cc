#include <iostream>

#include "image.h"

// We create a function to return the complete image
std::vector<std::vector<uint8_t>> Image::getPixels() {
  return pixels;
}

// We create a function to return the requested RGB value
std::vector<uint8_t> Image::getRgbColor(unsigned int x, unsigned int y) {

  // If the X or Y value is out of range, we throw an error
  if(x >= width) {
    throw std::runtime_error("Error : in Image::getRgbColor : The X value is out of range");
  }
  else if(y >= height) {
    throw std::runtime_error("Error : in Image::getRgbColor : The Y value is out of range");
  }

  // If the image is monochrome, we throw an error
  if(pixelSize == 1) {
    throw std::runtime_error("Error : in Image::getRgbColor : The image is monochrome");
  }

  // We create a vector to store the RGB values
  std::vector<uint8_t> pixel;

  // We push the pixels values in the vector
  for(int i = 0; i < 3; i++) {
    pixel.push_back(pixels[y][x * 3 + i]);
  }

  // We return the scanned pixel
  return pixel;
}

// We create a function to return the luminance of a pixel
uint8_t Image::getLuminance(unsigned int x, unsigned int y) {

  // If the X or Y value is out of range, we throw an error
  if(x >= width) {
    throw std::runtime_error("Error : in Image::getLuminance : The X value is out of range");
  }
  else if(y >= height) {
    throw std::runtime_error("Error : in Image::getLuminance : The Y value is out of range");
  }

  // We store the luminance into a variable
  uint8_t luminance = 0;

  // If the image is monochrome
  if(pixelSize == 1) {

    // We get the luminance with the pixel value
    luminance = pixels[y][x];
  }

  // Else if the image is colored
  else if(pixelSize == 3) {

    // We create a vector to store the RGB values
    std::vector<uint8_t> pixel = getRgbColor(x, y);

    // We get the luminance with this operation
    luminance = (pixel[0] * 0.21 + pixel[1] * 0.71 + pixel[2] * 0.07);
  }

  // We return the luminance
  return luminance;
}
