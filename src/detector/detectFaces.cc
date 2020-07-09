#include <iostream>

#include "detector.h"

std::vector<std::vector<unsigned int>> faceDetector::detectHumanFaces(std::vector<std::vector<uint8_t>> pixels, unsigned int width, unsigned int height, unsigned int pixelSize) {

  // We check the pixelSize
  if(pixelSize != 1) {
    throw std::runtime_error("Error : in faceDetector::detectHumanFaces : the image must be monochrome");
  }

  // We compute the global luminance
  for(unsigned int i = 0; i < height; i++) {
    for(unsigned int j = 0; j < height; j++) {

    }
  }
  std::vector<std::vector<unsigned int>> faces;
  return faces;
}
