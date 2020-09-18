load("@rules_python//python:defs.bzl", "py_binary")

package(
    default_visibility = ["//visibility:public"],
)

py_binary(
    name = "mymath_demo",
    srcs = ["mymath_demo.py"],
    data = [
        "//py3_ext:mymath.so",
    ],
)

py_binary(
    name = "pet_demo",
    srcs = ["pet_demo.py"],
    data = [
        "//py3_ext:pet.so",
    ],
)
