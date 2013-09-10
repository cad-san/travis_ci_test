#!/bin/bash
# send coverage report to coveralls


if [ "$BUILD_TARGET" = "test" ]; then 
	coveralls --root gcov
fi
