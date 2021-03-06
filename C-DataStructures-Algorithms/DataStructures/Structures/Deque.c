/**
 * @file Deque.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 09/05/2018
 *
 * @brief Source file for @c Deque implementations in C
 *
 */

#include "Deque.h"

// +-------------------------------------------------------------------------------------------------+
// |                                          Initializers                                           |
// +-------------------------------------------------------------------------------------------------+

Status deq_init_queue(Deque **deq)
{
	(*deq) = malloc(sizeof(Deque));

	if (!(*deq))
		return DS_ERR_ALLOC;

	(*deq)->length = 0;

	(*deq)->front = NULL;
	(*deq)->rear = NULL;

	return DS_OK;
}

Status deq_init_node(DequeNode **node)
{
	(*node) = malloc(sizeof(DequeNode));

	if (!(*node))
		return DS_ERR_ALLOC;

	(*node)->data = 0;

	(*node)->prev = NULL;
	(*node)->next = NULL;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                            Getters                                              |
// +-------------------------------------------------------------------------------------------------+

Status deq_make_node(DequeNode **node, int value)
{
	(*node) = malloc(sizeof(DequeNode));

	if (!(*node))
		return DS_ERR_ALLOC;

	(*node)->data = value;

	(*node)->prev = NULL;
	(*node)->next = NULL;

	return DS_OK;
}

Status deq_get_length(Deque *deq, size_t *result)
{
	*result = 0;

	if (deq == NULL)
		return DS_ERR_NULL_POINTER;

	if (deq_is_empty(deq))
		return DS_ERR_INVALID_OPERATION;

	DequeNode *scan = deq->rear;

	while (scan != NULL)
	{
		(*result)++;

		scan = scan->next;
	}

	if ((*result) != deq->length)
		return DS_ERR_UNEXPECTED_RESULT;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                            Insertion                                            |
// +-------------------------------------------------------------------------------------------------+

Status deq_enqueue_front(Deque *deq, int value)
{
	if (deq == NULL)
		return DS_ERR_NULL_POINTER;

	DequeNode *node;

	deq_make_node(&node, value);

	if (!node)
		return DS_ERR_ALLOC;

	if (deq_is_empty(deq))
	{

		deq->front = node;
		deq->rear = node;
	}
	else
	{

		node->prev = deq->front;

		deq->front->next = node;
		deq->front = node;
	}

	(deq->length)++;

	return DS_OK;
}

Status deq_enqueue_rear(Deque *deq, int value)
{

	if (deq == NULL)
		return DS_ERR_NULL_POINTER;

	DequeNode *node;

	deq_make_node(&node, value);

	if (!node)
		return DS_ERR_ALLOC;

	if (deq_is_empty(deq))
	{

		deq->front = node;
		deq->rear = node;
	}
	else
	{

		node->next = deq->rear;

		deq->rear->prev = node;
		deq->rear = node;
	}

	(deq->length)++;

	return DS_OK;
}

Status deq_enqueue_front_node(Deque *deq, DequeNode *node)
{
	if (deq == NULL)
		return DS_ERR_NULL_POINTER;

	if (deq_is_empty(deq))
	{

		deq->front = node;
		deq->rear = node;
	}
	else
	{

		node->prev = deq->front;

		deq->front->next = node;
		deq->front = node;
	}

	(deq->length)++;

	return DS_OK;
}

Status deq_enqueue_rear_node(Deque *deq, DequeNode *node)
{
	if (deq == NULL)
		return DS_ERR_NULL_POINTER;

	if (deq_is_empty(deq))
	{

		deq->front = node;
		deq->rear = node;
	}
	else
	{

		node->next = deq->rear;

		deq->rear->prev = node;
		deq->rear = node;
	}

	(deq->length)++;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Removal                                             |
// +-------------------------------------------------------------------------------------------------+

Status deq_dequeue_front(Deque *deq)
{
	if (deq == NULL)
		return DS_ERR_NULL_POINTER;

	if (deq_is_empty(deq))
		return DS_ERR_INVALID_OPERATION;

	DequeNode *node = deq->front;

	deq->front = deq->front->prev;

	if (deq->front == NULL)
		deq->rear = NULL;
	else
		deq->front->next = NULL;

	free(node);

	(deq->length)--;

	return DS_OK;
}

Status deq_dequeue_rear(Deque *deq)
{
	if (deq == NULL)
		return DS_ERR_NULL_POINTER;

	if (deq_is_empty(deq))
		return DS_ERR_INVALID_OPERATION;

	DequeNode *node = deq->rear;

	deq->rear = deq->rear->next;

	if (deq->rear == NULL)
		deq->front = NULL;
	else
		deq->rear->prev = NULL;

	free(node);

	(deq->length)--;

	return DS_OK;
}

Status deq_dequeue_front_node(Deque *deq, DequeNode **result)
{
	if (deq == NULL)
		return DS_ERR_NULL_POINTER;

	if (deq_is_empty(deq))
		return DS_ERR_INVALID_OPERATION;

	(*result) = deq->front;

	deq->front = deq->front->prev;

	if (deq->front == NULL)
		deq->rear = NULL;
	else
		deq->front->next = NULL;

	(*result)->next = NULL;
	(*result)->prev = NULL;

	(deq->length)--;

	return DS_OK;
}

Status deq_dequeue_rear_node(Deque *deq, DequeNode **result)
{
	if (deq == NULL)
		return DS_ERR_NULL_POINTER;

	if (deq_is_empty(deq))
		return DS_ERR_INVALID_OPERATION;

	(*result) = deq->rear;

	deq->rear = deq->rear->next;

	if (deq->rear == NULL)
		deq->front = NULL;
	else
		deq->rear->prev = NULL;

	(*result)->next = NULL;
	(*result)->prev = NULL;

	(deq->length)--;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Display                                             |
// +-------------------------------------------------------------------------------------------------+

Status deq_display(Deque *deq)
{
	if (deq == NULL)
		return DS_ERR_NULL_POINTER;

	if (deq_is_empty(deq))
	{

		printf("\nDeque\n[ empty ]\n");
		return DS_OK;
	}

	DequeNode *scan = deq->front;

	printf("\nDeque\nfront <->");

	while (scan != NULL)
	{
		printf(" %d <->", scan->data);
		scan = scan->prev;
	}

	printf(" rear\n");

	return DS_OK;
}

Status deq_display_raw(Deque *deq)
{
	if (deq == NULL)
		return DS_ERR_NULL_POINTER;

	printf("\n");

	if (deq_is_empty(deq))
		return DS_ERR_INVALID_OPERATION;

	DequeNode *scan = deq->front;

	while (scan != NULL)
	{
		printf("%d ", scan->data);
		scan = scan->prev;
	}

	printf("\n");

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Resets                                              |
// +-------------------------------------------------------------------------------------------------+

Status deq_delete_node(DequeNode **node)
{
	free(*node);

	(*node) = NULL;

	return DS_OK;
}

Status deq_delete_queue(Deque **deq)
{
	if ((*deq) == NULL)
		return DS_ERR_NULL_POINTER;

	DequeNode *prev = (*deq)->front;

	while ((*deq)->front != NULL)
	{
		(*deq)->front = (*deq)->front->prev;

		free(prev);

		prev = (*deq)->front;
	}

	free((*deq));

	(*deq) = NULL;

	return DS_OK;
}

Status deq_erase_queue(Deque **deq)
{
	if ((*deq) == NULL)
		return DS_ERR_NULL_POINTER;

	Status st = deq_delete_queue(deq);

	if (st != DS_OK)
		return st;

	st = deq_init_queue(deq);

	if (st != DS_OK)
		return st;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Search                                              |
// +-------------------------------------------------------------------------------------------------+

Status deq_peek_front(Deque *deq, int *result)
{
	if (deq == NULL)
		return DS_ERR_NULL_POINTER;

	if (deq_is_empty(deq))
		return DS_ERR_INVALID_OPERATION;

	*result = deq->front->data;

	return DS_OK;
}

Status deq_peek_rear(Deque *deq, int *result)
{
	if (deq == NULL)
		return DS_ERR_NULL_POINTER;

	if (deq_is_empty(deq))
		return DS_ERR_INVALID_OPERATION;

	*result = deq->rear->data;

	return DS_OK;
}

size_t deq_length(Deque *deq)
{
	if (deq == NULL)
		return 0;

	return deq->length;
}

bool deq_is_empty(Deque *deq)
{
	return (deq->length == 0 || deq->rear == NULL);
}

Status deq_find_max(Deque *deq, int *result)
{
	*result = 0;

	if (deq == NULL)
		return DS_ERR_NULL_POINTER;

	if (deq_is_empty(deq))
		return DS_ERR_INVALID_OPERATION;

	DequeNode *scan = deq->front;

	*result = scan->data;
	while (scan != NULL)
	{
		if (scan->data < *result)
			*result = scan->data;

		scan = scan->prev;
	}

	return DS_OK;
}

Status deq_find_min(Deque *deq, int *result)
{
	*result = 0;

	if (deq == NULL)
		return DS_ERR_NULL_POINTER;

	if (deq_is_empty(deq))
		return DS_ERR_INVALID_OPERATION;

	DequeNode *scan = deq->front;

	*result = scan->data;
	while (scan != NULL)
	{
		if (scan->data < *result)
			*result = scan->data;

		scan = scan->prev;
	}

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Copy                                                |
// +-------------------------------------------------------------------------------------------------+

Status deq_copy_node(DequeNode *node, DequeNode **result)
{
	if (node == NULL)
		return DS_ERR_NULL_POINTER;

	Status st = deq_make_node(result, node->data);

	if (st != DS_OK)
		return st;

	return DS_OK;
}

Status deq_copy_queue(Deque *deq, Deque **result)
{
	*result = NULL;

	if (deq == NULL)
		return DS_ERR_NULL_POINTER;

	Status st = deq_init_queue(result);

	if (st != DS_OK)
		return st;

	if (deq_is_empty(deq))
		return DS_OK;

	DequeNode *scan = deq->front;

	while (scan != NULL)
	{
		st = deq_enqueue_rear(*result, scan->data);

		if (st != DS_OK)
			return st;

		scan = scan->prev;
	}

	return DS_OK;
}
