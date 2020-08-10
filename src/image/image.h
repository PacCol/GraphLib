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
    unsigned int getPixelSize();
    bool isAlphaChannelUsed();
    unsigned int getColorSpace();
    unsigned int getColorType();

    // We create a function to save the modified image
    void save(char * fileName, int quality, std::string option);

    // We create a function to return the image
    std::vector<std::vector<uint8_t>> getPixels();

    // We create a function to return the requested pixel values
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
    //void showEdgeOnly();

    // We create a function to return the alpha value of a pixel
    uint8_t getAlphaValue(unsigned int x, unsigned int y);

    // We create a function to remove the alpha channel of the image
    void removeAlphaChannel();

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
    // The width and the height are the dimensions of the image in pixels
    unsigned int width = 0;
    unsigned int height = 0;

    // The pixel size is the number of values for a pixel
    // For exmple an RGB image will have a pixelSize of 3
    unsigned int pixelSize = 0;

    // The alpha used variable tell us if the alpha channel is used
    bool alphaUsed = false;

    // The color space is the same thing that the color type
    unsigned int colorSpace = 0;
    // The color type has more possibilities
    unsigned int colorType = 0;
};

#endif // GRAPHLIB_IMAGE_H
