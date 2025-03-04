load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "node",
    srcs = ["node.c"],
    hdrs = ["include/node.h"],
    include_prefix = "btree",
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = ["//lib:data"],
)

cc_library(
    name = "nodeops",
    srcs = ["node_ops.c"],
    hdrs = ["include/node_ops.h"],
    include_prefix = "btree",
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = [
        ":node",
        "//lib:cursor",
    ],
)
