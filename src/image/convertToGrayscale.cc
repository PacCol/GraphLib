#include <iostream>

#include "image.h"

// We create a function to convert the image to grayscale
void Image::convertToGrayscale() {

  // We check the actual color space
  if(colorSpace == 1) {
    throw std::runtime_error("Error : in Image::convertToGrayscale : the image is already monochrome");
  }

  // We create a vector to save the new image
  std::vector<std::vector<uint8_t>> newPixels;
  // We reserve the output height
  newPixels.reserve(height);

  // For each line of the image...
  for(unsigned int i = 0; i < height; i++) {

    // We create a vector to save the new line
    std::vector<uint8_t> newLine;
    // We reserve the line width
    newLine.reserve(width * pixelSize);

    // For each pixel of this line...
    for(unsigned int j = 0; j < width; j++) {

      // We push the luminance of the pixel
      newLine.push_back(getLuminance(j, i));

      // If the alpha channel is used, we push the alpha value
      if(alphaUsed) {
        newLine.push_back(getAlphaValue(j, i));
      }
    }
    // We push the new line into the newPixels vector
    newPixels.push_back(newLine);
  }

  // We update the image
  pixels = newPixels;

  // We update the image informations
  pixelSize = pixelSize - 2;
  colorSpace = 1;
  
  if(!alphaUsed) {
    colorType = 0;
  }
  else {
    colorType = 4;
  }
}
