#ifndef NODE_H
#define NODE_H

#include "lib/row.h"
#include "lib/table.h"
#include <stdint.h>

typedef enum { NODE_INTERNAL, NODE_LEAF } NodeType;

/*
  Common (both internal and leaf) node header layout
*/

static const uint8_t NODE_TYPE_SIZE = sizeof(uint8_t);
static const uint8_t NODE_TYPE_OFFSET = 0;
static const uint8_t IS_ROOT_SIZE = sizeof(uint8_t); // bool
static const uint8_t IS_ROOT_OFFSET = NODE_TYPE_SIZE;
static const uint8_t PARENT_POINTER_SIZE = sizeof(uint32_t);
static const uint8_t PARENT_POINTER_OFFSET = IS_ROOT_OFFSET + IS_ROOT_OFFSET;
static const uint8_t COMMON_NODE_HEADER_SIZE = NODE_TYPE_SIZE + IS_ROOT_SIZE + PARENT_POINTER_SIZE;


/*
  Leaf node header layout
*/

static const uint8_t LEAF_NODE_NUM_CELLS_SIZE = sizeof(uint32_t); // number of KV pairs
static const uint8_t LEAF_NODE_NUM_CELLS_OFFSET = COMMON_NODE_HEADER_SIZE;
static const uint8_t LEAF_NODE_HEADER_SIZE = COMMON_NODE_HEADER_SIZE + LEAF_NODE_NUM_CELLS_SIZE;


/*
  Leaf node body layout
*/

static const uint32_t LEAF_NODE_KEY_SIZE = sizeof(uint32_t);
static const uint32_t LEAF_NODE_KEY_OFFSET = 0;
static const uint32_t LEAF_NODE_VALUE_SIZE = ROW_SIZE;
static const uint32_t LEAF_NODE_VALUE_OFFSET = LEAF_NODE_KEY_OFFSET + LEAF_NODE_KEY_SIZE;
static const uint32_t LEAF_NODE_CELL_SIZE = LEAF_NODE_KEY_SIZE + LEAF_NODE_VALUE_SIZE;
static const uint32_t LEAD_NODE_SPACE_FOR_CELLS = PAGE_SIZE - LEAF_NODE_HEADER_SIZE;
static const uint32_t LEAF_NODE_MAX_CELLS = LEAD_NODE_SPACE_FOR_CELLS / LEAF_NODE_CELL_SIZE;


/*
  Leaf node fields access
*/

uint32_t* leaf_node_num_cells(void* node);
void* leaf_node_cell(void* node, uint32_t cell_num);
uint32_t* leaf_node_key(void* node, uint32_t cell_num);
void* leaf_node_value(void* node, uint32_t cell_num);
void initialize_leaf_node(void* node);


#endif