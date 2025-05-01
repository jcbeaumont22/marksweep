#include <stdio.h>
#include <gc.h>
#include <heap.h>

int main() {
    Heap heap;
    GarbageCollector gc;

    void* ptr1 = gc.malloc(100, &heap);
    cout << "Free space: " << heap.available_memory() << endl;
    gc.ms_collect(&heap);
    cout << "Free space: " << heap.available_memory() << endl;

    void* ptr2 = gc.malloc(100, &heap);
    cout << "Free space: " << heap.available_memory() << endl;
    gc.ms_collect(&heap);
    cout << "Free space: " << heap.available_memory() << endl;

    void* ptr3 = gc.malloc(100, &heap);
    cout << "Free space: " << heap.available_memory() << endl;
    gc.ms_collect(&heap);
    cout << "Free space: " << heap.available_memory() << endl;

    gc.delete_reference(ptr2);
    gc.ms_collect(&heap);
    cout << "Free space: " << heap.available_memory() << endl;

    gc.delete_reference(ptr1);
    gc.ms_collect(&heap);
    cout << "Free space: " << heap.available_memory() << endl;

    gc.delete_reference(ptr3);
    gc.ms_collect(&heap);
    cout << "Free space: " << heap.available_memory() << endl;

    
}