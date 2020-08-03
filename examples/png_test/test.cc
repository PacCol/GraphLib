#include <iostream>

#include <graphlib/image.h>

int main() {
  std::cout << "\n";

  char fileNameToRead[] = "images/testSaved.jpg";
  Image myImage(fileNameToRead, "jpeg");

  std::cout << "Image Dimensions : " << myImage.getWidth() << "x" << myImage.getHeight() <<"\n";
  std::cout << "Image Pixel Size : " << myImage.getPixelSize() << "\n";
  std::cout << "Image Color Space : " << myImage.getColorSpace() << "\n";
  std::cout << "Image : is alpha used ? : " << myImage.isAlphaChannelUsed() << "\n";

  int x = myImage.getWidth() / 2;
  int y = myImage.getHeight() / 2;
  std::vector<uint8_t> pixel = myImage.getPixel(x, y);
  std::cout << "Image Pixel : X=3, Y=6 : R=" << +pixel[0] << " G=" << +pixel[1]  << " B=" << +pixel[2] << " A=" << +pixel[3] << "\n";
  std::cout << "Image Luminance : X=3, Y=6 : " << +myImage.getLuminance(x, y) << "\n";

  myImage.resize(60);

  char fileNameToSave[] = "images/testSaved.png";
  myImage.save(fileNameToSave, 100, "jpg");

  std::cout << "\n";

  return 0;
}
