#ifndef IO_H
#define IO_H

#include <stddef.h>
#include <unistd.h>

typedef struct {
  char *buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

InputBuffer *new_input_buffer();

void print_prompt();
void read_input(InputBuffer *input_buffer);
void free_input_buffer(InputBuffer *input_buffer);

#endif
