#! /bin/bash
PRJECTDIR=`pwd`
EMSDK_PATH=$HOME/emsdk
cd $EMSDK_PATH && git pull &&
./emcmdprompt
./emsdk install latest && 
./emsdk activate latest && 
source ./emsdk_env.sh &&
HELLO=WORLD
EMSCRIPTEN_PATH=$EMSDK_PATH/upstream/emscripten
CLANG_PATH=$EMSDK_PATH/upstream/bin
NODE_PATH=$EMSDK_PATH/node/12.9.1_64bit/bin
PATH=$PATH:$EMSDK_PATH:$EMSCRIPTEN_PATH:$CLANG_PATH:$NODE_PATH &&
cd $PRJECTDIR &&
emcmake cmake -S . -B build &&
make PLATFORM=PLATFORM_WEB -B &&
cmake --build build && 
make -C build PLATFORM=PLATFORM_WEB -B &&
python3 wasm-server.py
