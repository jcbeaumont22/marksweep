#include <assert.h>
#include <gc.h>
#include <heap.h>
#include <iostream>

/**
 * Allocates memory from the heap and registers it with the garbage collector.
 *
 * @param size The number of bytes to allocate.
 * @param heap Pointer to the heap object used for allocation.
 * @return A pointer to the allocated memory block, or NULL if allocation fails.
 */
void* GarbageCollector::malloc(size_t size, Heap *heap) {
    void *ptr = heap->my_malloc(size);

    if (ptr) {
        allocation allocation = {size, false};
        allocations[ptr] = allocation;
    } else {
        cerr << "Memory allocation failed!" << endl;
        return NULL;
    }

    return ptr;
}

/**
 * Recursively marks reachable memory blocks by scanning for pointers within the given block.
 *
 * @param ptr Pointer to the memory block to scan.
 */
void GarbageCollector::walk_block(void* ptr) {
    if (!ptr) return;

    allocation *alloc = ((allocation *)ptr) - 1;
    size_t size = alloc->size;

    if (alloc->marked) return;
    alloc->marked = true;

    uintptr_t* scan = reinterpret_cast<uintptr_t*>(ptr);
    uintptr_t* end = reinterpret_cast<uintptr_t*>(reinterpret_cast<char*>(ptr) + size);

    while (scan < end) {
        void* maybe_ptr = reinterpret_cast<void*>(*scan);
        if (allocations.find(maybe_ptr) != allocations.end()) {
            allocation& found_block = allocations[maybe_ptr];
            if (!found_block.marked) {
                found_block.marked = true;
                walk_block(maybe_ptr);
            }
        }
        ++scan;
    }
}

/**
 * Initiates the mark phase of the garbage collection process.
 * Marks all reachable memory blocks starting from the root set.
 */
void GarbageCollector::mark() {
    cout << "Beginning marking phase..." << endl;

    // Clear all markings
    for (auto alloc = allocations.begin(); alloc != allocations.end(); alloc++) {
        alloc->second.marked = false;
    }

    // Traverse the root set to identify reachable objects
    for (void* root : root_set) {
        PointerMap::iterator alloc = allocations.find(root);
        if (alloc != allocations.end()) {
            walk_block(alloc->first); // Traverse the block's memory to identify additional references
        }
    }
}

/**
 * Initiates the sweep phase of the garbage collection process.
 * Frees all memory blocks not marked as reachable.
 *
 * @param heap Pointer to the heap object used for deallocation.
 */
void GarbageCollector::sweep(Heap *heap) {
    cout << "Beginning sweeping phase..." << endl;
    
    // Free all allocations not marked as found
    if (allocations.empty()) {
        heap->reset();
    }
    for (auto alloc = allocations.begin(); alloc != allocations.end(); ) {
        if (!alloc->second.marked) {
            heap->my_free(alloc->first);
            alloc = allocations.erase(alloc);
        } else {
            alloc++;
        }
    }
}

int GarbageCollector::add_reference(void *ptr) {

}

int GarbageCollector::delete_reference(void *ptr) {

}

void GarbageCollector::ms_collect(Heap *heap) {
    mark();
    sweep(heap);
}

void GarbageCollector::rc_collect(Heap *heap) {

}
