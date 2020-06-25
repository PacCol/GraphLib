#include <iostream>
#include "jpeg/jpeg.h"

int main() {
  char fileName[] = "test.jpg";
  jpegImage myImage(fileName);

  std::cout << "Image Dimensions : " << myImage.width << "x" << myImage.height <<"\n";
  std::cout << "Image Color Space : " << myImage.colorSpace << "\n";
  std::cout << "Image Pixel Size : " << myImage.pixelSize << "\n";

  std::cout << "Image Pixel : X = 3, Y = 6 : ";
  std::vector<uint8_t> scannedLine = myImage.getPixel(3, 6);
  std::cout << "R -> " << scannedLine[0] << "\n";
  std::cout << "                             G -> " << scannedLine[1] << "\n";
  std::cout << "                             B -> " << scannedLine[2] << "\n";
}
