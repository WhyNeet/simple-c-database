#include "lib/commands.h"
#include "btree/node.h"
#include "btree/node_ops.h"
#include "lib/cursor.h"
#include "lib/row_ops.h"
#include "lib/table.h"
#include "lib/table_ops.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MetaCommandResult exec_meta_command(InputBuffer *input_buffer, Table *table) {
  if (strcmp(input_buffer->buffer, ".exit") == 0) {
    db_close(table);
    exit(EXIT_SUCCESS);
  } else {
    return META_COMMAND_UNRECOGNIZED_COMMAND;
  }
}

PrepareResult prepare_insert(InputBuffer *input_buffer, Statement *statement) {
  statement->kind = STATEMENT_INSERT;

  char *keyword = strtok(input_buffer->buffer, " ");
  char *id_string = strtok(NULL, " ");
  char *username = strtok(NULL, " ");
  char *email = strtok(NULL, " ");

  if (id_string == NULL || username == NULL || email == NULL) {
    return PREPARE_SYNTAX_ERROR;
  }

  int id = atoi(id_string);

  if (id < 0) {
    return PREPARE_NEGATIVE_ID;
  }
  if (strlen(username) > COLUMN_USERNAME_SIZE) {
    return PREPARE_STRING_TOO_LONG;
  }
  if (strlen(email) > COLUMN_EMAIL_SIZE) {
    return PREPARE_STRING_TOO_LONG;
  }

  statement->row_to_insert.id = (uint32_t)id;
  strcpy(statement->row_to_insert.username, username);
  strcpy(statement->row_to_insert.email, email);

  return PREPARE_SUCCESS;
}

PrepareResult prepare_statement(InputBuffer *input_buffer,
                                Statement *statement) {
  if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
    return prepare_insert(input_buffer, statement);
  }

  if (strncmp(input_buffer->buffer, "select", 6) == 0) {
    statement->kind = STATEMENT_SELECT;
    return PREPARE_SUCCESS;
  }

  return PREPARE_UNRECOGNIZED_STATEMENT;
}

ExecuteResult exec_insert(Statement *statement, Table *table) {
  void *node = get_page(table->pager, table->root_page_num);
  if (*leaf_node_num_cells(node) >= LEAF_NODE_MAX_CELLS) {
    return EXECUTE_TABLE_FULL;
  }

  Row *row_to_insert = &statement->row_to_insert;
  Cursor *cursor = table_end(table);

  leaf_node_insert(cursor, row_to_insert->id, row_to_insert);

  free(cursor);

  return EXECUTE_SUCCESS;
}

ExecuteResult exec_select(Statement *statement, Table *table) {
  Cursor *cursor = table_start(table);
  Row row;

  while (!cursor->is_at_end) {
    deserialize_row(cursor_value(cursor), &row);
    print_row(&row);
    cursor_advance(cursor);
  }

  free(cursor);

  return EXECUTE_SUCCESS;
}

ExecuteResult exec_statement(Statement *statement, Table *table) {
  switch (statement->kind) {
  case (STATEMENT_INSERT):
    return exec_insert(statement, table);

  case (STATEMENT_SELECT):
    return exec_select(statement, table);
  }
}