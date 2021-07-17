load("@rules_cc//cc:defs.bzl", "cc_library")

licenses(["notice"])

package(default_visibility = ["//visibility:public"])

# FIXME(all): hide vtk version from end users
cc_library(
    name = "vtk",
    includes = ["."],
    linkopts = [
        "-lvtkCommonDataModel-7.1",
        "-lvtkCommonCore-7.1",
        "-lvtkCommonMath-7.1",
        "-lvtkCommonSystem-7.1",
        "-lvtkCommonMisc-7.1",
        "-lvtkCommonTransforms-7.1",
        "-lvtksys-7.1",
    ],
)
