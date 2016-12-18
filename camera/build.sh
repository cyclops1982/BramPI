#!/bin/bash

# to get these parameters
# use export PKG_CONFIG_PATH=path to gphotolib
# and use LD_LIBRARY_PATH=/pathto/ ./executable to run these than...

gcc -Wall -o capture -I/home/cyclops/dev/BramPI/libgphoto2/include/gphoto2 -I/usr/include/libexif capture.c -L/home/cyclops/dev/BramPI/libgphoto2/lib -lgphoto2 -lgphoto2_port -lm 
