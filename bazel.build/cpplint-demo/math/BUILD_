load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")
load("//bazel:cpplint.bzl", "cpplint")

cc_library(
    name = "base",
    srcs = ["base.cc"],
    hdrs = ["base.h"],
)

cc_test(
    name = "base_test",
    size = "small",
    srcs = ["base_test.cc"],
    deps = [
        ":base",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "base_bm",
    srcs = ["base_bm.cc"],
    tags = ["benchmark"],
    deps = [
        "@com_github_google_benchmark//:benchmark_main",
    ],
)

cpplint()
