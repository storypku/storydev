load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "md5",
    srcs = ["md5.cpp"],
    hdrs = ["md5.h"],
)

cc_library(
    name = "fixed_size_string",
    hdrs = ["fixed_size_string.hpp"],
)

cc_test(
    name = "fixed_size_string_test",
    srcs = ["fixed_size_string_test.cpp"],
    deps = [
        ":fixed_size_string",
        "@com_google_googletest//:gtest_main",
    ],
)
