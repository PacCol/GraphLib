#include <iostream>
#include <jpeglib.h>
#include <setjmp.h>

#include "jpeg.h"

struct my_error_mgr {
  struct jpeg_error_mgr pub;
  jmp_buf setjmp_buffer;
};

typedef struct my_error_mgr * my_error_ptr;

void my_error_exit(j_common_ptr imageInfo) {
  my_error_ptr myerr = (my_error_ptr) imageInfo->err;
  (*imageInfo->err->output_message) (imageInfo);
  longjmp(myerr->setjmp_buffer, 1);
}

// We create a class to create jpegImage object
jpegImage::jpegImage(char* fileName) {
  struct jpeg_decompress_struct imageInfo;
  struct my_error_mgr jerr;

  // We try to open the image file
  FILE * jpegFile;
  if ((jpegFile = fopen(fileName, "rb")) == NULL) {
    throw std::runtime_error("Fatal error : can't open this file");
    return;
  }

  // We search potential errors
  imageInfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;

  if (setjmp(jerr.setjmp_buffer)) {
    throw std::runtime_error("Fatal error : can't decode this file");
    jpeg_destroy_decompress(&imageInfo);
    fclose(jpegFile);
    return;
  }

  // We decompress the image
  jpeg_create_decompress(&imageInfo);
  jpeg_stdio_src(&imageInfo, jpegFile);
  jpeg_read_header(&imageInfo, TRUE);
  jpeg_start_decompress(&imageInfo);

  // We store the image informations into public variables
  width = imageInfo.output_width;
  height = imageInfo.output_height;
  colorSpace = imageInfo.out_color_space;
  pixelSize = imageInfo.output_components;

  int rowStride = imageInfo.output_width * imageInfo.output_components;

  JSAMPARRAY decompressedImage = (*imageInfo.mem->alloc_sarray) ((j_common_ptr) &imageInfo, JPOOL_IMAGE, rowStride, 1);

  // We put the pixel values into a table
  while(imageInfo.output_scanline < imageInfo.output_height) {
    jpeg_read_scanlines(&imageInfo, decompressedImage, 1);
  }

  //std::cout << "pixel 2|4 : " << decompressedImage[0];



  // Then we finish the decompression
  jpeg_finish_decompress(&imageInfo);
  jpeg_destroy_decompress(&imageInfo);

  // We close the image file
  fclose(jpegFile);
}
