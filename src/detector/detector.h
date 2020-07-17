#include <vector>
#include <cstdint>

#ifndef GRAPHLIB_DETECTOR_H
#define GRAPHLIB_DETECTOR_H

// We create a class to create faceDetector object
class faceDetector {
  public:

    // The class takes no argument
    explicit faceDetector();

    // We create a function to set the fiability value
    void setFiability(unsigned int newFiability);

    // We create a function to load the image
    void loadImage(std::vector<std::vector<uint8_t>> imagePixels, unsigned int imageWidth, unsigned int imageHeight, unsigned int imagePixelSize);

    // We create a function to detect human eyes
    std::vector<std::vector<uint8_t>> detectHumanEyes();

  private:
    
    // We store the fiability value into a variable
    unsigned int fiability;

    // We store the pixels values into a vector
    std::vector<std::vector<uint8_t>> pixels;

    // We store the image informations into private variables
    unsigned int width;
    unsigned int height;
    unsigned int pixelSize;
};

#endif // GRAPHLIB_DETECTOR_H
