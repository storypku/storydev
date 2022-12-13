#! /usr/bin/env python3

import platform
import sys
from os.path import isfile


def hello(who):
    osname = platform.system()
    print("Hello world from {} on an ${} machine".format(who, osname))


if __name__ == "__main__":
    if len(sys.argv) >= 2:
        hello(sys.argv[1])
