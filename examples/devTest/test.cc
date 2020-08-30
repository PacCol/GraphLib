#include <iostream>

#include <graphlib/image.h>

int main() {
  std::cout << "\n";

  char fileNameToRead[] = "test2_noise_removed.jpg";
  Image myImage(fileNameToRead, "jpg");

  std::cout << "Image Dimensions : " << myImage.getWidth() << "x" << myImage.getHeight() <<"\n";
  std::cout << "Image Color Space : " << myImage.getColorSpace() << "\n";
  std::cout << "Image Color Type : " << myImage.getColorType() << "\n";
  std::cout << "Image Pixel Size : " << myImage.getPixelSize() << "\n";

  myImage.applyMedianFilter();
  myImage.applyCannyFilter();

  std::cout << "saving..." << "\n";

  char fileNameToSave[] = "testSaved1.jpg";
  myImage.save(fileNameToSave, 100, "jpg");

  std::cout << "\n";

  system("gwenview testSaved.jpg");

  return 0;
}
