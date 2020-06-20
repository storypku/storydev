# Sample VTK program using Bazel: Example 02

## PreReq

You are supposed to have finished example01.

## Improvement

Here we move all the VERSION related parts inside `third_party/vtk`, and

"init" VTK rules in `WORKSPACE` file as follows:

```
load("//third_party/vtk:workspace.bzl", vtk = "repo")

vtk()
```

We now don't have to re-run `path/to/myscript WORKSPACE.in > WORKSPACE` every
time we add a new dependency to `WORKSPACE`.

The good part of this approach is that we "hide" VTK version from `WORKSPACE`
file. As the saying goes, "Out of sight, Out of mind."

The hard-coded VTK version now lives inside the "third_party/vtk" directory,
a directory that didn't got updated regularly.

How can we "hide" VTK version completed, and instruct Bazel to figure out
which VTK version to use.

This is a problem what `example03` attempts to express.




