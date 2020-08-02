#include <iostream>

#include <graphlib/image.h>

int main() {
  std::cout << "\n";

  char fileNameToRead[] = "images/test.png";
  Image myImage(fileNameToRead, "png");

  std::cout << "Image Dimensions : " << myImage.getWidth() << "x" << myImage.getHeight() <<"\n";
  std::cout << "Image Pixel Size : " << myImage.getPixelSize() << "\n";
  std::cout << "Image Color Space : " << myImage.getColorSpace() << "\n";
  std::cout << "Image : is alpha used ? : " << myImage.isAlphaChannelUsed() << "\n";
  std::cout << "Image Luminance : X=3, Y=6 : " << +myImage.getLuminance(3, 6) << "\n";

  myImage.resize(60);

  char fileNameToSave[] = "images/testSaved.png";
  myImage.save(fileNameToSave, 100, "png");

  std::cout << "\n";

  return 0;
}
