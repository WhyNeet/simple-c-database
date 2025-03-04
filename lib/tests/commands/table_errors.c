#include "lib/commands.h"
#include "lib/row.h"
#include "lib/table.h"
#include "lib/table_ops.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_table_full_error() {
  Table *table = db_open("test_full_db");

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

  db_close(table);
}

int main() {
  test_table_full_error();

  return 0;
}