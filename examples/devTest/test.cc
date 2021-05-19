#include <graphlib.h>

int main()
{
  Image myImage;

  myImage.openJpegImage("../imageSamples/beam.jpg");

  myImage.applyMedianFilter(1);

  myImage.saveJpegImage("output.jpg", 100);
}
