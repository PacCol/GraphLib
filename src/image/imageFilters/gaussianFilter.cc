#define _USE_MATH_DEFINES
#include <cmath>

#include "../image.h"

// We create a function to reduce the noise of the image
void Image::applyGaussianFilter(int kernelSize) {

  // We check the kernel
  if(kernelSize == 0) {
    throw std::runtime_error("Error : in Image::applyGaussianFilter : The kernel size can't be 0");
  }
  else if(kernelSize * 2 + 1 > height || kernelSize * 2 + 1 > width) {
    throw std::runtime_error("Error : in Image::applyGaussianFilter : The kernel size is to big for this image");
  }

  int kernelHeight = 2 * kernelSize + 1;
  int kernelWidth = 2 * kernelSize + 1;
  double sigma = ceil((2 * float(kernelSize) + 1) / 6);

  std::cout << "sigma : " << sigma << "\n";

  std::vector<std::vector<double>> kernel(kernelHeight, std::vector<double>(kernelWidth));

  double sum = 0.0;

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

  std::cout << "\n---  kernelValues  ---\n\n";

  for(int i = 0; i < kernelHeight; i++) {
    for(int j = 0; j < kernelWidth; j++) {
      std::cout << kernel[i][j] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}
