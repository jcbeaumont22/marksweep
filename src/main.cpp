#include <stdio.h>
#include <gc.h>
#include <heap.h>

int main() {
    Heap heap;
    GarbageCollector gc;

    void* ptr1 = gc.malloc(4, &heap);
    cout << "Free space: " << heap.available_memory() << endl;

    void* ptr2 = gc.malloc(100, &heap);
    cout << "Free space: " << heap.available_memory() << endl;

    gc.delete_reference(ptr1);
    gc.add_nested_reference(ptr2, ptr1);
    gc.ms_collect(&heap);
    cout << "Free space: " << heap.available_memory() << endl;

    gc.delete_reference(ptr2);
    gc.ms_collect(&heap);
    cout << "Free space: " << heap.available_memory() << endl;
    
}