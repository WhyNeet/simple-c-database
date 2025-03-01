#include "lib/commands.h"
#include "io.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  InputBuffer *input_buffer = new_input_buffer();

  while (true) {
    print_prompt();
    read_input(input_buffer);

    if (input_buffer->buffer[0] == '.') {
      switch (exec_meta_command(input_buffer)) {
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
    case (PREPARE_UNRECOGNIZED_STATEMENT):
      printf("unregonized statement: `%s`.\n", input_buffer->buffer);
      continue;
    }

    exec_statement(&statement);
    printf("executed.\n");
  }

  return 0;
}
