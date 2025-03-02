#include "lib/commands.h"
#include "lib/row.h"
#include "lib/table.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_database_persistence() {
  Table *table = new_table();

  Row row;
  row.id = 0;

  strcpy(&row.username, "whyneet");
  strcpy(&row.email, "whyneet@example.com");

  Statement insert_stmt;
  insert_stmt.kind = STATEMENT_INSERT;
  insert_stmt.row_to_insert = row;
  exec_statement(&insert_stmt, table);

  // same behavior ad with ".exit" meta command
  free_table(table);

  Table *table_2 = new_table();

  // capture the select statement output and redirect to a buffer
  char buffer[100];
  memset(buffer, 0, sizeof(buffer));
  FILE *stream = fmemopen(buffer, sizeof(buffer), "w");
  assert(stream != NULL);
  fflush(stdout);
  stdout = stream;

  Statement select_stmt;
  select_stmt.kind = STATEMENT_SELECT;
  ExecuteResult result = exec_statement(&select_stmt, table_2);

  assert(result == EXECUTE_SUCCESS);

  fflush(stdout);
  fclose(stream);
  stdout = fdopen(dup(fileno(stdout)), "w");

  assert(strcmp(buffer, "row[0]: `whyneet` `whyneet@example.com`\n") == 0);

  free_table(table);
}

int main() {
  test_database_persistence();
  return 0;
}