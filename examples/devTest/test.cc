#include <graphlib.h>

int main()
{
  Image myImage;

  myImage.openJpegImage("../imageSamples/beam.jpg");

  myImage.applyCannyFilter();

  myImage.saveJpegImage("output.jpg", 100);
}
