#include <iostream>

#include "detector.h"

std::vector<std::vector<uint8_t>> faceDetector::detectHumanEyes() {

  for(uint8_t faceGlobalLuminance = 220; faceGlobalLuminance != 30; faceGlobalLuminance = faceGlobalLuminance - 10) {

    convertImageToBlackAndWhite(faceGlobalLuminance);
  }

  return pixels;
}

// We create a function to convert the loaded image to black and white
void faceDetector::convertImageToBlackAndWhite(uint8_t limit) {

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
}
