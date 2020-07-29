#include <iostream>

#include <graphlib/image.h>

int main() {
  std::cout << "\n";
  
  char fileNameToRead[] = "images/test1.png";
  Image myImage(fileNameToRead, "png");

  std::cout << "Image Dimensions : " << myImage.getWidth() << "x" << myImage.getHeight() <<"\n";
  std::cout << "Image Pixel Size : " << myImage.getPixelSize() << "\n";
  std::cout << "Image Color Space : " << myImage.getColorSpace() << "\n";
  
  std::vector<uint8_t> pixel = myImage.getRgbColor(3, 6);
  
  std::cout << "Image Pixel : X=3, Y=6 : R=" << +pixel[0] << " G=" << +pixel[1]  << " B=" << +pixel[2] << "\n";

  std::cout << "Image Luminance : X=3, Y=6 : " << +myImage.getLuminance(3, 6) << "\n";
  
  // We create a vector that contains the RGB values of the pixel
  std::vector<uint8_t> rgbValues;
  rgbValues.push_back(255); // R (red) value
  rgbValues.push_back(0); // G (green) value
  rgbValues.push_back(0); // B (blue) value
  // We set the pixel where X = 0 and Y = 0 to the RGB values
  myImage.setRgbColor(rgbValues, 0, 0);
  // We set the pixel where X = 1 and Y = 0 to the RGB values
  myImage.setRgbColor(rgbValues, 1, 0);
  // We set the pixel where X = 0 and Y = 1 to the RGB values
  myImage.setRgbColor(rgbValues, 0, 1);
  // We set the pixel where X = 1 and Y = 1 to the RGB values
  myImage.setRgbColor(rgbValues, 1, 1);
  // The top left corner is now red
  
  char fileNameToSave[] = "images/testSaved.jpg";
  myImage.save(fileNameToSave, 100, "jpg");
  
  system("gpicview images/testSaved.jpg");

  std::cout << "\n";

  return 0;
}
