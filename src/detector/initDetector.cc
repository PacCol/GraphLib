#include <iostream>

#include "detector.h"

// We create a class to create a jpegImage object
faceDetector::faceDetector() {
  // We set the fiability to the default value
  fiability = 50;
}

// We create a function to set the fiability value
void faceDetector::setFiability(unsigned int newFiability) {

  // Check the new fiability value
  if(newFiability > 100) {
    throw std::runtime_error("Error : in faceDetector::setFiability : the fiability value can't be larger than 100");
  }

  // We set the value
  fiability = newFiability;
}

// We create a function to load the image
void faceDetector::loadImage(std::vector<std::vector<uint8_t>> imagePixels, unsigned int imageWidth, unsigned int imageHeight, unsigned int imagePixelSize) {

  // We check the pixelSize
  if(imagePixelSize != 1) {
    throw std::runtime_error("Error : in faceDetector::loadImage : the image must be monochrome");
  }

  // We set the pixel values
  pixels = imagePixels;

  // We set the image informations
  width = imageWidth;
  height = imageHeight;
  pixelSize = imagePixelSize;
}
