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
