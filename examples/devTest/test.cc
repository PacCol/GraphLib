#include <iostream>

#include <graphlib/image.h>

int main() {
  std::cout << "\n";

  char fileNameToRead[] = "../imageSamples/test.jpg";
  Image myImage(fileNameToRead, "jpg");

  std::cout << "Image Dimensions : " << myImage.getWidth() << "x" << myImage.getHeight() <<"\n";
  std::cout << "Image Color Space : " << myImage.getColorSpace() << "\n";
  std::cout << "Image Pixel Size : " << myImage.getPixelSize() << "\n";

  char fileNameToSave[] = "testSaved.png";
  myImage.save(fileNameToSave, 100, "png");

  std::cout << "\n";

  return 0;
}
