#include "btree/node.h"
#include "lib/cursor.h"
#include "lib/row_ops.h"
#include "lib/table_ops.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void leaf_node_insert(Cursor *cursor, uint32_t key, Row *value) {
  void *node = get_page(cursor->table->pager, cursor->page_num);

  uint32_t num_cells = *leaf_node_num_cells(node);
  if (num_cells >= LEAF_NODE_MAX_CELLS) {
    // node is full.
    printf("todo: implement leaf node splitting.\n");
    exit(EXIT_FAILURE);
  }

  if (cursor->cell_num < num_cells) {
    // cursor is not at the end of the page.
    for (uint32_t i = num_cells; i > cursor->cell_num; i--) {
      memcpy(leaf_node_cell(node, i), leaf_node_cell(node, i - 1),
             LEAF_NODE_CELL_SIZE);
    }
  }

  *leaf_node_num_cells(node) += 1;
  *leaf_node_key(node, cursor->cell_num) = key;
  serialize_row(value, leaf_node_value(node, cursor->cell_num));
}