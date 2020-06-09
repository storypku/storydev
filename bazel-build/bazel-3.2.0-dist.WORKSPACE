workspace(name = "io_bazel")

load("//tools/build_defs/repo:http.bzl", "http_archive", "http_file")

# These can be used as values for the patch_cmds and patch_cmds_win attributes
# of http_archive, in order to export the WORKSPACE file from the BUILD or
# BUILD.bazel file. This is useful for cases like //src:test_repos, where we
# have to be able to trigger a fetch of a repo by depending on it, but we don't
# actually want to build anything (so we can't depend on a target inside that
# repo).
EXPORT_WORKSPACE_IN_BUILD_FILE = [
    "test -f BUILD && chmod u+w BUILD || true",
    "echo >> BUILD",
    "echo 'exports_files([\"WORKSPACE\"], visibility = [\"//visibility:public\"])' >> BUILD",
]

EXPORT_WORKSPACE_IN_BUILD_BAZEL_FILE = [
    "test -f BUILD.bazel && chmod u+w BUILD.bazel || true",
    "echo >> BUILD.bazel",
    "echo 'exports_files([\"WORKSPACE\"], visibility = [\"//visibility:public\"])' >> BUILD.bazel",
]

EXPORT_WORKSPACE_IN_BUILD_FILE_WIN = [
    "Add-Content -Path BUILD -Value \"`nexports_files([`\"WORKSPACE`\"], visibility = [`\"//visibility:public`\"])`n\" -Force",
]

EXPORT_WORKSPACE_IN_BUILD_BAZEL_FILE_WIN = [
    "Add-Content -Path BUILD.bazel -Value \"`nexports_files([`\"WORKSPACE`\"], visibility = [`\"//visibility:public`\"])`n\" -Force",
]

# Protobuf expects an //external:python_headers label which would contain the
# Python headers if fast Python protos is enabled. Since we are not using fast
# Python protos, bind python_headers to a dummy target.
bind(
    name = "python_headers",
    actual = "//:dummy",
)

# Protobuf code generation for GRPC requires three external labels:
# //external:grpc-java_plugin
# //external:grpc-jar
# //external:guava
bind(
    name = "grpc-java-plugin",
    actual = "//third_party/grpc:grpc-java-plugin",
)

bind(
    name = "grpc-jar",
    actual = "//third_party/grpc:grpc-jar",
)

bind(
    name = "guava",
    actual = "//third_party:guava",
)

http_archive(
    name = "bazel_j2objc",
    # Computed using "shasum -a 256 j2objc-2.5.zip"
    sha256 = "8d3403b5b7db57e347c943d214577f6879e5b175c2b59b7e075c0b6453330e9b",
    strip_prefix = "j2objc-2.5",
    urls = [
        "https://mirror.bazel.build/github.com/google/j2objc/releases/download/2.5/j2objc-2.5.zip",
        "https://github.com/google/j2objc/releases/download/2.5/j2objc-2.5.zip",
    ],
)

# For src/test/shell/bazel:test_srcs
load("//src/test/shell/bazel:list_source_repository.bzl", "list_source_repository")

list_source_repository(name = "local_bazel_source_list")

# To run the Android integration tests in //src/test/shell/bazel/android:all or
# build the Android sample app in //examples/android/java/bazel:hello_world
#
#   1. Install an Android SDK and NDK from https://developer.android.com
#   2. Set the $ANDROID_HOME and $ANDROID_NDK_HOME environment variables
#   3. Uncomment the two lines below
#
# android_sdk_repository(name = "androidsdk")
# android_ndk_repository(name = "androidndk")

# In order to run //src/test/shell/bazel:maven_skylark_test, follow the
# instructions above for the Android integration tests and uncomment the
# following lines:
# load("//tools/build_defs/repo:maven_rules.bzl", "maven_dependency_plugin")
# maven_dependency_plugin()

# This allows rules written in Starlark to locate apple build tools.
bind(
    name = "xcrunwrapper",
    actual = "@bazel_tools//tools/objc:xcrunwrapper",
)

http_archive(
    name = "com_google_protobuf",
    patch_args = ["-p1"],
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_FILE_WIN,
    patches = ["//third_party/protobuf:3.11.3.patch"],
    sha256 = "cf754718b0aa945b00550ed7962ddc167167bd922b842199eeb6505e6f344852",
    strip_prefix = "protobuf-3.11.3",
    urls = [
        "https://mirror.bazel.build/github.com/protocolbuffers/protobuf/archive/v3.11.3.tar.gz",
        "https://github.com/protocolbuffers/protobuf/archive/v3.11.3.tar.gz",
    ],
)

# This is a mock version of bazelbuild/rules_python that contains only
# @rules_python//python:defs.bzl. It is used by protobuf.
# TODO(#9029): We could potentially replace this with the real @rules_python.
new_local_repository(
    name = "rules_python",
    build_file = "//third_party/rules_python:BUILD",
    path = "./third_party/rules_python",
    workspace_file = "//third_party/rules_python:rules_python.WORKSPACE",
)

local_repository(
    name = "googleapis",
    path = "./third_party/googleapis/",
)

local_repository(
    name = "remoteapis",
    path = "./third_party/remoteapis/",
)

http_archive(
    name = "desugar_jdk_libs",
    # Commit e0b0291b2c51fbe5a7cfa14473a1ae850f94f021 of 2018-12-4
    # Computed using "shasum -a 256 <zip>"
    sha256 = "fe2e04f91ce8c59d49d91b8102edc6627c6fa2906c1b0e7346f01419ec4f419d",
    strip_prefix = "desugar_jdk_libs-e0b0291b2c51fbe5a7cfa14473a1ae850f94f021",
    urls = [
        "https://mirror.bazel.build/github.com/google/desugar_jdk_libs/archive/e0b0291b2c51fbe5a7cfa14473a1ae850f94f021.zip",
        "https://github.com/google/desugar_jdk_libs/archive/e0b0291b2c51fbe5a7cfa14473a1ae850f94f021.zip",
    ],
)

load("//:distdir.bzl", "distdir_tar")

distdir_tar(
    name = "additional_distfiles",
    # Keep in sync with the archives fetched as part of building bazel.
    archives = [
        "e0b0291b2c51fbe5a7cfa14473a1ae850f94f021.zip",
        "java_tools_javac11_linux-v8.0.zip",
        "java_tools_javac11_windows-v8.0.zip",
        "java_tools_javac11_darwin-v8.0.zip",
        "coverage_output_generator-v2.1.zip",
        "c7bbde2950769aac9a99364b0926230060a3ce04.tar.gz",
        "1.25.0.zip",
        "rules_nodejs-1.3.0.tar.gz",
        "android_tools_pkg-0.16.0.tar.gz",
        # bazelbuild/bazel-skylib
        "2d4c9528e0f453b5950eeaeac11d8d09f5a504d4.tar.gz",
        # bazelbuild/platforms
        "46993efdd33b73649796c5fc5c9efb193ae19d51.zip",
        # bazelbuild/rules_java
        "7cf3cefd652008d0a64a419c34c13bdca6c8f178.zip",
        # bazelbuild/rules_cc
        "8bd6cd75d03c01bb82561a96d9c1f9f7157b13d0.zip",
        # bazelbuild/bazel-toolchains
        "3.2.0.tar.gz",
        # bazelbuild/rules_pkg
        "rules_pkg-0.2.4.tar.gz",
        # bazelbuild/rules_proto
        "97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
        # protocolbuffers/protobuf
        "v3.11.3.tar.gz",
    ],
    dirname = "derived/distdir",
    sha256 = {
        "e0b0291b2c51fbe5a7cfa14473a1ae850f94f021.zip": "fe2e04f91ce8c59d49d91b8102edc6627c6fa2906c1b0e7346f01419ec4f419d",
        "java_tools_javac11_linux-v8.0.zip": "c24aef916cc5a8e9f6d53db1f93c54fe5790a58996a1099592e1dfe992acc81e",
        "java_tools_javac11_windows-v8.0.zip": "444c391977e50af4e10549a28d021069d2ca7745a0e7b9b968a7b153fe3ea430",
        "java_tools_javac11_darwin-v8.0.zip": "e0291e8956ac295143da4a673ca50727f7376665ee82b649a4ee810b64ff76c1",
        "coverage_output_generator-v2.1.zip": "96ac6bc9b9fbc67b532bcae562da1642409791e6a4b8e522f04946ee5cc3ff8e",
        "c7bbde2950769aac9a99364b0926230060a3ce04.tar.gz": "e6a76586b264f30679688f65f7e71ac112d1446681010a13bf22d9ca071f34b7",
        # rules_sass
        "1.25.0.zip": "c78be58f5e0a29a04686b628cf54faaee0094322ae0ac99da5a8a8afca59a647",
        # rules_nodejs
        "rules_nodejs-1.3.0.tar.gz": "b6670f9f43faa66e3009488bbd909bc7bc46a5a9661a33f6bc578068d1837f37",
        "android_tools_pkg-0.16.0.tar.gz": "e2cbd43a9d23aa32197c29d689a7e017f205acb07053f5dd584f500a1a9d4361",
        # bazelbuild/bazel-skylib
        "2d4c9528e0f453b5950eeaeac11d8d09f5a504d4.tar.gz": "c00ceec469dbcf7929972e3c79f20c14033824538038a554952f5c31d8832f96",
        # bazelbuild/platforms
        "46993efdd33b73649796c5fc5c9efb193ae19d51.zip": "66184688debeeefcc2a16a2f80b03f514deac8346fe888fb7e691a52c023dd88",
        # bazelbuild/rules_java
        "7cf3cefd652008d0a64a419c34c13bdca6c8f178.zip": "bc81f1ba47ef5cc68ad32225c3d0e70b8c6f6077663835438da8d5733f917598",
        # bazelbuild/rules_cc
        "8bd6cd75d03c01bb82561a96d9c1f9f7157b13d0.zip": "1d4dbbd1e1e9b57d40bb0ade51c9e882da7658d5bfbf22bbd15b68e7879d761f",
        # bazelbuild/bazel-toolchains
        "3.2.0.tar.gz": "db48eed61552e25d36fe051a65d2a329cc0fb08442627e8f13960c5ab087a44e",
        # bazelbuild/rules_pkg
        "rules_pkg-0.2.4.tar.gz": "4ba8f4ab0ff85f2484287ab06c0d871dcb31cc54d439457d28fd4ae14b18450a",
        # bazelbuild/rules_proto
        "97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz": "602e7161d9195e50246177e7c55b2f39950a9cf7366f74ed5f22fd45750cd208",
        # protocolbuffers/protobuf
        "v3.11.3.tar.gz": "cf754718b0aa945b00550ed7962ddc167167bd922b842199eeb6505e6f344852",
    },
    urls = {
        "e0b0291b2c51fbe5a7cfa14473a1ae850f94f021.zip": [
            "https://mirror.bazel.build/github.com/google/desugar_jdk_libs/archive/e0b0291b2c51fbe5a7cfa14473a1ae850f94f021.zip",
            "https://github.com/google/desugar_jdk_libs/archive/e0b0291b2c51fbe5a7cfa14473a1ae850f94f021.zip",
        ],
        "java_tools_javac11_linux-v8.0.zip": [
            "https://mirror.bazel.build/bazel_java_tools/releases/javac11/v8.0/java_tools_javac11_linux-v8.0.zip",
        ],
        "java_tools_javac11_windows-v8.0.zip": [
            "https://mirror.bazel.build/bazel_java_tools/releases/javac11/v8.0/java_tools_javac11_windows-v8.0.zip",
        ],
        "java_tools_javac11_darwin-v8.0.zip": [
            "https://mirror.bazel.build/bazel_java_tools/releases/javac11/v8.0/java_tools_javac11_darwin-v8.0.zip",
        ],
        "coverage_output_generator-v2.1.zip": [
            "https://mirror.bazel.build/bazel_coverage_output_generator/releases/coverage_output_generator-v2.1.zip",
        ],
        "c7bbde2950769aac9a99364b0926230060a3ce04.tar.gz": [
            "https://mirror.bazel.build/github.com/bazelbuild/skydoc/archive/c7bbde2950769aac9a99364b0926230060a3ce04.tar.gz",
            "https://github.com/bazelbuild/skydoc/archive/c7bbde2950769aac9a99364b0926230060a3ce04.tar.gz",
        ],
        "1.25.0.zip": [
            "https://mirror.bazel.build/github.com/bazelbuild/rules_sass/archive/1.25.0.zip",
            "https://github.com/bazelbuild/rules_sass/archive/1.25.0.zip",
        ],
        "rules_nodejs-1.3.0.tar.gz": [
            "https://mirror.bazel.build/github.com/bazelbuild/rules_nodejs/releases/download/1.3.0/rules_nodejs-1.3.0.tar.gz",
            "https://github.com/bazelbuild/rules_nodejs/releases/download/1.3.0/rules_nodejs-1.3.0.tar.gz",
        ],
        "android_tools_pkg-0.16.0.tar.gz": [
            "https://mirror.bazel.build/bazel_android_tools/android_tools_pkg-0.16.0.tar.gz",
        ],
        # bazelbuild/bazel-skylib
        "2d4c9528e0f453b5950eeaeac11d8d09f5a504d4.tar.gz": [
            "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/archive/2d4c9528e0f453b5950eeaeac11d8d09f5a504d4.tar.gz",
            "https://github.com/bazelbuild/bazel-skylib/archive/2d4c9528e0f453b5950eeaeac11d8d09f5a504d4.tar.gz",
        ],
        # bazelbuild/platforms
        "46993efdd33b73649796c5fc5c9efb193ae19d51.zip": [
            "https://mirror.bazel.build/github.com/bazelbuild/platforms/archive/46993efdd33b73649796c5fc5c9efb193ae19d51.zip",
            "https://github.com/bazelbuild/platforms/archive/46993efdd33b73649796c5fc5c9efb193ae19d51.zip",
        ],
        # bazelbuild/rules_java
        "7cf3cefd652008d0a64a419c34c13bdca6c8f178.zip": [
            "https://mirror.bazel.build/github.com/bazelbuild/rules_java/archive/7cf3cefd652008d0a64a419c34c13bdca6c8f178.zip",
            "https://github.com/bazelbuild/rules_java/archive/7cf3cefd652008d0a64a419c34c13bdca6c8f178.zip",
        ],
        # bazelbuild/rules_cc
        "8bd6cd75d03c01bb82561a96d9c1f9f7157b13d0.zip": [
            "https://mirror.bazel.build/github.com/bazelbuild/rules_cc/archive/8bd6cd75d03c01bb82561a96d9c1f9f7157b13d0.zip",
            "https://github.com/bazelbuild/rules_cc/archive/8bd6cd75d03c01bb82561a96d9c1f9f7157b13d0.zip",
        ],
        # bazelbuild/bazel-toolchains
        "3.2.0.tar.gz": [
            "https://mirror.bazel.build/github.com/bazelbuild/bazel-toolchains/archive/3.2.0.tar.gz",
            "https://github.com/bazelbuild/bazel-toolchains/releases/download/3.2.0/bazel-toolchains-3.2.0.tar.gz",
        ],
        # bazelbuild/rules_pkg
        "rules_pkg-0.2.4.tar.gz": [
            "https://mirror.bazel.build/github.com/bazelbuild/rules_pkg/releases/download/0.2.4/rules_pkg-0.2.4.tar.gz",
            "https://github.com/bazelbuild/rules_pkg/releases/download/0.2.4/rules_pkg-0.2.4.tar.gz",
        ],
        # bazelbuild/rules_proto
        "97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz": [
            "https://mirror.bazel.build/github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
            "https://github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
        ],
        # protocolbuffers/protobuf
        "v3.11.3.tar.gz": [
            "https://mirror.bazel.build/github.com/protocolbuffers/protobuf/archive/v3.11.3.tar.gz",
            "https://github.com/protocolbuffers/protobuf/archive/v3.11.3.tar.gz",
        ],
    },
)

# OpenJDK distributions used to create a version of Bazel bundled with the OpenJDK.
http_file(
    name = "openjdk_linux",
    downloaded_file_path = "zulu-linux.tar.gz",
    sha256 = "65bfe4e0ffa74a680ee4410db46b17e30cd9397b664a92a886599fe1f3530969",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu11.37.17-ca-jdk11.0.6/zulu11.37.17-ca-jdk11.0.6-linux_x64-linux_x64-allmodules-b23d4e05466f2aa1fdcd72d3d3a8e962206b64bf-1581689070.tar.gz"],
)

http_file(
    name = "openjdk_linux_vanilla",
    downloaded_file_path = "zulu-linux-vanilla.tar.gz",
    sha256 = "360626cc19063bc411bfed2914301b908a8f77a7919aaea007a977fa8fb3cde1",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu11.37.17-ca-jdk11.0.6/zulu11.37.17-ca-jdk11.0.6-linux_x64.tar.gz"],
)

http_file(
    name = "openjdk_linux_minimal",
    downloaded_file_path = "zulu-linux-minimal.tar.gz",
    sha256 = "91f7d52f695c681d4e21499b4319d548aadef249a6b3053e306308992e1e29ae",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu11.37.17-ca-jdk11.0.6/zulu11.37.17-ca-jdk11.0.6-linux_x64-minimal-b23d4e05466f2aa1fdcd72d3d3a8e962206b64bf-1581689068.tar.gz"],
)

http_file(
    name = "openjdk_linux_aarch64",
    downloaded_file_path = "zulu-linux-aarch64.tar.gz",
    sha256 = "6b245793087300db3ee82ab0d165614f193a73a60f2f011e347756c1e6ca5bac",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu11.37.48-ca-jdk11.0.6/zulu11.37.48-ca-jdk11.0.6-linux_aarch64-allmodules-b23d4e05466f2aa1fdcd72d3d3a8e962206b64bf-1581690750.tar.gz"],
)

http_file(
    name = "openjdk_linux_aarch64_vanilla",
    downloaded_file_path = "zulu-linux-aarch64-vanilla.tar.gz",
    sha256 = "a452f1b9682d9f83c1c14e54d1446e1c51b5173a3a05dcb013d380f9508562e4",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu11.37.48-ca-jdk11.0.6/zulu11.37.48-ca-jdk11.0.6-linux_aarch64.tar.gz"],
)

http_file(
    name = "openjdk_linux_aarch64_minimal",
    downloaded_file_path = "zulu-linux-aarch64-minimal.tar.gz",
    sha256 = "06f6520a877704c77614bcfc4f846cc7cbcbf5eaad149bf7f19f4f16e285c9de",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu11.37.48-ca-jdk11.0.6/zulu11.37.48-ca-jdk11.0.6-linux_aarch64-minimal-b23d4e05466f2aa1fdcd72d3d3a8e962206b64bf-1581690750.tar.gz"],
)

http_file(
    name = "openjdk_macos",
    downloaded_file_path = "zulu-macos.tar.gz",
    sha256 = "8e283cfd23c7555be8e17295ed76eb8f00324c88ab904b8de37bbe08f90e569b",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu11.37.17-ca-jdk11.0.6/zulu11.37.17-ca-jdk11.0.6-macosx_x64-allmodules-b23d4e05466f2aa1fdcd72d3d3a8e962206b64bf-1581689066.tar.gz"],
)

http_file(
    name = "openjdk_macos_vanilla",
    downloaded_file_path = "zulu-macos-vanilla.tar.gz",
    sha256 = "e1fe56769f32e2aaac95e0a8f86b5a323da5af3a3b4bba73f3086391a6cc056f",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu11.37.17-ca-jdk11.0.6/zulu11.37.17-ca-jdk11.0.6-macosx_x64.tar.gz"],
)

http_file(
    name = "openjdk_macos_minimal",
    downloaded_file_path = "zulu-macos-minimal.tar.gz",
    sha256 = "1bacb1c07035d4066d79f0b65b4ea0ebd1954f3662bdfe3618da382ac8fd23a6",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu11.37.17-ca-jdk11.0.6/zulu11.37.17-ca-jdk11.0.6-macosx_x64-minimal-b23d4e05466f2aa1fdcd72d3d3a8e962206b64bf-1581689063.tar.gz"],
)

http_file(
    name = "openjdk_win",
    downloaded_file_path = "zulu-win.zip",
    sha256 = "8e1604b3a27dcf639bc6d1a73103f1211848139e4cceb081d0a74a99e1e6f995",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu11.37.17-ca-jdk11.0.6/zulu11.37.17-ca-jdk11.0.6-win_x64-allmodules-b23d4e05466f2aa1fdcd72d3d3a8e962206b64bf-1581689080.zip"],
)

http_file(
    name = "openjdk_win_vanilla",
    downloaded_file_path = "zulu-win-vanilla.zip",
    sha256 = "a9695617b8374bfa171f166951214965b1d1d08f43218db9a2a780b71c665c18",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu11.37.17-ca-jdk11.0.6/zulu11.37.17-ca-jdk11.0.6-win_x64.zip"],
)

http_file(
    name = "openjdk_win_minimal",
    downloaded_file_path = "zulu-win-minimal.zip",
    sha256 = "b90a713c9c2d9ea23cad44d2c2dfcc9af22faba9bde55dedc1c3bb9f556ac1ae",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu11.37.17-ca-jdk11.0.6/zulu11.37.17-ca-jdk11.0.6-win_x64-minimal-b23d4e05466f2aa1fdcd72d3d3a8e962206b64bf-1581689080.zip"],
)

http_archive(
    name = "bazel_toolchains",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_FILE_WIN,
    sha256 = "db48eed61552e25d36fe051a65d2a329cc0fb08442627e8f13960c5ab087a44e",
    strip_prefix = "bazel-toolchains-3.2.0",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-toolchains/archive/3.2.0.tar.gz",
        "https://github.com/bazelbuild/bazel-toolchains/releases/download/3.2.0/bazel-toolchains-3.2.0.tar.gz",
    ],
)

load("@bazel_toolchains//rules:rbe_repo.bzl", "rbe_autoconfig")

rbe_autoconfig(
    name = "rbe_ubuntu1804_java11",
    detect_java_home = True,
    registry = "gcr.io",
    repository = "bazel-public/ubuntu1804-bazel-java11",
    tag = "latest",
)

rbe_autoconfig(
    name = "rbe_ubuntu1604_java8",
    detect_java_home = True,
    registry = "gcr.io",
    repository = "bazel-public/ubuntu1604-bazel-java8",
    tag = "latest",
)

# Creates toolchain configuration for remote execution with BuildKite CI
# for rbe_ubuntu1604.
# To run the tests with RBE on BuildKite CI uncomment the two lines below
# load("@bazel_toolchains//rules:rbe_repo.bzl", "rbe_autoconfig")
# rbe_autoconfig(name = "buildkite_config")

http_archive(
    name = "com_google_googletest",
    sha256 = "9dc9157a9a1551ec7a7e43daea9a694a0bb5fb8bec81235d8a1e6ef64c716dcb",
    strip_prefix = "googletest-release-1.10.0",
    urls = [
        "https://mirror.bazel.build/github.com/google/googletest/archive/release-1.10.0.tar.gz",
        "https://github.com/google/googletest/archive/release-1.10.0.tar.gz",
    ],
)

http_archive(
    name = "bazel_skylib",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_FILE_WIN,
    # Commit 2d4c9528e0f453b5950eeaeac11d8d09f5a504d4 of 2020-02-06
    sha256 = "c00ceec469dbcf7929972e3c79f20c14033824538038a554952f5c31d8832f96",
    strip_prefix = "bazel-skylib-2d4c9528e0f453b5950eeaeac11d8d09f5a504d4",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/archive/2d4c9528e0f453b5950eeaeac11d8d09f5a504d4.tar.gz",
        "https://github.com/bazelbuild/bazel-skylib/archive/2d4c9528e0f453b5950eeaeac11d8d09f5a504d4.tar.gz",
    ],
)

# Note that skydoc depends on being called io_bazel_skydoc (and not just skydoc)
# to work without being patched, as it hard-codes this name in its sources.
http_archive(
    name = "io_bazel_skydoc",
    sha256 = "e6a76586b264f30679688f65f7e71ac112d1446681010a13bf22d9ca071f34b7",
    strip_prefix = "skydoc-c7bbde2950769aac9a99364b0926230060a3ce04",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/skydoc/archive/c7bbde2950769aac9a99364b0926230060a3ce04.tar.gz",
        "https://github.com/bazelbuild/skydoc/archive/c7bbde2950769aac9a99364b0926230060a3ce04.tar.gz",
    ],
)

http_archive(
    name = "rules_cc",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_FILE_WIN,
    sha256 = "1d4dbbd1e1e9b57d40bb0ade51c9e882da7658d5bfbf22bbd15b68e7879d761f",
    strip_prefix = "rules_cc-8bd6cd75d03c01bb82561a96d9c1f9f7157b13d0",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_cc/archive/8bd6cd75d03c01bb82561a96d9c1f9f7157b13d0.zip",
        "https://github.com/bazelbuild/rules_cc/archive/8bd6cd75d03c01bb82561a96d9c1f9f7157b13d0.zip",
    ],
)

http_archive(
    name = "rules_java",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_FILE_WIN,
    sha256 = "bc81f1ba47ef5cc68ad32225c3d0e70b8c6f6077663835438da8d5733f917598",
    strip_prefix = "rules_java-7cf3cefd652008d0a64a419c34c13bdca6c8f178",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_java/archive/7cf3cefd652008d0a64a419c34c13bdca6c8f178.zip",
        "https://github.com/bazelbuild/rules_java/archive/7cf3cefd652008d0a64a419c34c13bdca6c8f178.zip",
    ],
)

http_archive(
    name = "rules_proto",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_BAZEL_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_BAZEL_FILE_WIN,
    sha256 = "602e7161d9195e50246177e7c55b2f39950a9cf7366f74ed5f22fd45750cd208",
    strip_prefix = "rules_proto-97d8af4dc474595af3900dd85cb3a29ad28cc313",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
        "https://github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
    ],
)

# For testing, have an distdir_tar with all the archives implicit in every
# WORKSPACE, to that they don't have to be refetched for every test
# calling `bazel sync`.
distdir_tar(
    name = "test_WORKSPACE_files",
    archives = [
        "java_tools_javac11_linux-v8.0.zip",
        "java_tools_javac11_windows-v8.0.zip",
        "java_tools_javac11_darwin-v8.0.zip",
        "coverage_output_generator-v2.1.zip",
        "zulu11.37.17-ca-jdk11.0.6-linux_x64.tar.gz",
        "zulu11.37.48-ca-jdk11.0.6-linux_aarch64.tar.gz",
        "zulu11.37.17-ca-jdk11.0.6-macosx_x64.tar.gz",
        "zulu11.37.17-ca-jdk11.0.6-win_x64.zip",
        "android_tools_pkg-0.16.0.tar.gz",
        # bazelbuild/bazel-skylib
        "2d4c9528e0f453b5950eeaeac11d8d09f5a504d4.tar.gz",
        # bazelbuild/platforms
        "46993efdd33b73649796c5fc5c9efb193ae19d51.zip",
        # bazelbuild/rules_java
        "7cf3cefd652008d0a64a419c34c13bdca6c8f178.zip",
        # bazelbuild/rules_cc
        "8bd6cd75d03c01bb82561a96d9c1f9f7157b13d0.zip",
        # bazelbuild/rules_proto
        "97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
        # protocolbuffers/protobuf
        "v3.11.3.tar.gz",
    ],
    dirname = "test_WORKSPACE/distdir",
    sha256 = {
        "java_tools_javac11_linux-v8.0.zip": "c24aef916cc5a8e9f6d53db1f93c54fe5790a58996a1099592e1dfe992acc81e",
        "java_tools_javac11_windows-v8.0.zip": "444c391977e50af4e10549a28d021069d2ca7745a0e7b9b968a7b153fe3ea430",
        "java_tools_javac11_darwin-v8.0.zip": "e0291e8956ac295143da4a673ca50727f7376665ee82b649a4ee810b64ff76c1",
        "coverage_output_generator-v2.1.zip": "96ac6bc9b9fbc67b532bcae562da1642409791e6a4b8e522f04946ee5cc3ff8e",
        "zulu11.37.17-ca-jdk11.0.6-linux_x64.tar.gz": "360626cc19063bc411bfed2914301b908a8f77a7919aaea007a977fa8fb3cde1",
        "zulu11.37.48-ca-jdk11.0.6-linux_aarch64.tar.gz": "a452f1b9682d9f83c1c14e54d1446e1c51b5173a3a05dcb013d380f9508562e4",
        "zulu11.37.17-ca-jdk11.0.6-macosx_x64.tar.gz": "e1fe56769f32e2aaac95e0a8f86b5a323da5af3a3b4bba73f3086391a6cc056f",
        "zulu11.37.17-ca-jdk11.0.6-win_x64.zip": "a9695617b8374bfa171f166951214965b1d1d08f43218db9a2a780b71c665c18",
        "android_tools_pkg-0.16.0.tar.gz": "e2cbd43a9d23aa32197c29d689a7e017f205acb07053f5dd584f500a1a9d4361",
        # bazelbuild/bazel-skylib
        "2d4c9528e0f453b5950eeaeac11d8d09f5a504d4.tar.gz": "c00ceec469dbcf7929972e3c79f20c14033824538038a554952f5c31d8832f96",
        # bazelbuild/platforms
        "46993efdd33b73649796c5fc5c9efb193ae19d51.zip": "66184688debeeefcc2a16a2f80b03f514deac8346fe888fb7e691a52c023dd88",
        # bazelbuild/rules_java
        "7cf3cefd652008d0a64a419c34c13bdca6c8f178.zip": "bc81f1ba47ef5cc68ad32225c3d0e70b8c6f6077663835438da8d5733f917598",
        # bazelbuild/rules_cc
        "8bd6cd75d03c01bb82561a96d9c1f9f7157b13d0.zip": "1d4dbbd1e1e9b57d40bb0ade51c9e882da7658d5bfbf22bbd15b68e7879d761f",
        # bazelbuild/rules_proto
        "97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz": "602e7161d9195e50246177e7c55b2f39950a9cf7366f74ed5f22fd45750cd208",
        # protocolbuffers/protobuf
        "v3.11.3.tar.gz": "cf754718b0aa945b00550ed7962ddc167167bd922b842199eeb6505e6f344852",
    },
    urls = {
        "java_tools_javac11_linux-v8.0.zip": ["https://mirror.bazel.build/bazel_java_tools/releases/javac11/v8.0/java_tools_javac11_linux-v8.0.zip"],
        "java_tools_javac11_windows-v8.0.zip": ["https://mirror.bazel.build/bazel_java_tools/releases/javac11/v8.0/java_tools_javac11_windows-v8.0.zip"],
        "java_tools_javac11_darwin-v8.0.zip": ["https://mirror.bazel.build/bazel_java_tools/releases/javac11/v8.0/java_tools_javac11_darwin-v8.0.zip"],
        "coverage_output_generator-v2.1.zip": ["https://mirror.bazel.build/bazel_coverage_output_generator/releases/coverage_output_generator-v2.1.zip"],
        "zulu11.37.17-ca-jdk11.0.6-linux_x64.tar.gz": ["https://mirror.bazel.build/openjdk/azul-zulu11.37.17-ca-jdk11.0.6/zulu11.37.17-ca-jdk11.0.6-linux_x64.tar.gz"],
        "zulu11.37.48-ca-jdk11.0.6-linux_aarch64.tar.gz": ["https://mirror.bazel.build/openjdk/azul-zulu11.37.48-ca-jdk11.0.6/zulu11.37.48-ca-jdk11.0.6-linux_aarch64.tar.gz"],
        "zulu11.37.17-ca-jdk11.0.6-macosx_x64.tar.gz": ["https://mirror.bazel.build/openjdk/azul-zulu11.37.17-ca-jdk11.0.6/zulu11.37.17-ca-jdk11.0.6-macosx_x64.tar.gz"],
        "zulu11.37.17-ca-jdk11.0.6-win_x64.zip": ["https://mirror.bazel.build/openjdk/azul-zulu11.37.17-ca-jdk11.0.6/zulu11.37.17-ca-jdk11.0.6-win_x64.zip"],
        "android_tools_pkg-0.16.0.tar.gz": [
            "https://mirror.bazel.build/bazel_android_tools/android_tools_pkg-0.16.0.tar.gz",
        ],
        # bazelbuild/bazel-skylib
        "2d4c9528e0f453b5950eeaeac11d8d09f5a504d4.tar.gz": [
            "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/archive/2d4c9528e0f453b5950eeaeac11d8d09f5a504d4.tar.gz",
            "https://github.com/bazelbuild/bazel-skylib/archive/2d4c9528e0f453b5950eeaeac11d8d09f5a504d4.tar.gz",
        ],
        # bazelbuild/platforms
        "46993efdd33b73649796c5fc5c9efb193ae19d51.zip": [
            "https://mirror.bazel.build/github.com/bazelbuild/platforms/archive/46993efdd33b73649796c5fc5c9efb193ae19d51.zip",
            "https://github.com/bazelbuild/platforms/archive/46993efdd33b73649796c5fc5c9efb193ae19d51.zip",
        ],
        # bazelbuild/rules_java
        "7cf3cefd652008d0a64a419c34c13bdca6c8f178.zip": [
            "https://mirror.bazel.build/github.com/bazelbuild/rules_java/archive/7cf3cefd652008d0a64a419c34c13bdca6c8f178.zip",
            "https://github.com/bazelbuild/rules_java/archive/7cf3cefd652008d0a64a419c34c13bdca6c8f178.zip",
        ],
        # bazelbuild/rules_cc
        "8bd6cd75d03c01bb82561a96d9c1f9f7157b13d0.zip": [
            "https://mirror.bazel.build/github.com/bazelbuild/rules_cc/archive/8bd6cd75d03c01bb82561a96d9c1f9f7157b13d0.zip",
            "https://github.com/bazelbuild/rules_cc/archive/8bd6cd75d03c01bb82561a96d9c1f9f7157b13d0.zip",
        ],
        # bazelbuild/rules_proto
        "97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz": [
            "https://mirror.bazel.build/github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
            "https://github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
        ],
        # protocolbuffers/protobuf
        "v3.11.3.tar.gz": [
            "https://mirror.bazel.build/github.com/protocolbuffers/protobuf/archive/v3.11.3.tar.gz",
            "https://github.com/protocolbuffers/protobuf/archive/v3.11.3.tar.gz",
        ],
    },
)

load("//scripts/docs:doc_versions.bzl", "DOC_VERSIONS")

[http_file(
    # Split on "-" to get the version without cherrypick commits.
    name = "jekyll_tree_%s" % DOC_VERSION["version"].split("-")[0].replace(".", "_"),
    sha256 = DOC_VERSION["sha256"],
    urls = ["https://mirror.bazel.build/bazel_versioned_docs/jekyll-tree-%s.tar" % DOC_VERSION["version"]],
) for DOC_VERSION in DOC_VERSIONS]

# Skydoc recommends declaring its dependencies via "*_dependencies" functions.
# This requires that the repositories these functions come from need to be
# fetched unconditionally for everything (including just building bazel!), so
# provide them as http_archives that can be shiped in the distdir, to keep the
# distribution archive self-contained.
http_archive(
    name = "io_bazel_rules_sass",
    sha256 = "c78be58f5e0a29a04686b628cf54faaee0094322ae0ac99da5a8a8afca59a647",
    strip_prefix = "rules_sass-1.25.0",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_sass/archive/1.25.0.zip",
        "https://github.com/bazelbuild/rules_sass/archive/1.25.0.zip",
    ],
)

http_archive(
    name = "build_bazel_rules_nodejs",
    sha256 = "b6670f9f43faa66e3009488bbd909bc7bc46a5a9661a33f6bc578068d1837f37",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_nodejs/releases/download/1.3.0/rules_nodejs-1.3.0.tar.gz",
        "https://github.com/bazelbuild/rules_nodejs/releases/download/1.3.0/rules_nodejs-1.3.0.tar.gz",
    ],
)

http_archive(
    name = "java_tools_langtools_javac11",
    sha256 = "cf0814fa002ef3d794582bb086516d8c9ed0958f83f19799cdb08949019fe4c7",
    urls = [
        "https://mirror.bazel.build/bazel_java_tools/jdk_langtools/langtools_jdk11_v2.zip",
    ],
)

http_archive(
    name = "platforms",
    sha256 = "66184688debeeefcc2a16a2f80b03f514deac8346fe888fb7e691a52c023dd88",
    strip_prefix = "platforms-46993efdd33b73649796c5fc5c9efb193ae19d51",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/platforms/archive/46993efdd33b73649796c5fc5c9efb193ae19d51.zip",
        "https://github.com/bazelbuild/platforms/archive/46993efdd33b73649796c5fc5c9efb193ae19d51.zip",
    ],
)

http_archive(
    name = "java_tools_langtools_javac12",
    sha256 = "99b107105165a91df82cd7cf82a8efb930d803fb7de1663cf7f780142104cd14",
    urls = [
        "https://mirror.bazel.build/bazel_java_tools/jdk_langtools/langtools_jdk12.zip",
    ],
)

# This must be kept in sync with src/main/java/com/google/devtools/build/lib/bazel/rules/android/android_remote_tools.WORKSPACE
http_archive(
    name = "android_tools_for_testing",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_FILE_WIN,
    sha256 = "e2cbd43a9d23aa32197c29d689a7e017f205acb07053f5dd584f500a1a9d4361",  # DO_NOT_REMOVE_THIS_ANDROID_TOOLS_UPDATE_MARKER
    url = "https://mirror.bazel.build/bazel_android_tools/android_tools_pkg-0.16.0.tar.gz",
)

# This must be kept in sync with src/main/java/com/google/devtools/build/lib/bazel/rules/coverage.WORKSPACE.
http_archive(
    name = "remote_coverage_tools_for_testing",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_FILE_WIN,
    sha256 = "96ac6bc9b9fbc67b532bcae562da1642409791e6a4b8e522f04946ee5cc3ff8e",
    urls = [
        "https://mirror.bazel.build/bazel_coverage_output_generator/releases/coverage_output_generator-v2.1.zip",
    ],
)

# This must be kept in sync with src/main/java/com/google/devtools/build/lib/bazel/rules/java/jdk.WORKSPACE.
http_archive(
    name = "remotejdk11_linux_for_testing",
    build_file = "@local_jdk//:BUILD.bazel",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_BAZEL_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_BAZEL_FILE_WIN,
    sha256 = "360626cc19063bc411bfed2914301b908a8f77a7919aaea007a977fa8fb3cde1",
    strip_prefix = "zulu11.37.17-ca-jdk11.0.6-linux_x64",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu11.37.17-ca-jdk11.0.6/zulu11.37.17-ca-jdk11.0.6-linux_x64.tar.gz"],
)

# This must be kept in sync with src/main/java/com/google/devtools/build/lib/bazel/rules/java/jdk.WORKSPACE.
http_archive(
    name = "remotejdk11_linux_aarch64_for_testing",
    build_file = "@local_jdk//:BUILD.bazel",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_BAZEL_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_BAZEL_FILE_WIN,
    sha256 = "a452f1b9682d9f83c1c14e54d1446e1c51b5173a3a05dcb013d380f9508562e4",
    strip_prefix = "zulu11.37.48-ca-jdk11.0.6-linux_aarch64",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu11.37.48-ca-jdk11.0.6/zulu11.37.48-ca-jdk11.0.6-linux_aarch64.tar.gz"],
)

# This must be kept in sync with src/main/java/com/google/devtools/build/lib/bazel/rules/java/jdk.WORKSPACE.
http_archive(
    name = "remotejdk11_macos_for_testing",
    build_file = "@local_jdk//:BUILD.bazel",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_BAZEL_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_BAZEL_FILE_WIN,
    sha256 = "e1fe56769f32e2aaac95e0a8f86b5a323da5af3a3b4bba73f3086391a6cc056f",
    strip_prefix = "zulu11.37.17-ca-jdk11.0.6-macosx_x64",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu11.37.17-ca-jdk11.0.6/zulu11.37.17-ca-jdk11.0.6-macosx_x64.tar.gz"],
)

# This must be kept in sync with src/main/java/com/google/devtools/build/lib/bazel/rules/java/jdk.WORKSPACE.
http_archive(
    name = "remotejdk11_win_for_testing",
    build_file = "@local_jdk//:BUILD.bazel",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_BAZEL_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_BAZEL_FILE_WIN,
    sha256 = "a9695617b8374bfa171f166951214965b1d1d08f43218db9a2a780b71c665c18",
    strip_prefix = "zulu11.37.17-ca-jdk11.0.6-win_x64",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu11.37.17-ca-jdk11.0.6/zulu11.37.17-ca-jdk11.0.6-win_x64.zip"],
)

# This must be kept in sync with src/main/java/com/google/devtools/build/lib/bazel/rules/java/jdk.WORKSPACE.
http_archive(
    name = "remote_java_tools_linux_for_testing",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_FILE_WIN,
    sha256 = "c24aef916cc5a8e9f6d53db1f93c54fe5790a58996a1099592e1dfe992acc81e",
    urls = [
        "https://mirror.bazel.build/bazel_java_tools/releases/javac11/v8.0/java_tools_javac11_linux-v8.0.zip",
        "https://github.com/bazelbuild/java_tools/releases/download/javac11_v8.0/java_tools_javac11_linux-v8.0.zip",
    ],
)

# This must be kept in sync with src/main/java/com/google/devtools/build/lib/bazel/rules/java/jdk.WORKSPACE.
http_archive(
    name = "remote_java_tools_windows_for_testing",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_FILE_WIN,
    sha256 = "444c391977e50af4e10549a28d021069d2ca7745a0e7b9b968a7b153fe3ea430",
    urls = [
        "https://mirror.bazel.build/bazel_java_tools/releases/javac11/v8.0/java_tools_javac11_windows-v8.0.zip",
        "https://github.com/bazelbuild/java_tools/releases/download/javac11_v8.0/java_tools_javac11_windows-v8.0.zip",
    ],
)

# This must be kept in sync with src/main/java/com/google/devtools/build/lib/bazel/rules/java/jdk.WORKSPACE.
http_archive(
    name = "remote_java_tools_darwin_for_testing",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_FILE_WIN,
    sha256 = "e0291e8956ac295143da4a673ca50727f7376665ee82b649a4ee810b64ff76c1",
    urls = [
        "https://mirror.bazel.build/bazel_java_tools/releases/javac11/v8.0/java_tools_javac11_darwin-v8.0.zip",
        "https://github.com/bazelbuild/java_tools/releases/download/javac11_v8.0/java_tools_javac11_darwin-v8.0.zip",
    ],
)

# This must be kept in sync with src/test/shell/bazel/testdata/jdk_http_archives.
http_archive(
    name = "remote_java_tools_javac11_test_linux",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_FILE_WIN,
    sha256 = "c24aef916cc5a8e9f6d53db1f93c54fe5790a58996a1099592e1dfe992acc81e",
    urls = [
        "https://mirror.bazel.build/bazel_java_tools/releases/javac11/v8.0/java_tools_javac11_linux-v8.0.zip",
    ],
)

# This must be kept in sync with src/test/shell/bazel/testdata/jdk_http_archives.
http_archive(
    name = "remote_java_tools_javac11_test_windows",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_FILE_WIN,
    sha256 = "444c391977e50af4e10549a28d021069d2ca7745a0e7b9b968a7b153fe3ea430",
    urls = [
        "https://mirror.bazel.build/bazel_java_tools/releases/javac11/v8.0/java_tools_javac11_windows-v8.0.zip",
    ],
)

# This must be kept in sync with src/test/shell/bazel/testdata/jdk_http_archives.
http_archive(
    name = "remote_java_tools_javac11_test_darwin",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_FILE_WIN,
    sha256 = "e0291e8956ac295143da4a673ca50727f7376665ee82b649a4ee810b64ff76c1",
    urls = [
        "https://mirror.bazel.build/bazel_java_tools/releases/javac11/v8.0/java_tools_javac11_darwin-v8.0.zip",
    ],
)

# This must be kept in sync with src/test/shell/bazel/testdata/jdk_http_archives.
http_archive(
    name = "remote_java_tools_javac12_test_linux",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_FILE_WIN,
    sha256 = "3997ee9a57b095748f1c0d084839fab2fbc72504aeb7b37b1f71c31738d330e3",
    urls = ["https://mirror.bazel.build/bazel_java_tools/releases/javac12/v3.0/java_tools_javac12_linux-v3.0.zip"],
)

# This must be kept in sync with src/test/shell/bazel/testdata/jdk_http_archives.
http_archive(
    name = "remote_java_tools_javac12_test_windows",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_FILE_WIN,
    sha256 = "cfad1718dad1fed12816748eed27ab30b9ea1268c8ce9940acf3b5b7d82d483d",
    urls = [
        "https://mirror.bazel.build/bazel_java_tools/releases/javac12/v3.0/java_tools_javac12_windows-v3.0.zip",
    ],
)

# This must be kept in sync with src/test/shell/bazel/testdata/jdk_http_archives.
http_archive(
    name = "remote_java_tools_javac12_test_darwin",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_FILE_WIN,
    sha256 = "54df966e7583bafe659e39b4103a4ce934201d969de638d071ada07d8e0c1a3a",
    urls = [
        "https://mirror.bazel.build/bazel_java_tools/releases/javac12/v3.0/java_tools_javac12_darwin-v3.0.zip",
    ],
)

# This must be kept in sync with src/test/shell/bazel/testdata/jdk_http_archives.
http_archive(
    name = "openjdk11_linux_archive",
    build_file_content = """
java_runtime(name = 'runtime', srcs =  glob(['**']), visibility = ['//visibility:public'])
exports_files(["WORKSPACE"], visibility = ["//visibility:public"])
""",
    sha256 = "360626cc19063bc411bfed2914301b908a8f77a7919aaea007a977fa8fb3cde1",
    strip_prefix = "zulu11.37.17-ca-jdk11.0.6-linux_x64",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu11.37.17-ca-jdk11.0.6/zulu11.37.17-ca-jdk11.0.6-linux_x64.tar.gz"],
)

# This must be kept in sync with src/test/shell/bazel/testdata/jdk_http_archives.
http_archive(
    name = "openjdk11_darwin_archive",
    build_file_content = """
java_runtime(name = 'runtime', srcs =  glob(['**']), visibility = ['//visibility:public'])
exports_files(["WORKSPACE"], visibility = ["//visibility:public"])
""",
    sha256 = "e1fe56769f32e2aaac95e0a8f86b5a323da5af3a3b4bba73f3086391a6cc056f",
    strip_prefix = "zulu11.37.17-ca-jdk11.0.6-macosx_x64",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu11.37.17-ca-jdk11.0.6/zulu11.37.17-ca-jdk11.0.6-macosx_x64.tar.gz"],
)

# This must be kept in sync with src/test/shell/bazel/testdata/jdk_http_archives.
http_archive(
    name = "openjdk11_windows_archive",
    build_file_content = """
java_runtime(name = 'runtime', srcs =  glob(['**']), visibility = ['//visibility:public'])
exports_files(["WORKSPACE"], visibility = ["//visibility:public"])
""",
    sha256 = "a9695617b8374bfa171f166951214965b1d1d08f43218db9a2a780b71c665c18",
    strip_prefix = "zulu11.37.17-ca-jdk11.0.6-win_x64",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu11.37.17-ca-jdk11.0.6/zulu11.37.17-ca-jdk11.0.6-win_x64.zip"],
)

# This must be kept in sync with src/test/shell/bazel/testdata/jdk_http_archives.
http_archive(
    name = "openjdk12_linux_archive",
    build_file_content = """
java_runtime(name = 'runtime', srcs =  glob(['**']), visibility = ['//visibility:public'])
exports_files(["WORKSPACE"], visibility = ["//visibility:public"])
""",
    sha256 = "529c99841d69e11a85aea967ccfb9d0fd40b98c5b68dbe1d059002655e0a9c13",
    strip_prefix = "zulu12.2.3-ca-jdk12.0.1-linux_x64",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu12.2.3-ca-jdk12.0.1/zulu12.2.3-ca-jdk12.0.1-linux_x64.tar.gz"],
)

# This must be kept in sync with src/test/shell/bazel/testdata/jdk_http_archives.
http_archive(
    name = "openjdk12_darwin_archive",
    build_file_content = """
java_runtime(name = 'runtime', srcs =  glob(['**']), visibility = ['//visibility:public'])
exports_files(["WORKSPACE"], visibility = ["//visibility:public"])
""",
    sha256 = "67ca9d285056132ebb19fa237a14affda52132142e1171fe1c20e18974b3b8a5",
    strip_prefix = "zulu12.2.3-ca-jdk12.0.1-macosx_x64",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu12.2.3-ca-jdk12.0.1/zulu12.2.3-ca-jdk12.0.1-macosx_x64.tar.gz"],
)

# This must be kept in sync with src/test/shell/bazel/testdata/jdk_http_archives.
http_archive(
    name = "openjdk12_windows_archive",
    build_file_content = """
java_runtime(name = 'runtime', srcs =  glob(['**']), visibility = ['//visibility:public'])
exports_files(["WORKSPACE"], visibility = ["//visibility:public"])
""",
    sha256 = "cf28404c23c3aa1115363ba6e796c30580a768e1d7d6681a7d053e516008e00d",
    strip_prefix = "zulu12.2.3-ca-jdk12.0.1-win_x64",
    urls = ["https://mirror.bazel.build/openjdk/azul-zulu12.2.3-ca-jdk12.0.1/zulu12.2.3-ca-jdk12.0.1-win_x64.zip"],
)

load("@io_bazel_skydoc//:setup.bzl", "skydoc_repositories")

skydoc_repositories()

load("@io_bazel_rules_sass//:package.bzl", "rules_sass_dependencies")

rules_sass_dependencies()

load("@build_bazel_rules_nodejs//:index.bzl", "node_repositories")

node_repositories()

load("@io_bazel_rules_sass//:defs.bzl", "sass_repositories")

sass_repositories()

register_execution_platforms("//:default_host_platform")  # buildozer: disable=positional-args

# Tools for building deb, rpm and tar files.
http_archive(
    name = "rules_pkg",
    patch_cmds = EXPORT_WORKSPACE_IN_BUILD_FILE,
    patch_cmds_win = EXPORT_WORKSPACE_IN_BUILD_FILE_WIN,
    sha256 = "4ba8f4ab0ff85f2484287ab06c0d871dcb31cc54d439457d28fd4ae14b18450a",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_pkg/releases/download/0.2.4/rules_pkg-0.2.4.tar.gz",
        "https://github.com/bazelbuild/rules_pkg/releases/download/0.2.4/rules_pkg-0.2.4.tar.gz",
    ],
)

load("@rules_pkg//:deps.bzl", "rules_pkg_dependencies")

rules_pkg_dependencies()

# Toolchains for Resource Compilation (.rc files on Windows).
load("//src/main/res:winsdk_configure.bzl", "winsdk_configure")

winsdk_configure(name = "local_config_winsdk")

load("@local_config_winsdk//:toolchains.bzl", "register_local_rc_exe_toolchains")

register_local_rc_exe_toolchains()

register_toolchains("//src/main/res:empty_rc_toolchain")

load("//tools/distributions/debian:deps.bzl", "debian_deps")

debian_deps()
