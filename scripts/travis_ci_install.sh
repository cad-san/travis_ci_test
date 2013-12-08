#!/bin/bash
# install script for Travis CI

sudo apt-get install libboost-dev
sudo apt-get install libboost-thread-dev
sudo apt-get install libboost-system-dev
sudo easy_install cpp-coveralls

if [ "$BUILD_TARGET" = "sample_qt" ]; then
    sudo apt-get install qt4-qmake
    sudo apt-get install libqt4-dev libqt4-gui
fi
