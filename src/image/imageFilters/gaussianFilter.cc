#define _USE_MATH_DEFINES
#include <cmath>

#include "../image.h"

// We create a function to reduce the noise of the image
void Image::applyGaussianFilter(unsigned int kernelSize) {

  unsigned int kernelHeight = 2 * kernelSize + 1;
  unsigned int kernelWidth = 2 * kernelSize + 1;
  double sigma = ceil((2 * kernelSize + 1) / 6);;

  std::vector<std::vector<uint8_t>> kernel(kernelHeight, std::vector<uint8_t>(kernelWidth));

  double sum=0.0;

  for(unsigned int i = 0; i < kernelHeight; i++) {
    for(unsigned int j = 0; j < kernelWidth; j++) {
      kernel[i][j] = exp( -(i * i + j * j) / (2 * sigma * sigma))/(2 * M_PI * sigma * sigma );
      sum = sum + kernel[i][j];
    }
  }

  for(unsigned int i = 0; i < kernelHeight; i++) {
    for(unsigned int j = 0; j < kernelWidth; j++) {
      kernel[i][j] = kernel[i][j] / sum;
    }
  }
}
