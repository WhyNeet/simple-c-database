#include "lib/commands.h"
#include "lib/io.h"
#include "lib/table.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  Table *table = db_open("main.db");
  InputBuffer *input_buffer = new_input_buffer();

  while (true) {
    print_prompt();
    read_input(input_buffer);

    if (input_buffer->buffer[0] == '.') {
      switch (exec_meta_command(input_buffer, table)) {
      case (META_COMMAND_SUCCESS):
        continue;
      case (META_COMMAND_UNRECOGNIZED_COMMAND):
        printf("unrecognized meta command: `%s`.\n", input_buffer->buffer);
        continue;
      }
    }

    Statement statement;

    switch (prepare_statement(input_buffer, &statement)) {
    case (PREPARE_SUCCESS):
      break;
    case (PREPARE_SYNTAX_ERROR):
      printf("syntax error.\n");
      continue;
    case (PREPARE_STRING_TOO_LONG):
      printf("argument is too long.\n");
      continue;
    case (PREPARE_NEGATIVE_ID):
      printf("id must be positive.\n");
      continue;
    case (PREPARE_UNRECOGNIZED_STATEMENT):
      printf("unrecognized statement: `%s`.\n", input_buffer->buffer);
      continue;
    }

    switch (exec_statement(&statement, table)) {
    case (EXECUTE_SUCCESS):
      printf("executed.\n");
      break;
    case (EXECUTE_TABLE_FULL):
      printf("failed to insert: table is full.\n");
      break;
    }
  }

  return 0;
}
