#include <iostream>
#include <algorithm>

#include "image.h"

// We create a function to reduce the noise of the image
void Image::applyMedianFilter(unsigned int kernelSize) {

  // We check the kernel
  if(kernelSize == 0) {
    throw std::runtime_error("Error : in Image::applyMedianFilter : The kernel size can't be 0");
  }
  else if(kernelSize * 2 + 1 > height || kernelSize * 2 + 1 > width) {
    throw std::runtime_error("Error : in Image::applyMedianFilter : The kernel size is to big for this image");
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

        // We create a vector to store the pixel values (value per value)
        // For example for an RGB image :
        // Fist, we calculate the median of the red values of the pixels of the neighborhood
        std::vector<uint8_t> medianPixels;
        medianPixels.reserve(kernelSize * 2 + 1);

        // We add the pixels values in the vector
        for(int l = -(int(kernelSize)); l <= int(kernelSize); l++) {
          for(int m = -(int(kernelSize)); m <= int(kernelSize); m++) {
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
  width = width - kernelSize * 2;
  height = height - kernelSize * 2;

  // We update the image
  pixels = newPixels;
}

// We create a function to reduce the noise of the image
void Image::applyGaussianFilter(unsigned int kernelSize) {

  unsigned int kernelHeight = 2 * kernelSize + 1;
  unsigned int kernelWidth = 2 * kernelSize + 1;
  double sigma;

  std::vector<std::vector<uint8_t>> kernel(kernelHeight, std::vector<uint8_t>(kernelWidth));
  double sum=0.0;

  for(unsigned int i = 0; i < kernelHeight; i++) {
    for(unsigned int j = 0; j < kernelWidth; j++) {
      kernel[i][j] = exp(-(i*i+j*j)/(2*sigma*sigma))/(2*M_PI*sigma*sigma);
      sum = sum + kernel[i][j];
    }
  }

  for(unsigned int i = 0; i < kernelHeight; i++) {
    for(unsigned int j = 0; j < kernelWidth; j++) {
      kernel[i][j] = kernel[i][j] / sum;
    }
  }

  // We check the radius
  /*if(radius == 0) {
    throw std::runtime_error("Error : in Image::applyGaussianFilter : The radius can't be 0");
  }
  else if(radius * 2 + 1 >= height || radius * 2 + 1 >= width) {
    throw std::runtime_error("Error : in Image::applyGaussianFilter : The radius is to big");
  }


  sigma = ceil((2 * indice + 1) / 6);
  sum = 0;

  std::vector<std::vector<float>> coeff;
  coeff.reserve(2 * indice + 1);

  for(int l = -(int(indice)); l <= indice; l++) {

    std::vector<float> newLine;
    newLine.reserve(2 * indice + 1);

    for(int m = -(int(indice)); m <=  indice; m++) {
      coeff =  exp(- m * m / (2 * sigma * sigma) )/sqrt(2 * M_PI * sigma * sigma) *
          exp(- l * l / (2 * sigma * sigma) )/sqrt(2 * M_PI * sigma * sigma);
          sum = sum + coeff;
      newLine.push_back(  );
    }

    coeff.push_back(newLine);
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
        for(int l = -(int(radius)); l < int(radius + 1); l++) {
          for(int m = -(int(radius)); m < int(radius + 1); m++) {
            medianPixels.push_back(pixels[i + l][(j + m) * pixelSize + k]);
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
  width = width - radius * 2;
  height = height - radius * 2;

  // We update the image
  pixels = newPixels;*/
}
