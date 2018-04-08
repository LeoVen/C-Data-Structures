/**
 * @file SinglyLinkedListTests.c
 *
 * @author Leonardo Vencovsky
 * @date 14/03/2018
 *
 * @brief Test Cases for @c SinglyLinkedLists implementations in C
 *
 * Here all functions are tested to assure that they operate as expected. Note
 * that not all test cases are performed.
 *
 */

#include "..\Headers\SinglyLinkedList.h"

int SinglyLinkedListTests()
{
	printf("\n");
	printf(" +-------------------------------------+\n");
	printf(" |                                     |\n");
	printf(" |         C Singly Linked List        |\n");
	printf(" |                                     |\n");
	printf(" +-------------------------------------+\n");
	printf("\n");

	SinglyLinkedList *sll;
	if (sll_init_list(&sll) != DS_OK)
		printf("\nError");

	SinglyLinkedNode *node;
	if (sll_init_node(&node) != DS_OK)
		printf("\nError");

	node->data = 1;

	size_t len;

	if (sll_get_length(sll, &len) == DS_OK)
		printf("\nLength: %ld", (long)len);

	print_status_repr(sll_insert_head(sll, 2));
	print_status_repr(sll_insert_head(sll, 3));
	print_status_repr(sll_insert_head(sll, 4));

	if (sll_get_length(sll, &len) == DS_OK)
		printf("\nLength: %ld", (long)len);

	int res;

	print_status_repr(sll_get_node_data(sll, 1, &res));

	int i;
	size_t j;
	if (sll_get_length(sll, &j) == DS_OK) {
		for (i = 0; i < j; i++) {
			sll_get_node_data(sll, i, &res);
			printf("\nData of node at position %d = %d", i, res);
		}
	}

	print_status_repr(sll_insert_tail(sll, 3));
	print_status_repr(sll_insert_tail(sll, 4));
	print_status_repr(sll_insert_tail(sll, 5));
	
	print_status_repr(sll_insert_head(sll, 5));

	sll_display(sll);

	print_status_repr(sll_insert_at(sll, 2, 3));
	print_status_repr(sll_insert_at(sll, 1, 4));
	print_status_repr(sll_insert_at(sll, 1, 4));

	sll_display_raw(sll);

	int k;
	do {
		sll_get_node_data(sll, 0, &k);
		sll_remove_head(sll);
	} while (k != 1);

	sll_display(sll);

	size_t l;
	sll_get_length(sll, &l);
	while (l > 0)
	{
		sll_remove_tail(sll);
		sll_get_length(sll, &l);
	}

	sll_display(sll);

	for (i = 0; i < 100; i++) {
		sll_insert_tail(sll, i);
	}

	sll_display_raw(sll);

	k = 0;
	size_t p = 52;
	while (k < 70)
	{
		sll_get_node_data(sll, p, &k);
		sll_remove_at(sll, p);
	}

	sll_display_raw(sll);

	sll_delete_list(&sll);

	if (sll == NULL)
		printf("\nOK");

	sll_init_list(&sll);

	for (i = 0; i < 10; i++)
		sll_insert_tail(sll, i);

	sll_display(sll);

	sll_erase_list(&sll);

	sll_display(sll);

	int a = NULL;
	printf("\nNULL: %d", (int)a); // lol

	for (i = 0; i < 100; i++)
		sll_insert_tail(sll, rand() % 10);

	size_t f;
	for (i = -10; i < 20; i++) {
		if (sll_exists(sll, i)) {
			sll_frequency(sll, i, &f);
			printf("\nData %d frequency : %u", i, f);
		}
		else {
			printf("\nData %d is not in the list", i);
		}
	}

	sll_erase_list(&sll);

	for (i = 0; i < 100; i++) {
		sll_insert_tail(sll, i);
	}

	SinglyLinkedList *sll_even = NULL, *sll_odd = NULL;
	
	int data;

	if (sll_init_list(&sll_odd) == DS_OK && sll_init_list(&sll_even) == DS_OK) {
		sll_get_length(sll, &len);
		for (i = 0; i < len; i++) {
			sll_get_node_data(sll, 0, &data);
			if (data % 2 == 0) {
				sll_remove_node_head(sll, &node);
				sll_insert_node_tail(sll_even, node);
			}
			else {
				sll_remove_node_head(sll, &node);
				sll_insert_node_tail(sll_odd, node);
			}
		}
	}

	printf("\n");
	sll_display(sll);
	sll_display(sll_even);
	sll_display(sll_odd);


	free(node);
	free(sll);
	free(sll_even);
	free(sll_odd);
	printf("\n");
	return 0;
}