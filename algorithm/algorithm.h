//
// Created by Yulia on 13.03.2022.
//

#ifndef INC_5C_ALGORITHM_H
#define INC_5C_ALGORITHM_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

void inputArray_(int *a,size_t n);

void outputArray_(int *a,size_t n);

void swap(void *a, void *b, size_t size);

bool isOrdered(int *a, size_t n);

void generateRandomArray(int *a, size_t n);

void generateOrderedArray(int *a, size_t n);

void generateOrderedBackwards(int *a, size_t n);

#endif //INC_5C_ALGORITHM_H
