#include <iostream>
#include <algorithm>

#include "image.h"

// We create a function to reduce the noise of the image
void Image::applyMedianFilter(unsigned int radius) {

  // We check the radius
  if(radius == 0) {
    throw std::runtime_error("Error : in Image::applyMedianFilter : The radius can't be 0");
  }
  else if(radius * 2 + 1 >= height || radius * 2 + 1 >= width) {
    throw std::runtime_error("Error : in Image::applyMedianFilter : The radius is to big");
  }

  // We create a vector to save the new image
  std::vector<std::vector<uint8_t>> newPixels;
  // We reserve the output height
  // (We can't compute the median of the borders of the image)
  newPixels.reserve(height - radius  * 2);

  // For each line of the image...
  for(unsigned int i = radius; i < height - radius; i++) {

    // We create a vector to save the new line
    std::vector<uint8_t> newLine;
    // We reserve the line width
    // (We can't compute the median of the borders of the image)
    newLine.reserve(width - radius  * 2);

    // For each pixel of this line...
    for(unsigned int j = radius; j < width - radius; j++) {

      // For each value of this pixel...
      for(unsigned int k = 0; k < pixelSize; k++) {

        // We create a vector to store the pixel values (value per value)
        // For example for an RGB image :
        // Fist, we calculate the median of the red values of the pixels of the neighborhood
        std::vector<uint8_t> medianPixels;
        medianPixels.reserve(radius * 2 + 1);

        // We add the pixels values in the vector
        for(int l = -(int(radius)); l < radius + 1; l++) {
          for(int m = -(int(radius)); m < radius + 1; m++) {
            medianPixels.push_back(pixels[i + l][(j + m) * pixelSize + k]);
          }
        }

        // We compute the median of this values
        std::sort(medianPixels.begin(), medianPixels.end());
        uint8_t median = medianPixels[medianPixels.size() / 2];

        // And we update the value
        newLine.push_back(median);
      }
    }

    // We push the new line
    newPixels.push_back(newLine);
  }

  // We update the image dimensions
  // (We can't compute the median of the borders of the image)
  width = width - radius * 2;
  height = height - radius * 2;

  // We update the image
  pixels = newPixels;
}

// We create a function to reduce the noise of the image
void Image::applyGaussianFilter(unsigned int radius) {}
