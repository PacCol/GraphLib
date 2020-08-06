#include <iostream>

#include "image.h"

// We create functions to return the image informations
unsigned int Image::getWidth() {
  return width;
}

unsigned int Image::getHeight() {
  return height;
}

unsigned int Image::getPixelSize() {
  return pixelSize;
}

bool Image::isAlphaChannelUsed() {
  return alphaUsed;
}

unsigned int Image::getColorSpace() {
  return colorSpace;
}

unsigned int Image::getColorType() {
  return colorType;
}
