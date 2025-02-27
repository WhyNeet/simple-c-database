cc_library(
  name = "io",
  srcs = ["io.c"],
  hdrs = ["include/io.h"],
  includes = ["include"],
  visibility = ["//visibility:public"]
)

cc_library(
  name = "commands",
  srcs = ["commands.c"],
  hdrs = ["include/commands.h"],
  includes = ["include"],
  deps = [":io"],
  visibility = ["//visibility:public"]
)
