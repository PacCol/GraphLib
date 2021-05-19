#include "graphlib.h"

// We create a function to resize the image
void Image::resize(unsigned int newWidth)
{
  // We check the new width
  if (newWidth == width)
  {
    return;
  }
  else if (newWidth > width)
  {
    throw std::runtime_error("Error : in Image::resize : The new width can't be larger than the actual width");
  }

  // We are computing the scale
  float scale = float(width) / float(newWidth);

  // We are computing the new height with the new width and the actual width
  unsigned int newHeight = float(newWidth) / float(width) * float(height);

  // We create a vector to save the new image
  std::vector<std::vector<uint8_t>> newPixels;
  // We reserve the output height
  newPixels.reserve(newHeight);

  // We are computing the row stride
  int rowStride = newWidth * pixelSize;

  // For each line of the image...
  for (unsigned int i = 0; i < newHeight; i++)
  {
    // We create a vector to save the new line
    std::vector<uint8_t> newLine;
    // We reserve the row stride
    newLine.reserve(rowStride);

    // For each pixel of this line...
    for (unsigned int j = 0; j < newWidth; j++)
    {
      // For each value of this pixel...
      for (unsigned int k = 0; k < pixelSize; k++)
      {
        // We set the pixel value using the scale
        // With the scale, we find the corresponding pixels between the resized image and the original image
        newLine.push_back(pixels[static_cast<unsigned int>(i * scale)][(static_cast<unsigned int>(j * scale)) * pixelSize + k]);
      }
    }
    // We push the new line into the newPixels vector
    newPixels.push_back(newLine);
  }

  // We update the image
  pixels = newPixels;

  // We update the image informations
  width = newWidth;
  height = newHeight;
}

// We create a function to crop the image
void Image::crop(unsigned int xStartPoint, unsigned int yStartPoint, unsigned int newWidth, unsigned int newHeight)
{
  // We check the values
  if (xStartPoint + newWidth > width)
  {
    throw std::runtime_error("Error : in Image::crop : The X value is out of range");
  }
  else if (newWidth == 0)
  {
    throw std::runtime_error("Error : in Image::crop : The new width can't be 0");
  }
  else if (yStartPoint + newHeight > height)
  {
    throw std::runtime_error("Error : in Image::crop : The Y value is out of range");
  }
  else if (newHeight == 0)
  {
    throw std::runtime_error("Error : in Image::crop : The new height can't be 0");
  }

  // We create a vector to save the new image
  std::vector<std::vector<uint8_t>> newPixels;
  // We reserve the output height
  newPixels.reserve(newHeight);

  // We are computing the row stride
  int rowStride = newWidth * pixelSize;

  // For each line of the image...
  for (unsigned int i = 0; i < newHeight; i++)
  {
    // We create a vector to save the new line
    std::vector<uint8_t> newLine;
    // We reserve the line width
    newLine.reserve(rowStride);

    // For each pixel of this line...
    for (unsigned int j = 0; j < newWidth; j++)
    {
      // For each value of this pixel...
      for (unsigned int k = 0; k < pixelSize; k++)
      {
        // We set the pixel value
        // We take into consideration the x start point and the y start point
        newLine.push_back(pixels[yStartPoint + i][(xStartPoint + j) * pixelSize + k]);
      }
    }
    // We push the new line into the newPixels vector
    newPixels.push_back(newLine);
  }

  // We update the image
  pixels = newPixels;

  // We update the image informations
  width = newWidth;
  height = newHeight;
}
