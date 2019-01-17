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
    if [ "$TRAVIS_OS_NAME" = "windows" ] ; then
        # TODO: watch https://gitlab.kitware.com/cmake/cmake/issues/18745
        cmake -G"$TRAVIS_CMAKE_GENERATOR" \
              -DCMAKE_BUILD_TYPE=$TRAVIS_BUILD_TYPE \
              -DCMAKE_INSTALL_PREFIX="$DEPS_INSTALL_PREFIX" \
              -DCMAKE_C_COMPILER=clang-cl \
              -DCMAKE_CXX_COMPILER=clang-cl \
              -DCMAKE_LINKER=lld-link \
              -DCMAKE_GENERATOR_RC=llvm-rc \
              -DCMAKE_RC_COMPILER=llvm-rc \
              -DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=lld-link" \
              ..
        cmake --build .
        cmake --build . --target install
    else
        cmake -G"$TRAVIS_CMAKE_GENERATOR" \
              -DCMAKE_BUILD_TYPE=$TRAVIS_BUILD_TYPE \
              -DCMAKE_INSTALL_PREFIX="$DEPS_INSTALL_PREFIX" \
              ..
              cmake --build .
              cmake --build . --target install
    fi
fi
