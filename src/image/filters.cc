#include <iostream>

#include "image.h"

// We create a function to reduce the noise of the image
void Image::applyMedianFilter(unsigned int filterType) {

  // We check the filter type
  if(filterType != 3 && filterType != 5) {
    throw std::runtime_error("Error : in Image::applyMedianFilter : the filter type can be 3 or 5 (3x3 or 5x5)");
  }

  // We create a vector to save the new image
  std::vector<std::vector<uint8_t>> newPixels;
  // We reserve the output height
  newPixels.reserve(height);

  // We are computing the row stride
  int rowStride = width * pixelSize;

  // For each line of the image...
  for(unsigned int i = 1; i < newHeight - 1; i++) {

    // We create a vector to save the new line
    std::vector<uint8_t> newLine;
    // We reserve the row stride
    newLine.reserve(rowStride);

    // For each pixel of this line...
    for(unsigned int j = 1; j < newWidth - 1; j++) {

      // For each value of this pixel...
      for(unsigned int k = 0; k < pixelSize; k++) {

        std::vector<uint8_t> medianPixels(8 * pixelSize);

        // ###
        // #o#
        // ###
        medianPixels.push_back(pixels[i][j * pixelSize + k]);

        // #o#
        // ###
        // ###
        medianPixels.push_back(pixels[i - 1][j * pixelSize + k]);

        // ##o
        // ###
        // ###
        medianPixels.push_back(pixels[i - 1][(j + 1) * pixelSize + k]);

        // ###
        // ##o
        // ###
        medianPixels.push_back(pixels[i][(j + 1) * pixelSize + k]);

        // ###
        // ###
        // ##o
        medianPixels.push_back(pixels[i + 1][(j + 1) * pixelSize + k]);

        // ###
        // ###
        // #o#
        medianPixels.push_back(pixels[i + 1][j * pixelSize + k]);

        // ###
        // ###
        // o##
        medianPixels.push_back(pixels[i + 1][(j - 1) * pixelSize + k]);

        // ###
        // o##
        // ###
        medianPixels.push_back(pixels[i][(j - 1) * pixelSize + k]);

        // o##
        // ###
        // ###
        medianPixels.push_back(pixels[i - 1][(j - 1) * pixelSize + k]);

        //newPixels[i][j * pixelSize + k] = newPixels[i][j * pixelSize + k]
      }
    }
    // We push the new line into the newPixels vector
    newPixels.push_back(newLine);
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

  // In developpement...

}
