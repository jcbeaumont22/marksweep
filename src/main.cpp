#include <stdio.h>
#include <gc.h>
#include <heap.h>

int main() {
    Heap heap;
    GarbageCollector gc;

    void* ptr1 = gc.malloc(100, &heap);
    void* ptr2 = gc.malloc(100, &heap);
    void* ptr3 = gc.malloc(100, &heap);
    void* ptr4 = gc.malloc(100, &heap);

    
}