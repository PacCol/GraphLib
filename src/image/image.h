#include <vector>
#include <cstdint>

#ifndef GRAPHLIB_IMAGE_H
#define GRAPHLIB_IMAGE_H

// We create a class to the Image object
class Image {
  public:

    // The class takes one argument to open the image file
    explicit Image(char* fileName, std::string option);

    // We create functions to return the image informations
    unsigned int getWidth();
    unsigned int getHeight();
    unsigned int getColorSpace();
    unsigned int getPixelSize();
    bool isAlphaChannelUsed();

    // We create a function to save the modified image
    void save(char * fileName, int quality, std::string option);

    // We create a function to return the image
    std::vector<std::vector<uint8_t>> getPixels();

    // We create a function to return the RGB value of a pixel
    std::vector<uint8_t> getPixel(unsigned int x, unsigned int y);

    // We create a function to return the luminance of a pixel
    uint8_t getLuminance(unsigned int x, unsigned int y);

    // We create a function to set all pixels of the image
    void setPixels(std::vector<std::vector<uint8_t>> newPixels);

    // We create a function to set the RGB values of a pixel
    void setPixel(std::vector<uint8_t> rgbValues, unsigned int x, unsigned int y);

    // We create a function to set the luminance of a pixel
    void setLuminance(uint8_t newLuminance, unsigned int x, unsigned int y);

    // We create a function to crop the image
    void crop(unsigned int xStartPoint, unsigned int yStartPoint, unsigned int newWidth, unsigned int newHeight);

    // We create a function to resize the image
    void resize(unsigned int newWidth);

    // We create a function to convert the image to grayscale
    void convertToGrayscale();

    // We create a function to reduce the noise of the image
    void reduceNoise(uint8_t strength);

    // We create a function to show the edge of the objects of the image
    void showEdgeOnly();

  private:

    // We create a function to open a jpeg image
    void openJpegImage(char* fileName);

    // We create a function to save a jpeg image
    void saveJpegImage(char* fileName, unsigned int quality);

    // We create a function to open a png image
    void openPngImage(char* fileName);

    // We create a function to save a png image
    void savePngImage(char* fileName);

    // We store the pixels values into a vector
    std::vector<std::vector<uint8_t>> pixels;

    // We store the image informations into private variables
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int pixelSize = 0;
    unsigned int colorSpace = 0;
    bool alphaUsed = false;
};

#endif // GRAPHLIB_IMAGE_H