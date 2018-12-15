#!/bin/bash

# sudo apt-get install libjpeg-dev

rm TestApp

g++ -Wall  test.cpp -o TestApp -ljpeg


