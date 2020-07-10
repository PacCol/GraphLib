#include <iostream>

#include "detector.h"

std::vector<std::vector<unsigned int>> faceDetector::detectHumanFaces(std::vector<std::vector<uint8_t>> pixels, unsigned int width, unsigned int height, unsigned int pixelSize) {

  // We check the pixelSize
  if(pixelSize != 1) {
    throw std::runtime_error("Error : in faceDetector::detectHumanFaces : the image must be monochrome");
  }

  // We store the total luminance into a variable
  unsigned int totalLuminance = 0;

  // For each line of the image...
  for(unsigned int i = 0; i < height; i++) {

    // For each pixel of this line ... (the pixel size is 1)
    for(unsigned int j = 0; j < width; j++) {

      // We compute the total luminance
      totalLuminance = totalLuminance + pixels[i][j];
    }
  }

  // We compute the global luminance
  uint8_t globalLuminance = int(totalLuminance / (height * width));

  // We want to convert the image into a black and white image (not to grayscale)
  // So we set a limit
  // If the luminance of the pixel if larger than the limit, the pixel will be white
  // Else the pixel will be black
  uint8_t limit = 140;

  // For each line of the image...
  for(unsigned int i = 0; i < height; i++) {

    // For each pixel of this line ... (the pixel size is 1)
    for(unsigned int j = 0; j < width; j++) {

      // If the luminance of the pixel if larger than the limit
      if(pixels[i][j] > limit) {

        // The pixel will be white
        pixels[i][j] = 255;
      }

      // Else
      else {

        // The pixel will be black
        pixels[i][j] = 0;
      }
    }
  }

  std::vector<std::vector<unsigned int>> faces;
  return faces;
}
