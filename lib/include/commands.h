#ifndef COMMANDS_H
#define COMMANDS_H

#include "io.h"

typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT } PrepareResult;

MetaCommandResult exec_meta_command(InputBuffer *input_buffer);

typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementKind;
typedef struct {
  StatementKind kind;
} Statement;

PrepareResult prepare_statement(InputBuffer *input_buffer,
                                Statement *statement);

void exec_statement(Statement *statement);

#endif
