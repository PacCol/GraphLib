#include <iostream>

#include "jpeg.h"

// We create functions to return the image informations
unsigned int jpegImage::getWidth() {
  return width;
}

unsigned int jpegImage::getHeight() {
  return height;
}

unsigned int jpegImage::getColorSpace() {
  return colorSpace;
}

unsigned int jpegImage::getPixelSize() {
  return pixelSize;
}

// We create a function to return the image
std::vector<std::vector<uint8_t>> jpegImage::getPixels() {
  return pixels;
}
