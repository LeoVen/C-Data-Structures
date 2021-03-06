/**
 * @file DynamicArray.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 20/03/2018
 *
 * @brief Source file for @c DynamicArray implementations in C
 *
 */

#include "DynamicArray.h"

// +-------------------------------------------------------------------------------------------------+
// |                                          Initializers                                           |
// +-------------------------------------------------------------------------------------------------+

Status dar_init(DynamicArray **dar)
{
	(*dar) = malloc(sizeof(DynamicArray));

	if (!(*dar))
		return DS_ERR_ALLOC;

	(*dar)->buffer = calloc(DYNAMIC_ARRAY_INIT_SIZE, sizeof(int));

	if (!((*dar)->buffer))
		return DS_ERR_ALLOC;

	(*dar)->capacity = DYNAMIC_ARRAY_INIT_SIZE;
	(*dar)->growth_rate = DYNAMIC_ARRAY_GROW_RATE;

	(*dar)->size = 0;

	return DS_OK;
}

Status dar_make(DynamicArray **dar, int *array, size_t arr_size)
{
	Status st = dar_init(dar);

	if (st != DS_OK)
		return st;

	size_t i;
	for (i = 0; i < arr_size; i++)
	{
		st = dar_insert_back((*dar), array[i]);

		if (st != DS_OK)
			return st;
	}

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                            Insertion                                            |
// +-------------------------------------------------------------------------------------------------+

Status dar_insert(DynamicArray *dar, int *array, size_t arr_size, size_t index)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (index > dar->size)
		return DS_ERR_INVALID_POSITION;

	Status st;

	while (!dar_fits(dar, arr_size))
	{
		st = dar_realloc(dar);

		if (st != DS_OK)
			return st;
	}

	for (size_t i = dar->size; i > index; i--)
	{
		dar->buffer[i + arr_size - 1] = dar->buffer[i - 1];
	}

	for (size_t i = index, j = 0; j < arr_size; i++, j++)
	{
		dar->buffer[i] = array[j];
	}

	dar->size += arr_size;

	return DS_OK;
}

Status dar_insert_front(DynamicArray *dar, int value)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_full(dar))
	{
		Status st = dar_realloc(dar);

		if (st != DS_OK)
			return st;
	}

	size_t i;
	for (i = dar->size; i > 0; i--)
	{
		dar->buffer[i] = dar->buffer[i - 1];
	}

	dar->buffer[0] = value;

	(dar->size)++;

	return DS_OK;
}

Status dar_insert_at(DynamicArray *dar, int value, size_t index)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (index > dar->size)
		return DS_ERR_INVALID_POSITION;

	Status st;

	if (index == 0)
	{
		st = dar_insert_front(dar, value);

		if (st != DS_OK)
			return st;
	}
	else if (index == dar->size)
	{
		st = dar_insert_back(dar, value);

		if (st != DS_OK)
			return st;
	}
	else
	{
		if (dar_is_full(dar))
		{
			st = dar_realloc(dar);

			if (st != DS_OK)
				return st;
		}

		size_t i;
		for (i = dar->size; i > index; i--)
		{
			dar->buffer[i] = dar->buffer[i - 1];
		}

		dar->buffer[index] = value;

		(dar->size)++;
	}

	return DS_OK;
}

Status dar_insert_back(DynamicArray *dar, int value)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_full(dar))
	{
		Status st = dar_realloc(dar);

		if (st != DS_OK)
			return st;
	}

	dar->buffer[dar->size] = value;

	(dar->size)++;

	return DS_OK;
}

Status dar_update(DynamicArray *dar, int value, size_t index)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	if (index >= dar->size)
		return DS_ERR_INVALID_POSITION;

	dar->buffer[index] = value;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Removal                                             |
// +-------------------------------------------------------------------------------------------------+

Status dar_remove(DynamicArray *dar, size_t from, size_t to)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (from > to)
		return DS_ERR_INVALID_ARGUMENT;

	if (to >= dar->size)
		return DS_ERR_INVALID_POSITION;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	Status st;

	// 'from' and 'to' are inclusive
	size_t distance = to - from + 1;

	if (from == to)
	{
		st = dar_remove_at(dar, from);

		if (st != DS_OK)
			return st;

		return DS_OK;
	}
	else if (to == dar->size - 1)
	{
		dar->size -= distance;

		return DS_OK;
	}

	for (size_t i = from, j = to + 1; j <= dar->size - 1; i++, j++)
	{
		dar->buffer[i] = dar->buffer[j];
	}

	dar->size -= distance;

	return DS_OK;
}

Status dar_remove_front(DynamicArray *dar)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		dar->buffer[i] = dar->buffer[i + 1];
	}

	(dar->size)--;

	return DS_OK;
}

Status dar_remove_at(DynamicArray *dar, size_t index)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	if (index >= dar->size)
		return DS_ERR_INVALID_POSITION;

	Status st;

	if (index == 0)
	{
		st = dar_remove_front(dar);

		if (st != DS_OK)
			return st;
	}
	else if (index == dar->size - 1)
	{
		st = dar_remove_back(dar);

		if (st != DS_OK)
			return st;
	}
	else
	{
		size_t i;
		for (i = index; i < dar->size; i++)
		{
			dar->buffer[i] = dar->buffer[i + 1];
		}

		(dar->size)--;
	}

	return DS_OK;
}

Status dar_remove_back(DynamicArray *dar)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	(dar->size)--;

	return DS_OK;
}

Status dar_remove_keys(DynamicArray *dar, int value)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	Status st;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (dar->buffer[i] == value)
		{
			st = dar_remove_at(dar, i);

			if (st != DS_OK)
				return st;

			i--;
		}
	}

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Display                                             |
// +-------------------------------------------------------------------------------------------------+

Status dar_display(DynamicArray *dar)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar->size == 0)
	{

		printf("\n[ Empty ] \n");

		return DS_OK;
	}

	printf("\nDynamicArray\n[ ");

	size_t i;
	for (i = 0; i < dar->size - 1; i++)
	{

		printf("%d, ", dar->buffer[i]);
	}

	printf("%d", dar->buffer[dar->size - 1]);

	printf(" ]\n");

	return DS_OK;
}

Status dar_display_raw(DynamicArray *dar)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	printf("\n");

	if (dar_is_empty(dar))
		return DS_OK;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{

		printf("%d ", dar->buffer[i]);
	}

	printf("\n");

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Resets                                              |
// +-------------------------------------------------------------------------------------------------+

Status dar_delete(DynamicArray **dar)
{
	if (*dar == NULL)
		return DS_ERR_NULL_POINTER;

	free((*dar)->buffer);
	free((*dar));

	(*dar) = NULL;

	return DS_OK;
}

Status dar_erase(DynamicArray **dar)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	Status st = dar_delete(dar);

	if (st != DS_OK)
		return st;

	st = dar_init(dar);

	if (st != DS_OK)
		return st;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Search                                              |
// +-------------------------------------------------------------------------------------------------+

Status dar_get(DynamicArray *dar, size_t index, int *result)
{
	*result = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	if (index >= dar->size)
		return DS_ERR_INVALID_POSITION;

	*result = dar->buffer[index];

	return DS_OK;
}

size_t dar_cap(DynamicArray *dar)
{
	return dar->capacity;
}

size_t dar_size(DynamicArray *dar)
{
	return dar->size;
}

bool dar_is_empty(DynamicArray *dar)
{
	return dar->size == 0;
}

bool dar_is_full(DynamicArray *dar)
{
	return dar->size == dar->capacity;
}

bool dar_fits(DynamicArray *dar, size_t size)
{
	return (dar->size + size) <= dar->capacity;
}

Status dar_find_max(DynamicArray *dar, int *result)
{
	*result = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	*result = dar->buffer[0];

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (dar->buffer[i] > *result)
			*result = dar->buffer[i];
	}

	return DS_OK;
}

Status dar_find_min(DynamicArray *dar, int *result)
{
	*result = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	*result = dar->buffer[0];

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (dar->buffer[i] < *result)
			*result = dar->buffer[i];
	}

	return DS_OK;
}

Status dar_find_max_pos(DynamicArray *dar, size_t *result)
{
	*result = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (dar->buffer[i] > dar->buffer[(*result)])
			*result = i;
	}

	return DS_OK;
}

Status dar_find_min_pos(DynamicArray *dar, size_t *result)
{
	*result = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (dar->buffer[i] < dar->buffer[(*result)])
			*result = i;
	}

	return DS_OK;
}

Status dar_frequency(DynamicArray *dar, int value, size_t *frequency)
{
	*frequency = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (dar->buffer[i] == value)
			(*frequency)++;
	}

	return DS_OK;
}

Status dar_contains(DynamicArray *dar, int value, bool *result)
{
	*result = false;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (dar->buffer[i] == value)
		{
			*result = true;

			return DS_OK;
		}
	}

	return DS_OK;
}

bool dar_exists(DynamicArray *dar, int value)
{
	if (dar == NULL)
		return false;

	if (dar_is_empty(dar))
		return false;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (dar->buffer[i] == value)
			return true;
	}

	return false;
}

Status dar_find_occurrance_first(DynamicArray *dar, int value, size_t *position)
{
	*position = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		if (dar->buffer[i] == value)
		{
			*position = i;

			return DS_OK;
		}
	}

	return DS_ERR_NOT_FOUND;
}

Status dar_find_occurrance_last(DynamicArray *dar, int value, size_t *position)
{
	*position = 0;

	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar))
		return DS_ERR_INVALID_OPERATION;

	size_t i;
	for (i = dar->size; i > 0; i--)
	{
		if (dar->buffer[i] == value)
		{
			*position = i;

			return DS_OK;
		}
	}

	return DS_ERR_NOT_FOUND;
}

// +-------------------------------------------------------------------------------------------------+
// |                                             Copy                                                |
// +-------------------------------------------------------------------------------------------------+

Status dar_copy(DynamicArray *dar, DynamicArray **result)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	Status st = dar_init(result);

	if (st != DS_OK)
		return st;

	if (dar_is_empty(dar))
		return DS_OK;

	while (!dar_fits(*result, dar->size))
	{
		st = dar_realloc(*result);

		if (st != DS_OK)
			return st;
	}

	size_t i;
	for (i = 0; i < dar->size; i++)
	{
		(*result)->buffer[i] = dar->buffer[i];
	}

	(*result)->size = dar->size;

	return DS_OK;
}

//Status dar_merge_sorted(DynamicArray *dar1, DynamicArray *dar2, DynamicArray **result);

Status dar_prepend(DynamicArray *dar1, DynamicArray *dar2)
{
	if (dar1 == NULL || dar2 == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar2))
		return DS_OK;

	Status st;

	while (!dar_fits(dar1, dar2->size))
	{
		st = dar_realloc(dar1);

		if (st != DS_OK)
			return st;
	}

	size_t i;
	for (i = dar1->size; i > 0; i--)
	{
		dar1->buffer[i + dar2->size - 1] = dar1->buffer[i - 1];
	}

	for (i = 0; i < dar2->size; i++)
	{
		dar1->buffer[i] = dar2->buffer[i];
	}

	dar1->size += dar2->size;

	return DS_OK;
}

Status dar_add(DynamicArray *dar1, DynamicArray *dar2, size_t index)
{
	if (dar1 == NULL || dar2 == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar2))
		return DS_OK;

	Status st;

	if (index == dar1->size)
	{
		st = dar_append(dar1, dar2);

		if (st != DS_OK)
			return st;
	}
	else if (index == 0)
	{
		st = dar_prepend(dar1, dar2);

		if (st != DS_OK)
			return st;
	}
	else
	{
		while (!dar_fits(dar1, dar2->size))
		{
			st = dar_realloc(dar1);

			if (st != DS_OK)
				return st;
		}

		size_t i, j;
		for (i = dar1->size; i >= index; i--)
		{
			dar1->buffer[i + dar2->size] = dar1->buffer[i];
		}

		for (i = index, j = 0; i < index + dar2->size; i++, j++)
		{
			dar1->buffer[i] = dar2->buffer[j];
		}

		dar1->size += dar2->size;

	}

	return DS_OK;
}

Status dar_append(DynamicArray *dar1, DynamicArray *dar2)
{
	if (dar1 == NULL || dar2 == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar_is_empty(dar2))
		return DS_OK;

	Status st;

	while (!dar_fits(dar1, dar2->size))
	{
		st = dar_realloc(dar1);

		if (st != DS_OK)
			return st;
	}

	size_t i, j;
	for (i = dar1->size, j = 0; i < dar1->size + dar2->size - 1; i++, j++)
	{
		dar1->buffer[i] = dar2->buffer[j];
	}

	dar1->size += dar2->size;

	return DS_OK;
}

// +-------------------------------------------------------------------------------------------------+
// |                                           Sorting                                               |
// +-------------------------------------------------------------------------------------------------+

//Status dar_is_sorted(DynamicArray *dar, bool *result)
//Status dar_reverse(DynamicArray *dar)
//Status dar_sort_bubble(DynamicArray *dar)
//Status dar_sort_selection(DynamicArray *dar)
//Status dar_sort_insertion(DynamicArray *dar)

// +-------------------------------------------------------------------------------------------------+
// |                                            Buffer                                               |
// +-------------------------------------------------------------------------------------------------+

Status dar_grow(DynamicArray *dar, size_t size)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	if (dar->capacity >= size)
		return DS_OK;

	size_t temp_cap = dar->capacity;

	while (dar->capacity < size)
	{
		dar->capacity *= dar->growth_rate;
	}

	int *new_buffer = realloc(dar->buffer, sizeof(int) * dar->capacity);

	if (!new_buffer)
	{
		dar->capacity = temp_cap;

		return DS_OK;
	}

	dar->buffer = new_buffer;

	return DS_OK;
}

Status dar_realloc(DynamicArray *dar)
{
	if (dar == NULL)
		return DS_ERR_NULL_POINTER;

	dar->capacity *= dar->growth_rate;

	int *new_buffer = realloc(dar->buffer, sizeof(int) * dar->capacity);

	if (!new_buffer)
	{
		dar->capacity /= dar->growth_rate;

		return DS_ERR_ALLOC;
	}

	dar->buffer = new_buffer;

	return DS_OK;
}
