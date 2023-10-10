#!/bin/bash
set -e

# Compile
./build.sh

echo "==============================================================================="
# Run Catch2 binary with arguments passed to the script
ARGS=""
if [ -n "$1" ]; then
    ARGS+="--gtest_filter=Task$1.*"
fi
set -x

cd bin
./astro_test $ARGS
