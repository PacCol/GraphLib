#include "graphlib.h"

// We create a class to create the Image object
Image::Image() {

        // We initialize an empty image
        // (The dimensions are set by default to zero)

        // By default :
        // We use pixel size 3
        pixelSize = 3;

        // And color space 2
        colorSpace = 2;
}

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

unsigned int Image::getColorSpace() {
  return colorSpace;
}
