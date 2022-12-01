#!/bin/bash
set -euo pipefail

function main() {
  arch="$(uname -m)"
  libm_so_path="/lib/${arch}-linux-gnu/libm.so.6"
  if [[ ! -f "${libm_so_path}" ]]; then
    echo >&2 "[Error]: ${libm_so_path} doesn't exist."
    return 1
  fi

  readarray -t versions < <(strings "${libm_so_path}" | grep -e "GLIBC_[0-9]\." | sort -rV)
  if [[ "${#versions[@]}" -eq 0 ]]; then
    echo >&2 "[Error] Unable to figure out GLIBC versions in ${libm_so_path}"
    return 1
  fi

  version="${versions[0]}"
  echo "${version##GLIBC_}"
}

main "$@"
