#include <iostream>

#include "jpeg.h"

// We create a function to show the edge of the objects of the image
void jpegImage::showEdgeOnly() {

  // We check the pixelSize
  if(pixelSize != 1) {
    throw std::runtime_error("Error : in jpegImage::showEdgeOnly : the image must be monochrome");
  }

  

}
