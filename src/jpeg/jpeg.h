#include <vector>
#include <cstdint>

#ifndef GRAPHLIB_JPEG_H
#define GRAPHLIB_JPEG_H

// We create a class to create jpegImage object
class jpegImage {
  public:
    // The class takes one argument to open the image file
    explicit jpegImage(char* fileName);

    // We create functions to return the image informations
    unsigned int getWidth();
    unsigned int getHeight();
    unsigned int getColorSpace();
    unsigned int getPixelSize();

    // We create a function to return the image
    std::vector<std::vector<uint8_t>> getPixels();

    // We create a function to set all pixels of the image
    void setPixels(std::vector<std::vector<uint8_t>> newPixels);

    // We create a function to save the modified image
    void save(char * fileName, int quality);

    // We create a function to return the RGB value of a pixel
    std::vector<uint8_t> getRgbColor(unsigned int x, unsigned int y);

    // We create a function to return the luminance of a pixel
    uint8_t getLuminance(unsigned int x, unsigned int y);

    // We create a function to set the RGB values of a pixel
    void setRgbColor(std::vector<uint8_t> rgbValues, unsigned int x, unsigned int y);

    // We create a function to set the luminance of a pixel
    void setLuminance(uint8_t newLuminance, unsigned int x, unsigned int y);

    // We create a function to crop the image
    void crop(unsigned int xStartPoint, unsigned int yStartPoint, unsigned int newWidth, unsigned int newHeight);

    // We create a function to resize the image
    void resize(unsigned int newWidth);

    // We create a function to convert the image to grayscale
    void convertToGrayscale();

  private:

    // We store the pixels values into a vector
    std::vector<std::vector<uint8_t>> pixels;

    // We store the image informations into private variables
    unsigned int width;
    unsigned int height;
    unsigned int colorSpace;
    unsigned int pixelSize;
};

#endif // GRAPHLIB_JPEG_H
