#include <iostream>

#include "image.h"

// We create a class to create the Image object
Image::Image(std::string fileName, std::string option) {

  // If the image is a jpeg file, we open it as jpeg
  if(option == "jpg" || option == "jpeg") {
    openJpegImage(fileName);
  }

  // Else if the image is a png file, we open it as png
  else if(option == "png") {
    openPngImage(fileName);
  }

  // Else if the file type is not supported...
  else {
    throw std::runtime_error("Error : in Image::Image : " + option + " is not a supported option");
  }
}

void Image::save(std::string fileName, unsigned int quality, std::string option) {

  // If the image to save will be a jpeg file, we save it as a jpeg image
  if(option == "jpg" || option == "jpeg") {
    saveJpegImage(fileName, quality);
  }

  // Else if the image will be a png file, we save it as a png image
  else if(option == "png") {

    // The quality will be ignored for a png image
    savePngImage(fileName);
  }

  // Else if the file type is not supported...
  else {
    throw std::runtime_error("Error : in Image::save : " + option + " is not a supported option");
  }
}
