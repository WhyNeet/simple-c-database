#ifndef TABLE_H
#define TABLE_H

#include "lib/row.h"
#include <stdint.h>

#define TABLE_MAX_PAGES 100

static const uint32_t PAGE_SIZE = 4096;
static const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
static const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

typedef struct {
  int fd;
  uint32_t file_length;
  uint32_t num_pages;
  void *pages[TABLE_MAX_PAGES];
} Pager;

typedef struct {
  uint32_t num_rows;
  uint32_t root_page_num;
  Pager *pager;
} Table;

#endif
