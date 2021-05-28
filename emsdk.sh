#! /bin/bash
PRJECTDIR=`pwd`
EMSDK_PATH=$HOME/emsdk
if [[ ! -d $HOME/emsdk ]]; then
    git clone https://github.com/emscripten-core/emsdk.git
fi
cd $EMSDK_PATH &&
./emsdk install tot &&
./emsdk install latest && 
./emsdk activate latest && 
source ./emsdk_env.sh &&
EMSCRIPTEN_PATH=$EMSDK_PATH/upstream/emscripten
CLANG_PATH=$EMSDK_PATH/upstream/bin
PATH=$PATH:$EMSDK_PATH:$EMSCRIPTEN_PATH:$CLANG_PATH:$NODE_PATH &&
cd $PRJECTDIR &&
emcmake cmake -S . -B build &&
make PLATFORM=PLATFORM_WEB -B &&
cmake --build build && 
make -C build PLATFORM=PLATFORM_WEB -B &&
python3 wasm-server.py
