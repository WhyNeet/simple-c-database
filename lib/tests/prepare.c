#include "lib/commands.h"
#include "lib/io.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void test_argument_too_long_error() {
  InputBuffer *buffer = new_input_buffer();
  buffer->buffer = malloc(58);
  strcpy(buffer->buffer,
         "insert 0 whneetqwewqewewewqeqewqeqefdfdsfdfsdfsfsfs email");

  Statement statement;
  PrepareResult result = prepare_statement(buffer, &statement);

  assert(result == PREPARE_STRING_TOO_LONG);
}

int main() {
  test_argument_too_long_error();

  return 0;
}