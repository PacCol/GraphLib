#include <iostream>

#include <graphlib/image.h>

int main() {
  std::cout << "\n";

  char fileNameToRead[] = "images/testYUV.jpg";
  Image myImage(fileNameToRead, "jpg");

  std::cout << "Image Dimensions : " << myImage.getWidth() << "x" << myImage.getHeight() <<"\n";
  std::cout << "Image Pixel Size : " << myImage.getPixelSize() << "\n";
  std::cout << "Image Color Space : " << myImage.getColorSpace() << "\n";
  std::cout << "Image : is alpha used ? : " << myImage.isAlphaChannelUsed() << "\n";

  std::vector<uint8_t> pixel = myImage.getRgbColor(3, 6);
  std::cout << "Image Pixel : X=3, Y=6 : R=" << +pixel[0] << " G=" << +pixel[1]  << " B=" << +pixel[2] << "\n";
  std::cout << "Image Luminance : X=3, Y=6 : " << +myImage.getLuminance(3, 6) << "\n";

  myImage.resize(60);

  char fileNameToSave[] = "images/testSaved.jpg";
  myImage.save(fileNameToSave, 100, "jpg");

  std::cout << "\n";

  return 0;
}
