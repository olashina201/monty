#ifndef __STACK_H__
#define __STACK_H__

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

stack_t *stack_top(stack_t **stack);
stack_t *stack_push(stack_t **stack, int n);
stack_t *stack_pop(stack_t **stack);
void stack_free(stack_t **stack);

#endif
