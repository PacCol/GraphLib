#include <iostream>

#include <graphlib/jpeg.h>
#include <graphlib/detector.h>

int main() {
  std::cout << "\n";

  char fileNameToRead[] = "images/test.jpg";
  jpegImage myImage(fileNameToRead);

  std::cout << "Image Dimensions : " << myImage.getWidth() << "x" << myImage.getHeight() <<"\n";
  std::cout << "Image Color Space : " << myImage.getColorSpace() << "\n";
  std::cout << "Image Pixel Size : " << myImage.getPixelSize() << "\n";

  myImage.resize(500);
  myImage.convertToGrayscale();

  faceDetector myDetector;
  myDetector.setFiability(50);
  myDetector.detectHumanFaces(myImage.getPixels(), myImage.getWidth(), myImage.getHeight(), myImage.getPixelSize());

  std::cout << "\n";
  return 0;
}
