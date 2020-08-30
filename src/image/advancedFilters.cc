#include <iostream>
#include <algorithm>

#define _USE_MATH_DEFINES
#include <cmath>

#include "image.h"

// We create a function to show the edge of the objects of the image
void Image::applyCannyFilter() {

  // We define the limits to select the pixels that will be retained
  const unsigned int highLimit = 170;
  const unsigned int lowLimit = 85;

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

  // We store the gradient values into a vector
  std::vector<std::vector<uint8_t>> gradient;
  // We reserve the height of the image
  gradient.reserve(height - 2);

  // We store the gradient direction of the pixels into a vector
  std::vector<std::vector<float>> gradientDirection;
  // We reserve the height of the image
  gradientDirection.reserve(height - 2);

  // For each line of the image...
  for(unsigned int i = 1; i < height - 1; i++) {

    // We create a vector to save the new line
    std::vector<uint8_t> gradientLine;
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
                        ) / 8;

      float SYvalue = (-1 * pixels[i - 1][j - 1]
                        + 1 * pixels[i - 1][j + 1]
                        + -2 * pixels[i - 1][j]
                        + 2 * pixels[i + 1][j]
                        + -1 * pixels[i + 1][j - 1]
                        + 1 * pixels[i + 1][j + 1]
                        ) / 8;

      // We define the gradient value
      gradientLine.push_back( sqrt( pow(SXvalue * pixels[i][j], 2) + pow(SYvalue * pixels[i][j], 2) ) );

      // We define the direction of the gradient
      if(!SXvalue == 0) {
        gradientDirectionLine.push_back( atan(SYvalue / SXvalue) * 180 / M_PI );
      }
      else {
        gradientDirectionLine.push_back(90);
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

      if(gradientDirection[i][j] > - 90 && gradientDirection[i][j] <= - 67.5) {
        if(gradient[i][j] > gradient[i - 1][j] && gradient[i][j] > gradient[i + 1][j]) {
          newLine.push_back(255);
        }
        else {
          newLine.push_back(0);
        }
      }

      if(gradientDirection[i][j] > - 67.5 && gradientDirection[i][j] <= - 22.5) {
        if(gradient[i][j] > gradient[i - 1][j - 1] && gradient[i][j] > gradient[i - 1][j - 1]) {
          newLine.push_back(255);
        }
        else {
          newLine.push_back(0);
        }
      }

      if(gradientDirection[i][j] > - 22.5 && gradientDirection[i][j] <= 22.5) {
        if(gradient[i][j] > gradient[i][j - 1] && gradient[i][j] > gradient[i][j + 1]) {
          newLine.push_back(255);
        }
        else {
          newLine.push_back(0);
        }
      }

      if(gradientDirection[i][j] > 22.5 && gradientDirection[i][j] <= 67.5) {
        if(gradient[i][j] > gradient[i - 1][j + 1] && gradient[i][j] > gradient[i + 1][j - 1]) {
          newLine.push_back(255);
        }
        else {
          newLine.push_back(0);
        }
      }

      if(gradientDirection[i][j] > 67.5 && gradientDirection[i][j] <= 90) {
        if(gradient[i][j] > gradient[i - 1][j] && gradient[i][j] > gradient[i + 1][j]) {
          newLine.push_back(255);
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
