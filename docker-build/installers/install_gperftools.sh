#!/usr/bin/env bash

###############################################################################
# Copyright 2020 The Apollo Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
###############################################################################

# Fail on first error.
set -e

cd "$(dirname "${BASH_SOURCE[0]}")"

. /tmp/installers/installer_base.sh

apt-get -y update && \
    apt-get -y install \
    valgrind \
    libunwind-dev

VALGRIND_FLAGS="$(pkg-config --cflags valgrind)"

VERSION="2.7"
PKG_NAME="gperftools-${VERSION}.tar.gz"
DOWNLOAD_LINK="https://github.com/gperftools/gperftools/releases/download/gperftools-${VERSION}/${PKG_NAME}"
CHECKSUM="1ee8c8699a0eff6b6a203e59b43330536b22bbcbe6448f54c7091e5efb0763c9"

download_if_not_cached "${PKG_NAME}" "${CHECKSUM}" "${DOWNLOAD_LINK}"

tar xzf ${PKG_NAME}

pushd gperftools-${VERSION}

    export CXXFLAGS="${VALGRIND_FLAGS} -O2 -DNDEBUG -fno-strict-aliasing"
    ./configure \
        --prefix=${SYSROOT_DIR} \
        --enable-shared \
        --enable-static=no \
        --with-gnu-ld \
        --with-pic \
        --enable-libunwind \
        --enable-frame-pointers \
        --disable-debugalloc

    make -j$(nproc)
    make install
popd

# clean up
rm -rf gperftools-${VERSION} ${PKG_NAME}
