#!/usr/bin/env python3

import os
import re
import subprocess
import sys


class ConfigError(Exception):
    pass


def find_clang_version(clang_binary):
    if not os.path.exists(clang_binary):
        raise ConfigError("File-not-found: {}".format(clang_binary))
    command = [clang_binary, "--version"]
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode != 0:
        raise ConfigError(result.stderr.decode("utf-8").strip("\n"))
    for line in result.stdout.decode("utf-8").strip().split("\n"):
        match = re.match(r"clang version (\d+\.\d+\.\d+)", line)
        if match:
            return match.group(1)
    raise ConfigError("Unable to determine clang version")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.stderr.write("Usage: find_clang_version.py <path/to/bin/clang>\n")
        sys.exit(1)

    clang_binary = sys.argv[1]
    try:
        clang_version = find_clang_version(clang_binary)
        print(clang_version)
    except ConfigError as ex:
        sys.stderr.write(str(ex) + "\n")
        sys.exit(1)
