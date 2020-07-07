#include <iostream>

#include "jpeg.h"

// We create a function to crop the image
void jpegImage::crop(unsigned int xStartPoint, unsigned int yStartPoint, unsigned int newWidth, unsigned int newHeight) {

  // We check the values
  if(xStartPoint + newWidth > width) {
    throw std::runtime_error("Error : in jpegImage::crop : The X value is out of range");
  }
  else if(newWidth == 0) {
    throw std::runtime_error("Error : in jpegImage::crop : The new width can't be 0");
  }
  else if(yStartPoint + newHeight > height) {
    throw std::runtime_error("Error : in jpegImage::crop : The Y value is out of range");
  }
  else if(newHeight == 0) {
    throw std::runtime_error("Error : in jpegImage::crop : The new height can't be 0");
  }

  // We create a vector to save the new image
  std::vector<std::vector<uint8_t>> newPixels;
  // We reserve the output height
  newPixels.reserve(newHeight);

  // We are computing the row stride
  int rowStride = newWidth * pixelSize;

  // We fill in the new vector line per line
  for(unsigned int i = 0; i < newHeight; i++) {

    // We create a new vector to save the new line
    std::vector<uint8_t> newLine;
    // We reserve the line width
    newLine.reserve(rowStride);

    // We get the value of each pixel
    for(unsigned int j = 0; j < newWidth; j++) {
      for(unsigned int k = 0; k < pixelSize; k++) {

        // We set the pixel value
        newLine.push_back(pixels[yStartPoint + i][(xStartPoint + j) * pixelSize + k]);
      }
    }
    // We push the new line into the newPixels vector
    newPixels.push_back(newLine);
  }

  // We update the image
  pixels = newPixels;

  // We update the image informations
  width = newWidth;
  height = newHeight;
}
