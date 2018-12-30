#include <stdio.h>
#include <jpeglib.h>


class JpegLum {
private:
  #define LUT_LENGTH 33
  struct lut_t {
   double x;
   double y;
  };


  struct lum_info_t {
    unsigned int size;
    //unsigned int histogram[3][256];
    unsigned int width;
    unsigned int height;
    double luminance;
    double clipped;
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


  double lum(double x);
  lum_info_t ReadJpegFile(const char *filename);




public:
  JpegLum(const std::string *filename);

  unsigned int size;
  unsigned int width;
  unsigned int height;
  double luminance;
  double clipped;
};