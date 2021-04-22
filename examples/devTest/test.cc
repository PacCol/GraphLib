#include <graphlib/image.h>

int main() {

  /*Image myImage;

  while(true) {

    system("streamer -f jpeg -o picture.jpeg");

    myImage.openJpegImage("picture.jpeg");

    myImage.convertToGrayscale();

    myImage.applyGaussianFilter(3);

    myImage.applyCannyFilter(1500, 3000);

    myImage.saveJpegImage("output.jpg", 100);
  }*/
  
  Image myImage;
  myImage.openJpegImage("../../../../Web/kingdomsBattle/frontend/textures/brick.jpg");
  myImage.resize(128);
  myImage.saveJpegImage("../../../../Web/kingdomsBattle/frontend/textures/brick.jpg", 60);
}
