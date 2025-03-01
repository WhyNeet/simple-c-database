cc_library(
  name = "io",
  srcs = ["io.c"],
  hdrs = ["include/io.h"],
  includes = ["include"],
  strip_include_prefix = "include",
  include_prefix = "lib",
  visibility = ["//visibility:public"]
)

cc_library(
  name = "data",
  srcs = ["row.c", "table.c"],
  includes = ["include"],
  strip_include_prefix = "include",
  hdrs = ["include/row.h", "include/table.h"],
  include_prefix = "lib",
  visibility = ["//visibility:public"]
)

cc_library(
  name = "commands",
  srcs = ["commands.c"],
  hdrs = ["include/commands.h"],
  includes = ["include"],
  include_prefix = "lib",
  strip_include_prefix = "include",
  deps = [":io", ":data"],
  visibility = ["//visibility:public"]
)

cc_test(
  name = "data_test",
  srcs = ["tests/row.c"],
  deps = [":data"],
  size = "small"
)
