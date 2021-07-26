load("@rules_cc//cc:defs.bzl", "cc_binary")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "http_sync_client",
    srcs = ["http_sync_client.cc"],
    deps = [
        "@boost//:beast",
    ],
)

cc_binary(
    name = "websocket_sync_client",
    srcs = ["websocket_sync_client.cc"],
    deps = [
        "@boost//:beast",
    ],
)

cc_binary(
    name = "http_async_client",
    srcs = ["http_async_client.cc"],
    deps = [
        "@boost//:beast",
    ],
)

cc_binary(
    name = "websocket_async_client",
    srcs = ["websocket_async_client.cc"],
    deps = [
        "@boost//:beast",
    ],
)

cc_binary(
    name = "http_sync_server",
    srcs = ["http_sync_server.cc"],
    deps = [
        "@boost//:beast",
    ],
)

cc_binary(
    name = "http_async_server",
    srcs = ["http_async_server.cc"],
    deps = [
        "@boost//:beast",
    ],
)

cc_binary(
    name = "http_fast_server",
    srcs = [
        "fields_alloc.hpp",
        "http_fast_server.cc",
    ],
    deps = [
        "@boost//:beast",
    ],
)

cc_binary(
    name = "websocket_sync_server",
    srcs = ["websocket_sync_server.cc"],
    deps = [
        "@boost//:beast",
    ],
)

cc_binary(
    name = "websocket_async_server",
    srcs = ["websocket_async_server.cc"],
    deps = [
        "@boost//:beast",
    ],
)

cc_binary(
    name = "websocket_fast_server",
    srcs = ["websocket_fast_server.cc"],
    deps = [
        "@boost//:beast",
        "@boost//:coroutine",
    ],
)

cc_binary(
    name = "advanced_server",
    srcs = ["advanced_server.cc"],
    deps = [
        ":http_util",
        "@boost//:beast",
    ],
)

cc_library(
    name = "http_util",
    srcs = ["http_util.cc"],
    hdrs = ["http_util.h"],
    deps = [
        "//onboard/utils:file_util",
        "@boost//:beast",
    ],
)
