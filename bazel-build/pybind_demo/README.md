# pybind11 demo

## How to Run

```
bazel build //...
source setup.bash
bazel run //demos:mymath_demo
```

## Project Directories
- `cyber`: C++ source files
- `py3_ext`: Python Wrapper around C++ classes and functions in `cyber`
- `demos`: py3 binary demos show how to use generated python extensions.
