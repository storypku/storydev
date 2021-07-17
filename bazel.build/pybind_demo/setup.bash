#! /usr/bin/env bash
TOP_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"
export PYTHONPATH="${TOP_DIR}/bazel-bin/py3_ext"


