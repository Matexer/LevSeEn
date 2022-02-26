source ~/Programy/emsdk/emsdk_env.sh
emcmake cmake .. -WebAssembly=ON
make -s ERROR_ON_UNDEFINED_SYMBOLS=0
