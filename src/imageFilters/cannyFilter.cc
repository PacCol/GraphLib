#include <algorithm>
#include <cmath>

#include "../image.h"

// We create a function to show the edge of the objects of the image
void Image::applyCannyFilter(unsigned int highLimit, unsigned int lowLimit) {

  // If the image is not a grayscale, we convert it
  if(colorSpace != 1) {
    convertToGrayscale();
  }

  // If the image has an alpha channel, we remove it
  if(alphaUsed) {
    removeAlphaChannel();
  }

  // We can't compute the gradient of the borders of the image
  // So the output image will be smaller

  // We check if the dimensions will be sufficient
  if(width < 25 || height < 25) {
    throw std::runtime_error("Error : in Image::applyCannyFilter : The dimensions of the input image are too small");
  }

  // We store the gradient values into a vector
  std::vector<std::vector<uint16_t>> gradient;
  // We reserve the height of the image
  gradient.reserve(height - 2);

  // We store the gradient direction of the pixels into a vector
  std::vector<std::vector<float>> gradientDirection;
  // We reserve the height of the image
  gradientDirection.reserve(height - 2);

  // For each line of the image...
  for(unsigned int i = 1; i < height - 1; i++) {

    // We create a vector to save the new line
    std::vector<uint16_t> gradientLine;
    // We reserve the line width
    gradientLine.reserve(width - 2);

    // We create a vector to save the new line
    std::vector<float> gradientDirectionLine;
    // We reserve the line width
    gradientDirectionLine.reserve(width - 2);

    // For each pixel of this line...
    for(unsigned int j = 1; j < width - 1; j++) {

      // We want to compute the gradient
      float SXvalue = (-1 * pixels[i - 1][j - 1]
                        + 1 * pixels[i - 1][j + 1]
                        + -2 * pixels[i][j - 1]
                        + 2 * pixels[i][j + 1]
                        + -1 * pixels[i + 1][j - 1]
                        + 1 * pixels[i + 1][j + 1]
                      );

      float SYvalue = (-1 * pixels[i - 1][j - 1]
                        + 1 * pixels[i - 1][j + 1]
                        + -2 * pixels[i - 1][j]
                        + 2 * pixels[i + 1][j]
                        + -1 * pixels[i + 1][j - 1]
                        + 1 * pixels[i + 1][j + 1]
                      );

      // We define the gradient value
      gradientLine.push_back( sqrt( pow(SXvalue * pixels[i][j], 2) + pow(SYvalue * pixels[i][j], 2) ) );

      // We define the direction of the gradient (in grades)
      if(!SXvalue == 0) {
        gradientDirectionLine.push_back(atan(SYvalue / SXvalue) * 200 / M_PI);
      }
      else {
        gradientDirectionLine.push_back(100);
      }
    }

    // We push the new lines
    gradient.push_back(gradientLine);
    gradientDirection.push_back(gradientDirectionLine);
  }

  // We delete the borders of the image
  // (We can't compute the gradient of the borders of the image)
  width = width - 2;
  height = height - 2;

  // We create a new vector to save the new pixels
  std::vector<std::vector<uint8_t>> newPixels;
  // We reserve the output height
  // (The borders are ignored once again)
  newPixels.reserve(height - 2);

  // For each line of the image...
  for(unsigned int i = 1; i < height - 1; i++) {

    // We create a vector to save the new line
    std::vector<uint8_t> newLine;
    // We reserve the line width
    // (The borders are ignored once again)
    newLine.reserve(width - 2);

    // For each pixel of this line...
    for(unsigned int j = 1; j < width - 1; j++) {

      // We remove the pixels that are not part of the outlines
      // A pixel is only retained if the gradient is maximum in its direction

      // We create a macro to to do the hysteresis thresholding
      #define HYSTERESIS_THRESOLDING          \
        if(gradient[i][j] > highLimit) {      \
          newLine.push_back(255);             \
        }                                     \
        else if(gradient[i][j] > lowLimit) {  \
          newLine.push_back(100);             \
        }                                     \
        else {                                \
          newLine.push_back(0);               \
        }


      if(-100 <= gradientDirection[i][j] && gradientDirection[i][j] < -75) {
        if(gradient[i][j] > gradient[i + 1][j] && gradient[i][j] > gradient[i - 1][j]) {
          HYSTERESIS_THRESOLDING;
        }
        else {
          newLine.push_back(0);
        }
      }
      else if(-75 <= gradientDirection[i][j] && gradientDirection[i][j] < -25) {
        if(gradient[i][j] > gradient[i - 1][j + 1] && gradient[i][j] > gradient[i + 1][j - 1]) {
          HYSTERESIS_THRESOLDING;
        }
        else {
          newLine.push_back(0);
        }
      }
      else if(-25 <= gradientDirection[i][j] && gradientDirection[i][j] < 25) {
        if(gradient[i][j] > gradient[i][j + 1] && gradient[i][j] > gradient[i][j - 1]) {
          HYSTERESIS_THRESOLDING;
        }
        else {
          newLine.push_back(0);
        }
      }
      else if(25 <= gradientDirection[i][j] && gradientDirection[i][j] < 75) {
        if(gradient[i][j] > gradient[i + 1][j + 1] && gradient[i][j] > gradient[i - 1][j - 1]) {
          HYSTERESIS_THRESOLDING;
        }
        else {
          newLine.push_back(0);
        }
      }
      else if(75 <= gradientDirection[i][j] && gradientDirection[i][j] <= 100) {
        if(gradient[i][j] > gradient[i - 1][j] && gradient[i][j] > gradient[i + 1][j]) {
          HYSTERESIS_THRESOLDING;
        }
        else {
          newLine.push_back(0);
        }
      }

    }

    // We push the new line
    newPixels.push_back(newLine);
  }

  // We delete the borders of the image
  // (We find the values for the borders of the image)
  width = width - 2;
  height = height - 2;

  // We update the pixels
  pixels = newPixels;
}
