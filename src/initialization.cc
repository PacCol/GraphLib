#include "graphlib.h"

// We create a class to create the Image object
Image::Image() {

  // We initialize an empty image
  // (The dimensions are set by default to zero)

  // By default :
  // We use a common pixel size
  pixelSize = 3;

  // We use a common color space
  colorSpace = 2;

  // We use a common color type
  colorType = 2;
}
