//
// Created by Yulia on 12.03.2022.
//
#include "sortFunctions.h"
#include "../algorithm/algorithm.h"

double getTime() {
    clock_t start_time = clock();
    clock_t end_time = clock();\
    clock_t sort_time = end_time - start_time;

    return (double) sort_time / CLOCKS_PER_SEC;
}

void checkTime(void (*sortFunc)(int *, size_t),
               void (*generateFunc)(int *, size_t),
               size_t size, char *experimentName) {
    static size_t runCounter = 1;

    // генерация последовательности
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);
    printf("Run #%zu| ", runCounter++);
    printf("Name: %s\n", experimentName);

    double time;
    TIME_TEST ({
                   sortFunc(innerBuffer, size);
               }, time);

    // результаты замера
    printf("Status: ");
    if (isOrdered(innerBuffer, size)) {
        printf("OK! Time : %.3f s.\n", time);

        // запись в файл
        char filename[256];
        sprintf(filename, "./data/%s.csv", experimentName);
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf("FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3f\n", size, time);
        fclose(f);
    } else {
        printf(" Wrong !\n");

        // вывод массива, который не смог быть отсортирован
        outputArray_(innerBuffer, size);

        exit(1);
    }
}

void timeExperiment() {
    SortFunc sorts[] = {
            {selectionSort, "selectionSort"},
            {insertionSort, "insertionSort"},
            {bubbleSort,    "bubbleSort"},
            {combSort,      "combSort"},
            {shellSort,     "shellSort"},
            {digitSort,     "digitSort"}
    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);

    GeneratingFunc generatingFuncs[] = {
            {generateRandomArray,      "random"},
            {generateOrderedArray,     "ordered"},
            {generateOrderedBackwards, "orderedBackwards"}
    };
    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

    for (size_t size = 10000; size <= 100000; size += 10000) {
        printf(" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf("Size: %d\n", size);
        for (int i = 0; i < FUNCS_N; i++) {
            for (int j = 0; j < CASES_N; j++) {
                static char filename[128];
                sprintf(filename, "%s_%s_time ",
                        sorts[i].name, generatingFuncs[j].name);
                checkTime(sorts[i].sort,
                          generatingFuncs[j].generate,
                          size, filename);
            }
        }
        printf("\n");
    }
}

void checkNComps(long long (*sortFunc )(int *, size_t),
                 void (*generateFunc )(int *, size_t),
                 size_t size, char *experimentName) {
    static size_t runCounter = 1;

    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);
    printf("Run #%zu| ", runCounter++);
    printf("Name : %s\n", experimentName);

    size_t nComps = sortFunc(innerBuffer, size);

    printf("Status: ");
    if (isOrdered(innerBuffer, size)) {
        printf("OK! nComps : %lld\n", nComps);

        char filename[256];
        sprintf(filename, "./data/%s.csv", experimentName);

        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf("FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %lld\n", size, nComps);
        fclose(f);
    } else {
        printf("Wrong!\n");

        outputArray_(innerBuffer, size);
        exit(1);
    }
}

void compsExperiment() {
    SortFunc sorts[] = {
            {selectionSort, "selectionSort"},
            {insertionSort, "insertionSort"},
            {bubbleSort,    "bubbleSort"},
            {combSort,      "combSort"},
            {shellSort,     "shellSort"},
            {digitSort,     "radixSort"},
    };
    const unsigned FUNCS_N = ARRAY_SIZE (sorts);

    GeneratingFunc generatingFuncs[] = {
            {generateRandomArray,      "random"},
            {generateOrderedArray,     "ordered"},
            {generateOrderedBackwards, "orderedBackwards"}
    };
    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

    for (size_t size = 10000; size <= 100000; size += 10000) {
        printf("------------------------------\n");
        printf(" Size : %d\n", size);
        for (int i = 0; i < FUNCS_N; i++) {
            for (int j = 0; j < CASES_N; j++) {
                static char filename[128];
                sprintf(filename, "%s_%s_comps",
                        sorts[i].name, generatingFuncs[j].name);
                checkNComps(sorts[i].sort,
                            generatingFuncs[j].generate,
                            size, filename);
            }
        }
        printf("\n");
    }
}

long long bubbleSort(int *a, size_t n) {
    long long nComps = 0;
    for (size_t i = 0; ++nComps && i < n - 1; i++) {
        for (size_t j = n - 1; ++nComps && j > i; j--) {
            if (++nComps && a[j - 1] > a[j])
                swap(&a[j - 1], &a[j], sizeof(int));
        }
    }

    return nComps;
}

//int getMinIndex(const int *a, size_t n) {
//    int minIndex = 0;
//    for (int i = 0; i < n; i++)
//        if (a[i] < a[minIndex])
//            minIndex = i;
//
//    return minIndex;
//}

long long selectionSort(int *a, size_t n) {
    long long nComps = 0;
    for (int i = 0; ++nComps && i < n - 1; i++) {
        int minPos = i;
        for (int j = i + 1; ++nComps && j < n; j++)
            if (++nComps && a[j] < a[minPos])
                minPos = j;
        swap(&a[i], &a[minPos], sizeof(int));
    }

    return nComps;
}

long long insertionSort(int *a, size_t n) {
    long long nComps = 0;
    for (int i = 1; ++nComps && i < n; i++) {
        int t = a[i];
        int j = i;
        while (++nComps && j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }

    return nComps;
}

long long combSort(int *a, size_t n) {
    long long nComps = 0;
    size_t step = n;
    int swapped = 1;
    while (++nComps && step > 1 || swapped) {
        if (++nComps && step > 1)
            step /= 1.24733;
        swapped = 0;
        for (size_t i = 0, j = i + step; ++nComps && j < n; i++, j++)
            if (++nComps && a[i] > a[j]) {
                swap(&a[i], &a[j], sizeof(int));
                swapped = 1;
            }
    }

    return nComps;
}

long long shellSort(int *a, size_t n) {
    long long nComps = 0;
    for (int step = n / 2; ++nComps && step > 0; step /= 2) {
        for (int i = step; ++nComps && i < n; i++) {
            for (int j = i - step; ++nComps && j >= 0 && a[j] > a[j + step]; j -= step) {
                swap(&a[j], &a[j + step], sizeof(int));
            }
        }
    }

    return nComps;
}

void getPrefSum(int *a, size_t n) {
    int prev = a[0];
    *a = 0;
    for (int i = 1; i < n; i++) {
        int t = a[i];
        a[i] = prev + a[i - 1];
        prev = t;
    }
}

long long digitSort(int *a, size_t n) {
    long long nComps = 0;
    int buffer[100000];
    size_t step = 8;
    int mask = 0b11111111;
    int currentByte;

    for (int byte = 0; ++nComps && byte < sizeof(int); byte++) {
        int value[UCHAR_MAX + 1] = {0};
        for (int i = 0; ++nComps && i < n; i++) {
            currentByte = (a[i] >> (byte * step)) & mask;
            value[currentByte]++;
        }
        getPrefSum(value, UCHAR_MAX + 1);

        for (int i = 0; ++nComps && i < n; i++) {
            currentByte = (a[i] >> (byte * step)) & mask;
            buffer[value[currentByte]++] = a[i];
        }
        memcpy(a, buffer, sizeof(int) * n);
    }

    return nComps;
}

