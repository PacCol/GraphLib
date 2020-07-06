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

#### Build your own project with Graphlib :
Replace the main.cc file by your own code. The main.cc file is an example to show you how to use the lib.

#### Important :
To get the first RGB pixel value you must write : `myImage.getRgbColor(0, 0);` and not `myImage.getRgbColor(1, 1);`  
To get the last RGB pixel value you must write : `myImage.getRgbColor(myImage.getWidth() - 1, myImage.getHeight() - 1);` and not `myImage.getRgbColor(myImage.getWidth(), myImage.getHeight());`
