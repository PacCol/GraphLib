#define _USE_MATH_DEFINES
#include <cmath>

#include "../image.h"

// We create a function to reduce the noise of the image
void Image::applyGaussianFilter(int kernelSize) {

  // We check the kernel
  if(kernelSize <= 0) {
    throw std::runtime_error("Error : in Image::applyGaussianFilter : The kernel size must be at least 1");
  }
  else if(kernelSize * 2 + 1 > int(height) || kernelSize * 2 + 1 > int(width)) {
    throw std::runtime_error("Error : in Image::applyGaussianFilter : The kernel size is to big for this image");
  }

  // We want to compute the gaussian weights
  double sigma = ceil((2 * float(kernelSize) + 1) / 6);

  // We create a vector to store weight
  std::vector<std::vector<double>> kernel (kernelSize * 2 + 1, std::vector<double>(kernelSize * 2 + 1));

  double sum = 0.0;

  // We apply the algorythm
  for(int i = -(kernelSize); i <= kernelSize; i++) {
    for(int j = -(kernelSize); j <= kernelSize; j++) {
      kernel[i + kernelSize][j + kernelSize] = exp( -(pow(i, 2) + pow(j, 2)) / (2 * pow(sigma, 2))) / (2 * M_PI * pow(sigma, 2) );
      sum = sum + kernel[i + kernelSize][j + kernelSize];
    }
  }
  for(int i = -(kernelSize); i <= kernelSize; i++) {
    for(int j = -(kernelSize); j <= kernelSize; j++) {
      kernel[i + kernelSize][j + kernelSize] = kernel[i + kernelSize][j + kernelSize] / sum;
    }
  }

  // We create a vector to save the new image
  std::vector<std::vector<uint8_t>> newPixels;
  // We reserve the output height
  // (We can't compute the median of the borders of the image)
  newPixels.reserve(height - kernelSize  * 2);

  // For each line of the image...
  for(unsigned int i = kernelSize; i < height - kernelSize; i++) {

    // We create a vector to save the new line
    std::vector<uint8_t> newLine;
    // We reserve the line width
    // (We can't compute the median of the borders of the image)
    newLine.reserve(width - kernelSize  * 2);

    // For each pixel of this line...
    for(unsigned int j = kernelSize; j < width - kernelSize; j++) {

      // For each value of this pixel...
      for(unsigned int k = 0; k < pixelSize; k++) {

        std::vector<std::vector<uint8_t>> averagePixels;

        for(int l = -(kernelSize); l <= kernelSize; l++) {
          std::vector<uint8_t> averageLine;
          for(int m = -(kernelSize); m <= kernelSize; m++) {
            averageLine.push_back( pixels[i + l][(j + m) * pixelSize + k] );
          }
          averagePixels.push_back(averageLine);
        }

        float average = 0;

        for(int l = 0; l < kernelSize * 2 + 1; l++) {
          for(int m = 0; m < kernelSize * 2 + 1; m++) {
            average = average + kernel[l][m] * averagePixels[l][m];
          }
        }

        // And we update the value
        newLine.push_back(uint8_t(average));
      }
    }

    // We push the new line
    newPixels.push_back(newLine);
  }

  // We update the image dimensions
  // (We can't compute the median of the borders of the image)
  width = width - kernelSize * 2;
  height = height - kernelSize * 2;

  // We update the image
  pixels = newPixels;

}
