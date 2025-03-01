#ifndef TABLE_H
#define TABLE_H

#include "row.h"
#include <stdint.h>

#define TABLE_MAX_PAGES 100

static const uint32_t PAGE_SIZE = 4096;
static const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
static const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

typedef struct {
  uint32_t num_rows;
  void *pages[TABLE_MAX_ROWS];
} Table;

void* row_slot(Table* table, uint32_t row_num);

Table* new_table();
void free_table(Table* table);

#endif
