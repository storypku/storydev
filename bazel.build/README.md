# Bazel: Practical and expressive modern build system

## Introduction
[Bazel Documentation](https://docs.bazel.build/)


## Content

- [Build Bazel from Source](build-bazel-from-source.md)

- [WORKSPACE file for bazel-3.2.0-dist](README.md#workspace-file-for-bazel-320-dist)

## WORKSPACE file for bazel-3.2.0-dist

After downloading and extracting bazel-3.2.0-dist.zip from [Bazel 3.2.0-dist Download Link on Github](https://github.com/bazelbuild/bazel/releases/download/3.2.0/bazel-3.2.0-dist.zip):

```
unzip bazel-3.2.0-dist.zip -d bazel-3.2.0-dist
cd bazel-3.2.0-dist
mv WORKSPACE WORKSPACE.orig
cp path/to/this/bazel-3.2.0-dist.WORKSPACE WORKSPACE
```

