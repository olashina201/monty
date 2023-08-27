#ifndef __READER_H__
#define __READER_H__

#include <stdio.h>
#include <sys/types.h>

#define BUFFER_SIZE 100
#define T_EMPTY 0
#define T_EOF -1
#define T_ERR -2
#define T_HAS_DATA(state) ((state) > 0)

/**
 * struct command_s - the command line sections
 * @opcode: the opcode value
 * @arg: the opcode argument value if exist, if arg can't be casted to int then
 * its value is NULL
 * @value: integer casting for the argument if exist
 */
typedef struct command_s
{
	char *opcode, *arg;
	int value;
} command_t;

void resetline(void);
ssize_t readline(void);
int parseline(char *line, command_t *cmd);
int isadigit(char *arg);

#endif
