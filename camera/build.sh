#!/bin/bash

# to get these parameters
# use export PKG_CONFIG_PATH=path to gphotolib
# and use LD_LIBRARY_PATH=/pathto/ ./executable to run these than...


#g++ -Wall -g -o getcamerasettings `pkg-config --cflags --libs libgphoto2` getcamerasettings.cc
#gcc	-Wall -g -o capture -I/home/cyclops/dev/BramPI/libgphoto2/include/gphoto2 -I/usr/include/libexif -L/home/cyclops/dev/BramPI/libgphoto2/lib -lgphoto2 -lgphoto2_port -lm capture.c
gcc	-Wall -g -o capture `pkg-config --cflags --libs libgphoto2` capture.c
