#! /bin/bash
set -euo pipefail

CURR_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"
. ${CURR_DIR}/installer_base.sh

ARCH="$(uname -m)"
if [[ "${ARCH}" != "x86_64" ]]; then
  warning "Unsupported CPU architecture ${ARCH} for aws-sdk-cpp. Exit."
  exit 0
fi

VERSION="1.8.141"
PKG_NAME="aws-sdk-cpp-${VERSION}.tar.gz"
DOWNLOAD_LINK="https://github.com/aws/aws-sdk-cpp/archive/${VERSION}.tar.gz"
CHECKSUM="f45143289013c500f303ac1e4d5977a856b49aaa52fe604bb7c001ba4145bc44"

download_if_not_cached "${PKG_NAME}" "${CHECKSUM}" "${DOWNLOAD_LINK}"

tar xzf "${PKG_NAME}"

pushd "${PKG_NAME%.tar.gz}" > /dev/null
mkdir build && cd build
cmake .. \
  -DBUILD_ONLY="dynamodb;s3;storagegateway;transfer" \
  -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
make install

rm -rf "${PKG_NAME}" "${PKG_NAME%.tar.gz}"
ok "Done installing aws-sdk-cpp ${VERSION}"
