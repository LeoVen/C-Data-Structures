/**
 * @file SparseMatrix.h
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 02/05/2018
 *
 * @brief Test Cases for @c SparseMatrix implementations in C
 *
 */

#include "..\Headers\SparseMatrix.h"

int SparseMatrixTests()
{
	printf("\n");
	printf(" +-------------------------------------+\n");
	printf(" |                                     |\n");
	printf(" |           C Sparse Matrix           |\n");
	printf(" |                                     |\n");
	printf(" +-------------------------------------+\n");
	printf("\n");

	SparseMatrix spm;

	spm_init_matrix(&spm);



	printf("\n");
	return 0;
}