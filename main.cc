#include <iostream>

#include "graphlib/jpeg/jpeg.h"

int main() {
  std::cout << "\n";

  char fileNameToRead[] = "imageSamples/test.jpg";
  jpegImage myImage(fileNameToRead);

  std::cout << "Image Dimensions : " << myImage.getWidth() << "x" << myImage.getHeight() <<"\n";
  std::cout << "Image Color Space : " << myImage.getColorSpace() << "\n";
  std::cout << "Image Pixel Size : " << myImage.getPixelSize() << "\n";

  std::vector<uint8_t> scannedPixel = myImage.getRgbColor(3, 6);
  std::cout << "Image Pixel : X=3, Y=6 : R=" << +scannedPixel[0] << " G=" << +scannedPixel[1]  << " B=" << +scannedPixel[2] << "\n";
  std::cout << "Image Luminance : X=3, Y=6 : " << +myImage.getLuminance(3, 6) << "\n";

  myImage.crop(500, 300, 400, 300);

  std::vector<uint8_t> rgbValues;
  rgbValues.push_back(255);
  rgbValues.push_back(0);
  rgbValues.push_back(0);
  myImage.setRgbColor(rgbValues, 0, 0);
  myImage.setRgbColor(rgbValues, 1, 0);
  myImage.setRgbColor(rgbValues, 0, 1);
  myImage.setRgbColor(rgbValues, 1, 1);

  char fileNameToSave[] = "imageSamples/test_saved.jpg";
  myImage.save(fileNameToSave, 100);

  std::cout << "\n";

  return 0;
}
