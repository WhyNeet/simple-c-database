#include "include/commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MetaCommandResult exec_meta_command(InputBuffer *input_buffer) {
  if (strcmp(input_buffer->buffer, ".exit") == 0) {
    exit(EXIT_SUCCESS);
  } else {
    return META_COMMAND_UNRECOGNIZED_COMMAND;
  }
}

PrepareResult prepare_statement(InputBuffer *input_buffer,
                                Statement *statement) {
  if (strncmp(input_buffer->buffer, "INSERT", 6) == 0) {
    statement->kind = STATEMENT_INSERT;
    return PREPARE_SUCCESS;
  }

  if (strncmp(input_buffer->buffer, "SELECT", 6) == 0) {
    statement->kind = STATEMENT_SELECT;
    return PREPARE_SUCCESS;
  }

  return PREPARE_UNRECOGNIZED_STATEMENT;
}

void exec_statement(Statement *statement) {
  switch (statement->kind) {
  case (STATEMENT_INSERT):
    printf("todo: insert\n");
    break;

  case (STATEMENT_SELECT):
    printf("todo: select\n");
    break;
  }
}
