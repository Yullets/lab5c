//
// Created by Yulia on 12.03.2022.
//

#ifndef INC_5C_SORTFUNCTIONS_H
#define INC_5C_SORTFUNCTIONS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define TIME_TEST(testCode, time) { \
    clock_t start_time = clock(); \
    testCode \
        clock_t end_time = clock();\
    clock_t sort_time = end_time - start_time; \
    time = (double) sort_time / CLOCKS_PER_SEC; \
}

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

typedef struct SortFunc {
    void (*sort)(int *a, size_t n);

    char name[64];
} SortFunc;

typedef struct GeneratingFunc {
    void (*generate)(int *a, size_t n);

    char name[64];
} GeneratingFunc;

double getTime();

void checkTime(void (*sortFunc)(int *, size_t),
               void (*generateFunc)(int *, size_t),
               size_t size, char *experimentName);

void timeExperiment();

void bubbleSort(int *a, size_t n);

int getMinIndex(const int *a, size_t n);

void selectionSort_(int *unsortedPart, size_t nUnsorted);

void selectionSort(int *a, size_t n);

void insertionSort(int *a, size_t n);

void combSort(int *a, size_t n);

void shellSort(int *a, size_t n);

void getPrefSum(int *a, size_t n);

void digitSort(int *a, size_t n);

#endif //INC_5C_SORTFUNCTIONS_H
