load("@rules_cc//cc:defs.bzl", "cc_binary")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "http_sync_client",
    srcs = ["http_sync_client.cc"],
    deps = [
        "@boost//:beast",
    ],
)