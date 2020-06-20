# Sample VTK program using Bazel: Example 01

## VTK sample code in this demo

`src/dist_pt2line.cc` was was adapated from
https://vtk.org/Wiki/VTK/Examples/Cxx#Hello_World

```
Hello World
  ||
  \/
Simple Operations
   |
   |-> DistancePointToLine
```

https://lorensen.github.io/VTKExamples/site/Cxx/SimpleOperations/DistancePointToLine


## Step 1: Build with CMake

Build with CMake to determine vtk libraries in use.
```
mkdir build && cd build
cmake ..
make -j$(nproc)
```

## Step 2: Build with Bazel: First Attempt

```
bazel build //...
```

## Summary

The bazel approach in example1 shows how to use Bazel to build a simple VTK program.

## Disadvantage

The bad part of this approach is, you have to hardcode vtk headers path
(In this case, "/usr/include/vtk-7.1") in `WORKSPACE`.

Or, write a `WORKSPACE.in` template file, and then use handwritten script to
generate `WORKSPACE` from `WORKSPACE.in`.

Then, a natural question is: How can we "hide" VTK version in WORKSPACE file.

```
example01 ====> example02
```

Now we look into `example02`
