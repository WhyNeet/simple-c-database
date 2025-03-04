load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "io",
    srcs = ["io.c"],
    hdrs = ["include/io.h"],
    include_prefix = "lib",
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "data",
    hdrs = [
        "include/row.h",
        "include/table.h",
    ],
    include_prefix = "lib",
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = [],
)

cc_library(
    name = "dataops",
    srcs = [
        "row_ops.c",
        "table_ops.c",
    ],
    hdrs = [
        "include/row_ops.h",
        "include/table_ops.h",
    ],
    include_prefix = "lib",
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = [
        ":data",
        "//btree:node",
    ],
)

cc_library(
    name = "commands",
    srcs = ["commands.c"],
    hdrs = ["include/commands.h"],
    include_prefix = "lib",
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = [
        ":cursor",
        ":data",
        ":io",
        "//btree:nodeops",
    ],
)

cc_library(
    name = "cursor",
    srcs = ["cursor.c"],
    hdrs = ["include/cursor.h"],
    include_prefix = "lib",
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = [
        ":data",
        ":dataops",
        "//btree:node",
    ],
)

cc_test(
    name = "data_test",
    size = "small",
    srcs = ["tests/row.c"],
    deps = [
        ":data",
        ":dataops",
    ],
)

cc_test(
    name = "table_ops_test",
    size = "small",
    srcs = [
        "tests/commands/table_ops.c",
    ],
    deps = [
        ":commands",
        ":data",
    ],
)

cc_test(
    name = "table_errors_test",
    size = "small",
    srcs = [
        "tests/commands/table_errors.c",
    ],
    deps = [
        ":commands",
        ":data",
    ],
)

cc_test(
    name = "prepare_test",
    size = "small",
    srcs = [
        "tests/prepare.c",
    ],
    deps = [
        ":commands",
        ":io",
    ],
)

cc_test(
    name = "persistence_test",
    size = "small",
    srcs = [
        "tests/persistence.c",
    ],
    deps = [
        ":commands",
        ":data",
    ],
)
