#ifndef __OPCODES_H__
#define __OPCODES_H__
#include "stack.h"

#define UNUSE __attribute__((unused))

typedef void (*opcodefun)(stack_t **stack, unsigned int line_number);

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/* opcodes1.c */
void push_opcode(stack_t **stack, unsigned int line_number);
void pall_opcode(stack_t **stack, unsigned int line_number);
void pint_opcode(stack_t **stack, unsigned int UNUSE line_number);
void pop_opcode(stack_t **stack, unsigned int UNUSE line_number);
void swap_opcode(stack_t **stack, unsigned int UNUSE line_number);
/* opcodes2.c */
void add_opcode(stack_t **stack, unsigned int UNUSE line_number);
void sub_opcode(stack_t **stack, unsigned int UNUSE line_number);
void mul_opcode(stack_t **stack, unsigned int UNUSE line_number);
void div_opcode(stack_t **stack, unsigned int UNUSE line_number);
void mod_opcode(stack_t **stack, unsigned int UNUSE line_number);
/* opcodes3.c */
void pchar_opcode(stack_t **stack, unsigned int UNUSE line_number);
void pstr_opcode(stack_t **stack, unsigned int UNUSE line_number);
void rotl_opcode(stack_t **stack, unsigned int UNUSE line_number);
void rotr_opcode(stack_t **stack, unsigned int UNUSE line_number);
/* opcodes4.c */
void stack_opcode(stack_t **stack, unsigned int UNUSE line_number);
void queue_opcode(stack_t **stack, unsigned int UNUSE line_number);
void nop_opcode(stack_t **stack, unsigned int UNUSE line_number);

#endif
