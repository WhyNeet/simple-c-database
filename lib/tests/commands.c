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
  exec_statement(&select_stmt, table);

  fflush(stdout);
  fclose(stream);

  assert(strcmp(buffer, "row[0]: `whyneet` `whyneet@example.com`\n") == 0);
}

int main() {
  test_table_operations();
  return 0;
}