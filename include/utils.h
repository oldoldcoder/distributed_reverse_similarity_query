#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include "openssl//bn.h"

/*---------------定义常量------------*/
#define SUCCESS 2147483617
#define ERROR 2147483629
#define TRUE 1
#define FALSE 0
#define RESULT int

/*--------------------定义一个堆--------------------*/
typedef struct Heap {
    eTPSS **array;
    BIGNUM ** bnArr;
    int is_encrypt;
    int size;
    int capacity;
} Heap;

Heap* createHeap(int capacity,int is_encrypt);
void bubleDown(Heap* heap, int index);
void heapify(Heap* heap);
void bubleUp(Heap* heap, int index);
void insert(Heap* heap, void * key);
void deleteMax(Heap* heap);
void heapSort(Heap* heap);
// 清空heap
void heapClear(Heap * heap);
// 弹出前几个值
void heap_PopK_max_Val(Heap * heap,int k_max,eTPSS ** arr);
// 释放heap的内存
void heap_free(Heap * h,int y_len);

#endif // UTILS_H