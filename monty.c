#include "monty.h"
#include <stdarg.h>
#include <stdlib.h>

/**
 * context_init - initialize the global context object
 * Return: 1 on success, 0 on fail
 */
int context_init(void)
{
	context_t *ctx;

	ctx = malloc(sizeof(context_t));
	if (!ctx)
		return (0);

	CTX_FILE = NULL;
	CTX_LINE = NULL;
	CTX_CMD.opcode = NULL;
	CTX_CMD.arg = NULL;
	ctx->stack = NULL;
	ctx->line_number = 0;
	ctx->data_behavior = B_STACK;
	CTX_SET(ctx);
	return (1);
}

/**
 * context_destroy - destroy the global context object
 */
void context_destroy(void)
{
	CTX_DEC;

	if (CTX_FILE)
		fclose(CTX_FILE);
	if (ctx->stack)
		stack_free(&ctx->stack);
	if (CTX_LINE)
		free(CTX_LINE);
	free(ctx);
}

/**
 * monty_exit_msg - end the interpreter with error message
 * @msg: the error message
 */
void monty_exit_msg(const char *msg)
{
	CTX_DEC;
	monty_destroy("L%lu: %s\n", ctx->line_number, msg);
}

/**
 * monty_destroy - free memory show error message and exit
 * @format: the printf format
 */
void monty_destroy(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);

	context_destroy();
	exit(EXIT_FAILURE);
}

/**
 * context_control - global context storage
 * @ctx: context object to store
 * @action: the storage action { A_SET, A_GET }
 *
 * Description:
 * An alternative solution for global variables
 *
 * To store an object set ctx to its address and set action to A_SET
 *
 * To restore an object set ctx to NULL and set action to A_GET
 *
 * Return: context object if action is A_GET and already an object stored
 * otherwise NULL
 */
context_t *context_control(context_t *ctx, action_t action)
{
	/* can not store static var with NULL or 0 */
	static context_t *cache;
	static int has_cache = -1; /* true = 1, false -1 */

	if (action == A_SET)
	{
		cache = ctx;
		has_cache = cache ? 1 : -1;
	}
	return (has_cache && action == A_GET ? cache : NULL);
}
