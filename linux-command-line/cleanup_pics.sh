#! /usr/bin/env bash
# This script is expected to be under ${APOLLO_ROOT_DIR}/scripts
# It will remove any orphaned images not refered to by markdown documents
# Usage:
#   scripts/cleanup_pics.sh
set -e

TOP_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"

function find_images_under_dir() {
  local search_dir="$1"
  local -n _images="$2"
  readarray -t _images \
    < <(find "${search_dir}" -type f \
      -exec file --mime-type {} \+ |
      awk -F':' '{
                if ($2 ~/image\//)
                    print $1
                }')
}

function find_docs_under_dir() {
  local search_dir="$1"
  local -n _docs="$2"
  local max_depth="$3"
  if [[ -z "${max_depth}" || "${max_depth}" -eq 0 ]]; then
    max_depth=42 # answer to the ultimate question of life
  fi
  _docs="$(find "${search_dir}" -maxdepth "${max_depth}" \
    -type f -name "*.md")"
}

function _cleanup_orphaned_images_impl() {
  local -n _images="$1"
  local -n _docs="$2"
  for img in "${_images[@]}"; do
    local name="$(basename "${img}")"
    if ! grep -q "${name}" ${_docs}; then
      echo "Found orphaned image: ${img}"
      rm -f "${img}"
    fi
  done
}

function cleanup_orphaned_images() {
  local images_dir="$1"
  if [[ ! -d "${images_dir}" ]]; then
    echo "Non-existent image directory: ${images_dir} ignored."
    return 0
  fi

  local docs_dir="$2"
  if [[ -z "${docs_dir}" ]]; then
    docs_dir="${TOP_DIR}"
  fi

  if [[ ! -d "${docs_dir}" ]]; then
    echo "Non-existent document directory ${docs_dir} ignored."
    return 0
  fi

  declare -a images=()
  find_images_under_dir "${images_dir}" images

  local docs=
  if [[ "${docs_dir}" == "${TOP_DIR}" ]]; then
    docs="$(find "${TOP_DIR}" -path ${TOP_DIR}/.cache -prune -false \
      -o -name "*.md")"
  else
    find_docs_under_dir "${docs_dir}" docs
  fi
  _cleanup_orphaned_images_impl images docs 1
}

function main() {
  cleanup_orphaned_images "${TOP_DIR}/docs"
  for dir in ${TOP_DIR}/modules/*; do
    if [[ ! -d "${dir}" ]]; then
      continue
    fi
    cleanup_orphaned_images "${dir}/images" "${dir}"
  done
}

main "$@"
