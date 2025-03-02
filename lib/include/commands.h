#ifndef COMMANDS_H
#define COMMANDS_H

#include "io.h"
#include "row.h"
#include "table.h"

typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum {
  PREPARE_SUCCESS,
  PREPARE_UNRECOGNIZED_STATEMENT,
  PREPARE_SYNTAX_ERROR,
  PREPARE_STRING_TOO_LONG,
  PREPARE_NEGATIVE_ID
} PrepareResult;

MetaCommandResult exec_meta_command(InputBuffer *input_buffer, Table *table);

typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementKind;
typedef struct {
  StatementKind kind;
  Row row_to_insert;
} Statement;

PrepareResult prepare_statement(InputBuffer *input_buffer,
                                Statement *statement);

typedef enum { EXECUTE_SUCCESS, EXECUTE_TABLE_FULL } ExecuteResult;

ExecuteResult exec_statement(Statement *statement, Table *table);

#endif
