/**
 * @file CircularLinkedListTests.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 05/04/2018
 *
 * @brief Test Cases for @c CircularLinkedLists implementations in C
 *
 * Here all functions are tested to assure that they operate as expected. Note
 * that not all test cases are performed.
 *
 */

#include "..\Headers\CircularLinkedList.h"

int CircularLinkedListTests()
{
	printf("\n");
	printf(" +-------------------------------------+\n");
	printf(" |                                     |\n");
	printf(" |        C Circular Linked List       |\n");
	printf(" |                                     |\n");
	printf(" +-------------------------------------+\n");
	printf("\n");

	CircularLinkedList *cll;

	cll_init_list(&cll);

	CircularLinkedNode *cln;

	cll_init_node(&cln);

	if (0 == NULL)
		printf("\nTrue");

	int i;
	for (i = 0; i < 20; i++) {
		cll_insert_after(cll, i);
	}

	cll_display(cll);

	for (i = 0; i < 10; i++) {
		cll_remove_after(cll);
	}

	cll_display(cll);

	CircularLinkedList *jos;
	size_t k = 13, n = 40, result;
	if (cll_josephus(&jos, n, k, &result) == DS_OK)
		printf("\n Josephus (%zu, %zu) = %zu\n", n, k, result);

	cll_iter_before(cll);
	cll_display(cll);

	cll_iter_before(cll);
	cll_display(cll);

	cll_iter_before(cll);
	cll_display(cll);

	size_t cll_len;

	cll_get_length(cll, &cll_len);

	for (i = 0; i < cll_len; i++) {
		print_status_repr(cll_remove_current(cll));
		cll_display(cll);
	}

	cll_delete(&cll);

	printf("\n");
	return 0;
}