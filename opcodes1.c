#include "monty.h"
#include "opcodes.h"
#include "reader.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * push_opcode - push value to the stack
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void push_opcode(stack_t **stack, unsigned int UNUSE line_number)
{
	CTX_DEC;

	if (!stack)
		return;

	if (!CTX_CMD.arg)
		monty_exit_msg("usage: push integer");

	stack_push(stack, CTX_CMD.value);
	if (ctx->data_behavior == B_QUEUE)
		rotl_opcode(stack, line_number);
}

/**
 * pall_opcode - print all values in the stack from top to bottom
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void pall_opcode(stack_t **stack, unsigned int UNUSE line_number)
{
	stack_t *curr;

	if (!stack)
		return;

	for (curr = stack_top(stack); curr; curr = curr->prev)
		printf("%d\n", curr->n);
}

/**
 * pint_opcode - print the value at the top of the stack
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void pint_opcode(stack_t **stack, unsigned int UNUSE line_number)
{
	stack_t *curr;

	curr = stack_top(stack);
	if (curr)
		printf("%d\n", curr->n);
	else
		monty_exit_msg("can't pint, stack empty");
}

/**
 * pop_opcode - removes the top element of the stack
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void pop_opcode(stack_t **stack, unsigned int UNUSE line_number)
{
	stack_t *curr;

	curr = stack_pop(stack);
	if (!curr)
		monty_exit_msg("can't pop an empty stack");
	free(curr);
}

/**
 * swap_opcode - swaps the top most two elements of the stack
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void swap_opcode(stack_t **stack, unsigned int UNUSE line_number)
{
	stack_t *curr;
	int n;

	curr = stack_top(stack);
	if (!curr || !curr->prev)
		monty_exit_msg("can't swap, stack too short");

	n = curr->n;
	curr->n = curr->prev->n;
	curr->prev->n = n;
}
