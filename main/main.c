#include "../lib/include/io.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  InputBuffer *input_buffer = new_input_buffer();

  while (true) {
    print_prompt();
    read_input(input_buffer);

    if (strcmp(input_buffer->buffer, ".exit") == 0) {
      free_input_buffer(input_buffer);
      exit(EXIT_SUCCESS);
    } else {
      printf("unrecognized command: \"%s\"\n", input_buffer->buffer);
    }
  }

  return 0;
}
