#!/bin/bash

mkdir -p build  || exit 2
cd build || exit 2
cmake .. || exit 2
make -s -j4 || exit 2
cd ..

