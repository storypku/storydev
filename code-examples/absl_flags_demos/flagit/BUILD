load("@rules_cc//cc:defs.bzl", "cc_binary")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "hello_flags",
    srcs = ["hello_flags.cc"],
    deps = [
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/time",
    ],
)

cc_binary(
    name = "retired_flag",
    srcs = ["retired_flag.cc"],
    deps = [
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/time",
    ],
)

cc_binary(
    name = "custom_flag",
    srcs = ["custom_flag.cc"],
    deps = [
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/strings",
    ],
)

cc_binary(
    name = "compound_flag",
    srcs = ["compound_flag.cc"],
    deps = [
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/strings",
    ],
)

cc_binary(
    name = "validate",
    srcs = ["validate.cc"],
    deps = [
        "@com_google_absl//absl/flags:parse",
    ],
)

cc_binary(
    name = "logit",
    srcs = ["logit.cc"],
    deps = [
        "@com_github_google_glog//:glog",
        "@com_google_absl//absl/flags:parse",
    ],
)

cc_binary(
    name = "help_msg",
    srcs = ["help_msg.cc"],
    deps = [
        ":elsewhere",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/flags:usage",
        "@com_google_absl//absl/strings",
    ],
)

cc_library(
    name = "elsewhere",
    srcs = ["elsewhere.cc"],
    hdrs = ["elsewhere.h"],
    deps = [
        "@com_google_absl//absl/flags:flag",
    ],
)
