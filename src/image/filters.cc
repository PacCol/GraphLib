#include <iostream>

#include "image.h"

// We create a function to reduce the noise of the image
void Image::applyMedianFilter(unsigned int filterType) {

  // We check the filter type
  if(filterType != 3 || filterType != 5) {
    throw std::runtime_error("Error : in Image::getAlphaValue : the filter type can be 3 or 5 (3x3 or 5x5)");
  }



}

// We create a function to show the edge of the objects of the image
void Image::applyCannyFilter() {

  // If the image is not a grayscale, we convert it
  if(colorSpace != 1) {
    convertToGrayscale();
  }

  // If the image has an alpha channel, we remove it
  if(alphaUsed) {
    removeAlphaChannel();
  }



}
