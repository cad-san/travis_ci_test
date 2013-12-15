#!/bin/bash
# build script for Travis CI

if [ "$BUILD_TARGET" = "test" ]; then
    if [ "$CC" = "gcc" ]; then
        make gcov;
    else
        make test;
    fi
fi

if [ "$BUILD_TARGET" = "release" ]; then
	make release
fi

if [ "$BUILD_TARGET" = "sample_qt" ]; then
    make release
    cd sample
    qmake-qt4 sample_qt.pro
    make
fi
