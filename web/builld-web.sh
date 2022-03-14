rm -rfv web-build/*
cd web-build
source ~/Programy/emsdk/emsdk_env.sh
emcmake cmake ..
make