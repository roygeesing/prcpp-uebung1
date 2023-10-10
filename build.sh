#!/bin/bash
set -e

mkdir -p build
cd build
if [ ! -f Makefile ]; then
    cmake ..
fi
make