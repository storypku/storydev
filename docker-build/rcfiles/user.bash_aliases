#!/usr/bin/env bash

export PS1="\[\e[31m\][\[\e[m\]\[\e[32m\]\u\[\e[m\]\[\e[33m\]@\[\e[m\]\[\e[35m\]\h\[\e[m\]:\[\e[36m\]\w\[\e[m\]\[\e[31m\]]\[\e[m\]\[\e[1;32m\]\\$\[\e[m\] "

export PATH="$PATH:/apollo/scripts"

for script in /etc/profile.d/*.sh ; do
    . "${script}"
done

ulimit -c unlimited

if [[ -e "/apollo/scripts/apollo_base.sh" ]]; then
    . /apollo/scripts/apollo_base.sh
fi

alias bb="bazel build --distdir=/apollo/.cache/distdir"
alias bt="bazel test  --distdir=/apollo/.cache/distdir"

function inc() {
    local _path="$1"
    if [[ -d "${_path}" ]]; then
        /bin/grep "#include" -r "${_path}" | awk -F':' '{print $2}' | sort -u
    elif [[ -f "${_path}" ]]; then
        /bin/grep "#include" -r "${_path}" | sort -u
    fi
}

function show_line() {
    if [[ -z "$1" ]]; then
        error "No file specified"
        return
    fi
    local sed_cmd
    sed_cmd="$(command -v sed)"
    if [[ -z "${sed_cmd}" ]]; then
        error "sed not found in PATH"
        return
    fi
    local filename_w_ln="$1"; shift;
    local fname="${filename_w_ln%:*}"
    local start_ln=1
    if [[ "${filename_w_ln}" =~ :.* ]]; then
        start_ln="${filename_w_ln##*:}"
    elif [[ -z "$1" ]]; then
        start_ln=1
    else
        start_ln="$1"; shift
    fi
    local line_cnt=9; # 10
    if [[ -n "$1" ]];  then
        line_cnt="$1"; shift
    fi
    # '10,33p' print line 10 to line 33
    ${sed_cmd} -n "${start_ln},+${line_cnt}p" "${fname}"
}

