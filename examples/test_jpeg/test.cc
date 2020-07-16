#include <iostream>

#include <graphlib/jpeg.h>

int main() {
  std::cout << "\n";

  char fileNameToRead[] = "images/test.jpg";
  jpegImage myImage(fileNameToRead);

  std::cout << "Image Dimensions : " << myImage.getWidth() << "x" << myImage.getHeight() <<"\n";
  std::cout << "Image Color Space : " << myImage.getColorSpace() << "\n";
  std::cout << "Image Pixel Size : " << myImage.getPixelSize() << "\n";

  std::vector<uint8_t> pixel = myImage.getRgbColor(3, 6);
  std::cout << "Image Pixel : X=3, Y=6 : R=" << +pixel[0] << " G=" << +pixel[1]  << " B=" << +pixel[2] << "\n";

  std::cout << "Image Luminance : X=3, Y=6 : " << +myImage.getLuminance(3, 6) << "\n";

  myImage.convertToGrayscale();

  myImage.resize(500);

  myImage.showEdgeOnly();

  char fileNameToSave[] = "images/testSaved.jpg";
  myImage.save(fileNameToSave, 100);

  std::cout << "\n";

  return 0;
}
