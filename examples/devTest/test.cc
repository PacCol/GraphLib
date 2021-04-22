#include <graphlib/graphlib.h>

int main() {

  Image myImage;


    //system("streamer -f jpeg -o capture.jpeg");

    myImage.openJpegImage("../imageSamples/beam.jpg");

    myImage.convertToGrayscale();

    myImage.applyGaussianFilter(5);

    myImage.applyCannyFilter(1500, 3000);

    myImage.saveJpegImage("output.jpg", 100);
}
