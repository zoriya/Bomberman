#! /bin/bash
PRJECTDIR=`pwd`
EMSDK_PATH=./emsdk
if [[ ! -d ./emsdk ]]; then
    git clone https://github.com/emscripten-core/emsdk.git
fi
./emsdk/emsdk install tot
./emsdk/emsdk activate latest
source ./emsdk/emsdk_env.sh
mkdir -p build &&
cmake -S . -B build &&
cmake --build build