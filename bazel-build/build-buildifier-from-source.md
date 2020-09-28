# Build buildifier from Source

Since there is no arm64 buildifier release at
[Buildtools Release Page](https://github.com/bazelbuild/buildtools/releases)
, we have to build it from source.

## Pre-requisites

- bazel for arm64, available at [Bazel Releases](https://github.com/bazelbuild/bazel/releases)
  E.g., https://github.com/bazelbuild/bazel/releases/download/3.5.0/bazel-3.5.0-linux-arm64

## Steps to build buildifier

```
git clone  https://github.com/bazelbuild/buildtools.git buildtools.git
cd buildtools.git
git tag
git checkout 3.5.0
bazel build --config=release buildifier
bazel build --config=release buildozer
cp bazel-bin/buildozer/linux_arm64_stripped/buildifier path/to/my/bin
cp bazel-bin/buildozer/linux_arm64_stripped/buildozer path/to/my/bin
```



