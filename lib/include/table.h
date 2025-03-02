#ifndef TABLE_H
#define TABLE_H

#include "row.h"
#include <stdint.h>

#define TABLE_MAX_PAGES 100

static const uint32_t PAGE_SIZE = 4096;
static const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
static const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

typedef struct {
  int fd;
  uint32_t file_length;
  void *pages[TABLE_MAX_PAGES];
} Pager;

Pager *pager_open(const char *filename);

typedef struct {
  uint32_t num_rows;
  Pager *pager;
} Table;

void *row_slot(Table *table, uint32_t row_num);

Table *db_open(const char *filename);
void db_close(Table *table);

#endif
