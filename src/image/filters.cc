#include <iostream>
#include <algorithm>

#define _USE_MATH_DEFINES
#include <cmath>

#include "image.h"

// We create a function to reduce the noise of the image
void Image::applyMedianFilter() {

  // We create a vector to save the new image
  std::vector<std::vector<uint8_t>> newPixels = pixels;

  // For each line of the image...
  for(unsigned int i = 1; i < height - 1; i++) {

    // For each pixel of this line...
    for(unsigned int j = 1; j < width - 1; j++) {

      // For each value of this pixel...
      for(unsigned int k = 0; k < pixelSize; k++) {

        // We create a vector to store the pixel values (value per value)
        // For example for an RGB image :
        // Fist, we calculate the median of the red values of the pixels of the neighborhood
        std::vector<uint8_t> medianPixels;
        // We reserve 9 places (3x3)
        medianPixels.reserve(9);

        // We add the pixels values in the vector
        for(int l = -1; l < 2; l++) {
          for(int m = -1; m < 2; m++) {
            medianPixels.push_back(pixels[i + l][(j + m) * pixelSize + k]);
          }
        }

        // We compute the median of this values
        std::sort(medianPixels.begin(), medianPixels.end());
        uint8_t median = medianPixels[4];

        // And we update the value
        newPixels[i][j * pixelSize + k] = median;
      }
    }
  }
  // We update the image
  pixels = newPixels;
}

// We create a function to show the edge of the objects of the image
void Image::applyCannyFilter() {

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
  std::vector<std::vector<uint8_t>> gradient (height - 2, std::vector<uint8_t>(width - 2));

  // We store the gradient direction of the pixels into a vector
  std::vector<std::vector<float>> gradientDirection (height - 2, std::vector<float>(width - 2));

  // For each line of the image...
  for(unsigned int i = 1; i < height - 1; i++) {

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
      gradient[i][j] = sqrt( pow(SXvalue * pixels[i][j], 2) + pow(SYvalue * pixels[i][j], 2) );

      // We define the direction of the gradient
      if(!SXvalue == 0) {
        gradientDirection[i][j] = atan(SYvalue / SXvalue) * 180 / M_PI;
      }
      else {
        gradientDirection[i][j] = 90;
      }
    }
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
        if(gradient[i][j] > gradient[i - 1][j] && gradient[i][j] > gradient[i + 1][j]) {
          newLine.push_back(255);
        }
        else {
          newLine.push_back(0);
        }
      }

      if(gradientDirection[i][j] > - 22.5 && gradientDirection[i][j] <= 22.5) {
        if(gradient[i][j] > gradient[i - 1][j] && gradient[i][j] > gradient[i + 1][j]) {
          newLine.push_back(255);
        }
        else {
          newLine.push_back(0);
        }
      }

      if(gradientDirection[i][j] > 22.5 && gradientDirection[i][j] <= 67.5) {
        if(gradient[i][j] > gradient[i - 1][j] && gradient[i][j] > gradient[i + 1][j]) {
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

      // We push the new line
      newPixels.push_back(newLine);
    }
  }

  pixels = gradient;
}
