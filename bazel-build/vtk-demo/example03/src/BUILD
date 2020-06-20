load("@rules_cc//cc:defs.bzl", "cc_binary")

package(
    default_visibility = ["//visibility:public"],
)

cc_binary(
    name = "dist_pt2line",
    srcs = ["dist_pt2line.cc"],
    deps = [
        "@local_config_vtk//:vtk",
    ],
)
