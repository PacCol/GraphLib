#include <iostream>

#include <graphlib/jpeg.h>

int main() {
  std::cout << "\n";

  // We select an image
  char fileNameToRead[] = "images/testMonochrome.jpg";
  // We open and decode the image
  jpegImage myImage(fileNameToRead);

  // We print some informations
  std::cout << "Image Dimensions : " << myImage.getWidth() << "x" << myImage.getHeight() <<"\n";
  std::cout << "Image Color Space : " << myImage.getColorSpace() << "\n";
  // If the pixel size is 1, the image is monochrome
  // If the pixel size is 3, the image is colored
  std::cout << "Image Pixel Size : " << myImage.getPixelSize() << "\n";

  // For all functions the X and the Y value start to 0
  // If you want to get the first pixel luminance, do this :
  // uint8_t luminance = myImage.getLuminance(0, 0);

  // We print the luminance of a pixel
  std::cout << "Image Luminance : X=3, Y=6 : " << +myImage.getLuminance(3, 6) << "\n";

  // We crop the image
  // The new width will be 650 pixels
  // The new height will be 600 pixels
  // We start at X = 210 and Y = 90 to get the interesting part of the image
  myImage.crop(1800, 700, 650, 600);
  // Only the central part of the image has been preserved

  // We resize the image
  // The new width will be 150 pixels
  // The new height will be computed
  // The new width start to 1
  myImage.resize(150);

  // We create a variable to store the new luminance (a value between 0 and 255)
  uint8_t luminance = 100;
  // We set the pixel where X = 0 and Y = 0 to the new luminance
  myImage.setLuminance(luminance, 0, 0);
  // We set the pixel where X = 0 and Y = 1 to the new luminance
  myImage.setLuminance(luminance, 0, 1);
  // We set the pixel where X = 1 and Y = 0 to the new luminance
  myImage.setLuminance(luminance, 1, 0);
  // We set the pixel where X = 1 and Y = 1 to the new luminance
  myImage.setLuminance(luminance, 1, 1);
  // The top left corner is now darker

  // We choose a file name
  char fileNameToSave[] = "images/testSavedMonochrome.jpg";
  // We save the modified image
  myImage.save(fileNameToSave, 100);

  // Now open and compare the two images

  std::cout << "\n";

  return 0;
}
