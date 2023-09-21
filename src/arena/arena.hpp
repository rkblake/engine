#pragma once

#include <cstddef>

namespace memory {

class Allocator {
protected:
    size_t size;

public:
    Allocator(size_t size) {}
    ~Allocator() {}
    virtual unsigned int malloc(size_t bytes) = 0;
    // virtual unsigned int calloc(size_t bytes) = 0;
    virtual void free(void *ptr) = 0;
    // virtual void clear() = 0;
};

class StackAllocator : public Allocator {
private:
    size_t top;

public:
    unsigned int malloc(size_t bytes);
    // unsigned int calloc(size_t bytes);
    // void free(void *ptr);
    // void clear();
};

class BuddyAllocator : public Allocator {
public:
    unsigned int malloc(size_t bytes);
    // unsigned int calloc(size_t bytes);
    // void free(void *ptr);
    // void clear();
};

class Arena {
private:
    size_t *data;
    size_t reserved;
    Allocator *allocator;

public:
    Arena(Allocator *allocator, size_t initial_size);
    ~Arena();

    void *malloc(size_t bytes);
    // void *calloc(size_t bytes);
    void free(void *ptr, size_t bytes);
    // void clear();
};

} // namespace memory
