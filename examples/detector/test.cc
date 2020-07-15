#include <iostream>

#include <graphlib/jpeg.h>
#include <graphlib/detector.h>

int main() {
  std::cout << "\n";

  char fileNameToRead[] = "images/test2.jpg";
  jpegImage myImage(fileNameToRead);

  std::cout << "Image Dimensions : " << myImage.getWidth() << "x" << myImage.getHeight() <<"\n";
  std::cout << "Image Color Space : " << myImage.getColorSpace() << "\n";
  std::cout << "Image Pixel Size : " << myImage.getPixelSize() << "\n";

  myImage.convertToGrayscale();

  std::cout << "\n";

  std::cout << "Image Dimensions : " << myImage.getWidth() << "x" << myImage.getHeight() <<"\n";
  std::cout << "Image Color Space : " << myImage.getColorSpace() << "\n";
  std::cout << "Image Pixel Size : " << myImage.getPixelSize() << "\n";

  faceDetector myDetector;
  myDetector.setFiability(50);
  myDetector.loadImage(myImage.getPixels(), myImage.getWidth(), myImage.getHeight(), myImage.getPixelSize());
  std::vector<std::vector<uint8_t>> newPixels = myDetector.detectHumanEyes();

  myImage.setPixels(newPixels);

  char fileNameToWrite[] = "images/testSaved.jpg";
  myImage.save(fileNameToWrite, 100);

  std::cout << "\n";
  return 0;
}
