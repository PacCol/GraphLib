#include <iostream>

#include "detector.h"

std::vector<std::vector<unsigned int>> faceDetector::detectHumanFaces(std::vector<std::vector<uint8_t>> pixels, unsigned int width, unsigned int height, unsigned int pixelSize) {

  // We check the pixelSize
  if(pixelSize != 3) {
    throw std::runtime_error("Error : in faceDetector::detectHumanFaces : the image must be monochrome");
  }

  // We compute the global luminance
  
}
