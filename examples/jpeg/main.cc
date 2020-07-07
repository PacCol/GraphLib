#include <iostream>

#include <jpeg.h>

int main() {
  std::cout << "\n";

  // We select an image
  char fileNameToRead[] = "images/test.jpg";
  // We open and decode the image
  jpegImage myImage(fileNameToRead);

  // We print some informations
  std::cout << "Image Dimensions : " << myImage.getWidth() << "x" << myImage.getHeight() <<"\n";
  std::cout << "Image Color Space : " << myImage.getColorSpace() << "\n";
  // If the pixel size is 1, the image is monochrome
  // If the pixel size is 3, the image is colored
  std::cout << "Image Pixel Size : " << myImage.getPixelSize() << "\n";

  // We print the RGB values of a pixel
  // This return a vector that contains the RGB values
  std::vector<uint8_t> scannedPixel = myImage.getRgbColor(3, 6);
  // We use a + to print the value as a number
  std::cout << "Image Pixel : X=3, Y=6 : R=" << +scannedPixel[0] << " G=" << +scannedPixel[1]  << " B=" << +scannedPixel[2] << "\n";

  // We print the luminance of a pixel
  std::cout << "Image Luminance : X=3, Y=6 : " << +myImage.getLuminance(3, 6) << "\n";

  // We crop the image
  // The new width will be 650 pixels
  // The new height will be 600 pixels
  // We start at X = 210 and Y = 90 to get the interesting part of the image
  //myImage.crop(1800, 700, 650, 600);
  // Only the central part of the image has been preserved

  myImage.resize(1000);

  // We create a vector that contains the RGB values of the pixel
  std::vector<uint8_t> rgbValues;
  rgbValues.push_back(255); // R (red) value
  rgbValues.push_back(0); // G (green) value
  rgbValues.push_back(0); // B (blue) value
  // We set the pixel where X = 0 and Y = 0 to the RGB values
  myImage.setRgbColor(rgbValues, 0, 0);
  // We set the pixel where X = 1 and Y = 0 to the RGB values
  myImage.setRgbColor(rgbValues, 1, 0);
  // We set the pixel where X = 0 and Y = 1 to the RGB values
  myImage.setRgbColor(rgbValues, 0, 1);
  // We set the pixel where X = 1 and Y = 1 to the RGB values
  myImage.setRgbColor(rgbValues, 1, 1);
  // The top left corner is now red

  // We choose a file name
  char fileNameToSave[] = "images/testSaved.jpg";
  // We save the modified image
  myImage.save(fileNameToSave, 100);

  // Now open and compare the two images

  std::cout << "\n";

  return 0;
}
