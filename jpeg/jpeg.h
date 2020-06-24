#include <vector>
#include <cstdint>

// We create a class to create jpegImage object
class jpegImage {
  public:
    // The class take one argument to open the image file
    explicit jpegImage(char* fileName);

    // We store the image informations into public variables
    unsigned int width;
    unsigned int height;
    unsigned int colorSpace;
    int pixelSize;

    // We create a table to store the pixel values
    std::vector<std::vector<uint8_t>> decompressedImage;

    std::vector<uint8_t> jpegImage::getPixel(unsigned int x, unsigned int y);
};
