#ifndef ROW_OPS_H
#define ROW_OPS_H

#include "lib/row.h"

void serialize_row(Row *source, void *destination);
void deserialize_row(void *source, Row *destination);

void print_row(Row *row);

#endif