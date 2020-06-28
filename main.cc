#include <iostream>
#include "graphlib/jpeg/jpeg.h"

int main() {
  std::cout << "\n";
  
  char fileName[] = "imageSamples/test.jpg";
  jpegImage myImage(fileName);

  std::cout << "Image Dimensions : " << myImage.width << "x" << myImage.height <<"\n";
  std::cout << "Image Color Space : " << myImage.colorSpace << "\n";
  std::cout << "Image Pixel Size : " << myImage.pixelSize << "\n";
  
  std::cout << "Image Pixel : X=3, Y=6 : ";
  std::vector<uint8_t> scannedPixel = myImage.getRgbColor(3, 6);
  std::cout << " R=" << +scannedPixel[0] << " G=" << +scannedPixel[1]  << " B=" << +scannedPixel[2] << "\n";
  
  std::cout << "Image Luminance : X=3, Y=6 : " << +myImage.getLuminance(3, 6) << "\n";
  
  myImage.resize(100);
  
  std::cout << "\n";
  
  return 0;
}
