#include "monty.h"
#include "opcodes.h"
#include "reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

__attribute__((noreturn)) void mainloop(void);

/**
 * runner - the core function to execute opcodes
 */
void runner(void)
{
	CTX_DEC;
	int i, len;
	instruction_t instructions[] = {
		{ "push", push_opcode }, { "pall", pall_opcode }, { "pint", pint_opcode },
		{ "pop", pop_opcode }, { "swap", swap_opcode }, { "add", add_opcode },
		{ "sub", sub_opcode }, { "div", div_opcode }, { "mul", mul_opcode },
		{ "mod", mod_opcode }, { "pchar", pchar_opcode }, { "pstr", pstr_opcode },
		{ "rotl", rotl_opcode }, { "rotr", rotr_opcode },
		{ "stack", stack_opcode }, { "queue", queue_opcode },
		{ "nop", nop_opcode }, { NULL, NULL },
	};

	/*
	 * printf("%lu: %s(%d)\n", ctx->line_number, CTX_CMD.opcode, CTX_CMD.value);
	 */
	len = strlen(CTX_CMD.opcode);
	for (i = 0; instructions[i].opcode; i++)
		if (!strncmp(instructions[i].opcode, CTX_CMD.opcode, len))
		{
			instructions[i].f(&ctx->stack, ctx->line_number);
			return;
		}

	monty_destroy("L%lu: unknown instruction %s\n",
							 ctx->line_number, CTX_CMD.opcode);
}

/**
 * mainloop - the main interpreter loop to read line by line and execute them
 */
void mainloop(void)
{
	ssize_t readstate = 0;

loop:
	fflush(stdout);
	readstate = readline();
	if (readstate == T_EMPTY)
		goto loop;
	else if (readstate == T_EOF)
		goto end;
	else if (readstate == T_ERR)
		monty_destroy("Error: malloc failed\n");
	else if (T_HAS_DATA(readstate))
		runner();
	goto loop;
end:
	context_destroy();
	exit(EXIT_SUCCESS);
}

/**
 * main - Monty language bytecodes interpreter
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: exit status code
 */
int main(int argc, char **argv)
{
	char *filepath = NULL;
	context_t *ctx;

	/* make sure to initialize the context object to hold the state */
	if (!context_init())
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	filepath = argv[1];
	ctx = CTX_LOAD; /* load context to store the file object */
	CTX_FILE = fopen(filepath, "r");
	if (!CTX_FILE)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filepath);
		exit(EXIT_FAILURE);
	}

	mainloop();
}
