#!/bin/sh
# shellcheck shell=sh

## Prevent multiple entries of my_bin_path in PATH
add_to_path() {
  if [ -z "$1" ]; then
    return
  fi
  my_bin_path="$1"
  if [ -n "${PATH##*${my_bin_path}}" ] && [ -n "${PATH##*${my_bin_path}:*}" ]; then
    export PATH=$PATH:${my_bin_path}
  fi
}
