#include "monty.h"
#include "opcodes.h"
#include <stdlib.h>

/**
 * add_opcode - adds the top most two elements of the stack
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void add_opcode(stack_t **stack, unsigned int UNUSE line_number)
{
	stack_t *a, *b;

	a = stack_pop(stack);
	b = stack_top(stack);
	if (!a || !b)
		monty_exit_msg("can't add, stack too short");
	b->n += a->n;
	free(a);
}

/**
 * sub_opcode - subtracts the second top element of the stack by the top one
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void sub_opcode(stack_t **stack, unsigned int UNUSE line_number)
{
	stack_t *a, *b;

	a = stack_pop(stack);
	b = stack_top(stack);
	if (!a || !b)
		monty_exit_msg("can't sub, stack too short");
	b->n -= a->n;
	free(a);
}

/**
 * mul_opcode - multplies the second top element of the stack by the top one
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void mul_opcode(stack_t **stack, unsigned int UNUSE line_number)
{
	stack_t *a, *b;

	a = stack_pop(stack);
	b = stack_top(stack);
	if (!a || !b)
		monty_exit_msg("can't mul, stack too short");
	b->n *= a->n;
	free(a);
}

/**
 * div_opcode - divides the second top element of the stack by the top one
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void div_opcode(stack_t **stack, unsigned int UNUSE line_number)
{
	stack_t *a, *b;

	a = stack_pop(stack);
	b = stack_top(stack);
	if (!a || !b)
		monty_exit_msg("can't div, stack too short");
	if (!a->n)
	{
		free(a);
		monty_exit_msg("division by zero");
	}
	b->n /= a->n;
	free(a);
}

/**
 * mod_opcode - calculates the division remaining of
 * the second top element of the stack divided by the top one
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void mod_opcode(stack_t **stack, unsigned int UNUSE line_number)
{
	stack_t *a, *b;

	a = stack_pop(stack);
	b = stack_top(stack);
	if (!a || !b)
		monty_exit_msg("can't mod, stack too short");
	if (!a->n)
	{
		free(a);
		monty_exit_msg("division by zero");
	}
	b->n %= a->n;
	free(a);
}
