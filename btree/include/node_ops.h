#include "btree/node.h"
#include "lib/cursor.h"

/*
  Leaf node methods.
*/

void leaf_node_insert(Cursor *cursor, uint32_t key, Row *value);