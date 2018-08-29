#!/bin/bash

if [ $1 ] && [ $1 = '-c' ] # clean
then
    rm -rf build
fi

mkdir -p lib
cd lib
cmake ..

if [[ "$OSTYPE" == "linux-gnu" ]]; then
    # Linux
    make -j `nproc`
elif [[ "$OSTYPE" == "darwin"* ]]; then
    # Mac OSX
    make -j `sysctl -n hw.ncpu`
fi
