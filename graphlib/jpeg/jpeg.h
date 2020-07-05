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

    // We create a function to return the RGB value of a pixel
    std::vector<uint8_t> getRgbColor(int x, int y);

    // We create a function to return the luminance of a pixel
    uint8_t getLuminance(int x, int y);

    // We create a function to reduce the image width and height
    //void resize(int newWidth);

    // We create a function to crop the image
    void crop(int xStartPoint, int yStartPoint, int newWidth, int newHeight);

    // We create a function to save the modified image
    void save(char * fileName, int quality);

  private:
    // We store the pixels values into a vector
    std::vector<std::vector<uint8_t>> pixels;
};
