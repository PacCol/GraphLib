#include <iostream>
#include "jpeg/jpeg.h"

int main() {
  char fileName[] = "test.jpg";
  jpegImage myImage(fileName);
  std::cout << "Image Dimensions : " << myImage.width << "x" << myImage.height <<"\n";
  std::cout << "Image Pixel Size : " << myImage.pixelSize << "\n";
}
