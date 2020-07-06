# GraphLib
### A graphic library

## Get started
First install libjpeg-dev (debian, ubuntu) or libjpeg-devel (fedora)  
Install G++

## Open an image
`jpegImage myImage(fileName);` will open the image  
You must create a char named fileName : `char fileName[] = "test.jpg";`

## Read some informations
### There are some functions to read the image informations :

#### The dimensions `myImage.getWidth(); myImage.getHeight();`
You can get the dimensions of the image (in pixels)

#### The pixelSize `myImage.getPixelSize();`
If the pixelSize is 1, the image is monochrome  
If the pixelSize is 3, the image is colored

## Read the pixels color
Use : `myImage.getRgbColor(x, y);` to get the color of a pixel (X and Y are integer)
This will return an `std::vector<uint8_t>` that contain the RGB values or a single value if the image is monochrome

#### Example :
```
#include <iostream>
#include "graphlib/jpeg/jpeg.h"

int main() {
  std::cout << "\n";

  char fileName[] = "imageSamples/test.jpg";
  jpegImage myImage(fileName);

  std::cout << "Image Dimensions : " << myImage.width << "x" << myImage.height <<"\n";
  std::cout << "Image Color Space : " << myImage.colorSpace << "\n";
  std::cout << "Image Pixel Size : " << myImage.pixelSize << "\n";

  std::cout << "Image Pixel : X=3, Y=6 : ";
  std::vector<uint8_t> scannedPixel = myImage.getRgbColor(3, 6);
  std::cout << " R=" << +scannedPixel[0] << " G=" << +scannedPixel[1]  << " B=" << +scannedPixel[2] << "\n";

  std::cout << "\n";
}

```

#### Important :
To get the first pixel you must write : `myImage.getRgbColor(0, 0);` and not `myImage.getRgbColor(1, 1);`  
To get the last pixel you must write : `myImage.getRgbColor(myImage.width - 1, myImageHeight - 1);` and not `myImage.getRgbColor(myImage.width, myImageHeight);`
