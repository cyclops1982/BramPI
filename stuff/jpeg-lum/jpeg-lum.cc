// Simple C++ program that outputs the luminicance of a jpeg file.
// Code copied from https://github.com/elijahparker/node-jpeg-lum


#include <stdio.h>
#include <jpeglib.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <math.h>

#include "jpeg-lum.hh"

using namespace std;

double JpegLum::lum(double x)
{
    if(x < lut[0].x) {
      return lut[0].y - 1;
    }
    if(x > lut[LUT_LENGTH-1].x) {
      return lut[LUT_LENGTH-1].y + 1;
    }

    for(int i = 0; i < LUT_LENGTH-1; i++ ) {
        if ( lut[i].x <= x && lut[i+1].x >= x ) {
            double diffx = x - lut[i].x;
            double diffn = lut[i+1].x - lut[i].x;

            return lut[i].y + ( lut[i+1].y - lut[i].y ) * diffx / diffn; 
        }
    }
    cout << "error - not found"<<std::endl;
    return 0; // Not in Range
}

JpegLum::JpegLum(const std::string *filename) {
  ReadJpegFile(filename->c_str());
}

void JpegLum::ReadJpegFile(const char *filename)
{
  double pixel;
  unsigned long count = 0;

  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  JSAMPROW row_pointer[1];
  FILE *infile = fopen(filename, "rb");
  if (!infile) {
      cout<<"Error opening jpeg file "<<filename<<endl; 
      throw "Error opening jpeg file";
  }
  
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, infile);
  jpeg_read_header(&cinfo, TRUE);
  jpeg_start_decompress(&cinfo);

  this->width = cinfo.output_width;
  this->height = cinfo.output_height;
  this->luminance = 0.0;
  this->size = cinfo.output_width * cinfo.output_height * cinfo.num_components * sizeof(unsigned int);
  row_pointer[0] = (unsigned char *)malloc(cinfo.output_width*cinfo.num_components);
  
  while (cinfo.output_scanline < cinfo.image_height) {
      jpeg_read_scanlines( &cinfo, row_pointer, 1 );
      for (unsigned int i=0; i<cinfo.image_width;i+=cinfo.num_components) {
          pixel = 0.0;
          for(int component=0;component<cinfo.num_components;component++) {
              if(component < 3) {
                  pixel = lum((double)row_pointer[0][i + component]);
                  if(pixel > 4) {
                    this->clipped++;
                  }
                  this->luminance += pixel;
                  this->histogram[component][(int)pixel]++;
                  count++;
              }
          }
      }
  }
  this->luminance /= (double)count;
  this->clipped /= (double)count;
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  free(row_pointer[0]);
  fclose(infile);
}