#ifndef TABLE_OPS_H
#define TABLE_OPS_H

#include "lib/table.h"

Pager *pager_open(const char *filename);
void *get_page(Pager *pager, uint32_t page_num);

Table *db_open(const char *filename);
void db_close(Table *table);

#endif