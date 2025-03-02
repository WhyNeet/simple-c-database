load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "io",
    srcs = ["io.c"],
    hdrs = ["include/io.h"],
    include_prefix = "lib",
    includes = ["include"],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "data",
    srcs = [
        "row.c",
        "table.c",
    ],
    hdrs = [
        "include/row.h",
        "include/table.h",
    ],
    include_prefix = "lib",
    includes = ["include"],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "commands",
    srcs = ["commands.c"],
    hdrs = ["include/commands.h"],
    include_prefix = "lib",
    includes = ["include"],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = [
        ":data",
        ":io",
    ],
)

cc_test(
    name = "data_test",
    size = "small",
    srcs = ["tests/row.c"],
    deps = [":data"],
)

cc_test(
    name = "commands_test",
    size = "small",
    srcs = ["tests/commands.c"],
    deps = [
        ":commands",
        ":data",
    ],
)
