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

int readJpegImage(char* fileName) {
  struct jpeg_decompress_struct imageInfo;
  struct my_error_mgr jerr;

  FILE * jpegFile;
  JSAMPARRAY buffer;
  int row_stride;

  if ((jpegFile = fopen(fileName, "rb")) == NULL) {
    throw std::runtime_error("Fatal error : can't open this file");
    return 0;
  }

  imageInfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;

  if (setjmp(jerr.setjmp_buffer)) {
    throw std::runtime_error("Fatal error : can't decode this file");
    jpeg_destroy_decompress(&imageInfo);
    fclose(jpegFile);
    return 0;
  }

  jpeg_create_decompress(&imageInfo);
  jpeg_stdio_src(&imageInfo, jpegFile);
  jpeg_read_header(&imageInfo, TRUE);
  jpeg_start_decompress(&imageInfo);

  row_stride = imageInfo.output_width * imageInfo.output_components;

  buffer = (*imageInfo.mem->alloc_sarray)
		((j_common_ptr) &imageInfo, JPOOL_IMAGE, row_stride, 1);

  while (imageInfo.output_scanline < imageInfo.output_height) {
    jpeg_read_scanlines(&imageInfo, buffer, 1);
    /* Assume put_scanline_someplace wants a pointer and sample count. */
    //put_scanline_someplace(buffer[0], row_stride);
  }

  (void) jpeg_finish_decompress(&imageInfo);
  jpeg_destroy_decompress(&imageInfo);

  fclose(jpegFile);

  return 1;
}
