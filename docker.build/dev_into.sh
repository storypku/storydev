#!/usr/bin/env bash

###############################################################################
# Copyright 2017 The Apollo Authors. All Rights Reserved.
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

# Usage: dev_into.sh [TARGET [ARCH]]
#  E.g., dev_into.sh dev x86_64 # default
#        dev_into.sh cyber aarch64
#        dev_into.sh cyber  # cyber.x86_64
TARGET="dev"
ARCH="x86_64"

STORY_CONTAINER=

function parse_arguments() {
    if [[ $# -eq 1 ]]; then
        TARGET="$1"
    elif [[ $# -ge 2 ]]; then
        TARGET="$1"
        ARCH="$2"
    fi
    STORY_CONTAINER="story_${TARGET}_${ARCH}"
}

function dev_into_container() {
    xhost +local:root 1>/dev/null 2>&1

    USER_ID=$(id -u)

    docker exec \
        -u $USER \
        -e HISTFILE=/apollo/.dev_bash_hist \
        -it ${STORY_CONTAINER} \
        /bin/bash

    xhost -local:root 1>/dev/null 2>&1
}

function main() {
    parse_arguments "$@"
    dev_into_container
}

main "$@"
