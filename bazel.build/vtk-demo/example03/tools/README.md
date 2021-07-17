# Sample VTK program using Bazel: Example 03

## PreReq

You are supposed to have finished example01 & example02.

## Improvement

Here we removed all the VTK version related "hard-codes", and instruct Bazel
to auto configure VTK **version** & **headers** & **library path** for us.

We "configure" VTK rules in `WORKSPACE` as follows:

```
load("//third_party:vtk_configure.bzl", "vtk_configure")

vtk_configure(name = "local_config_vtk")
```

This is a technique we used when we configure CUDA/TensorRT support.
Refer to my [CUDA Support for Bazel](https://github.com/storypku/cuda-support-for-bazel)
project or [TensorFlow](https://github.com/tensorflow/tensorflow") for more.

## Summary
By far, we have successfully removed hard-coded VTK version in our project,
and instruct Bazel to configure which VTK version to use.

Although I can't enumerate all the cases in the current implementation,
it works fine for most use cases.

Btw, the difficulty comes from that VTK didn't support `pkg-config`. A better
Bazel implemention may be inspired by looking into [VTK Support in CMake](https://github.com/Kitware/VTK/tree/master/CMake)


