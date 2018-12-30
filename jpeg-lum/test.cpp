#include <iostream>
#include <vector>
#include "jpeg-lum.cc"

using namespace std;


int main(int argc, char **argv) 
{

  if (argc <= 1) {
    cout<<"Usage "<<argv[0]<<" <file> "<<endl;
    return -1;
  }

  std::vector<std::string> images;
  images.assign(argv+1, argv+argc);

  for (std::vector<string>::const_iterator image = images.begin(); image != images.end(); ++image) {
    cout<<"File:" <<*image<<endl;
    JpegLum a = JpegLum(&(*image));
    cout<<"\tLuminance:"<<a.luminance<<endl;
  }
  return 0;
} 