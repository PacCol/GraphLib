#define _USE_MATH_DEFINES
#include <cmath>

#include "../image.h"

// We create a function to reduce the noise of the image
void Image::applyGaussianFilter(unsigned int kernelSize) {

  int kernelHeight = 2 * kernelSize + 1;
  int kernelWidth = 2 * kernelSize + 1;
  //double sigma = ceil((2 * kernelSize + 1) / 6);
  double sigma = 10.0;

  std::cout << "sigma : " << sigma << "\n";

  std::vector<std::vector<double>> kernel(kernelHeight, std::vector<double>(kernelWidth));

  double sum = 0.0;

  for(int i = 0; i < kernelHeight; i++) {
    for(int j = 0; j < kernelWidth; j++) {
      kernel[i][j] = exp( -(i * i + j * j) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma );
      sum = sum + kernel[i][j];
    }
  }

  for(int i = 0; i < kernelHeight; i++) {
    for(int j = 0; j < kernelWidth; j++) {
      kernel[i][j] = kernel[i][j] / sum;
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
