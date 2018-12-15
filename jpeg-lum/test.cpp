#include <iostream>

#include "jpeg-lum.cc"

using namespace std;


int main() 
{
    string abc = "TestPics/Test_-1.jpg";
    int x = read_jpeg_file(abc.c_str());
    cout << "luminance = " <<luminance<<endl;
    return 0;
}