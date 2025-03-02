#include "lib/commands.h"
#include "lib/row.h"
#include "lib/table.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_table_operations() {
  Table *table = new_table();

  Row row;
  row.id = 0;

  strcpy(&row.username, "whyneet");
  strcpy(&row.email, "whyneet@example.com");

  Statement insert_stmt;
  insert_stmt.kind = STATEMENT_INSERT;
  insert_stmt.row_to_insert = row;
  exec_statement(&insert_stmt, table);

  // capture the select statement output and redirect to a buffer
  char buffer[100];
  memset(buffer, 0, sizeof(buffer));
  FILE *stream = fmemopen(buffer, sizeof(buffer), "w");
  assert(stream != NULL);
  fflush(stdout);
  stdout = stream;

  Statement select_stmt;
  select_stmt.kind = STATEMENT_SELECT;
  ExecuteResult result = exec_statement(&select_stmt, table);

  assert(result == EXECUTE_SUCCESS);

  fflush(stdout);
  fclose(stream);
  stdout = fdopen(dup(fileno(stdout)), "w");

  assert(strcmp(buffer, "row[0]: `whyneet` `whyneet@example.com`\n") == 0);

  free_table(table);
}

void test_table_operations_errors() {
  Table *table = new_table();

  for (uint32_t i = 0; i < TABLE_MAX_ROWS; i++) {
    Row row;
    row.id = i;
    strcpy(&row.username, "whyneet");
    strcpy(&row.email, "whyneet@example.com");
    Statement insert_stmt;
    insert_stmt.kind = STATEMENT_INSERT;
    insert_stmt.row_to_insert = row;
    ExecuteResult result = exec_statement(&insert_stmt, table);
    assert(result == EXECUTE_SUCCESS);
  }

  Row row;
  row.id = 9999;
  strcpy(&row.username, "whyneet");
  strcpy(&row.email, "whyneet@example.com");
  Statement insert_stmt;
  insert_stmt.kind = STATEMENT_INSERT;
  insert_stmt.row_to_insert = row;
  ExecuteResult result = exec_statement(&insert_stmt, table);
  assert(result == EXECUTE_TABLE_FULL);
}

int main() {
  test_table_operations();
  test_table_operations_errors();
  return 0;
}