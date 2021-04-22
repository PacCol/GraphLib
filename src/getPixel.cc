#include "graphlib.h"

// We create a function to return the complete image
std::vector<std::vector<uint8_t>> Image::getPixels() {
  return pixels;
}

// We create a function to return the requested pixel values
std::vector<uint8_t> Image::getPixel(unsigned int x, unsigned int y) {

  // If the X or Y value is out of range, we throw an error
  if(x >= width) {
    throw std::runtime_error("Error : in Image::getPixel : The X value is out of range");
  }
  else if(y >= height) {
    throw std::runtime_error("Error : in Image::getPixel : The Y value is out of range");
  }

  // We create a vector to store the pixel values
  std::vector<uint8_t> pixel;

  // We push the pixels values in the vector
  for(unsigned int i = 0; i < pixelSize; i++) {
    pixel.push_back(pixels[y][x * pixelSize + i]);
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

  // If the image is monochrome...
  if(colorSpace == 1) {

    // We get the luminance with the pixel value
    luminance = pixels[y][x * pixelSize];
  }

  // Else if the image is colored
  else if(colorSpace == 2) {

    // We create a vector to store the RGB values
    std::vector<uint8_t> pixel = getPixel(x, y);

    // We get the luminance with this operation
    luminance = (pixel[0] * 0.21 + pixel[1] * 0.71 + pixel[2] * 0.07);
  }

  // We return the luminance
  return luminance;
}
