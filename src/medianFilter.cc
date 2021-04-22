#include <algorithm>

#include "graphlib.h"

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
