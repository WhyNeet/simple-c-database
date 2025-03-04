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
