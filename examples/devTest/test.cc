#include <iostream>

#include <graphlib/image.h>

int main() {
  std::cout << "\n";

  char fileNameToRead[] = "testNoise.jpg";
  Image myImage(fileNameToRead, "jpg");

  std::cout << "Image Dimensions : " << myImage.getWidth() << "x" << myImage.getHeight() <<"\n";
  std::cout << "Image Color Space : " << myImage.getColorSpace() << "\n";
  std::cout << "Image Color Type : " << myImage.getColorType() << "\n";
  std::cout << "Image Pixel Size : " << myImage.getPixelSize() << "\n";

  myImage.applyMedianFilter();

  std::cout << "saving..." << "\n";

  char fileNameToSave[] = "testSaved.png";
  myImage.save(fileNameToSave, 100, "png");

  std::cout << "\n";

  return 0;
}
