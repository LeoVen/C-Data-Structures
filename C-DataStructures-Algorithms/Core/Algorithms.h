/**
 * @file Algorithms.h
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 11/04/2018
 *
 * @brief Header to include all algorithms implementations
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "Core.h"
#include "Display.h"

#include "..\Algorithms\Cryptography\Cryptography.h"
#include "..\Algorithms\Generators\Generators.h"
#include "..\Algorithms\Mathematics\Mathematics.h"
#include "..\Algorithms\Sorting\Sorting.h"

	int AlgorithmsMenu(void);

#ifdef __cplusplus
}
#endif