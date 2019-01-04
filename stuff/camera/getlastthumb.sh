#!/bin/bash


../gphoto2/bin/gphoto2 -t `../gphoto2/bin/gphoto2 -L  | grep 'jpeg' | tail -1 | cut -f 2 -d '#' | cut -f 1 -d ' '`