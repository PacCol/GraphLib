#include "graphlib.h"

// We create a function to return the alpha value of a pixel
uint8_t Image::getAlphaValue(unsigned int x, unsigned int y) {

  // We check the alpha channel
  if(!alphaUsed) {
    throw std::runtime_error("Error : in Image::getAlphaValue : alpha channel not found");
  }

  // We store the alpha value into a variable
  uint8_t alphaValue = pixels[y][x * pixelSize + colorSpace];

  // We return the alpha value
  return alphaValue;
}

// We create a function to remove the alpha channel of the image
void Image::removeAlphaChannel() {

  // We check the alpha channel
  if(!alphaUsed) {
    throw std::runtime_error("Error : in Image::removeAlphaChannel : alpha channel not found");
  }

  // We create a vector to save the new image
  std::vector<std::vector<uint8_t>> newPixels;
  // We reserve the output height
  newPixels.reserve(height);

  // We are computing the row stride
  int rowStride = width * (pixelSize - 1);

  // For each line of the image...
  for(unsigned int i = 0; i < height; i++) {

    // We create a vector to save the new line
    std::vector<uint8_t> newLine;
    // We reserve the row stride
    newLine.reserve(rowStride);

    // For each pixel of this line...
    for(unsigned int j = 0; j < width; j++) {

      // For each value of this pixel...
      for(unsigned int k = 0; k < pixelSize - 1; k++) {

        // We push the pixel without the alpha channel
        newLine.push_back(pixels[i][j * pixelSize + k]);
      }
    }
    // We push the new line into the newPixels vector
    newPixels.push_back(newLine);
  }

  // We update the image
  pixels = newPixels;

  // We update the image informations
  pixelSize = pixelSize - 1;

  if(colorType == 4) {
    colorType = 0;
  }
  else {
    colorType = 2;
  }
  alphaUsed = false;
}
