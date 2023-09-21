#include "arena.hpp"

#include <stdlib.h>

using namespace memory;

Arena::Arena(Allocator *allocator, size_t initial_size) {
    data = (size_t *)malloc(initial_size);
    reserved = initial_size;
    this->allocator = allocator;
}

Arena::~Arena() { ::free(data); }

void *Arena::malloc(size_t bytes) {
    void *ptr = (void *)(data + allocator->malloc(bytes));
#if DEBUG
    // Check if alloc size is within arena size
    assert(ptr + bytes <= data + initial_size);
#endif
    return ptr;
}

void Arena::free(void *ptr, size_t bytes) { allocator->free(ptr); }

unsigned int StackAllocator::malloc(size_t bytes) {
    unsigned int offset = top + bytes;
    top += bytes;
    return offset;
}

unsigned int BuddyAllocator::malloc(size_t bytes) {
    unsigned int offset;

    return offset;
}
