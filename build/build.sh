#! /bin/sh

rm -rf src
rm -rf eFiles
rm cmake_install.cmake
rm Makefile
cmake ..
make 
