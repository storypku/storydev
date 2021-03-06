# Source Build Bazel: A Summary

## Official Docs First!

https://docs.bazel.build/versions/master/install-compile-source.html


## PreRequisites Install

On Ubuntu 18.04

```
sudo apt-get install build-essential openjdk-11-jdk python3 zip unzip
sudo ln -s /usr/bin/python3 /usr/local/bin/python
```

## Download Bazel Sources

Visit [Bazel Github Release Page](https://github.com/bazelbuild/bazel/releases),
and choose `bazel-x.y.z-dist.zip`.

For example, to build bazel 3.2.0,

```
wget https://github.com/bazelbuild/bazel/releases/download/3.2.0/bazel-3.2.0-dist.zip
unzip bazel-3.2.0-dist.zip -d bazel-3.2.0-dist
```

## Build Bazel using Bazel
### `//src:bazel-dev`

```
bazel build //src:bazel-dev
```

Generated bazel is located at `bazel-bin/src/bazel-dev`. It's advantage
is that you can remove the openjdk stuff after built:

```
sudo apt-get autoremove openjdk-11-jdk openjdk-11-jdk-headless openjdk-11-jre-headless
```

### `//src:bazel`

```
bazel build //src:bazel --compilation_mode=opt
```

Generated bazel is located at `bazel-bin/src/bazel`. Just like the above approach, we can
kick off the ladder once built.

## Build Bazel from Scratch

### Bootstrapping Bazel without Embedded JDK


```
env EXTRA_BAZEL_ARGS="--host_javabase=@local_jdk//:jdk" bash ./compile.sh
```

If resproducible build is needed, run the following

```
DATE_FMT="+%Y-%m-%d"
SOURCE_DATE_EPOCH="${SOURCE_DATE_EPOCH:-$(date +%s)}"
BUILD_DATE=$(date -u -d "@$SOURCE_DATE_EPOCH" "$DATE_FMT" 2>/dev/null || date -u -r "$SOURCE_DATE_EPOCH" "$DATE_FMT" 2>/dev/null || date -u "$DATE_FMT")
env SOURCE_DATE_EPOCH="${SOURCE_DATE_EPOCH}" EXTRA_BAZEL_ARGS="--host_javabase=@local_jdk//:jdk" bash ./compile.sh
```

See https://reproducible-builds.org/docs/source-date-epoch/ for more.

Excerpt from [Official Bazel Link Above](https://docs.bazel.build/versions/master/install-compile-source.html):

> The compiled output is placed into `output/bazel`. This is a self-contained
> Bazel binary, ** without an embedded JDK**. You can copy it anywhere or use
> it in-place. For convenience we recommend copying this binary to a directory
> that’s on your PATH (such as /usr/local/bin on Linux).

### Bootstrapping Bazel with Embedded JDK

Modify `compile.sh` as follows:

```
--- compile.sh.bak	2020-06-10 16:49:47.401787887 +0800
+++ compile.sh	2020-06-10 16:50:08.633539611 +0800
@@ -63,12 +63,12 @@
 log "Building output/bazel"
 # We set host and target platform directly because we are building for the local
 # host.
-bazel_build "src:bazel_nojdk${EXE_EXT}" \
+bazel_build "src:bazel${EXE_EXT}" \
   --action_env=PATH \
   --host_platform=@local_config_platform//:host \
   --platforms=@local_config_platform//:host \
   || fail "Could not build Bazel"
-bazel_bin_path="$(get_bazel_bin_path)/src/bazel_nojdk${EXE_EXT}"
+bazel_bin_path="$(get_bazel_bin_path)/src/bazel${EXE_EXT}"
 [ -e "$bazel_bin_path" ] \
   || fail "Could not find freshly built Bazel binary at '$bazel_bin_path'"
 cp -f "$bazel_bin_path" "output/bazel${EXE_EXT}" \
```

Then execute:

```
env EXTRA_BAZEL_ARGS="--host_javabase=@local_jdk//:jdk" bash ./compile.sh
```

If you have a working bazel by now, you can also run

```
env BAZEL=/opt/apollo/sysroot/bin/bazel bash compile.sh
```

to build `Bazel with Embedded JDK`.

