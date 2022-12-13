#!/bin/bash

rm -rf build
mkdir build
cd build
conan install ../scripts/
cmake ..
cmake --build .