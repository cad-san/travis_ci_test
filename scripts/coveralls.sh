#!/bin/bash
# send coverage report to coveralls

if [ "$CC" = "clang" ]; then
	exit 0
fi

if [ "$BUILD_TARGET" = "test" ]; then
	coveralls --root gcov || exit 1
fi
