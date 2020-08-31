#include <iostream>

#include <graphlib/image.h>

int main() {
  std::cout << "\n";

  // We create an image
  Image myImage;

  // We open an existing image
  myImage.openJpegImage("../imageSamples/test.jpg");

  // We print some informations

  // The dimensions in pixels
  std::cout << "Image Dimensions : " << myImage.getWidth() << "x" << myImage.getHeight() <<"\n";

  // - Color space 1 :
  //    1 value (luminance --> monochrome image)
  // - Color space 2 :
  //    3 values (RGB --> colored image)
  std::cout << "Image Color Space : " << myImage.getColorSpace() << "\n";

  // - Color type 0 :
  //    1 value (monochrome image)
  // - Color type 2 :
  //    3 values (RGB --> colored image)
  // - Color type 4 :
  //    2 values (monochrome image with alpha channel)
  // - Color type 6 :
  //    4 values (RGBA --> colored image with alpha channel)
  std::cout << "Image Color Type : " << myImage.getColorType() << "\n";

  // The pixel size is the number of value for a pixel
  // For example : an RGB image will have a pixel size of 3
  std::cout << "Image Pixel Size : " << myImage.getPixelSize() << "\n";

  // The alpha channel is the transparancy
  std::cout << "Image Alpha Channel : ";
  if(myImage.isAlphaChannelUsed()) {
    std::cout << "Used" << "\n";
  }
  else {
    std::cout << "Unused" << "\n";
  }

  // For all functions the X and the Y value start to 0
  // If you want to get the first pixel values, do this :
  // std::vector<uint8_t> pixel = myImage.getPixel(0, 0);

  // We print the RGB values of a pixel
  // In this example, the image is an RGB image (color type 3)
  // Please read the color type explanations
  // This function return vector that contain in this case three values (see the pixel size)
  std::vector<uint8_t> pixel = myImage.getPixel(3, 6);
  // We use a + to print the value as a number
  std::cout << "Image Pixel : X=3, Y=6 : R=" << +pixel[0] << " G=" << +pixel[1]  << " B=" << +pixel[2] << "\n";

  // We print the luminance of a pixel
  std::cout << "Image Luminance : X=3, Y=6 : " << +myImage.getLuminance(3, 6) << "\n";

  // We crop the image
  // The new width will be 650 pixels
  // The new height will be 600 pixels
  // We start at X = 210 and Y = 90 to get the interesting part of the image
  myImage.crop(1800, 700, 650, 600);
  // Only the central part of the image has been preserved

  // We resize the image
  // The new width will be 150 pixels
  // The new height will be computed
  // The new width start to 1
  myImage.resize(150);

  // We create a vector that contains the RGB values of the pixel
  std::vector<uint8_t> rgbValues;
  rgbValues.push_back(255); // R (red) value
  rgbValues.push_back(0); // G (green) value
  rgbValues.push_back(0); // B (blue) value
  // We set the pixel where X = 0 and Y = 0 to the RGB values
  myImage.setPixel(rgbValues, 0, 0);
  // We set the pixel where X = 1 and Y = 0 to the RGB values
  myImage.setPixel(rgbValues, 1, 0);
  // We set the pixel where X = 0 and Y = 1 to the RGB values
  myImage.setPixel(rgbValues, 0, 1);
  // We set the pixel where X = 1 and Y = 1 to the RGB values
  myImage.setPixel(rgbValues, 1, 1);
  // The top left corner is now red

  // We convert the image to grayscale (you can remove the // to do it)
  //myImage.convertToGrayscale();

  // We save the modified image
  // We set the quality to 100
  myImage.saveJpegImage("../imageSamples/testSaved.jpg", 100);

  // Now, you can open and compare the two images

  std::cout << "\n";

  return 0;
}
