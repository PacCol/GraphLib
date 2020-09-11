#include <graphlib/image.h>

int main() {
  std::cout << "\n";

  Image myImage;
  myImage.openPngImage("test.png");

  myImage.resize(400);

  std::cout << "Image Dimensions : " << myImage.getWidth() << "x" << myImage.getHeight() <<"\n";
  std::cout << "Image Color Space : " << myImage.getColorSpace() << "\n";
  std::cout << "Image Color Type : " << myImage.getColorType() << "\n";
  std::cout << "Image Pixel Size : " << myImage.getPixelSize() << "\n";

  //myImage.removeAlphaChannel();

  myImage.convertToGrayscale();

  //myImage.applyMedianFilter(1);
  myImage.applyGaussianFilter(2);

  myImage.applyCannyFilter(250, 1800);

  std::cout << "Saving..." << "\n";

  myImage.saveJpegImage("testSaved.jpg", 100);

  std::cout << "\n";

  return 0;
}
