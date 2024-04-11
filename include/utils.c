#include "utils.h"

Heap* createHeap(int capacity,int is_encrypt) {
    Heap* heap = ( Heap* )malloc(sizeof( Heap));
    heap->capacity = capacity;
    heap->size = 0;
    if(is_encrypt == TRUE)
        heap->array = (eTPSS **)malloc(capacity * sizeof(eTPSS *));
    else
        heap->bnArr = (BIGNUM **) malloc(capacity * sizeof (BIGNUM *));
    // 对于每一个array又需要再次进行初始化内部节点
    for(int i = 0 ; i < capacity ; ++i ){
        if(is_encrypt == TRUE){
            heap->array[i] = (eTPSS *) malloc(sizeof (eTPSS));
            init_eTPSS(heap->array[i]);
        }else{
            heap->bnArr[i] = BN_CTX_get(CTX);
        }
    }
    heap->is_encrypt = is_encrypt;
    return heap;
}

void bubleDown(Heap* heap, int index) {
    int largest = index;
    int leftChild = 2*index+1;
    int rightChild = 2*index+2;
    int res = -2;
    while(leftChild < heap->size) {
        if(heap->is_encrypt == TRUE){
            et_Sub(&res,heap->array[leftChild],heap->array[largest]);
            if(leftChild < heap->size && res == 1 ) {
                largest = leftChild;
            }
            et_Sub(&res,heap->array[rightChild], heap->array[largest]);
            if(rightChild < heap->size &&  res == 1 ) {
                largest = rightChild;
            }
            if(largest != index) {
                eTPSS *temp = heap->array[index];
                heap->array[index] = heap->array[largest];
                heap->array[largest] = temp;
                index = largest;
            }else {
                break;
            }

        }else{
            res = BN_cmp(heap->bnArr[leftChild],heap->bnArr[largest]);
            if(leftChild < heap->size && res == -1 ) {
                largest = leftChild;
            }
            res = BN_cmp(heap->bnArr[rightChild],heap->bnArr[largest]);
            if(rightChild < heap->size &&  res == -1 ) {
                largest = rightChild;
            }
            if(largest != index) {
                BIGNUM *temp = heap->bnArr[index];
                heap->bnArr[index] = heap->bnArr[largest];
                heap->bnArr[largest] = temp;
                index = largest;
            }else {
                break;
            }
        }

        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;

    }

}

void heapify(Heap* heap) {
    for (int i = heap->size/2-1; i >= 0; i--) {
        bubleDown(heap,i);
    }
}

void bubleUp(Heap* heap, int index) {
    int temp = index;
    int parent = (index-1)/2;
    int res = -1;
    if(heap->is_encrypt == TRUE){
        et_Sub(&res,heap->array[parent], heap->array[temp]);
        while(res == 0 && parent >= 0) {
            eTPSS * tempNode = heap->array[temp];
            heap->array[temp] = heap->array[parent];
            heap->array[parent] = tempNode;
            temp = parent;
            parent = (temp-1)/2;
            if(temp == parent)
                break;
            et_Sub(&res,heap->array[parent], heap->array[temp]);
        }
    }else{
        res = BN_cmp(heap->bnArr[parent], heap->bnArr[temp]);
        while(res == 1 && parent >= 0) {
            BIGNUM * tempNode = heap->bnArr[temp];
            heap->bnArr[temp] = heap->bnArr[parent];
            heap->bnArr[parent] = tempNode;
            temp = parent;
            parent = (temp-1)/2;
            if(temp == parent)
                break;
            res = BN_cmp(heap->bnArr[parent], heap->bnArr[temp]);
        }
    }
}

void insert(Heap* heap, void * key) {

    if(heap->size < heap->capacity) {
        heap->size++;
        if(heap->is_encrypt == TRUE){
            // 直接引用
            et_Copy(heap->array[heap->size-1],key);
        }else{
            BN_copy(heap->bnArr[heap->size -1],key);
        }
        bubleUp(heap,heap->size-1);
    }
}

void deleteMax(Heap* heap) {
    void * temp;
    if(heap->size >= 1) {
        if(heap->is_encrypt == TRUE){
            temp = heap->array[0];
            heap->array[0] = heap->array[heap->size-1];
            heap->array[heap->size-1] = temp;
            heap->size--;
            bubleDown(heap,0);
        }else{
            temp = heap->bnArr[0];
            heap->bnArr[0] = heap->bnArr[heap->size-1];
            heap->bnArr[heap->size-1] = temp;
            heap->size--;
            bubleDown(heap,0);
        }
    }
}

void heapSort(Heap* heap) {
    int temp = heap->size;

    for (int i = 0; i <temp ; ++i) {
        deleteMax(heap);
    }
    heap->size = temp;
}
