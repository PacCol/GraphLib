#include <iostream>

#include "jpeg.h"

// We create a function to return the requested RGB value
std::vector<uint8_t> jpegImage::getRgbColor(int x, int y) {
  // If the X or Y value is out of range, we throw an error
  if(x >= width) {
    throw std::runtime_error("Error : The X value is out of range");
  }
  else if(y >= height) {
    throw std::runtime_error("Error : The Y value is out of range");
  }

  // If the image is monochrome, we throw an error
  if(pixelSize == 1) {
    throw std::runtime_error("Error : The image is monochrome");
  }

  // We create a vector
  std::vector<uint8_t> scannedPixel;
  scannedPixel.reserve(3);

  // We push the pixels values in the vector
  for(int i = 0; i < 3; i++) {
    scannedPixel.push_back(pixels[y][x * pixelSize + i]);
  }

  // We return the scanned pixel
  return scannedPixel;
}

// We create a function to return the luminance of a pixel
uint8_t jpegImage::getLuminance(int x, int y) {
  // If the X or Y value is out of range, we throw an error
  if(x >= width) {
    throw std::runtime_error("Error : The X value is out of range");
  }
  else if(y >= height) {
    throw std::runtime_error("Error : The Y value is out of range");
  }

  // If the image is monochrome
  if(pixelSize == 1) {
    // We just return the pixel value
    return pixels[y][x];
  }

  // Else if the image is colored
  else if (pixelSize == 3) {
    // We get the RGB pixel value
    std::vector<uint8_t> pixel = getRgbColor(x, y);

    // We get the luminance with this operation
    uint8_t luminance = (pixel[0] * 0.21 + pixel[1] * 0.71 + pixel[2] * 0.07);

    // We return the luminance
    return luminance;
  }
}

// We create a function to reduce the image width and height
void jpegImage::resize(int newWidth) {
  // We check the new width value
  if(newWidth == 0) {
    throw std::runtime_error("Error : The new width can't be 0");
    return;
  }
  else if(newWidth > width) {
    throw std::runtime_error("Error : The new width can't be bigger");
    return;
  }
  else if(newWidth == width) {
    return;
  }
  
  float scale = float(newWidth) / width;
  int newHeight = scale * height;

  std::vector<std::vector<uint8_t>> newPixels;
  newPixels.reserve(height);
  
  std::cout << newHeight << " : " << scale << "\n";
  
  int rowStride = width * pixelSize;

  for(int i = 0; i < newHeight; i++) {
    std::vector<uint8_t> newLine;
    newLine.reserve(rowStride);
    for(int j = 0; j < newWidth; j++) {
      for(int k = 0; k < pixelSize; k++) {
        int x = float(j) / scale * float(pixelSize) + k;
        int y = float(i) / scale;
        //std::cout << y << " : " << x << "\n";
        //std::cout << i << " : " << j << " : " << k << "\n";
        //std::cout << "Pixel : " << +pixels[y][x] << "\n";
        newLine[j * k] = pixels[y][x];
      }
    }
    newPixels.push_back(newLine);
  }
  pixels = newPixels;
  width = newWidth;
  height = newHeight;
}
