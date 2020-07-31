#include <iostream>

#include <graphlib/image.h>

int main() {
  std::cout << "\n";
  
  char fileNameToRead[] = "images/test.jpeg";
  Image myImage(fileNameToRead, "jpg");

  std::cout << "Image Dimensions : " << myImage.getWidth() << "x" << myImage.getHeight() <<"\n";
  std::cout << "Image Pixel Size : " << myImage.getPixelSize() << "\n";
  std::cout << "Image Color Space : " << myImage.getColorSpace() << "\n";
  
  std::vector<uint8_t> pixel = myImage.getPixel(3, 6);
  std::cout << "Image Pixel : X=3, Y=6 : R=" << +pixel[0] << " G=" << +pixel[1]  << " B=" << +pixel[2] << "\n";

  std::cout << "Image Luminance : X=3, Y=6 : " << +myImage.getLuminance(3, 6) << "\n";
  
  std::vector<uint8_t> rgbValues;
  rgbValues.push_back(255);
  rgbValues.push_back(0);
  rgbValues.push_back(0);
  //rgbValues.push_back(0);
  myImage.setPixel(rgbValues, 0, 0);
  myImage.setPixel(rgbValues, 1, 0);
  myImage.setPixel(rgbValues, 0, 1);
  myImage.setPixel(rgbValues, 1, 1);
  
  pixel = myImage.getPixel(0, 0);
  std::cout << "Image Pixel : X=0, Y=0 : R=" << +pixel[0] << " G=" << +pixel[1]  << " B=" << +pixel[2] << "\n";
  
  char fileNameToSave[] = "images/testSaved.png";
  myImage.save(fileNameToSave, 100, "png");
  
  system("gpicview images/testSaved.png");
  
  /*char fileNameToSave[] = "images/testSaved.jpg";
  myImage.save(fileNameToSave, 100, "jpg");
  
  system("gpicview images/testSaved.jpg");*/

  std::cout << "\n";

  return 0;
}
