#ifndef CURSOR_H
#define CURSOR_H

#include "lib/table.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct {
  Table *table;
  uint32_t row_num;
  bool is_at_end;
} Cursor;

Cursor *table_start(Table *table);
Cursor *table_end(Table *table);

void *cursor_value(Cursor *cursor);
void cursor_advance(Cursor *cursor);

#endif