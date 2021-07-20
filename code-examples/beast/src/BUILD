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
