#!/bin/bash

rm -rf build
mkdir build
cd build
conan install ../scripts/ --build=missing
cmake ..
cmake --build .