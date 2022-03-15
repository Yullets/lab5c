//
// Created by Yulia on 13.03.2022.
//
#include "algorithm.h"

void inputArray_(int *a, size_t n) {
    for (size_t i = 0; i < n; i++)
        scanf("%d", &a[i]);
}

void outputArray_(int *a, size_t n) {
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void swap(void *a, void *b, size_t size) {
    for (size_t i = 0; i < size; i++) {
        char *pa = a + i;
        char *pb = b + i;

        char t = *pa;
        *pa = *pb;
        *pb = t;
    }
}

bool isOrdered(int *a, size_t n) {
    for (int i = 1; i < n; i++) {
        if (a[i - 1] > a[i])
            return false;
    }

    return true;
}

void generateRandomArray(int *a, size_t n) {
    srand(time(0));
    for (size_t i = 0; i < n; i++)
        a[i] = rand();
}

void generateOrderedArray(int *a, size_t n) {
    for (size_t i = 0; i < n; i++) {
        a[i] = i;
    }
}

void generateOrderedBackwards(int *a, size_t n) {
    int value = n - 1;
    for (size_t i = 0; i < n; i++) {
        a[i] = value--;
    }
}