#! /usr/bin/env bash
# Usage: dev_start.sh dev-18.04-x86_64-20200421_1656
#        dev_start.sh local-dev-aarch64

TOP_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"
source "${TOP_DIR}/storydev.bashrc"

set -euo pipefail

REPO="storypku/storydev"
STORY_IMAGE=
STORY_CONTAINER=
TARGET=
ARCH=

function _usage() {
    info "Usage: ${0} docker-image-name"
    info "E.g. ${0} dev-x86_64-18.04-20200421_1656"
    info "     ${0} local-dev-aarch64"
    exit 1
}

function check_arguments() {
    if [[ $# -ne 1 ]]; then
        _usage
    fi
    local tag="$1"
    STORY_IMAGE="${REPO}:${tag}"

    IFS='-' read -ra __arr <<< "${tag}"
    IFS=' ' # restore

    if [[ ${#__arr[@]} -lt 3 ]]; then
        _usage
    fi
    local arch
    local target
    if [[ "${__arr[0]}" == "local" ]]; then
        target="${__arr[1]}"
        arch="${__arr[2]}"
    else
        arch="${__arr[1]}"
        target="${__arr[0]}"
    fi
    TARGET="${target}"
    ARCH="${arch}"
    STORY_CONTAINER="story_${TARGET}_${ARCH}"
}

function remove_container_if_exists() {
    local container="$1"
    # docker ps -a | awk -v pat="${container}" '$0~pat {print $1}'
    if docker ps -a --format "{{.Names}}" | grep -q "${container}"; then
        warning "Found existing container ${container}.  Stop it first."
        docker stop "${container}"
        docker rm "${container}"
    fi
}

function start_container() {
    local container_name="$1"
    local image_name="$2"
    local target="$3"

    local local_host="$(hostname)"
    local host_inside="in_${target}_docker"

    local uid="$(id -u)"
    local gid="$(id -g)"
    local group_name="$(id -g -n)"

    docker run -it -d \
        --privileged \
        --name "${container_name}" \
        -e DOCKER_USER="${USER}" \
        -e USER="${USER}" \
        -e DOCKER_USER_ID="${uid}" \
        -e DOCKER_GRP="${group_name}" \
        -e DOCKER_GRP_ID="${gid}" \
        --net host \
        -w /apollo \
        --add-host ${host_inside}:127.0.0.1 \
        --add-host ${local_host}:127.0.0.1 \
        --hostname "${host_inside}" \
        --shm-size 2G \
        --pid=host \
        -v /dev/null:/dev/raw1394 \
        "${image_name}" \
        /bin/bash
}

function post_process() {
    local container="$1"
    if [[ "${USER}" != "root" ]]; then
        docker exec -u root "${container}" \
            bash -c '/opt/apollo/scripts/docker_start_user.sh'
    fi
}

function main() {
    check_arguments "$@"
    local host_arch="$(uname -m)"

    if [[ "${ARCH}" != "${host_arch}" ]]; then
        info "Detected: Docker ${ARCH} container to run on ${host_arch} host."
        info "Please make sure the following command has been executed."
        info "   docker run --rm --privileged multiarch/qemu-user-static --reset -p yes"
    fi

    remove_container_if_exists "${STORY_CONTAINER}"
    start_container "${STORY_CONTAINER}" "${STORY_IMAGE}" "${TARGET}"
    post_process "${STORY_CONTAINER}"
    info "Please run the following command to enter into the newly started container: "
    info "    bash dev_into.sh"
}

main "$@"


