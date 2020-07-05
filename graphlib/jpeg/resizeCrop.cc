#include <iostream>

#include "jpeg.h"

/*// We create a function to reduce the image width and height
void jpegImage::resize(int newWidth) {

  // We check the new width value
  if(newWidth == 0) {
    throw std::runtime_error("Error : The new width can't be 0");
  }
  else if(newWidth > width) {
    throw std::runtime_error("Error : The new width can't be bigger");
  }
  else if(newWidth == width) {
    return;
  }

  float scale = float(newWidth) / width;
  int newHeight = scale * height;

  std::vector<std::vector<uint8_t>> newPixels;
  newPixels.reserve(height);

  int rowStride = width * pixelSize;

  int x = 0;
  int y = 0;

  for(int i = 0; i < newHeight; i++) {
    std::vector<uint8_t> newLine;
    newLine.reserve(rowStride);
    for(int j = 0; j < newWidth; j++) {
      for(int k = 0; k < pixelSize; k++) {
        x = float(j) / scale * float(pixelSize) + k;
        y = float(i) / scale;
        if(i == 5 && j == 4 && k == 2) {
          std::cout << "X, Y = " << x << ", " << y << "\n";
        }
        //std::cout << "j * pixelSize + k = " << j * pixelSize + k << "\n";
        newLine[j * pixelSize + k] = pixels[y][x];
      }
    }
    newPixels.push_back(newLine);
  }
  pixels = newPixels;
  width = newWidth;
  height = newHeight;
}*/


void jpegImage::crop(int xStartPoint, int yStartPoint, int newWidth, int newHeight) {

  // We check the values
  if(xStartPoint + newWidth > width) {
    throw std::runtime_error("Error : The X value is out of range");
  }
  else if(newWidth == 0) {
    throw std::runtime_error("Error : The new width can't be 0");
  }
  else if(yStartPoint + newHeight > height) {
    throw std::runtime_error("Error : The Y value is out of range");
  }
  else if(newHeight == 0) {
    throw std::runtime_error("Error : The new height can't be 0");
  }

  // We create a vector to save the new image
  std::vector<std::vector<uint8_t>> newPixels;
  // We reserve the output height
  newPixels.reserve(newHeight);

  // We are computing the row stride
  int rowStride = newWidth * pixelSize;

  // We fill in the new vector line per line
  for(int i = 0; i < newHeight; i++) {

    // We create a new vector to save the new line
    std::vector<uint8_t> newLine;
    // We reserve the line width
    newLine.reserve(rowStride);

    // We get the values of each pixel
    for(int j = 0; j < newWidth; j++) {
      for(int k = 0; k < pixelSize; k++) {

        // We set the pixel value
        newLine[j * pixelSize + k] = pixels[yStartPoint + i][(xStartPoint + j) * pixelSize];
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
