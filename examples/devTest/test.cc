#include <graphlib.h>

int main() {

  Image myImage;

  myImage.openJpegImage("../imageSamples/beam.jpg");

  myImage.convertToGrayscale();

  //myImage.applyGaussianFilter(3);

  myImage.applyCannyFilter(1, 1);

  myImage.saveJpegImage("output.jpg", 100);
}
