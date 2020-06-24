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
};
