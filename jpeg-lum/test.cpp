#include <iostream>
#include <vector>
#include "jpeg-lum.cc"

using namespace std;


int main(int argc, char **argv) 
{

  if (argc < 1) {
    cout<<"Usage "<<argv[0]<<" <file> "<<endl;
    return -1;
  }

  std::vector<std::string> images;
  images.assign(argv+1, argv+argc);

  for (std::vector<string>::iterator image = images.begin(); image != images.end(); ++image) {
    cout<<"File:" <<*image<<endl;
    string a(*image);
    cout<<"A="<<a<<endl;
    lum_info_t info = read_jpeg_file(a.c_str());
    cout<<"\tLuminance:"<<info.luminance<<endl;
  }
  return 0;
} 