#ifndef COMMANDS_H
#define COMMANDS_H

#include "io.h"
#include "row.h"

typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum {
  PREPARE_SUCCESS,
  PREPARE_UNRECOGNIZED_STATEMENT,
  PREPARE_SYNTAX_ERROR
} PrepareResult;

MetaCommandResult exec_meta_command(InputBuffer *input_buffer);

typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementKind;
typedef struct {
  StatementKind kind;
  Row row_to_insert;
} Statement;

PrepareResult prepare_statement(InputBuffer *input_buffer,
                                Statement *statement);

void exec_statement(Statement *statement);

#endif
