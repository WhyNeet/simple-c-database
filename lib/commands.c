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
  if (strlen(username) >= COLUMN_USERNAME_SIZE) {
    return PREPARE_STRING_TOO_LONG;
  }
  if (strlen(email) >= COLUMN_EMAIL_SIZE) {
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
  if (table->num_rows >= TABLE_MAX_ROWS) {
    return EXECUTE_TABLE_FULL;
  }

  Row *row_to_insert = &statement->row_to_insert;

  serialize_row(row_to_insert, row_slot(table, table->num_rows));
  table->num_rows += 1;

  return EXECUTE_SUCCESS;
}

ExecuteResult exec_select(Statement *statement, Table *table) {
  Row row;

  for (uint32_t i = 0; i < table->num_rows; i++) {
    deserialize_row(row_slot(table, i), &row);
    print_row(&row);
  }

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