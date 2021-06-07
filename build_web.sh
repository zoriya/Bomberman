#! /bin/bash
EMSDK_PATH=./emsdk
if [[ ! -d ./emsdk ]]; then
    git clone https://github.com/emscripten-core/emsdk.git
fi
./emsdk/emsdk install latest
./emsdk/emsdk activate latest
source ./emsdk/emsdk_env.sh
mkdir -p build_web
emcmake cmake -S . -B build_web -DPLATFORM=Web &&
cd build_web && make -j $2