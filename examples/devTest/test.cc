#include <graphlib/image.h>

int main() {
  std::cout << "\n";

  Image myImage;
  myImage.openJpegImage("test.jpg");

  std::cout << "Image Dimensions : " << myImage.getWidth() << "x" << myImage.getHeight() <<"\n";
  std::cout << "Image Color Space : " << myImage.getColorSpace() << "\n";
  std::cout << "Image Color Type : " << myImage.getColorType() << "\n";
  std::cout << "Image Pixel Size : " << myImage.getPixelSize() << "\n";

  //myImage.convertToGrayscale();

  myImage.applyGaussianFilter(2);

  //myImage.applyMedianFilter(3);

  //myImage.applyCannyFilter();

  std::cout << "Saving..." << "\n";

  myImage.saveJpegImage("testSaved.jpg", 100);

  std::cout << "\n";

  //system("gwenview testSaved.jpg");

  return 0;
}
