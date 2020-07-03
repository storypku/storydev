#!/usr/bin/env bash
# Based on nvidia-l4t-apt-source_32.4.2-20200408182620_arm64.deb

if [ ! -f /.dockerenv ]; then
    echo "Expected to run inside container!"
    exit 1
fi

if [ "$(uname -m)" != "aarch64" ]; then
    echo "Expected to run on aarch64 only!"
    exit 1
fi

NV_CONF="/etc/nv_boot_control.conf"

if [ ! -e "${NV_CONF}" ]; then
    echo "${NV_CONF} not found. Please (docker) cp ${NV_CONF} from Jetson" \
         "host info container."
    echo "  E.g. docker cp ${NV_CONF} apollo_cyber_$USER:${NV_CONF}"
    exit 1
fi

cp -f nvidia-l4t-apt-source.list /etc/apt/sources.list.d/
cp -f jetson-ota-public.asc /etc/apt/trusted.gpg.d/

DOC_SHARE_DIR="/usr/share/doc/nvidia-l4t-apt-source"

if [ ! -d "${DOC_SHARE_DIR}" ]; then
    mkdir -p "${DOC_SHARE_DIR}"
fi

cp -f copyright "${DOC_SHARE_DIR}/copyright"

chmod a+x postinst
./postinst

echo "Done setting apt source for Jetson!"
exit 0
