#!/usr/bin/env bash

BOLD='\033[1m'
RED='\033[0;31m'
GREEN='\033[32m'
WHITE='\033[34m'
YELLOW='\033[33m'
NO_COLOR='\033[0m'

function info() {
  (echo >&2 -e "[${WHITE}${BOLD}INFO${NO_COLOR}] $*")
}

function error() {
  (echo >&2 -e "[${RED}ERROR${NO_COLOR}] $*")
}

function warning() {
  (echo >&2 -e "${YELLOW}[WARNING] $*${NO_COLOR}")
}

function ok() {
  (echo >&2 -e "[${GREEN}${BOLD} OK ${NO_COLOR}] $*")
}

# We only accept predownloaded git tarballs with format
# "pkgname.git.53549ad.tgz" or "pkgname_version.git.53549ad.tgz"
function package_schema {
  local __link=$1
  local schema="http"

  if [[ "${__link##*.}" == "git" ]]; then
    schema="git"
    echo $schema
    return
  fi

  IFS='.' # dot(.) is set as delimiter

  local __pkgname=$2
  read -ra __arr <<< "$__pkgname" # Array of tokens separated by IFS
  if [[ ${#__arr[@]} -gt 3 ]] && [[ "${__arr[-3]}" == "git" ]] \
    && [[ ${#__arr[-2]} -eq 7 ]]; then
    schema="git"
  fi
  IFS=' ' # reset to default value after usage

  echo "$schema"
}

function create_so_symlink() {
  local mydir="$1"
  for mylib in $(find "${mydir}" -name "lib*.so.*" -type f); do
    mylib=$(basename "${mylib}")
    ver="${mylib##*.so.}"
    if [ -z "$ver" ]; then
      continue
    fi
    libX="${mylib%%.so*}"
    IFS='.' read -ra arr <<< "${ver}"
    IFS=" " # restore IFS
    ln -s "${mylib}" "${mydir}/${libX}.so.${arr[0]}"
    ln -s "${mylib}" "${mydir}/${libX}.so"
  done
}

RCFILES_DIR="/opt/apollo/rcfiles"
DEST_DIR_BASE="/opt/apollo/pkgs"
SYSROOT_DIR="/opt/apollo/sysroot"
ARCHIVE_DIR="/tmp/archive"

DOWNLOAD_LOG="/opt/apollo/build.log"

LOCAL_HTTP_ADDR="http://172.17.0.1:8388"

if [[ ! -d "${DEST_DIR_BASE}" ]]; then
  mkdir -p "${DEST_DIR_BASE}"
fi

if [[ ! -d "${SYSROOT_DIR}" ]]; then
  mkdir -p "${SYSROOT_DIR}"
fi

if [[ ! -f "${DOWNLOAD_LOG}" ]]; then
  echo "#Summary: Apollo Package Downloads" > "${DOWNLOAD_LOG}"
fi

function local_http_cached() {
  if /usr/bin/curl -sfI "${LOCAL_HTTP_ADDR}/$1"; then
    return
  fi
  false
}

function _checksum_check_pass() {
  local pkg="$1"
  local expected_cs="$2"
  local actual_cs=$(/usr/bin/sha256sum "${pkg}" | awk '{print $1}')
  if [[ "${actual_cs}" == "${expected_cs}" ]]; then
    true
  else
    warning "$(basename ${pkg}): checksum mismatch, ${expected_cs}" \
      "exected, got: ${actual_cs}"
    false
  fi
}

function pip3_install() {
  python3 -m pip install --no-cache-dir $@
}

# sha256sum was provided by coreutils
function download_if_not_cached {
  local pkg_name=$1
  local expected_cs=$2
  local url=$3
  local use_cache=0

  echo -e "${pkg_name}\t${expected_cs}\t${url}" >> "${DOWNLOAD_LOG}"

  if local_http_cached "${pkg_name}"; then
    use_cache=2
    local local_addr="${LOCAL_HTTP_ADDR}/${pkg_name}"
    info "Local http cache hit ${pkg_name}..."
    wget "${local_addr}" -O "${pkg_name}"
    if _checksum_check_pass "${pkg_name}" "${expected_cs}"; then
      ok "Successfully downloaded ${pkg_name} from ${LOCAL_HTTP_ADDR}," \
        "will use it."
      return
    else
      warning "Found ${pkg_name} in local http cache, but checksum mismatch."
      rm -f "${pkg_name}"
      use_cache=0
    fi
  fi # end http cache check

  if [[ -e "${ARCHIVE_DIR}/${pkg_name}" ]]; then
    if _checksum_check_pass "${ARCHIVE_DIR}/${pkg_name}" "${expected_cs}"; then
      info "package $pkg_name found in fscache, will use it."
      use_cache=1
    else
      warning "package ${pkg_name} found in fscache, but checksum mismatch."
    fi
  fi

  local my_schema
  my_schema=$(package_schema "$url" "$pkg_name")

  if [[ $use_cache -eq 0 ]]; then
    if [[ "$my_schema" == "http" ]]; then
      info "Start to download $pkg_name from ${url} ..."
      wget "$url" -O "$pkg_name"
      ok "Successfully downloaded $pkg_name"
    elif [[ "$my_schema" == "git" ]]; then
      info "Clone into git repo $url..."
      git clone --recurse-submodules --single-branch "$url"
      ok "Successfully cloned git repo: $url"
    else
      error "Unknown schema for package \"$pkg_name\", url=\"$url\""
    fi
  else
    info "Congrats, fs cache hit ${pkg_name}, schema ${my_schema}, will use it."
    if [ "$my_schema" = "http" ]; then
      # ln -s "$ARCHIVE_DIR/${pkg_name}" "$pkg_name"
      mv -f "${ARCHIVE_DIR}/${pkg_name}" "${pkg_name}"
    elif [ "$my_schema" = "git" ]; then
      tar xzf "$ARCHIVE_DIR/${pkg_name}"
    else
      error "Unknown schema for package \"$pkg_name\", url=\"$url\""
    fi
  fi
}
