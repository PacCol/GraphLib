#include <iostream>

#include <graphlib/image.h>

int main() {
  std::cout << "\n";

  Image myImage("test1.jpg", "jpg");

  std::cout << "Image Dimensions : " << myImage.getWidth() << "x" << myImage.getHeight() <<"\n";
  std::cout << "Image Color Space : " << myImage.getColorSpace() << "\n";
  std::cout << "Image Color Type : " << myImage.getColorType() << "\n";
  std::cout << "Image Pixel Size : " << myImage.getPixelSize() << "\n";

  myImage.convertToGrayscale();

  myImage.applyMedianFilter(3);

  //myImage.applyCannyFilter();

  std::cout << "saving..." << "\n";
  
  myImage.save("testSaved.jpg", 100, "jpg");

  std::cout << "\n";

  system("gwenview testSaved.jpg");

  return 0;
}
