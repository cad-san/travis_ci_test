#!/bin/bash
# install script for Travis CI

echo "### install libboost-dev"
sudo apt-get install libboost-dev
echo "### install libboost-thread-dev"
sudo apt-get install libboost-thread-dev
echo "### install libboost-system-dev"
sudo apt-get install libboost-system-dev
echo "### install cpp-coveralls"
sudo easy_install cpp-coveralls

if [ "$BUILD_TARGET" = "sample_qt" ]; then
    echo "### install qt4-qmake"
    sudo apt-get install qt4-qmake
    echo "### install libqt4-dev and libqt4-gui"
    sudo apt-get install libqt4-dev libqt4-gui
fi
