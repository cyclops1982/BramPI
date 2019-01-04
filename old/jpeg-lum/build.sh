#!/bin/bash

# sudo apt-get install libjpeg-dev
rm TestApp
g++ -Wall -g test.cpp -o TestApp -ljpeg