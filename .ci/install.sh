#!/bin/sh
set -e
set -u

cd /tmp
git clone --depth 1 https://github.com/robotology/blockfactory
cd blockfactory
mkdir -p build && cd build

if [ "$TRAVIS_CMAKE_GENERATOR" = "Visual Studio 15 2017" ] ; then
    cmake -G"$TRAVIS_CMAKE_GENERATOR" \
          -A"$TRAVIS_CMAKE_ARCHITECTURE" \
          -DCMAKE_INSTALL_PREFIX="$DEPS_INSTALL_PREFIX" \
          ..
    cmake --build . --config $TRAVIS_BUILD_TYPE
    cmake --build . --config $TRAVIS_BUILD_TYPE --target INSTALL
else
    cmake -G"$TRAVIS_CMAKE_GENERATOR" \
          -DCMAKE_BUILD_TYPE=$TRAVIS_BUILD_TYPE \
          -DCMAKE_INSTALL_PREFIX="$DEPS_INSTALL_PREFIX" \
          ..
    cmake --build .
    cmake --build . --target install
fi
