#include "arena.hpp"

#include <stdlib.h>

using namespace memory;

Arena::Arena(Allocator *allocator, size_t initial_size) {
    data = malloc(initial_size);
    reserved = initial_size;
    this->allocator = allocator;
}

Arena::~Arena() { free(data); }

void *Arena::alloc(size_t bytes) { return allocator->alloc(bytes); }

void Arena::free(void *ptr) {}

void *StackAllocator::alloc(size_t bytes) {}
void StackAllocator::free(void *ptr) {}
