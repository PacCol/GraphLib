#include <iostream>
#include <algorithm>
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

  std::vector<std::vector<uint8_t>> gradient = pixels;

  std::vector<std::vector<float>> direction(height, std::vector<float>(width));

  // For each line of the image...
  for(unsigned int i = 1; i < height - 1; i++) {

    // For each pixel of this line...
    for(unsigned int j = 1; j < width - 1; j++) {

      uint8_t SXvalue = (-1 * pixels[i - 1][j - 1]
                        + 1 * pixels[i - 1][j + 1]
                        + -2 * pixels[i][j - 1]
                        + 2 * pixels[i][j + 1]
                        + -1 * pixels[i + 1][j - 1]
                        + 1 * pixels[i + 1][j + 1] ) / 8;

      uint8_t SYvalue = (-1 * pixels[i - 1][j - 1]
                        + 1 * pixels[i - 1][j + 1]
                        + -2 * pixels[i - 1][j]
                        + 2 * pixels[i + 1][j]
                        + -1 * pixels[i + 1][j - 1]
                        + 1 * pixels[i + 1][j + 1] ) / 8;

      gradient[i][j] = static_cast<unsigned int>( sqrt( pow(SXvalue * pixels[i][j], 2) + pow(SYvalue * pixels[i][j], 2) ));

      //direction[i][j] = atan(SYvalue / SXvalue);
    }
  }

  pixels = gradient;
  width = width;
  height = height;
}
