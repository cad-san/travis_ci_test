#!/bin/bash
# build script for Travis CI

if [ "$BUILD_TARGET" = "test" ]; then 
	make gcov
fi

if [ "$BUILD_TARGET" = "release" ]; then 
	make release
fi
