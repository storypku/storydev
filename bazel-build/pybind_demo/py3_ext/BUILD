load("@pybind11_bazel//:build_defs.bzl", "pybind_extension")

package(
    default_visibility = ["//visibility:public"],
)

pybind_extension(
    name = "mymath",
    srcs = ["mymath.cc"],
    deps = [
        "//cyber:mymath",
    ],
)

pybind_extension(
    name = "pet",
    srcs = ["pet.cc"],
    deps = [
        "//cyber:pet",
    ],
)
