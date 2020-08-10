#include <iostream>

#include "image.h"

// We create a function to show the edge of the objects of the image
void Image::showEdgeOnly() {

  // If the image is not a grayscale, we convert it
  if(colorSpace != 1) {
    convertToGrayscale();
  }

  // If the image has an alpha channel, we remove it
  if(alphaUsed) {
    removeAlphaChannel();
  }

  

}
