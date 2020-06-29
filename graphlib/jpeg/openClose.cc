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

// We create a class to create a jpegImage object
jpegImage::jpegImage(char* fileName) {
  struct jpeg_decompress_struct imageInfo;
  struct my_error_mgr jerr;

  // We try to open the image file
  FILE * inputJpegFile;
  if((inputJpegFile = fopen(fileName, "rb")) == NULL) {
    throw std::runtime_error("Error : can't open this file");
  }

  // We search potential errors
  imageInfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;

  if(setjmp(jerr.setjmp_buffer)) {
    throw std::runtime_error("Error : can't decode this file");
    jpeg_destroy_decompress(&imageInfo);
    fclose(inputJpegFile);
    return;
  }

  // We decompress the image
  jpeg_create_decompress(&imageInfo);
  jpeg_stdio_src(&imageInfo, inputJpegFile);
  jpeg_read_header(&imageInfo, TRUE);
  jpeg_start_decompress(&imageInfo);

  // We store the image informations into public variables
  width = imageInfo.output_width;
  height = imageInfo.output_height;
  colorSpace = imageInfo.out_color_space;
  pixelSize = imageInfo.output_components;

  int rowStride = width * pixelSize;

  // We read the image line per line
  while(imageInfo.output_scanline < height) {
    std::vector<uint8_t> scannedLine(rowStride);
    uint8_t* p = scannedLine.data();
    jpeg_read_scanlines(&imageInfo, &p, 1);

    // We put the pixels values into a table
    pixels.push_back(scannedLine);
  }

  // Then we finish the decompression
  jpeg_finish_decompress(&imageInfo);
  jpeg_destroy_decompress(&imageInfo);

  // We close the image file
  fclose(inputJpegFile);
}

void jpegImage::save(char * fileName, int quality) {
  struct jpeg_compress_struct imageInfo;
  struct jpeg_error_mgr jerr;

  // We try to create the image file
  FILE * outputJpegFile;
  if ((outputJpegFile = fopen(fileName, "wb")) == NULL) {
    throw std::runtime_error("Error : can't create this file");
  }
  
  imageInfo.err = jpeg_std_error(&jerr);

  jpeg_create_compress(&imageInfo);
  jpeg_stdio_dest(&imageInfo, outputJpegFile);

  // We define some informations
  imageInfo.image_width = width;
  imageInfo.image_height = height;
  imageInfo.input_components = pixelSize;
  imageInfo.in_color_space = J_COLOR_SPACE(colorSpace);

  jpeg_set_defaults(&imageInfo);
  jpeg_set_quality(&imageInfo, quality, TRUE);
  jpeg_start_compress(&imageInfo, TRUE);

  int rowStride = width * pixelSize;

  // Let's assume this vector is not empty.
  /*vector<string> strs;
  const vector<string>::iterator end_it = strs.end();

  for (vector<string>::iterator it = strs.begin(); it != end_it; ++it) {
    const string& s = *it;
    // Some code here...
  }
  
  vector<string> &strs;
  for (const auto &s : strs){
   //
  }*/

  for(auto const& vecLine : pixels) {
    JSAMPROW rowPtr[1];
    rowPtr[0] = const_cast<::JSAMPROW>( vecLine.data() );
    jpeg_write_scanlines(&imageInfo, rowPtr, 1);
  }

  // Then we finish the decompression
  jpeg_finish_compress(&imageInfo);
  jpeg_destroy_compress(&imageInfo);

  // We close the image file
  fclose(outputJpegFile);
}
