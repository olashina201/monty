#include "stack.h"
#include <stdlib.h>

/**
 * stack_top - get the latest stack node
 * @stack: pointer to the stack head
 * Return: the address of the node otherwise NULL on fail
 */
stack_t *stack_top(stack_t **stack)
{
	stack_t *curr;

	if (!stack)
		return (NULL);
	curr = *stack;
	while (curr && curr->next)
		curr = curr->next;
	return (curr);
}

/**
 * stack_push - push a new value to the stack
 * @stack: pointer to the stack head
 * @n: the value to push
 * Return: the address to the new stack node
 */
stack_t *stack_push(stack_t **stack, int n)
{
	stack_t *prev, *node;

	if (!stack)
		return (NULL);

	node = malloc(sizeof(stack_t));
	if (!node)
		return (NULL);
	node->n = n;
	node->next = NULL;
	node->prev = NULL;

	prev = stack_top(stack);
	if (!prev)
		*stack = node;
	else
		prev->next = node;
	node->prev = prev;
	return (node);
}

/**
 * stack_pop - pop a node from the end of the stack
 * @stack: pointer to the head of the stack
 *
 * Description:
 * Don't forget to free the node
 *
 * Return: address of the node otherwise NULL on fail
 */
stack_t *stack_pop(stack_t **stack)
{
	stack_t *node;

	if (!stack)
		return (NULL);
	node = stack_top(stack);
	if (!node)
		return (NULL);
	if (node->prev)
	{
		node->prev->next = NULL;
		node->prev = NULL;
	}
	else
		*stack = NULL;
	return (node);
}

/**
 * stack_free - free the stack
 * @stack: pointer to the stack head node
 */
void stack_free(stack_t **stack)
{
	stack_t *curr, *next;

	if (!stack)
		return;
	curr = *stack;
loop:
	if (!curr)
		return;
	next = curr->next;
	free(curr);
	curr = next;
	goto loop;
}
