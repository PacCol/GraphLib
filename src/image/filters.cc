#include <iostream>
#include <algorithm>

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

        std::vector<uint8_t> medianPixels;
        medianPixels.reserve(9);

        medianPixels.push_back(pixels[i - 1][(j -1) * pixelSize + k]);
        medianPixels.push_back(pixels[i][(j - 1) * pixelSize + k]);
        medianPixels.push_back(pixels[i + 1][(j - 1) * pixelSize + k]);

        medianPixels.push_back(pixels[i - 1][j * pixelSize + k]);
        medianPixels.push_back(pixels[i][j * pixelSize + k]);
        medianPixels.push_back(pixels[i + 1][j * pixelSize + k]);

        medianPixels.push_back(pixels[i - 1][(j + 1) * pixelSize + k]);
        medianPixels.push_back(pixels[i][(j + 1) * pixelSize + k]);
        medianPixels.push_back(pixels[i + 1][(j + 1) * pixelSize + k]);

        std::sort(medianPixels.begin(), medianPixels.end());

        uint8_t median = medianPixels[4];

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

  // In developpement...

}
