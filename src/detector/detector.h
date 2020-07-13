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

    // We create a function to detect human faces
    std::vector<std::vector<uint8_t>> detectHumanFaces(std::vector<std::vector<uint8_t>> pixels, uint8_t faceGlobalLuminance, unsigned int width, unsigned int height, unsigned int pixelSize);

  private:
    // We store the fiability value into a variable
    unsigned int fiability;
};

#endif // GRAPHLIB_DETECTOR_H
