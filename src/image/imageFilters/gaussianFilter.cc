#define _USE_MATH_DEFINES
#include <cmath>

#include "../image.h"

// We create a function to reduce the noise of the image
void Image::applyGaussianFilter(int kernelSize) {

  // We check the kernel
  if(kernelSize <= 0) {
    throw std::runtime_error("Error : in Image::applyGaussianFilter : The kernel size must be at least 1");
  }
  else if(kernelSize * 2 + 1 > height || kernelSize * 2 + 1 > width) {
    throw std::runtime_error("Error : in Image::applyGaussianFilter : The kernel size is to big for this image");
  }

  // We want to compute the gaussian weights
  double sigma = ceil((2 * float(kernelSize) + 1) / 6);

  // We create a vector to store weight
  std::vector<std::vector<double>> kernel(kernelHeight, std::vector<double>(kernelWidth));

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
        averagePixels.reserve(kernelSize * 2 + 1);

        for(int i = -(kernelSize); i <= kernelSize; i++) {
          for(int j = -(kernelSize); j <= kernelSize; j++) {
            kernel[i + kernelSize][j + kernelSize] = exp( -(pow(i, 2) + pow(j, 2)) / (2 * pow(sigma, 2))) / (2 * M_PI * pow(sigma, 2) );
            sum = sum + kernel[i + kernelSize][j + kernelSize];
          }
        }

        // And we update the value
        newLine.push_back(median);
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
