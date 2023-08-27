#include "monty.h"
#include "opcodes.h"


/**
 * stack_opcode - sets the behavior of the data to LIFO
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void stack_opcode(UNUSE stack_t **stack, unsigned int UNUSE line_number)
{
	CTX_DEC;

	ctx->data_behavior = B_STACK;
}

/**
 * queue_opcode - sets the behavior of the data to FIFO
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void queue_opcode(UNUSE stack_t **stack, unsigned int UNUSE line_number)
{
	CTX_DEC;

	ctx->data_behavior = B_QUEUE;
}

/**
 * nop_opcode - do no thing
 * @stack: pointer to the stack head
 * @line_number: the current line number
 */
void nop_opcode(UNUSE stack_t **stack, unsigned int UNUSE line_number)
{}
