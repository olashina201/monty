#include "reader.h"
#include "monty.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/**
 * resetline - resets the line and the cmd values to zeros and NULLs
 */
void resetline(void)
{
	CTX_DEC;

	if (!CTX_LINE)
		return;
	free(CTX_LINE);
	CTX_LINE = NULL;
	CTX_CMD.opcode = NULL;
	CTX_CMD.arg = NULL;
	CTX_CMD.value = 0;
}

/**
 * readline - read one line from the file, trim it then set ctx.line and return
 * its size or a state
 *
 * Description:
 * Reads the next line from the script file then trimming it
 * then allocates a fit memory for the new line and store it in ctx->line.
 *
 * Return States:
 * +ve value: line size
 * T_EMPTY: Empty
 * T_EOF: end of file
 * T_ERR: malloc error
 *
 * Return: 0 for empty, positive value for the size of the line or a state
 */
ssize_t readline(void)
{
	CTX_DEC;
	char buffer[BUFFER_SIZE], lc = 0, c = 0;
	size_t size = 0;

	resetline(); /* reset line if has value */
	for (c = fgetc(CTX_FILE); c != -1 && c != 10 && c != '#' &&
		size < BUFFER_SIZE; c = fgetc(CTX_FILE))
	{
		if ((!lc && isspace(c)) || (isspace(lc) && isspace(c)))
		{
			lc = c;
			continue; /* ignore waste chars */
		}
		buffer[size++] = c; /* write char to buffer */
		lc = c;
	}

	if (c == '#') /* handle comments, ignore chars until the end of the file */
		for (; c != -1 && c != 10; c = fgetc(CTX_FILE))
			continue;

	ctx->line_number++; /* count a line */
	if (c == -1 && !size)
		return (T_EOF); /* handle end of file case */
	if (!size)
		return (T_EMPTY); /* handle empty file case */

	/* allocate a new line */
	CTX_LINE = malloc(size + 1);
	if (!CTX_LINE)
		return (T_ERR);
	CTX_LINE[size] = 0; /* set NULL char at the end */
	/* copy bytes from buffer to the allocated line */
	memcpy(CTX_LINE, buffer, size);
	parseline(CTX_LINE, &CTX_CMD); /* parse arguments */
	return (size);
}

/**
 * parseline - parse command line into tokens
 * @line: the command line cstring
 * @cmd: the command object to fill with tokens
 * Return: 1 on success and 0 on fail
 */
int parseline(char *line, command_t *cmd)
{
	cmd->opcode = NULL;
	cmd->arg = NULL;
	cmd->value = 0;
	if (!line)
		return (0);

	cmd->opcode = strtok(line, " ");
	if (cmd->opcode)
		cmd->arg = strtok(NULL, " ");
	if (isadigit(cmd->arg))
	{
		if (cmd->arg[0] == '-')
			cmd->value = -(atoi(cmd->arg + 1));
		else
			cmd->value = atoi(cmd->arg);
	}
	else
		cmd->arg = NULL;
	return (1);
}

/**
 * isadigit - check if the cstring is a digit written in ascii form
 * @arg: the cstring
 * Return: 1 if true else 0
 */
int isadigit(char *arg)
{
	if (!arg)
		return (0);
	if (*arg == '-') /* is a start of a negative integer */
		arg++;
	for (; *arg; arg++)
		if (!isdigit(*arg))
			return (0);
	return (1);
}
