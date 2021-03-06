/**
 * @file StructureConversions.h
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 02/04/2018
 *
 * @brief Header file for Structure Conversion implementations in C
 *
 */

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "Core.h"
#include "DataStructures.h"

	// +-------------------------------------+
	// |              SLL -> X               |
	// +-------------------------------------+
	Status convert_sll_to_arr(SinglyLinkedList *sll, Array **array);

	Status convert_sll_to_darr(SinglyLinkedList *sll, DynamicArray **dar);

	Status convert_sll_to_dll(SinglyLinkedList *sll, DoublyLinkedList **dll);

	// +-------------------------------------+
	// |              DAR -> X               |
	// +-------------------------------------+

	Status convert_darr_to_sll(DynamicArray **dar, SinglyLinkedList **sll);

	// +-------------------------------------+
	// |              AAR -> X               |
	// +-------------------------------------+

	Status convert_arr_to_dar(Array *arr, DynamicArray **dar);

#ifdef __cplusplus
}
#endif