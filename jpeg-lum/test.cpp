#include <stdio.h>
#include <jpeglib.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <math.h>
#include <dirent.h>



unsigned int width;
unsigned int height;
double luminance;
double pixel;
double clipped;

int read_jpeg_file(char *filename);

int main()
{
    DIR* dirp = opendir(".");
    struct dirent *dp;
    while ((dp = readdir(dirp)) != NULL) {
      if(dp->d_name[0] == 't') {
        read_jpeg_file(dp->d_name);
        printf("%s - %f - %f\n", dp->d_name, luminance, clipped);
        luminance=0;
        clipped = 0;
      }
    }
    closedir(dirp);
}


#define LUT_LENGTH 33
struct lut_t {
  double val;
  double ev;
};
lut_t lut[LUT_LENGTH] = 
{
  {4.793865/4,  -7},
  {4.793865/2,  -6},
  {4.793865,  -5},
  {6.056875,  -4.66666666666667},
  {7.697362,  -4.33333333333333},
  {9.780035,  -4},
  {12.092661, -3.66666666666667},
  {15.089602, -3.33333333333333},
  {18.683953, -3},
  {23.421734, -2.66666666666667},
  {28.643862, -2.33333333333333},
  {35.019192, -2},
  {42.607219, -1.66666666666667},
  {52.126612, -1.33333333333333},
  {63.956853, -1},
  {76.885797, -0.666666666666667},
  {89.6882,   -0.333333333333333},
  {103.382354,  0},
  {118.336503,  0.333333333333333},
  {135.244366,  0.666666666666667},
  {147.969053,  1},
  {162.615242,  1.33333333333333},
  {182.654258,  1.66666666666667},
  {194.224312,  2},
  {206.764022,  2.33333333333333},
  {213.891809,  2.66666666666667},
  {230.007117,  3},
  {238.483315,  3.33333333333333},
  {246.258409,  3.66666666666667},
  {249.447248,  4},
  {249.495413,  4.33333333333333},
  {252,  5},
  {253,  6}
};

double lum(double inputVal)
{
    int i;

    if(inputVal < lut[0].val) {
      return lut[0].ev - 1;
    }
    if(inputVal > lut[LUT_LENGTH-1].val) {
      return lut[LUT_LENGTH-1].ev + 1;
    }

    for( i = 0; i < LUT_LENGTH-1; i++ )
    {
        if ( lut[i].val <= inputVal && lut[i+1].val >= inputVal )
        {
            double diffx = inputVal - lut[i].val;
            double diffn = lut[i+1].val - lut[i].val;

            return lut[i].ev + ( lut[i+1].ev - lut[i].ev ) * diffx / diffn; 
        }
    }
    printf("error - not found\n");
    return 0; // Not in Range
}

int read_jpeg_file(char *filename)
{
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  JSAMPROW row_pointer[1];
  FILE *infile = fopen(filename, "rb");
  unsigned int i = 0, component = 0;
  if (!infile) {
      printf("Error opening jpeg file %s\n!", filename);
      return -1;
  }
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, infile);
  jpeg_read_header(&cinfo, TRUE);
  jpeg_start_decompress(&cinfo);

  width = cinfo.output_width;
  height = cinfo.output_height;
  luminance = 0.0;
  row_pointer[0] = (unsigned char *)malloc(cinfo.output_width*cinfo.num_components);
  unsigned long count = 0;
  while (cinfo.output_scanline < cinfo.image_height) {
      jpeg_read_scanlines( &cinfo, row_pointer, 1 );
      for (i=0; i<cinfo.image_width;i+=cinfo.num_components) {
          pixel = 0.0;
          for(component=0;component<cinfo.num_components;component++) {
              if(component < 2) {
                  pixel = (double) row_pointer[0][i + component];
                  pixel = lum(pixel);
                  if(pixel > 4) {
                    clipped++;
                  }
                  luminance += pixel;
                  count++;
              }
          }
      }
  }
  luminance /= (double)count;
  clipped /= (double)count;
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  free(row_pointer[0]);
  fclose(infile);
  return 1;
}
