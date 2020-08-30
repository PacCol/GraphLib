#include <iostream>
#include <algorithm>

#define _USE_MATH_DEFINES
#include <cmath>

#include "image.h"

// We create a function to reduce the noise of the image
void Image::applyMedianFilter() {

  // We create a vector to save the new image
  std::vector<std::vector<uint8_t>> newPixels = pixels;

  // For each line of the image...
  for(unsigned int i = 1; i < height - 1; i++) {

    // For each pixel of this line...
    for(unsigned int j = 1; j < width - 1; j++) {

      // For each value of this pixel...
      for(unsigned int k = 0; k < pixelSize; k++) {

        // We create a vector to store the pixel values (value per value)
        // For example for an RGB image :
        // Fist, we calculate the median of the red values of the pixels of the neighborhood
        std::vector<uint8_t> medianPixels;
        // We reserve 9 places (3x3)
        medianPixels.reserve(9);

        // We add the pixels values in the vector
        for(int l = -1; l < 2; l++) {
          for(int m = -1; m < 2; m++) {
            medianPixels.push_back(pixels[i + l][(j + m) * pixelSize + k]);
          }
        }

        // We compute the median of this values
        std::sort(medianPixels.begin(), medianPixels.end());
        uint8_t median = medianPixels[4];

        // And we update the value
        newPixels[i][j * pixelSize + k] = median;
      }
    }
  }
  // We update the image
  pixels = newPixels;
}

// We create a function to reduce the noise of the image
void Image::applyGaussianFilter(unsigned int radius) {

  // We create a vector to save the new image
  std::vector<std::vector<uint8_t>> newPixels = pixels;

  // For each line of the image...
  for(unsigned int i = 1; i < height - 1; i++) {

    // For each pixel of this line...
    for(unsigned int j = 1; j < width - 1; j++) {

      // For each value of this pixel...
      for(unsigned int k = 0; k < pixelSize; k++) {

        // We create a vector to store the pixel values (value per value)
        // For example for an RGB image :
        // Fist, we calculate the median of the red values of the pixels of the neighborhood
        std::vector<uint8_t> medianPixels;
        // We reserve 9 places (3x3)
        medianPixels.reserve(9);

        // We add the pixels values in the vector
        for(int l = -1; l < 2; l++) {
          for(int m = -1; m < 2; m++) {
            medianPixels.push_back(pixels[i + l][(j + m) * pixelSize + k]);
          }
        }

        // We compute the median of this values
        std::sort(medianPixels.begin(), medianPixels.end());
        uint8_t median = medianPixels[4];

        // And we update the value
        newPixels[i][j * pixelSize + k] = median;
      }
    }
  }
  // We update the image
  pixels = newPixels;
}
