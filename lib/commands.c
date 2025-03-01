#include "commands.h"
#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MetaCommandResult exec_meta_command(InputBuffer *input_buffer) {
  if (strcmp(input_buffer->buffer, ".exit") == 0) {
    exit(EXIT_SUCCESS);
  } else {
    return META_COMMAND_UNRECOGNIZED_COMMAND;
  }
}

PrepareResult prepare_statement(InputBuffer *input_buffer,
                                Statement *statement) {
  if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
    statement->kind = STATEMENT_INSERT;
    int args_assigned = sscanf(
        input_buffer->buffer, "insert %d %s %s", &(statement->row_to_insert.id),
        statement->row_to_insert.username, statement->row_to_insert.email);

    if (args_assigned < 3) {
      return PREPARE_SYNTAX_ERROR;
    }

    return PREPARE_SUCCESS;
  }

  if (strncmp(input_buffer->buffer, "select", 6) == 0) {
    statement->kind = STATEMENT_SELECT;
    return PREPARE_SUCCESS;
  }

  return PREPARE_UNRECOGNIZED_STATEMENT;
}


ExecuteResult exec_insert(Statement* statement, Table* table) {
  if (table->num_rows >= TABLE_MAX_ROWS) {
    return EXECUTE_TABLE_FULL;
  }
  
  Row* row_to_insert = &statement->row_to_insert;
  
  serialize_row(row_to_insert, row_slot(table, table->num_rows));
  table->num_rows += 1;
  
  return EXECUTE_SUCCESS;
}

ExecuteResult exec_select(Statement* statement, Table* table) {
  Row row;
  
  for (uint32_t i = 0; i < table->num_rows; i++) {
    deserialize_row(row_slot(table, i), &row);
    print_row(&row);
  }
  
  return EXECUTE_SUCCESS;
}

ExecuteResult exec_statement(Statement *statement, Table* table) {
  switch (statement->kind) {
  case (STATEMENT_INSERT):
    return exec_insert(statement, table);

  case (STATEMENT_SELECT):
    return exec_select(statement, table);
  }
}