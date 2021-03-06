/**
 * @file StructureConversionsTests.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 02/04/2018
 *
 * @brief Test Cases for Structure Conversion implementations in C
 *
 * Here all functions are tested to assure that they operate as expected. Note
 * that not all test cases are performed.
 *
 */

#include "StructureConversions.h"

int StructureConversionsTests(void)
{
	printf("\n");
	printf(" +-------------------------------------+\n");
	printf(" |                                     |\n");
	printf(" |          C Conversion Tests         |\n");
	printf(" |                                     |\n");
	printf(" +-------------------------------------+\n");
	printf("\n");

	int i;
	SinglyLinkedList *sll;
	sll_init_list(&sll);

	for (i = 0; i < 10; i++)
		sll_insert_tail(sll, i);

	Array *array;
	status_repr(convert_sll_to_arr(sll, &array));

	arr_display(array);

	DynamicArray *darray;

	convert_sll_to_darr(sll, &darray);

	for (i = 0; i < 20; i++)
		dar_insert_back(darray, 99);

	dar_display(darray);

	sll_delete_list(&sll);

	convert_darr_to_sll(&darray, &sll);

	sll_display(sll);

	arr_delete(&array);

	convert_sll_to_arr(sll, &array);

	dar_delete(&darray);

	convert_arr_to_dar(array, &darray);

	for (i = 0; i < 5; i++)
		dar_insert_back(darray, 12);

	dar_display(darray);

	sll_delete_list(&sll);

	convert_darr_to_sll(&darray, &sll);

	sll_display(sll);

	DoublyLinkedList *dll;

	convert_sll_to_dll(sll, &dll);

	dll_display(dll);

	printf("\n");
	return 0;
}